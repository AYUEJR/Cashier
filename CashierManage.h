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
	//WindowImplBase:�ṩ���������麯��
	//xml�ļ���Ӧ��Ŀ¼
	virtual CDuiString GetSkinFolder();

	//xml�ļ�������
	virtual CDuiString GetSkinFile();

	//����������֣���ע�ᴰ��ʱ�����ṩ
	virtual LPCTSTR GetWindowClassName(void) const;

	//Cashiermanage�����ѯ��Ʒ
	void SelectGoods();

	//��Ʒ+1
	void AddGoodsCount();
	
	//��Ʒ-1
	void SubGoodsCount();

	//
	void InsertGoodsList();

	void CancelOrder();

	void CommitOeder();

public:
	MySQL* m_pMySQL;
};