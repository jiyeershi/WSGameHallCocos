#ifndef __WSGAMEHALL_TEST_SCENE_H__
#define __WSGAMEHALL_TEST_SCENE_H__

#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "WSGameHallProtocol.h"

class WSGameHallTestScene : public cocos2d::Scene, public WSGameHallProtocol
{
public:
	WSGameHallTestScene();

    virtual bool init() override;

    static cocos2d::Scene* scene();

    void buttonClickCallback(Ref* sender);

    CREATE_FUNC(WSGameHallTestScene);

	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	virtual void onGameHallPushPayResult(std::string result);

	virtual void onGameHallPushUserInfo(std::string userInfo);

	virtual void onGameHallPushNotification(std::string notification);

	virtual void onGameHallPushLocationChanged(std::string location);

private:
	Node* root;
	std::string posStr;
	std::string pushStr;
	std::string addAchivenmentStr;
	std::string payResultStr;
	std::string userInfoStr;
	std::string notificationStr;
	std::string posChangedStr;
	Node* lab;
};

#endif // __WSGAMEHALL_TEST_SCENE_H__
