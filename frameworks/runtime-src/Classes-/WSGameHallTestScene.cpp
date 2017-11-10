#include "WSGameHallTestScene.h"
#include "WSGameHallInfo.h"
#include "WSGameHallUtils.h"
#include "MD5.h"

USING_NS_CC;
using namespace cocos2d::network;

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	Label* lab = Label::create("UserInfo", "fonts/arial.ttf", 40);
	auto userInfoMenu = MenuItemLabel::create(lab, CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
	userInfoMenu->setPosition(Vec2(0, 320));
	userInfoMenu->setTag(10);
	userInfoMenu->setAnchorPoint(Vec2(0, 0));

	Label* lab1 = Label::create("Charge", "fonts/arial.ttf", 40);
	auto chargeMenu = MenuItemLabel::create(lab1, CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
	chargeMenu->setTag(11);
	chargeMenu->setPosition(Vec2(0, 420));
	chargeMenu->setAnchorPoint(Vec2(0, 0));

	Label* lab2 = Label::create("AddAchivementReq", "fonts/arial.ttf", 40);
	auto AchivementMenu = MenuItemLabel::create(lab2, CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
	AchivementMenu->setTag(12);
	AchivementMenu->setPosition(Vec2(0, 520));
	AchivementMenu->setAnchorPoint(Vec2(0, 0));

	Label* lab3 = Label::create("end", "fonts/arial.ttf", 40);
	auto end = MenuItemLabel::create(lab3, CC_CALLBACK_1(WSGameHallTestScene::buttonClickCallback, this));
	end->setTag(13);
	end->setPosition(Vec2(0, 620));
	end->setAnchorPoint(Vec2(0, 0));

	auto menu = Menu::create(userInfoMenu, chargeMenu, AchivementMenu, end, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	WSGameHallUtils::getInstance()->registHallEventListener(this);

    return true;
}

void WSGameHallTestScene::buttonClickCallback(Ref* sender)
{
	int tag = ((Node*)sender)->getTag();
	if (tag == 10)
	{
		std::string uid =  WSGameHallInfo::getInstance()->getUserId();
		WSGameHallUtils::getInstance()->doQueryUserInfo(uid);
	}
	else if (tag == 11)
	{
		WSGameHallUtils::getInstance()->doPay();
	}
	else if (tag == 12)
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl("http://game.test.api.wesai.com/intra/virtualMedal");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(WSGameHallTestScene::onHttpRequestCompleted, this));

		// write the post data
		char buff[256] = { 0 };
		//sprintf(buff, "app_key=9dbb474c-76f6-47e1-8f0f-0887de4ac205&game_id=%s&medal_value=1&timestamp=20110616132330&user_id=%s", WSGameHallInfo::getInstance()->getGameId().c_str(), WSGameHallInfo::getInstance()->getUserId().c_str());
		sprintf(buff, "app_key=9dbb474c-76f6-47e1-8f0f-0887de4ac205&game_id=62217d7ce7704f558a5a3246a418cf00&medal_value=1&timestamp=20110616132330&user_id=69db3e057a202f7be58857cc8aef3c4f");
		log("sign buff = %s", buff);
		Md5Encode encode_obj;
		std::string encodeStr = encode_obj.Encode(buff);
		log("sign ret = %s", encodeStr.c_str());
		char sendBuff[512] = { 0 };
		//sprintf(sendBuff, "app_id=8a828247589537960158a9bbb876000d&user_id=%s&game_id=%s&medal_value=1&timestamp=20110616132330&sign=%s", WSGameHallInfo::getInstance()->getUserId().c_str(), WSGameHallInfo::getInstance()->getGameId().c_str(), encodeStr.c_str());
		sprintf(sendBuff, "app_id=8a828247589537960158a9bbb876000d&user_id=69db3e057a202f7be58857cc8aef3c4f&game_id=62217d7ce7704f558a5a3246a418cf00&medal_value=1&timestamp=20110616132330&sign=%s", encodeStr.c_str());
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

    Label* lab = Label::create(data, "fonts/arial.ttf", 40);
    this->addChild(lab);
    lab->setAnchorPoint(Vec2(0, 0));
    lab->setPosition(Vec2(350, 520));

	if (response->getHttpRequest()->getReferenceCount() != 2)
	{
		log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
	}
}

void WSGameHallTestScene::onGameHallPushPayResult(std::string result)
{
	Label* lab1 = Label::create(result, "fonts/arial.ttf", 40);
	this->addChild(lab1);
	lab1->setPosition(Vec2(320, 420));
	lab1->setAnchorPoint(Vec2(0, 0));
}

void WSGameHallTestScene::onGameHallPushUserInfo(std::string userInfo)
{
	Label* lab = Label::create(userInfo, "fonts/arial.ttf", 40);
	this->addChild(lab);
	lab->setAnchorPoint(Vec2(0, 0));
	lab->setPosition(Vec2(320, 320));
}

void WSGameHallTestScene::onGameHallPushGameBaseInfo(std::string gameBaseInfo)
{

}
