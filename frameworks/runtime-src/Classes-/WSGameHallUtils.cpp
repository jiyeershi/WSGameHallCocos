#include "WSGameHallUtils.h"
#include "WSGameHallInfo.h"

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

void WSGameHallUtils::doQueryUserInfo(std::string uid)
{	
	string str = uid;
	log("WSGameHallUtils::queryUserInfo Uid = %s", str.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	jstring str_arg = NULL;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "queryUserInfo", "(Ljava/lang/String;)V");
	if (isHave)
	{
		str_arg = minfo.env->NewStringUTF(str.c_str()); 
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, str_arg);
		minfo.env->DeleteLocalRef(minfo.classID);
		minfo.env->DeleteLocalRef(str_arg);  
	}
	else
	{
		CCLOG("java queryUserInfo method is not found");
	}
#endif
}

void WSGameHallUtils::doPay()
{
	log("WSGameHallUtils doPay");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/wesai/mygame/Utils", "doPay", "()V");
	if (isHave)
	{
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		minfo.env->DeleteLocalRef(minfo.classID);
	}
	else
	{
		log("java doPay method is not found");
	}
#endif
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
		else if (event == "HallPushUserId")
		{
			int lastPos = 0;
			vector<string> vec_str;
			while (true)
			{
				int pos = param.find(",", lastPos);
				if (pos != std::string::npos)
				{
					vec_str.push_back(param.substr(lastPos, pos - lastPos));
					lastPos = pos+1;
				}
				else
				{
					if (param.substr(lastPos) != "")
					{
						vec_str.push_back(param.substr(lastPos));
					}
					break;
				}
			}
			assert(vec_str.size() >= 2);
			WSGameHallInfo::getInstance()->setUserId(vec_str[0]);
			WSGameHallInfo::getInstance()->setGameId(vec_str[1]);
			if (hallListener)
			{
				hallListener->onGameHallPushGameBaseInfo(param);
			}
		}
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



