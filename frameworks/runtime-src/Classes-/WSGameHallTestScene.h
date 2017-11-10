#ifndef __WSGAMEHALL_TEST_SCENE_H__
#define __WSGAMEHALL_TEST_SCENE_H__

#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "WSGameHallProtocol.h"

class WSGameHallTestScene : public cocos2d::Scene, public WSGameHallProtocol
{
public:
    virtual bool init() override;

    static cocos2d::Scene* scene();

    void buttonClickCallback(Ref* sender);

    CREATE_FUNC(WSGameHallTestScene);

	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	virtual void onGameHallPushPayResult(std::string result);

	virtual void onGameHallPushUserInfo(std::string userInfo);

	virtual void onGameHallPushGameBaseInfo(std::string gameBaseInfo);
};

#endif // __WSGAMEHALL_TEST_SCENE_H__
