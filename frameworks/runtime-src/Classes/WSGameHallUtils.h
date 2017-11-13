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

	/*获取微赛用户id，同步返回*/
	std::string doQueryWesaiUid();

	/*获取微赛游戏id，同步返回*/
	std::string doQueryGameId();

	/*查询微赛用户信息，异步返回结果*/
	void doQueryUserInfo();

	/*微赛支付接口，异步返回支付结果*/
	void doPay(std::string orderId, int cost, std::string desc, std::string extralInfo);

	/*微赛分享接口，异步返回结果*/
	void doShare(std::string title, std::string content, std::string iconUrl, std::string h5Url);

	/*微赛推送接口，同步返回结果*/
	std::string getPushStr();

	/*微赛定位接口，同步返回结果*/
	std::string getLocationStr();

	/*java端发送事件通知接口*/
	void postJavaEvent(std::string event, std::string param);

	/*注册对微赛大厅事件（用户信息返回，支付结果等事件）的监听*/
	void registHallEventListener(WSGameHallProtocol* listener);

private:

	WSGameHallProtocol* getHallEventListener();

private:
	WSGameHallProtocol* hallListener;

	static WSGameHallUtils* instance;
};

#endif  // __WSGAMEHALL_UTILS_H__

