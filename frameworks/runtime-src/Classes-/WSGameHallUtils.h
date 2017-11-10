#ifndef __WSGAMEHALL_UTILS_H__
#define __WSGAMEHALL_UTILS_H__

#include "string"
#include "WSGameHallProtocol.h"

class  WSGameHallUtils
{
public:
	WSGameHallUtils();

	virtual ~WSGameHallUtils();

	static WSGameHallUtils* getInstance();

// 	void login();

// 	void share();

	void doQueryUserInfo(std::string uid);

	void doPay();

	void postJavaEvent(std::string event, std::string param);

	void registHallEventListener(WSGameHallProtocol* listener);

private:

	WSGameHallProtocol* getHallEventListener();

private:
	WSGameHallProtocol* hallListener;

	static WSGameHallUtils* instance;
};

#endif  // __WSGAMEHALL_UTILS_H__

