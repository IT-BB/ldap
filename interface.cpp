#include <string.h>
#include "ldapInfoAPI.h"

//一下接口参数尽量按照功能取名。

extern "C" {
	ldapInfoDB ldapDB;
	//1.获取所有组的名称信息。
	//  无输入参数，返回所有组的名字。
	//----------------------------------------------------------------------------------------------
	//  |  @json_GroupName   eg:																   
	//  |  {"group":[{"group_id": 1,"group_name":"安全组"},{"group_id": 2,"group_name":"保密组"}]} 
	//----------------------------------------------------------------------------------------------
	int getAllGroupName(out char * json_GroupName){
		
	}
	//2. 获取组的详细信息。
	//   无输入参数，返回所有组的详细信息。
	//---------------------------------------------------------------------------------------------------------
	//  |  @json_GroupName   eg:																  
	//  |  {
	//	|	 "group":[
	//	|			 {"group_id": 1, "group_name": "安全组", "creator_name": "LDAP", "timestamp": 1437337466},
	//	|		     {"group_id": 2, "group_name": "保密组", "creator_name": "LDAP", "timestamp": 1437337467}
	//	|			 ]
	//	|  } 																							
	//----------------------------------------------------------------------------------------------------------
	int getAllGroupDes(out char * json_GroupDes){
		
	}
	//3. 获取组关系下的用户详细信息。
	//   无需输入参数，获取所有组及组内用户信息。
	//---------------------------------------------------------------------------------------------------------
	//  |  @json_GroupName   eg:
	//	| {
	//	|"groups":[
	//  |  		  {
	//	|	 		"group_name":"安全组",
	//	|	 		"group_user"：
	//	|						[
	//	|			 			{ "user_id": 8, "email": "shanyj@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 },
	//	|		     			{ "user_id": 9, "email": "luhh@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 }
	//	|			 			]
	//	|  		  },
	//  |  		  {
	//	|	 		"group_name":"保密组",
	//	|	 		"group_user"：
	//	|						[
	//	|			 			{ "user_id": 10, "email": "chenl@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 },
	//	|		     			{ "user_id": 11, "email": "bip@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 1 }
	//	|			 			]
	//	|  		  }
	//  |  		  ]
	//  | }
	//----------------------------------------------------------------------------------------------------------
	int getGroupAndUserDes(out char * Json_GroupAndUser){
		
	}
	//4. 获取指定组下所有用户的名称。
	//@json_Group_id  {"group_id":1}
	//@json_GroupName eg：
	//  |  	{
	//	|	"group_name":"保密组",
	//	|	"group_user"：
	//	|			[
	//	|			{ "user_id": 10, "email": "chenl@abc.com"},
	//	|		    { "user_id": 11, "email": "bip@abc.com"}
	//	|			]
	//	|   }
	int getAllUserByGroupName(in char * json_GroupId,out char *json_GroupName){
		
	}
	//5. 获取用户创建的组列表
	//@json_User_id  {"user_id":1}
	//@json_UserName
	//  |  {
	//	|	 "group":[
	//	|			 {"group_id": 1, "group_name": "安全组", "creator_name": "LDAP", "timestamp": 1437337466},
	//	|		     {"group_id": 2, "group_name": "保密组", "creator_name": "LDAP", "timestamp": 1437337467}
	//	|			 ]
	//	|  } 
	int getUserOwnGroupName(in char * json_UserId,out char * json_UserName){
		
	}
	//6. 用户增加新组
	//@json_UserId_GroupName
	//{"user_id":1,"group_name":"安全组"}
	int insertGroup(in char * json_UserId_GroupName){
		
	}
	//7. 用户更新组
	//@json_UserId_GroupName
	//{"user_id":1,"group_name":"安全组"}
	int updateGroup(in char * json_UserId_GroupName){
		
	}
	//8. 用户删除组
	//@json_GroupId  {"group_id":1}
	int deleteGroup(in char * json_GroupId){
		
	}
	//9. 获取用户组详情   用户所在的组的所有用户的信息。
	//@json_UserId {"group_id":1}
	//@json_UserInfo 
	//	|	{"id":1,"name":"group001","creator_name": "LDAP", "timestamp": 1437337467}
	int getGroupDes(in char * json_GroupId,out char *json_GroupInfo){
		
	}
	//10. 获取指定组内用户角色
	//Role 默认值 0 代表此用户没有担当角色，属于普通用户，1代表管理员
	//@json_GroupId  {"group_id":1}
	//@json_UserRole eg：
	//  |  	{
	//	|	"group_name":"保密组",
	//	|	"group_user"：
	//	|			[
	//	|			{ "user_id": 10, "email": "chenl@abc.com", "Role":1},
	//	|		    { "user_id": 11, "email": "bip@abc.com", "Role":0 }
	//	|			]
	//	|   }
	int getGroupUserRole(in char *json_GroupId,out char *json_UserRole){
		
	}
	//11. 组内用户角色添加
	//@json_GroupUserRole {"group_id":1,"user_id":10,"Role":1}  
	int insertGroupUserRole(in char *json_GroupUserRole){
		
	}
	//12. 组内用户角色删除
	//@json_GroupUserId  {"group_id":1,"user_id":10}
	int deleteGroupUserRole(in char *json_GroupUserId){
		
	}
	//13. 获取组内用户详细信息
	//@json_GroupId  {"group_id":1}
	//@json_GroupName eg：
	//  |  	{
	//	|	"group_name":"保密组",
	//	|	"group_user"：
	//	|			[
	//	|			{ "user_id": 10, "email": "chenl@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 0 },
	//	|		    { "user_id": 11, "email": "bip@abc.com", "password": "7c4a8d09ca3762af61e59520943dc26494f8941b", "is_staff": 0, "is_active": 1, "jurisdiction": 1 }
	//	|			]
	//	|   }
	int getGroupAllUser(in char *json_GroupId,out char * json_GroupName){
		
	}
	//14. 添加组成员
	//@json_GroupUserId  {"group_id":1,"user_id":10}
	int insertGroupUser(in char *json_GroupUserId){
		
	}
	//15. 更新组内成员角色
	//@json_GroupUserRole {"group_id":1,"user_id":10,"Role":1}  
	int updateGroupUserRole(in char *json_GroupUserRole){
		
	}
	//16. 删除组内成员
	//@json_GroupUserId  {"group_id":1,"user_id":10}
	int deleteGroupUser(in char *json_GroupUserId){
		
	}
	//17. 用户认证
	//@json_UserAndPasswd {"user":"zhouc@abc.com","password":"XXXXXXXXXXX"}
	//@json_UserInfo      {"id":1,"name":"用户名", "email":"test@163.com","is_staff": 0, "is_active": 1, "jurisdiction": 1}
	int certifiUser(in char *json_UserAndPasswd,out char * json_UserInfo){
		
	}
	// 18. 获取指定用户的所有信息   和第9点貌似雷同？？？？？
	// int getUserDes(in char *json_UserId){
		
	// }
	//修改用户密码
	//@json_UserInfo {"user":"zhouc@abc.com","oldPwd":"XXXXXXXXXXX","newPwd":"XXXXXXXXXXXX"}
	int modifyUserPasswd(in char *json_UserInfo){
		
	}
	//19. 获取用户所在的所有组担当角色
	//@json_UserId {"user_id":1}
	//@json_UserRole
	//	{
	//	"userRole":
	//				[
	//				{"group_id":1,"userRole":1},
	//				{"group_id":2,"userRole":0}
	//				]
	//	}
	int getUserAllRole(in char *json_UserId,out char * json_UserRole){
		
	}
	// //20. 更新用户所在某一组的角色    和 15 貌似雷同？？？？？？？
	// //@json_UserGroupRole {"group_id":1,"user_id":10,"Role":1}
	// int updateUserGroupRole(in char * json_UserGroupRole){
		
	// }
}


