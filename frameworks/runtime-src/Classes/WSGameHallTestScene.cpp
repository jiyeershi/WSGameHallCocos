#include "WSGameHallTestScene.h"
#include "WSGameHallUtils.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
extern "C" {
#include "lua.h"
}
USING_NS_CC;
using namespace cocos2d::network;

std::string apiArr[] = {
	"http://game.test.api.wesai.com/intra/virtualMedal",
	"http://game-pre.api.wesai.com/intra/virtualMeda",
	"http://game.api.wesai.com/intra/virtualMedal",
};


WSGameHallTestScene::WSGameHallTestScene() :
root(nullptr)
{

}

Scene* WSGameHallTestScene::scene()
{
     return WSGameHallTestScene::create();
}

bool WSGameHallTestScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	if (!(LuaEngine::getInstance()->executeScriptFile1("tempConfig.lua")))
	{
		lua_State* pL = LuaEngine::getInstance()->getLuaStack()->getLuaState();
		//return false;
		lua_getglobal(pL, "GETPOS");
		lua_getglobal(pL, "GETPUSH");
		lua_getglobal(pL, "ADD_ACHIVIMENT");
		lua_getglobal(pL, "PAY_RESULT");
		lua_getglobal(pL, "GET_USERINFO");
		lua_getglobal(pL, "NOTIFICATION");
		lua_getglobal(pL, "POS_CHANGED");
		this->posStr = lua_tostring(pL, -1);
		this->pushStr = lua_tostring(pL, -2);
		this->addAchivenmentStr = lua_tostring(pL, -3);
		this->payResultStr = lua_tostring(pL, -4);
		this->userInfoStr = lua_tostring(pL, -5);
		this->notificationStr = lua_tostring(pL, -6);
		this->posChangedStr = lua_tostring(pL, -7);
		lua_settop(pL, 0);
	}

	//auto node = cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("MainScene.csb");
	auto node = CSLoader::createNode("MainScene.csb");
	this->addChild(node);
	this->root = node;

	auto labApi = node->getChildByName("lab_api");
	auto labEventResult = node->getChildByName("lab_event");
	((ui::Text*)labApi)->setString(apiArr[0]);
	auto labLocation = node->getChildByName("lab_location");

	auto* btn_changeApi = node->getChildByName("btn_changeApi");
	int count = 0;
	((ui::Button*)btn_changeApi)->addClickEventListener([this, labApi, count](Ref*)mutable{
		((ui::Text*)labApi)->setString(apiArr[count++ % 3]);
	});

	auto* btn_charge = node->getChildByName("btn_charge");
	((ui::Button*)btn_charge)->addClickEventListener([this](Ref*){
		log("click doPay 1");
		struct timeval tv_begin;
		static int orderCount = 0;
		(++orderCount) %= 1000000;//每毫秒设定上限1000000订单
		int error = gettimeofday(&tv_begin,NULL);
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t = localtime(&tt);
		std::stringstream ss;                            
		ss << tt;
		ss << tv_begin.tv_usec / 1000;
		char temp[8] = { 0 };
		sprintf_s(temp, "%07d", orderCount);
		ss << temp;
		std::string ret = ss.str();
		WSGameHallUtils::getInstance()->doPay(ret, "10", "cocos测试购买", "");
		log("click doPay 2");
	});

	auto* btn_quary = node->getChildByName("btn_quary");
	((ui::Button*)btn_quary)->addClickEventListener([this](Ref*){
		log("click btn_quary 1");
		WSGameHallUtils::getInstance()->doQueryUserInfo();
		log("click btn_quary 2");
	});

	auto* btn_addAchivement = node->getChildByName("btn_addAchivement");
	((ui::Button*)btn_addAchivement)->addClickEventListener([this, count](Ref*){
		log("click btn_addAchivement ");
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl(apiArr[count]);
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(WSGameHallTestScene::onHttpRequestCompleted, this));
		log("request url = %s", apiArr[count].c_str());

		// write the post data
		char sendBuff[256] = { 0 };
		sprintf(sendBuff, "user_id=%s&game_id=%s&medal_value=1", WSGameHallUtils::getInstance()->doQueryWesaiUid().c_str(), WSGameHallUtils::getInstance()->doQueryGameId().c_str());
		log("send data: %s", sendBuff);
		request->setRequestData(sendBuff, strlen(sendBuff));
		request->setTag("POST test");
		HttpClient::getInstance()->send(request);
		request->release();
	});

	auto* btn_share = node->getChildByName("btn_share");
	((ui::Button*)btn_share)->addClickEventListener([this](Ref*){
		log("click btn_share 1");
		WSGameHallUtils::getInstance()->doShare("cocos2dx share", "this is test message!", "https://static.wesai.com/ticketv2-product_static/pc/img/v2/logov2.png?v=819c55576907f5d888b19dce8b33326d", "https://www.wesai.com/");
		log("click btn_share 2");
	});

	auto* btn_getLocation = node->getChildByName("btn_getLocation");
	((ui::Button*)btn_getLocation)->addClickEventListener([this, labLocation](Ref*){
		std::string temp = this->posStr;
		std::string location = WSGameHallUtils::getInstance()->getLocationStr();
		log("click btn_getLocation 1");
		if (location.compare("") == 0)
		{
			location = "null";
		}
		
		temp = temp + location;
		((ui::Text*)labLocation)->setString(temp);
		log("click btn_getLocation 2");
	});

	auto* btn_push = node->getChildByName("btn_push");
	((ui::Button*)btn_push)->addClickEventListener([this, labEventResult](Ref*){
		log("click btn_push 1");
		std::string temp = this->pushStr;
		std::string push = WSGameHallUtils::getInstance()->getPushStr();
		if (push.compare("") == 0)
		{
			push = "null";
		}
		temp = temp + push;
		((ui::Text*)labEventResult)->setString(temp);
		log("click btn_push 2");
	});

	auto* btn_quit = node->getChildByName("btn_quit");
	((ui::Button*)btn_quit)->addClickEventListener([this](Ref*){
		log("click end app");
		Director::getInstance()->end();
		log("click end app 2");
	});


