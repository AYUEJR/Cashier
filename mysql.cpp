#include"MySQL.h"
#include<iostream>
#include<mysql.h>
using namespace std;
MySQL::MySQL()
{
	_mySQL = mysql_init(nullptr);
}

bool MySQL::ConnectMySQL(const char* host, const char* user, const char* passward, const char* dbName)
{
	if (!mysql_real_connect(_mySQL, host, user, passward, dbName, 3306, nullptr, 0))
	{

		cout << "���ݿ�����ʧ��" << endl;
		return false;
	}
	mysql_query(_mySQL,"set names 'gbk'");
	return true;
}

vector<vector<string>> MySQL::Select(const string& strSQL)
{
	vector<vector<string>> vvRet;
	if (mysql_query(_mySQL, strSQL.c_str()))
	{
		//SQL������Ӧʧ��
		cout << mysql_error (_mySQL)<< endl;
		return vvRet;
	}

	//��ȡ��ѯ�ļ�¼��
	MYSQL_RES* mySQLRes = mysql_store_result(_mySQL);
	if (nullptr == mySQLRes)
	{
		cout << mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//��ȡ��¼���ж��ٸ��ֶ�
	int itemCount = mysql_num_fields(mySQLRes);
	MYSQL_ROW mysqlROW;

	while (mysqlROW = mysql_fetch_row(mySQLRes))
	{
		//�ѻ�ȡ��һ����¼
		vector<string> vItem;
		for (size_t i = 0; i < itemCount; i++)
		{
			vItem.push_back(mysqlROW[i]);
		}
		vvRet.push_back(vItem);
	}
	mysql_free_result(mySQLRes);

	return vvRet;
}

bool MySQL::Insert(const string& strSQL)
{
	if (mysql_query(_mySQL, strSQL.c_str()))
	{
		//SQL������Ӧʧ��
		cout << mysql_error(_mySQL) << endl;
		return false;
	}
	return true;
}

bool MySQL::UpDate(const string& strSQL)
{
	if (mysql_query(_mySQL, strSQL.c_str()))
	{
		//SQL������Ӧʧ��
		cout << mysql_error(_mySQL) << endl;
		return false;
	}
	return true;
}


MySQL::~MySQL()
{

}