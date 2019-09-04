
#include"CashierManage.h"

CashierWnd::CashierWnd(MySQL* pMySQL)
	:m_pMySQL(pMySQL)
{

}
CashierWnd::~CashierWnd()
{

}


CDuiString CashierWnd::GetSkinFolder()
{
	return _T("");
}

//xml�ļ�������
CDuiString CashierWnd::GetSkinFile()
{
	return _T("CashierManage.xml");
}

//����������֣���ע�ᴰ��ʱ�����ṩ
LPCTSTR CashierWnd::GetWindowClassName(void) const
{
	return _T("CashierManage");
}

void CashierWnd::Notify(TNotifyUI& msg)
{
	//m_PaintManager.FindControl(_T(""))
	CDuiString strName = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strName == _T("BIN_MIN"))
			//MessageBox(NULL, _T("MIN"), _T("Cashier"), IDOK);�����ȡС����ť
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if (strName == _T("BIN_CLOSE"))

			//*********************************************��ȫ�˳�����*************************************
			Close();
		else if (strName == _T("BTN_SELECT"))
			SelectGoods();
		else if (strName == _T("BTN_ADD"))
			AddGoodsCount();
		else if (strName == _T("BTN_SUB"))
			SubGoodsCount();
		else if (strName == _T("BTN_COMMIT"))
			CommitOeder();
		else if (strName == _T("BTN_CANCEL"))
			CancelOrder();
		else if (strName == _T("BTN_OK"))
			InsertGoodsList();
	}
}

//Cashiermanage�����ѯ��Ʒ
void CashierWnd::SelectGoods()
{
	//1.��ȡ��Ʒ����EDIT_GOODS_NAME	
	CDuiString strGoodsName= ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_NAME")))->GetText();

	//2.����SQL��䣬�����ݿ��в��Ҵ���Ʒ
	string strSQL("select * from goods where GoodsName='");
	strSQL += UnicodeToANSI(strGoodsName);
	strSQL += "';";
	vector<vector<string>>vRet = m_pMySQL->Select(strSQL);
	if(vRet.empty())
	{
		MessageBox(m_hWnd, _T("���޴���Ʒ!"), _T("Cashier"), IDOK);
		return;
	}
	//3.����Ʒʣ�������ʾ������༭����
	((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_LEFT")))->SetText(ANSIToUnicode(vRet[0][7]));
	
}

//��Ʒ+1

void CashierWnd::AddGoodsCount()
{
	//���-1
	CEditUI* pGoodsLeft = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_LEFT"));
	CDuiString strLeft=pGoodsLeft->GetText();
	if (strLeft == _T("0"))
	{
		MessageBox(m_hWnd, _T("���������"), _T("Cashier"), IDOK);
		return;
	}
	int count = 0;
	count = atoi(UnicodeToANSI(strLeft).c_str());
	--count;
	strLeft.Format(_T("%d"), count);
	pGoodsLeft->SetText(strLeft);

	//��Ʒ��+1
	CEditUI* pGoodsCount = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_COUNT"));
	CDuiString strCount = pGoodsCount->GetText();
	count= atoi(UnicodeToANSI(strCount).c_str());
	++count;
	strCount.Format(_T("%d"), count);
	pGoodsCount->SetText(strCount);
}


//��Ʒ-1
void CashierWnd::SubGoodsCount()
{
	//��Ʒ��-1
	CEditUI* pGoodsCount = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_COUNT"));
	CDuiString strCount = pGoodsCount->GetText();
	if (strCount==(_T("0")))
	{
		MessageBox(m_hWnd, _T("��Ʒ�����Ѿ�Ϊ0"), _T("Cashier"), IDOK);
		return;
	}
	int count = atoi(UnicodeToANSI(strCount).c_str());
	--count;
	strCount.Format(_T("%d"), count);
	pGoodsCount->SetText(strCount);
	
	
	//���-1
	CEditUI* pGoodsLeft = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_LEFT"));
	CDuiString strLeft=pGoodsLeft->GetText();	
	count = atoi(UnicodeToANSI(strLeft).c_str());
	++count;
	strLeft.Format(_T("%d"), count);
	pGoodsLeft->SetText(strLeft);
}

void CashierWnd::InsertGoodsList()
{
	//1.�ӽ����ȡ��Ʒ�����Լ���������
	CDuiString strGoodsName = ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_NAME")))->GetText();
	CEditUI* pGoodsCount = (CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_COUNT"));
	CDuiString strCount = pGoodsCount->GetText();
	//2.�����ݿ��л�ȡ��Ʒ�۸��Լ�������λ
	string strSQL("select* from goods where GoodsName ='");
	strSQL += UnicodeToANSI(strGoodsName);
	strSQL += "';";
	vector<vector<string>>vRet = m_pMySQL->Select(strSQL);
	//3.�ϼƼ۸�
	int count = atoi(UnicodeToANSI(strCount).c_str());
	double price = atof((vRet[0][5]).c_str());
	price = count * price;
	CDuiString strPrice;
	strPrice.Format(_T("%lf"), price);

	//4.����Ϣ���µ�List��
	CListTextElementUI* pItem = new CListTextElementUI;
	CListUI* pList=(CListUI*)m_PaintManager.FindControl(_T("OrderList"));
	pList->Add(pItem);
	pItem->SetText(0, strGoodsName);
	pItem->SetText(1, ANSIToUnicode(vRet[0][5]));
	pItem->SetText(2, strCount);
	pItem->SetText(3, ANSIToUnicode(vRet[0][6]));
	pItem->SetText(4, strPrice);

	
	//5.�������༭������
    ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_NAME")))->SetText(_T(""));
    ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_LEFT")))->SetText(_T(""));
    ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_COUNT")))->SetText(_T("0"));
	
}

void CashierWnd::CancelOrder()
{
	//���������Ʒ
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("OrderList"));
	pList->RemoveAll();
}

void CashierWnd::CommitOeder()
{
	//�ϼƼ۸�
	CListUI* pList = (CListUI*)m_PaintManager.FindControl(_T("OrderList"));
	int count=pList->GetCount();
	
	double totalPrice = 0;
	for (int i=0;i<count;++i)
	{
		CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(i);
		CDuiString strTotalPrice=pItem->GetText(4);
		totalPrice += atof(UnicodeToANSI(strTotalPrice).c_str());
	}
	 CDuiString strTotalPrice;
     strTotalPrice.Format(_T("%0.2lf"), totalPrice);
	((CEditUI*)m_PaintManager.FindControl(_T("EDIT_TOTAL")))->SetText(strTotalPrice);

	//������Ʒ���ݿ�
	for (int i = 0; i < count; ++i)
	{
		CDuiString strGoodsName = ((CEditUI*)m_PaintManager.FindControl(_T("EDIT_GOODS_NAME")))->GetText();
		CListTextElementUI* pItem = (CListTextElementUI*)pList->GetItemAt(i);
		CDuiString strCount = pItem->GetText(2);

		string strSQL("update goods set Inventory='");
		strSQL += UnicodeToANSI(strCount);
		strSQL += "';";
		m_pMySQL->UpDate(strSQL);

	}
    //���뱾�����ۼ�¼

}