//     auto visibleSize = Director::getInstance()->getVisibleSize();
//     auto origin = Director::getInstance()->getVisibleOrigin();
// 

// 	auto userInfoMenu = MenuItemImage::create("userinfo.png", "userinfo.png", "userinfo.png", CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
// 	userInfoMenu->setPosition(Vec2(0, 50));
// 	userInfoMenu->setTag(10);
// 	userInfoMenu->setAnchorPoint(Vec2(0, 0));
// 
// 
// 	auto chargeMenu = MenuItemImage::create("charge.png", "charge.png", "charge.png", CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
// 	chargeMenu->setTag(11);
// 	chargeMenu->setPosition(Vec2(0, 200));
// 	chargeMenu->setAnchorPoint(Vec2(0, 0));
// 
// 
// 	auto AchivementMenu = MenuItemImage::create("achivement.png", "achivement.png", "achivement.png", CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
// 	AchivementMenu->setTag(12);
// 	AchivementMenu->setPosition(Vec2(0, 350));
// 	AchivementMenu->setAnchorPoint(Vec2(0, 0));
// 
// 	auto end = MenuItemImage::create("quit.png", "quit.png", "quit.png", CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
// 	end->setTag(13);
// 	end->setPosition(Vec2(0, 500));
// 	end->setAnchorPoint(Vec2(0, 0));
// 
// 	auto menu = Menu::create(userInfoMenu, chargeMenu, AchivementMenu, end,  nullptr);
//     menu->setPosition(Vec2::ZERO);
//     this->addChild(menu, 1);