//old 
#if 0
extern "C"   {
	
	ldapInfoDB ldapDB;//*ldapDB = new ldapInfoDB();
	int getLdapGoupInfo(out char * json_GroupNames){
		int error = 0;
		string jsGNames;
		ldapDB.connectDB();
		error = ldapDB.getLdapGoupInfo(jsGNames);
		stpcpy(json_GroupNames,jsGNames.c_str());
		return error;
	}

	int getLdapUserByGroup(in int group_id,out char * json_Users){
		int error = 0;
		string jsUNames;
		ldapDB.connectDB();
		error = ldapDB.getLdapUserByGroup(group_id,jsUNames);
		stpcpy(json_Users,jsUNames.c_str());
		return error;
	}

	int getLdapAllUsers(out char * json_Users){
		int error = 0;
		string allUsers;
		ldapDB.connectDB();
		error = ldapDB.getLdapAllUsers(allUsers);
		stpcpy(json_Users,allUsers.c_str());
		return error;
	}

	int insertLdapGroup(in char * json_GrouInfo){
		int error = 0;
		string jsGInfo(json_GrouInfo);
		ldapDB.connectDB();
		error = ldapDB.insertLdapGroup(jsGInfo);
		return error;
	}
	
	int updateLdapGroup(in char * json_GrouInfo){
		int error = 0;
		string jsGInfo(json_GrouInfo);
		ldapDB.connectDB();
		error = ldapDB.updateLdapGroup(jsGInfo);
		return error;
	}
	
	int deleteLdapGroup(in int group_Id){
		int error = 0;
		ldapDB.connectDB();
		error = ldapDB.deleteLdapGroup(group_Id);
		return error;
	}
		
	int insertLdapUser(in char * json_User){
		int error = 0;
		string jsUInfo(json_User);
		ldapDB.connectDB();
		error = ldapDB.insertLdapUser(jsUInfo);
		return error;
	}
	
	int updateLdapUserInfo(in char * json_UserInfo){
		int error = 0;
		string jsUInfo(json_UserInfo);
		ldapDB.connectDB();
		error = ldapDB.updateLdapUserInfo(jsUInfo);
		return error;	
	}
	
	int deleteLdapUser(in char * userEmail_name){
		int error = 0;
		string userName(userEmail_name);
		ldapDB.connectDB();
		error = ldapDB.deleteLdapUser(userName);
	}
}
#endif