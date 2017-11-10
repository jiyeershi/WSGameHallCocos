#ifndef __WSGAMEHALL_PROTOCOL_H__
#define __WSGAMEHALL_PROTOCOL_H__

#include "string"
#include "cocos2d.h"


class  WSGameHallProtocol
{
public:
	
	virtual void onGameHallPushPayResult(std::string result) = 0;

	virtual void onGameHallPushUserInfo(std::string userInfo) = 0;

	virtual void onGameHallPushGameBaseInfo(std::string gameBaseInfo) = 0;

	// static void onEndDirector(){ cocos2d::Director::getInstance()->end(); };
};

#endif  // __WSGAMEHALL_PROTOCOL_H__