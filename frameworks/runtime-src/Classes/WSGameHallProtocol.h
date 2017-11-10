#ifndef __WSGAMEHALL_PROTOCOL_H__
#define __WSGAMEHALL_PROTOCOL_H__

#include "string"
#include "cocos2d.h"


class  WSGameHallProtocol
{
public:
	
	virtual void onGameHallPushPayResult(std::string result) = 0;

	virtual void onGameHallPushUserInfo(std::string userInfo) = 0;

	virtual void onGameHallPushNotification(std::string notification) = 0;

	virtual void onGameHallPushLocationChanged(std::string location) = 0;

};

#endif  // __WSGAMEHALL_PROTOCOL_H__