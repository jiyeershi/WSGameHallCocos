#ifndef __WSGameInfo_H__
#define __WSGameInfo_H__

#include "string"

class  WSGameHallInfo
{
public:
	WSGameHallInfo();

	virtual ~WSGameHallInfo();

	static WSGameHallInfo* getInstance();

	void setUserId(std::string uId);
	
	void setGameId(std::string gameId);

	std::string getUserId();
	
	std::string getGameId();

private:
	std::string uid;
	std::string gameid;
};

#endif  // __WSGameInfo_H__