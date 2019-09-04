#pragma once
#include"Common.h"
#include"MainWnd.h"
#include<mysql.h>
#include"MySQL.h"
class CashierWnd :public WindowImplBase
{
public:
	CashierWnd(MySQL* pMySQL);
	~CashierWnd();

	virtual void Notify(TNotifyUI& msg);

	void Cashier();

	
protected:
	//WindowImplBase:提供的三个纯虚函数
	//xml文件对应的目录
	virtual CDuiString GetSkinFolder();

	//xml文件的名字
	virtual CDuiString GetSkinFile();

	//窗口类的名字：在注册窗口时必须提供
	virtual LPCTSTR GetWindowClassName(void) const;

	//Cashiermanage界面查询商品
	void SelectGoods();

	//商品+1
	void AddGoodsCount();
	
	//商品-1
	void SubGoodsCount();

	//
	void InsertGoodsList();

	void CancelOrder();

	void CommitOeder();

public:
	MySQL* m_pMySQL;
};