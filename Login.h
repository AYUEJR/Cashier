
#include"Common.h"
#include"MySQL.h"

class LoginWnd :public WindowImplBase
{
public:
	virtual void Notify(TNotifyUI& msg);

	void Login();
public:
	MySQL* p_mysql;
	//WindowImplBase:�ṩ���������麯��
	//xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	//xml�ļ�������
	virtual CDuiString GetSkinFile();

	//����������֣���ע�ᴰ��ʱ�����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;
};