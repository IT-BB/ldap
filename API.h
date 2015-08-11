int getAllGroupName(out char * json_GroupName){
		
	}
	//获取组的详细信息。
	//无输入参数，返回所有组的详细信息。
	
	int getAllGroupDes(out char * json_GroupDes){
		
	}
	//获取用户和组的详细信息。
	int getGroupAndUserDes(out char * Json_GroupAndUser){
		
	}
	//获取指定组下所有用户的名称。
	int getAllUserByGroup(in char * json_Group_id,out char *json_GroupName){
		
	}
	//获取用户组创建的列表
	int getUserOwnGroupName(in char * json_User_id,out char * json_UserName){
		
	}
	//用户增加新组
	int insertGroup(in char * json_UserId_GroupName){
		
	}
	//用户更新组
	int updateGroup(in char * json_UserId_GroupName){
		
	}
	//用户删除组
	int deleteGroup(in char * json_UserId){
		
	}
	//获取用户组详情
	int getUserOwnGroupDes(in char * json_UserId){
		
	}
	//获取指定组内用户角色
	int getGroupUserRole(in char *json_GroupId){
		
	}
	//组内用户角色添加
	int insertGroupUserRole(in char *json_GroupUserRole){
		
	}
	//组内用户角色删除
	int deleteGroupUserRole(in char *json_GroupUserId){
		
	}
	//获取组内用户详细信息
	int getGroupAllUser(in char *json_GroupId){
		
	}
	//添加组成员
	int insertGroupUser(in char *json_GroupUserId){
		
	}
	//更新组内成员等级
	int updateGroupUserRole(in *json_GroupUserRole){
		
	}
	//删除组内成员
	int deleteGroupUser(in char *json_GroupUserId){
		
	}
	//用户认证
	int certifiUser(in char *json_UserAndPasswd){///常艳杰在核实需要返回什么信息
		
	}
	//获取指定用户的所有信息
	int getUserDes(in char *json_UserId){
		
	}
	//修改用户密码
	int modifyUserPasswd(in char *json_UserInfo){
		
	}
	//获取用户所在的所有组担当角色
	int getUserAllRole(in char *json_UserId,out char * json_UserRole){
		
	}
	//跟新用户所在某一组的角色
	int updateUserGroupRole(in char * json_UserGroupRole){
		
	}