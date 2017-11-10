#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"
#include "string"


class  TestScene : public cocos2d::Scene
{
public:
	TestScene();
	virtual ~TestScene();
	bool init();
};

class TestLayer : public cocos2d::Layer
{
public:
	TestLayer();
	~TestLayer();
	bool init();
private:

};


#endif  // __UTILS_H__

