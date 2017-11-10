#include "WSGameHallUtils.h"

USING_NS_CC;
using namespace std;

WSGameHallUtils* WSGameHallUtils::instance = nullptr;

WSGameHallUtils::WSGameHallUtils():
hallListener(nullptr)
{
}

WSGameHallUtils::~WSGameHallUtils()
{
	instance = nullptr;
}

WSGameHallUtils* WSGameHallUtils::getInstance()
{
	if (!instance)
	{
		instance = new WSGameHallUtils;
	}
	return instance;
}

string WSGameHallUtils::doQueryWesaiUid()
{
	log("WSGameHallUtils::doQueryWesaiUid");
	string uid = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "doQueryWesaiUid", "()Ljava/lang/String;");
	if (isHave)
	{
		jstring jstr = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		uid = JniHelper::jstring2string(jstr);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(jstr);
	}
	else
	{
		CCLOG("java getUserId method is not found");
	}
#endif
	return uid;
}


std::string WSGameHallUtils::doQueryGameId()
{
	log("WSGameHallUtils::doQueryGameId");
	string gameId = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "doQueryGameId", "()Ljava/lang/String;");
	if (isHave)
	{
		jstring jstr = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		gameId = JniHelper::jstring2string(jstr);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(jstr);
	}
	else
	{
		CCLOG("java getUserId method is not found");
	}
#endif
	return gameId;
}


void WSGameHallUtils::doQueryUserInfo()
{	
	log("WSGameHallUtils::queryUserInfo");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "doQueryUserInfo", "()V");
	if (isHave)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		minfo.env->DeleteLocalRef(minfo.classID);
	}
	else
	{
		CCLOG("java queryUserInfo method is not found");
	}
#endif
}

void WSGameHallUtils::doPay(std::string orderId, std::string cost, std::string desc, std::string extralInfo)
{
	log("WSGameHallUtils doPay");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "doPay", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jOrder = minfo.env->NewStringUTF(orderId.c_str()); 
		jstring jCost = minfo.env->NewStringUTF(cost.c_str());
		jstring jDesc = minfo.env->NewStringUTF(desc.c_str()); 
		jstring jExtral = minfo.env->NewStringUTF(extralInfo.c_str()); 
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jOrder, jCost, jDesc, jExtral);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(jOrder);  //释放String类
		minfo.env->DeleteLocalRef(jCost);  //释放String类
		minfo.env->DeleteLocalRef(jDesc);  //释放String类
		minfo.env->DeleteLocalRef(jExtral);  //释放String类
	}
	else
	{
		log("java doPay method is not found");
	}
#endif
}

void WSGameHallUtils::doShare(string title, string content, string iconUrl, string h5Url)
{
	log("WSGameHallUtils doShare");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "doShareRichText", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring jTitle = minfo.env->NewStringUTF(title.c_str()); 
		jstring jContent = minfo.env->NewStringUTF(content.c_str());
		jstring jIconUrl = minfo.env->NewStringUTF(iconUrl.c_str()); 
		jstring jH5Url = minfo.env->NewStringUTF(h5Url.c_str()); 
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jTitle, jContent, jIconUrl, jH5Url);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(jTitle);  //释放String类
		minfo.env->DeleteLocalRef(jContent);  //释放String类
		minfo.env->DeleteLocalRef(jIconUrl);  //释放String类
		minfo.env->DeleteLocalRef(jH5Url);  //释放String类
	}
	else
	{
		log("java doShare method is not found");
	}
#endif
}


std::string WSGameHallUtils::getPushStr()
{
	log("WSGameHallUtils getPushStr");
	std::string pushStr = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "getPushStr", "()Ljava/lang/String;");
	if (isHave)
	{
		jstring jstr = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		pushStr = JniHelper::jstring2string(jstr);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(jstr);
	}
	else
	{
		log("java getPushStr method is not found");
	}
#endif
	return pushStr;
}

std::string WSGameHallUtils::getLocationStr()
{
	log("WSGameHallUtils getLocationStr");
	std::string locationStr = "";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "getLocationStr", "()Ljava/lang/String;");
	if (isHave)
	{
		jstring jstr = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		locationStr = JniHelper::jstring2string(jstr);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(jstr);
	}
	else
	{
		log("java getLocationStr method is not found");
	}
#endif
	return locationStr;
}

void WSGameHallUtils::postJavaEvent(std::string event, std::string param)
{
	log("WSGameHallUtils PostJavaEvent event = %s, param = %s", event.c_str(), param.c_str());
	 Director::getInstance()->getScheduler()->performFunctionInCocosThread([event, param](){
		auto scene = Director::getInstance()->getRunningScene();
		auto hallListener = WSGameHallUtils::getInstance()->getHallEventListener();
		if (event == "HallPushPayResult")
		{
			if (hallListener)
			{
				hallListener->onGameHallPushPayResult(param);
			}	
		}
		else if (event == "HallPushUserInfo")
		{
			if (hallListener)
			{
				hallListener->onGameHallPushUserInfo(param);
			}
		}
		else if (event == "HallPushLocationChanged")
		{
			if (hallListener)
			{
				hallListener->onGameHallPushLocationChanged(param);
			}
		}
		else if (event == "HallPushNotification")
		{
			if (hallListener)
			{
				hallListener->onGameHallPushNotification(param);
			}
		}
// 		else if (event == "HallPushUserId")
// 		{
// 			int lastPos = 0;
// 			vector<string> vec_str;
// 			while (true)
// 			{
// 				int pos = param.find(",", lastPos);
// 				if (pos != std::string::npos)
// 				{
// 					vec_str.push_back(param.substr(lastPos, pos - lastPos));
// 					lastPos = pos+1;
// 				}
// 				else
// 				{
// 					if (param.substr(lastPos) != "")
// 					{
// 						vec_str.push_back(param.substr(lastPos));
// 					}
// 					break;
// 				}
// 			}
// 			assert(vec_str.size() >= 2);
// 			WSGameHallInfo::getInstance()->setUserId(vec_str[0]);
// 			WSGameHallInfo::getInstance()->setGameId(vec_str[1]);
// 			if (hallListener)
// 			{
// 				hallListener->onGameHallPushGameBaseInfo(param);
// 			}
// 		}
		//for more event		
    });
}

void WSGameHallUtils::registHallEventListener(WSGameHallProtocol* listener)
{
	hallListener = listener;
}

WSGameHallProtocol* WSGameHallUtils::getHallEventListener()
{
	return hallListener;
}







