#include"MainWnd.h"
#include"MySQL.h"
//ASCII

//xml文件对应的目录
CDuiString MainWnd::GetSkinFolder()
{
	return _T("");
}

//xml文件的名字
CDuiString MainWnd::GetSkinFile()
{
	return _T("MainWnd.xml");
}

//窗口类的名字：在注册窗口时必须提供
LPCTSTR MainWnd::GetWindowClassName(void) const
{
	return _T("MainWnd");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//字符转码
string UnicodeToANSI(const CDuiString& str) {
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_ACP, 0, str, -1, pElementText, iTextLen, NULL, NULL);
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}

CDuiString ANSIToUnicode(const string& str) {
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	CDuiString  rt;
	rt = (wchar_t*)pUnicode;
	delete  pUnicode;

	return  rt;
}

//**************************************************************************************************************************************

void MainWnd::Notify(TNotifyUI& msg)
{
	CDuiString strNAME = msg.pSender->GetName();
	if (msg.sType == _T("click"))
	{
		if (strNAME == _T("BTN_CLOSE"))
			Close();
		else if (strNAME == _T("BTN_MIN"))
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if (strNAME == _T("BTN_SELECT"))
			//MessageBox(NULL, _T("SSS"), _T("Cashier"), IDOK);
			SelectEmployeeInfo();
		else if (strNAME == _T("BTN_INSERT"))
			//MessageBox(NULL, _T("III"), _T("Cashier"), IDOK);
			InsertEmployeeInfo();
		else if (strNAME == _T("BTN_UPDATE"))
			MessageBox(NULL, _T("UUU"), _T("Cashier"), IDOK);
		else if (strNAME == _T("BTN_DELETE"))
			//MessageBox(NULL, _T("DDD"), _T("Cashier"), IDOK);
			DeleteEmployeeInfo();
		else if (strNAME == _T("BTN_SELL_RECORD"))
			MessageBox(NULL, _T("SR"), _T("Cashier"), IDOK);


	}
	else if (msg.sType == _T("selectchanged"))
	{
		CTabLayoutUI* pTab = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tablayout"));
		if (strNAME == _T("OPTION_EMPLOYEE"))
			pTab->SelectItem(0);
		else
			pTab->SelectItem(1);
	}
	
	else if (msg.sType == _T("windowinit")) {
		//窗口在创建期间，将一些空间初始化
		
		CComboBoxUI* pGender = (CComboBoxUI*)m_PaintManager.FindControl(_T("usergender"));
		pGender->SelectItem(0);

		CComboBoxUI* pPosition = (CComboBoxUI*)m_PaintManager.FindControl(_T("position"));
		pGender->SelectItem(0);

		CComboBoxUI* pSelect = (CComboBoxUI*)m_PaintManager.FindControl(_T("COMOB_SELECT"));
		pGender->SelectItem(0);
	
	}
	
}



//*************************************************************************************************************************插入
void MainWnd::InsertEmployeeInfo()
{
	//从界面中获取员工信息
	CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("username")))->GetText();
	CDuiString strgender = ((CComboBoxUI*)m_PaintManager.FindControl(_T("usergender")))->GetText();
	CDuiString strBirthday = ((CEditUI*)m_PaintManager.FindControl(_T("userbirthday")))->GetText();
	CDuiString strPos = ((CComboBoxUI*)m_PaintManager.FindControl(_T("position")))->GetText();
	CDuiString strTel = ((CEditUI*)m_PaintManager.FindControl(_T("telphone")))->GetText();
	CDuiString strSalary = ((CEditUI*)m_PaintManager.FindControl(_T("salary")))->GetText();


	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListDemo1"));
	char szCount[32] = { 0 };
	_itoa(pListUI->GetCount()+1,szCount,10);
	//构造SQL命令g
	string strSQL("insert into employee values(");
	strSQL +=szCount;
	strSQL += ",'";
	strSQL += UnicodeToANSI(strName);
	strSQL += "','";
	strSQL += UnicodeToANSI(strgender);
	strSQL += "','";
	strSQL += UnicodeToANSI(strBirthday);
	strSQL += "','0000','";
	strSQL += UnicodeToANSI(strPos);
	strSQL += "','";
	strSQL += UnicodeToANSI(strTel);
	strSQL += "','";
	strSQL += UnicodeToANSI(strSalary);
	strSQL += "');";

	//响应SQL命令
	p_mysql->Insert(strSQL);
	//将该员工插入到List
	CListTextElementUI* pItem = new CListTextElementUI;
	
	pListUI->Add(pItem);
	pItem->SetText(0, strName);
	pItem->SetText(1, strgender);
	pItem->SetText(2, strBirthday);
	pItem->SetText(3, strPos);
	pItem->SetText(4, strTel);
	pItem->SetText(5, strSalary);
}


//***********************************************************************************************************************查询
void MainWnd::SelectEmployeeInfo()
{
	string strSQL("select* from employee");

	CComboBoxUI* pCombo=(CComboBoxUI*)m_PaintManager.FindControl(_T("ListDemo1"));
	CDuiString strStyle = pCombo->GetText();
	if (strStyle == _T("无"))
			strSQL += ";";
	else if (strStyle==_T("名字"))
	{
		strSQL += "where Name = '";
		CDuiString strName = ((CEditUI*)m_PaintManager.FindControl(_T("")))->GetText();
		if (strName.IsEmpty())
		{
			MessageBox(m_hWnd, _T("请输入查询用户的名字"), _T("Cashier"), IDOK);
			return;
		}
		strSQL += UnicodeToANSI(strName);
		strSQL += "';";
	}
	else if(strStyle == _T("性别"))
		;
	else if (strStyle == _T("Salary"))
		;
	vector<vector<string>> vRet = p_mysql->Select(strSQL);
	if (vRet.empty())
		return;
	CListUI* pListUI= (CListUI*)m_PaintManager.FindControl(_T("ListDemo1"));
	pListUI->RemoveAll();
	for (size_t i=0;i<vRet.size();++i)
	{
		vector<string>& strItem = vRet[i];
		CListTextElementUI* pData = new CListTextElementUI;
		pData->SetAttribute(_T("align"), _T("center"));

		pListUI->Add(pData);
		//
		pData->SetText(0, ANSIToUnicode(strItem[1]));
		pData->SetText(1, ANSIToUnicode(strItem[2]));
		pData->SetText(2, ANSIToUnicode(strItem[3]));
		pData->SetText(3, ANSIToUnicode(strItem[5]));
		pData->SetText(4, ANSIToUnicode(strItem[6]));
		pData->SetText(5, ANSIToUnicode(strItem[7]));
	}
}

void MainWnd::DeleteEmployeeInfo()
{
	//获取当前选中信息
	CListUI* pListUI = (CListUI*)m_PaintManager.FindControl(_T("ListDemo1"));
	pListUI->RemoveAll();
	int lineNo = pListUI->GetCurSel();
	CListTextElementUI* pRow = (CListTextElementUI*)pListUI->GetItemAt(lineNo);
	//从数据库中将该员工的信息删除
	//构造SQL命令
	string strSQL("delete");

    //CDuiString strName = pRow->GetText(0);

	//从数据库中将该条记录删除
	//p_mysql->Delete(strSQL);

	//从list里删除
	pListUI->RemoveAt(lineNo);

}