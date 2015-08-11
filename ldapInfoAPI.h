//
// get ldap info API to everyBody
//
#ifndef __LDAP_INFO_API__
#define __LDAP_INFO_API__

#include <iostream>
#include<cstdio>
#include <mysql/mysql.h>
#include <vector>

#include "ldapException.hpp"

#define  in 
#define out

#define  SQL_BUF_LEN   1024

typedef int  ret_s;				//����״̬��

#define DB_IP "10.3.3.244"
#define USER "root"
#define PWD "123456"
#define DB_NAME "ccnet-db"

//group_json example
//{ "group": 
//	[ 
//		{ "group_id": 1, "group_name": "ykj", "creator_name": "LDAP", "timestamp": 1437337467 },
//		{ "group_id": 2, "group_name": "ykj222", "creator_name": "LDAP", "timestamp": 1437337506 } 
//	] 
//}

//user_json example
//{ "user": 
//	[ 
//		{ "user_id": 8, "email": "shanyj@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 },
//		{ "user_id": 9, "email": "luhh@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 },
//		{ "user_id": 10, "email": "chenl@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 },
//		{ "user_id": 11, "email": "bip@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 1 } 
//	] 
//}

struct Group_json
{
	int group_id;
	string group_name;
	string creator_name;
	long timestamp;
};

struct User_json
{
	int user_id;
	string email;
	string password;
	int is_staff;
	int is_active;
	long ctime;
	int jurisdiction;
};

class ldapInfoDB
{
	public:
		ldapInfoDB();
		~ldapInfoDB();
		
		void connectDB();

	public:
		//1.��ȡ�������б�             
		//@ domain				ָ���������������Ѿ��������ļ�����ӣ���ˣ�������ΪNULL
		//@ json_GroupNames		���ص������Ϣ��
		ret_s getLdapGoupInfo(out string &json_GroupNames);
		
		//2.��ȡָ�����µ������û�
		//@ domain      ...
		//@ json_GroupName		��������Ϣ��
		//@ json_Users 			���������û���Ϣ��
		ret_s getLdapUserByGroup(in int group_id,out string &json_Users);
		
		//3.��ȡ�����û���Ϣ
		//@ domain		...
		//@ json_Users			���������û���Ϣ��
		ret_s getLdapAllUsers(out string &json_Users);
		
		//4.�����
		//@ domain		...
		//@ json_GroupInfo		Ҫ��������Ϣ��
		ret_s insertLdapGroup(in string json_GrouInfo);
		
		//5.��������Ϣ
		//@ domain		...
		//@ json_groupInfo		Ҫ��������Ϣ��
		ret_s updateLdapGroup(in string json_GrouInfo);
		
		//6.ɾ����
		//@ domain		...
		//@ group_Id			Ҫɾ������Ϣ��
		ret_s deleteLdapGroup(in int group_Id);
		
		//7.����û�
		//@ domain		...
		//@ json_User			Ҫ�����û�����Ϣ��
		ret_s insertLdapUser(in string json_User);
		
		//8.�����û���Ϣ
		//@ domain		...
		//@	json_UserInfo		Ҫ�����û�����Ϣ��
		ret_s updateLdapUserInfo(in string json_UserInfo);
		
		//9.ɾ���û�
		//@ domain		...
		//@ json_UserId			Ҫ�����û�����Ϣ��
		ret_s deleteLdapUser(in string userEmail_name);
			
	private:			
		//void connectDB();
		void checksql();
		int selectJur(string email);
		void praseJsonUSer(vector<User_json> &vec_User_Js,string json_Users);
		void praseJsonGroup(vector<Group_json> &vec_Group_Js,string json_GroupNames);
		void buildJsonUser(string &json_Users);
		void buildJsonGroup(string &json_GroupNames);
	
	private:
		MYSQL *  			_my_con; //mysql ���Ӿ��
		char                _sql[SQL_BUF_LEN];
		vector<Group_json>  _vec_Group_Js;
		vector<User_json>   _vec_User_Js;
};
#endif
