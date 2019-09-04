#pragma once

#include"Common.h"
#include"MySQL.h"
class MainWnd :public WindowImplBase
{
public:

	virtual void Notify(TNotifyUI& msg);
	
protected:
	//WindowImplBase:提供的三个纯虚函数
	//xml文件对应的目录
	virtual CDuiString GetSkinFolder();

	//xml文件的名字
	virtual CDuiString GetSkinFile();

	//窗口类的名字：在注册窗口时必须提供
	virtual LPCTSTR GetWindowClassName(void) const;

	void InsertEmployeeInfo();

	void SelectEmployeeInfo();

	void DeleteEmployeeInfo();

public:
	MySQL* p_mysql;
};

string UnicodeToANSI(const CDuiString& str);
CDuiString ANSIToUnicode(const string& str);
