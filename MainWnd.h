#pragma once

#include"Common.h"
#include"MySQL.h"
class MainWnd :public WindowImplBase
{
public:

	virtual void Notify(TNotifyUI& msg);
	
protected:
	//WindowImplBase:�ṩ���������麯��
	//xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	//xml�ļ�������
	virtual CDuiString GetSkinFile();

	//����������֣���ע�ᴰ��ʱ�����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;

	void InsertEmployeeInfo();

	void SelectEmployeeInfo();

	void DeleteEmployeeInfo();

public:
	MySQL* p_mysql;
};

string UnicodeToANSI(const CDuiString& str);
CDuiString ANSIToUnicode(const string& str);
