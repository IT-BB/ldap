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

typedef int  ret_s;				//返回状态码

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
		//1.获取所有组列表。             
		//@ domain				指定根域名，由于已经在配置文件中添加，因此，可设置为NULL
		//@ json_GroupNames		返回的组的信息。
		ret_s getLdapGoupInfo(out string &json_GroupNames);
		
		//2.获取指定组下的所有用户
		//@ domain      ...
		//@ json_GroupName		输入组信息。
		//@ json_Users 			返回组下用户信息。
		ret_s getLdapUserByGroup(in int group_id,out string &json_Users);
		
		//3.获取所有用户信息
		//@ domain		...
		//@ json_Users			返回所有用户信息。
		ret_s getLdapAllUsers(out string &json_Users);
		
		//4.添加组
		//@ domain		...
		//@ json_GroupInfo		要插入组信息。
		ret_s insertLdapGroup(in string json_GrouInfo);
		
		//5.更新组信息
		//@ domain		...
		//@ json_groupInfo		要更新组信息。
		ret_s updateLdapGroup(in string json_GrouInfo);
		
		//6.删除组
		//@ domain		...
		//@ group_Id			要删除组信息。
		ret_s deleteLdapGroup(in int group_Id);
		
		//7.添加用户
		//@ domain		...
		//@ json_User			要插入用户的信息。
		ret_s insertLdapUser(in string json_User);
		
		//8.更新用户信息
		//@ domain		...
		//@	json_UserInfo		要插入用户的信息。
		ret_s updateLdapUserInfo(in string json_UserInfo);
		
		//9.删除用户
		//@ domain		...
		//@ json_UserId			要插入用户的信息。
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
		MYSQL *  			_my_con; //mysql 连接句柄
		char                _sql[SQL_BUF_LEN];
		vector<Group_json>  _vec_Group_Js;
		vector<User_json>   _vec_User_Js;
};
#endif
