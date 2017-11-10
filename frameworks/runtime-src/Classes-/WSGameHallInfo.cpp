#include "WSGameHallInfo.h"

WSGameHallInfo::WSGameHallInfo() :
uid(""),
gameid("")
{

}

WSGameHallInfo::~WSGameHallInfo()
{

}

WSGameHallInfo* WSGameHallInfo::getInstance()
{
	static WSGameHallInfo* gameInfo = new WSGameHallInfo;
	return gameInfo;
}

void WSGameHallInfo::setUserId(std::string uId)
{
	uid = uId;
}

void WSGameHallInfo::setGameId(std::string gameId)
{
	gameid = gameId;
}

std::string WSGameHallInfo::getUserId()
{
	return uid;
}

std::string WSGameHallInfo::getGameId()
{
	return gameid;
}
