#include <string>
#include <memory>
#include "cocos2d.h"
#include "com_wesai_mygame_Utils.h"
#include "../../Classes/WSGameHallUtils.h"
#include "platform/android/jni/JniHelper.h"
#include "AppDelegate.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

USING_NS_CC;
using namespace std;
void JNICALL Java_com_wesai_mygame_Utils_postMsg2Cocos
  (JNIEnv *, jclass, jstring jeventname, jstring jdata)
  {
	string eventname 	= JniHelper::jstring2string(jeventname);
	string data 		= JniHelper::jstring2string(jdata);
	WSGameHallUtils::getInstance()->postJavaEvent(eventname,data);
  }