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

	/*��ȡ΢���û�id��ͬ������*/
	std::string doQueryWesaiUid();

	/*��ȡ΢����Ϸid��ͬ������*/
	std::string doQueryGameId();

	/*��ѯ΢���û���Ϣ���첽���ؽ��*/
	void doQueryUserInfo();

	/*΢��֧���ӿڣ��첽����֧�����*/
	void doPay(std::string orderId, int cost, std::string desc, std::string extralInfo);

	/*΢������ӿڣ��첽���ؽ��*/
	void doShare(std::string title, std::string content, std::string iconUrl, std::string h5Url);

	/*΢�����ͽӿڣ�ͬ�����ؽ��*/
	std::string getPushStr();

	/*΢����λ�ӿڣ�ͬ�����ؽ��*/
	std::string getLocationStr();

	/*java�˷����¼�֪ͨ�ӿ�*/
	void postJavaEvent(std::string event, std::string param);

	/*ע���΢�������¼����û���Ϣ���أ�֧��������¼����ļ���*/
	void registHallEventListener(WSGameHallProtocol* listener);

private:

	WSGameHallProtocol* getHallEventListener();

private:
	WSGameHallProtocol* hallListener;

	static WSGameHallUtils* instance;
};

#endif  // __WSGAMEHALL_UTILS_H__