// 	auto testLab = Label::createWithTTF("&#x8F6C;&#x6362;&#x5DE5;&#x5177","FZZYJT.TTF",40);
// 	root->addChild(testLab);
// 	testLab->setPosition(300, 300);

	this->lab = Label::createWithTTF(" ", "fonts/arial.ttf", 35, Size(700, 600));
	this->addChild(this->lab);
	this->lab->setPosition(Vec2(240,0));
	// 	root->addChild(testLab);
	// 	testLab->setPosition(300, 300);

 	WSGameHallUtils::getInstance()->registHallEventListener(this);

    return true;
}

void WSGameHallTestScene::buttonClickCallback(Ref* sender)
{
	Size size = Director::getInstance()->getWinSize();
	log("winsize w = %f , h = %f", size.width, size.height);
	int tag = ((Node*)sender)->getTag();
	if (tag == 10)
	{
		WSGameHallUtils::getInstance()->doQueryUserInfo();
	}
	else if (tag == 11)
	{
		//WSGameHallUtils::getInstance()->doPay();
	}
	else if (tag == 12)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		//pub
		//std::string strUrl = "http://game.api.wesai.com/intra/virtualMedal";
		//pre
		// std::string strUrl = "http://game-pre.api.wesai.com/intra/virtualMedal";
		//test
		std::string strUrl = "http://game.test.api.wesai.com/intra/virtualMedal";
		request->setUrl(strUrl);
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(WSGameHallTestScene::onHttpRequestCompleted, this));
		log("request url = %s", strUrl.c_str());

		// write the post data
		char sendBuff[256] = { 0 };
		sprintf(sendBuff, "user_id=%s&game_id=%s&medal_value=1", WSGameHallUtils::getInstance()->doQueryWesaiUid().c_str(), WSGameHallUtils::getInstance()->doQueryGameId().c_str());
		log("send data: %s", sendBuff);
		request->setRequestData(sendBuff, strlen(sendBuff));
		request->setTag("POST test");
		HttpClient::getInstance()->send(request);
		request->release();
	}
	else if (tag == 13)
	{
		log("click end app");
		Director::getInstance()->end();
		log("click end app 2");
	}
}


void WSGameHallTestScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %ld", statusCode);
	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	log("Http Test, dump data: ");
    std::string data = "";
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
        data += (*buffer)[i];
	}
    log("%s", data.c_str());
	log("\n");

	std::string totalData = this->addAchivenmentStr + data;
	auto labEventResult = this->root->getChildByName("lab_event");
	((ui::Text*)labEventResult)->setString(totalData);

	//((Label*)lab)->setString(data);
	if (response->getHttpRequest()->getReferenceCount() != 2)
	{
		log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
	}
}

void WSGameHallTestScene::onGameHallPushPayResult(std::string result)
{
	std::string temp = this->payResultStr + result;
	auto labEventResult = this->root->getChildByName("lab_event");
	((ui::Text*)labEventResult)->setString(temp);
	//((Label*)lab)->setString(result);
}

void WSGameHallTestScene::onGameHallPushUserInfo(std::string userInfo)
{
	std::string temp = userInfo;
	if (temp.compare("") == 0)
	{
		temp = "null";
	}
	temp = this->userInfoStr + temp;
	auto labEventResult = this->root->getChildByName("lab_event");
	((ui::Text*)labEventResult)->setString(temp);
	//((Label*)lab)->setString(userInfo);
}

void WSGameHallTestScene::onGameHallPushNotification(std::string notification)
{
	std::string temp = notification;
	if (temp.compare("") == 0)
	{
		temp = "null";
	}
	temp = this->notificationStr + temp;
	auto labEventResult = this->root->getChildByName("lab_event");
	((ui::Text*)labEventResult)->setString(temp);
}

void WSGameHallTestScene::onGameHallPushLocationChanged(std::string location)
{
	std::string temp = this->posChangedStr + location;
	auto labLocation = this->root->getChildByName("lab_location");
	((ui::Text*)labLocation)->setString(temp);
}
