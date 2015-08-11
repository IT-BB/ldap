//
//  ldapInfoAPI.cpp
//
#include <string.h>
#include "ldapInfoAPI.h"
#include <json-c/json.h>

ldapInfoDB::ldapInfoDB(){
}

ldapInfoDB::~ldapInfoDB(){
	if (_my_con != NULL){	
		mysql_close(_my_con);  
		free(_my_con);  
	}
}

void 
ldapInfoDB::checksql(){
	
	if(strlen(_sql)){
		memset(_sql,0,SQL_BUF_LEN);
	}
	
}
void
ldapInfoDB::connectDB()
{
	_my_con = (MYSQL*)malloc(sizeof(MYSQL)); 
	mysql_init(_my_con);
	
	_my_con = mysql_real_connect(_my_con, DB_IP, USER, PWD, DB_NAME, 0, NULL, CLIENT_FOUND_ROWS);
	
	if(NULL == _my_con){
		THROW_EXCEPTION_LDAP_FATAL(LDAP_INFO_FAILURE,mysql_error(_my_con));
	}
	
	mysql_query(_my_con, "set character set utf8");

}


int 
ldapInfoDB::selectJur(string email){
	
	int fieldNum,rowNum;
	int res;
	int userJur = -1;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row; 
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select jurisdiction from UserJur where email = '%s';",email.c_str());
	
	res = mysql_query(_my_con,_sql);
	if(!res)
	{
		my_res = mysql_store_result(_my_con);
		if(my_res)
		{
			while(my_row = mysql_fetch_row(my_res))
			{
				fieldNum = 0;
				if(my_row[fieldNum])
					userJur = atoi(my_row[fieldNum]);
			}
		}
		mysql_free_result(my_res);
	}
	return userJur;
}

//prase and build json 
void 
ldapInfoDB::praseJsonUSer(vector<User_json> &vec_User_Js,string json_Users){
	
	struct json_object *prase_user_object = NULL;
	prase_user_object = json_tokener_parse(json_Users.c_str());
	
	if(!prase_user_object) {
			printf("prase error!!!");
	}
	
	json_type type = json_object_get_type(prase_user_object);
#ifdef TRACE
	printf("%s\n",json_object_to_json_string(prase_user_object));
#endif
	json_object *arr_json = json_object_object_get(prase_user_object,"user"); 
#ifdef TRACE
	printf("%s\n",json_object_to_json_string(arr_json));
#endif
    int length = json_object_array_length(arr_json);
	
	for(int i = 0;i < length;++i){
		User_json userNode;
		json_object *temp_object = json_object_array_get_idx(arr_json,i);
		json_object * user_id_object = json_object_object_get(temp_object,"user_id");
		json_object * email_object = json_object_object_get(temp_object,"email");
		json_object * password_object = json_object_object_get(temp_object,"password");
		json_object * is_staff_object = json_object_object_get(temp_object,"is_staff");
		json_object * is_active_object = json_object_object_get(temp_object,"is_active");
		json_object * ctime_object = json_object_object_get(temp_object,"ctime");
		json_object * jurisdiction_object = json_object_object_get(temp_object,"jurisdiction");
		userNode.user_id = json_object_get_int(user_id_object);
		userNode.email = json_object_get_string(email_object);
		userNode.password = json_object_get_string(password_object);
		userNode.is_staff = json_object_get_int(is_staff_object);
		userNode.is_active = json_object_get_int(is_active_object);
		userNode.ctime = json_object_get_int(ctime_object);
		userNode.jurisdiction = json_object_get_int(jurisdiction_object);
		
		vec_User_Js.push_back(userNode);
	}	
}
void 
ldapInfoDB::praseJsonGroup(vector<Group_json> &vec_Group_Js,string json_GroupNames){
		
	struct json_object *prase_group_object = NULL;
	prase_group_object = json_tokener_parse(json_GroupNames.c_str());
	
	if(!prase_group_object) {
			printf("prase error!!!");
	}
	
	json_type type = json_object_get_type(prase_group_object);
	
	printf("%s\n",json_object_to_json_string(prase_group_object));
	
	json_object *arr_json = json_object_object_get(prase_group_object,"group"); 
	
	printf("%s\n",json_object_to_json_string(arr_json));
	
	
    int length = json_object_array_length(arr_json);
	
	for(int i = 0;i < length;++i){
		Group_json groupNode;
		json_object *temp_object = json_object_array_get_idx(arr_json,i);
		json_object * group_id_object = json_object_object_get(temp_object,"group_id");
		json_object * group_name_object = json_object_object_get(temp_object,"group_name");
		json_object * creator_name_object = json_object_object_get(temp_object,"creator_name");
		json_object * timestamp_object = json_object_object_get(temp_object,"timestamp");
		groupNode.group_id = json_object_get_int(group_id_object);
		groupNode.group_name = json_object_get_string(group_name_object);
		groupNode.creator_name = json_object_get_string(creator_name_object);
		groupNode.timestamp = json_object_get_int(timestamp_object);
		
		vec_Group_Js.push_back(groupNode);
	}
	
#ifdef TRACE
	for(int i = 0; i < vec_Group_Js.size(); ++i){
		printf("group_id = [%d]\n",vec_Group_Js[i].group_id);
		printf("group_name = [%s]\n",vec_Group_Js[i].group_name.c_str());
		printf("creator_name = [%s]\n",vec_Group_Js[i].creator_name.c_str());
		printf("timestamp = [%ld]\n",vec_Group_Js[i].timestamp);
	}
#endif
	
}
void 
ldapInfoDB::buildJsonUser(string &json_Users){
	
	int rowNum;
	struct json_object *infor_group_object = NULL;
	infor_group_object = json_object_new_object();
	struct json_object *array_object = NULL;
	array_object = json_object_new_array();
	
	for(rowNum = 0; rowNum < _vec_User_Js.size(); ++rowNum){
		struct json_object *infor_object = NULL;
		infor_object = json_object_new_object();
		json_object_object_add(infor_object, "user_id", json_object_new_int(_vec_User_Js[rowNum].user_id));
		json_object_object_add(infor_object, "email", json_object_new_string(_vec_User_Js[rowNum].email.c_str()));
		json_object_object_add(infor_object, "password", json_object_new_string(_vec_User_Js[rowNum].password.c_str()));
		json_object_object_add(infor_object, "is_staff", json_object_new_int(_vec_User_Js[rowNum].is_staff));
		json_object_object_add(infor_object, "is_active", json_object_new_int(_vec_User_Js[rowNum].is_active));
		json_object_object_add(infor_object, "jurisdiction", json_object_new_int(_vec_User_Js[rowNum].jurisdiction));
		json_object_array_add(array_object, infor_object);
	}
	json_object_object_add(infor_group_object,"user",array_object);
	json_Users = json_object_to_json_string(infor_group_object);
	
#ifdef TRACE	
	printf("%s\n",json_object_to_json_string(infor_group_object));
#endif

	json_object_put(array_object);
	json_object_put(infor_group_object);
	
}
void 
ldapInfoDB::buildJsonGroup(string &json_GroupNames){
		
	//组织json
	int rowNum;
	struct json_object *infor_group_object = NULL;
	infor_group_object = json_object_new_object();
	struct json_object *array_object = NULL;
	array_object = json_object_new_array();
	
	
	for(rowNum = 0; rowNum < _vec_Group_Js.size(); ++rowNum){
		struct json_object *infor_object = NULL;
		infor_object = json_object_new_object();
		json_object_object_add(infor_object, "group_id", json_object_new_int(_vec_Group_Js[rowNum].group_id));
		json_object_object_add(infor_object, "group_name", json_object_new_string(_vec_Group_Js[rowNum].group_name.c_str()));
		json_object_object_add(infor_object, "creator_name", json_object_new_string(_vec_Group_Js[rowNum].creator_name.c_str()));
		json_object_object_add(infor_object, "timestamp", json_object_new_int(_vec_Group_Js[rowNum].timestamp));
		json_object_array_add(array_object, infor_object);
	}
	json_object_object_add(infor_group_object,"group",array_object);
	json_GroupNames = json_object_to_json_string(infor_group_object);
	
#ifdef TRACE	
	printf("%s\n",json_object_to_json_string(infor_group_object));
#endif

	//json_object_put(infor_object);
	json_object_put(array_object);
	json_object_put(infor_group_object);	
}
//end prase and build


//1.获取所有组列表。             
//@ domain				指定根域名，由于已经在配置文件中添加，因此，可设置为NULL
//@ json_GroupNames		返回的组的信息。
int
ldapInfoDB::getLdapGoupInfo(out string &json_GroupNames){
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row;
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select * from `Group`;");
	
	res = mysql_query(_my_con,_sql);
	if(!res)
	{
		my_res = mysql_store_result(_my_con);
		if(my_res)
		{
#ifdef TRACE
			cout<<"number of my_res: "<<(unsigned long)mysql_num_rows(my_res)<<endl;

			for(fieldNum = 0;fd = mysql_fetch_field(my_res);fieldNum++)
			{
				strcpy(column[fieldNum],fd->name);
			}
			rowNum = mysql_num_fields(my_res);
			for(fieldNum = 0;fieldNum < rowNum;fieldNum++)
			{
				printf("%s\t",column[fieldNum]);
			}
#endif
			
			while(my_row = mysql_fetch_row(my_res))
			{
				Group_json groupNode;
				fieldNum = 0;
				if(my_row[fieldNum])
					groupNode.group_id = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					groupNode.group_name = my_row[fieldNum];
				++fieldNum;
				if(my_row[fieldNum])
					groupNode.creator_name = my_row[fieldNum];
				++fieldNum;
				if(my_row[fieldNum])
					groupNode.timestamp = atol(my_row[fieldNum]);
				_vec_Group_Js.push_back(groupNode);
			}
		}
		mysql_free_result(my_res);
	}
	
	//构建json
	buildJsonGroup(json_GroupNames);
	return 0;
}

//2.获取指定组下的所有用户
//@ domain      ...
//@ json_GroupName		输入组信息。
//@ json_Users 			返回组下用户信息。
ret_s 
ldapInfoDB::getLdapUserByGroup(in int group_id,out string &json_Users){
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row; 
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select *  from EmailUser  where EmailUser.email = ANY (select user_name from `GroupUser` where group_id = %d);",group_id);
	
	res = mysql_query(_my_con,_sql);
	if(!res)
	{
		my_res = mysql_store_result(_my_con);
		if(my_res)
		{
#ifdef TRACE
			cout<<"number of my_res: "<<(unsigned long)mysql_num_rows(my_res)<<endl;

			for(fieldNum = 0;fd = mysql_fetch_field(my_res);fieldNum++)
			{
				strcpy(column[fieldNum],fd->name);
			}
			rowNum = mysql_num_fields(my_res);
			for(fieldNum = 0;fieldNum < rowNum;fieldNum++)
			{
				printf("%s\t",column[fieldNum]);
			}
#endif
			while(my_row = mysql_fetch_row(my_res))
			{
				User_json userNode;
				fieldNum = 0;
				int UserJur = -1;
				if(my_row[fieldNum])
					userNode.user_id = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					userNode.email = my_row[fieldNum];
				++fieldNum;
				if(my_row[fieldNum])
					userNode.password = my_row[fieldNum];
				++fieldNum;
				if(my_row[fieldNum])
					userNode.is_staff = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					userNode.is_active = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					userNode.ctime = atol(my_row[fieldNum]);
								
				userNode.jurisdiction = selectJur(userNode.email);
				
				_vec_User_Js.push_back(userNode);
			}
		}
		mysql_free_result(my_res);
	}
	
	//组织json
	buildJsonUser(json_Users);
	
	return 0;
}

//3.获取所有用户信息
//@ domain		...
//@ json_Users			返回所有用户信息。
ret_s 
ldapInfoDB::getLdapAllUsers(out string &json_Users){
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row; 
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select * from EmailUser;");
	
	res = mysql_query(_my_con,_sql);
	if(!res)
	{
		my_res = mysql_store_result(_my_con);
		if(my_res)
		{
#ifdef TRACE
			cout<<"number of my_res: "<<(unsigned long)mysql_num_rows(my_res)<<endl;

			for(fieldNum = 0;fd = mysql_fetch_field(my_res);fieldNum++)
			{
				strcpy(column[fieldNum],fd->name);
			}
			rowNum = mysql_num_fields(my_res);
			for(fieldNum = 0;fieldNum < rowNum;fieldNum++)
			{
				printf("%s\t",column[fieldNum]);
			}
#endif	
			while(my_row = mysql_fetch_row(my_res))
			{
				User_json userNode;
				fieldNum = 0;
				int UserJur = -1;
				if(my_row[fieldNum])
					userNode.user_id = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					userNode.email = my_row[fieldNum];
				++fieldNum;
				if(my_row[fieldNum])
					userNode.password = my_row[fieldNum];
				++fieldNum;
				if(my_row[fieldNum])
					userNode.is_staff = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					userNode.is_active = atoi(my_row[fieldNum]);
				++fieldNum;
				if(my_row[fieldNum])
					userNode.ctime = atol(my_row[fieldNum]);
				
				userNode.jurisdiction = selectJur(userNode.email);
				
				_vec_User_Js.push_back(userNode);
			}
		}
		mysql_free_result(my_res);
	}
	
	//组织json
	buildJsonUser(json_Users);
	return 0;
}

//4.添加组
//@ domain		...
//@ json_GroupInfo		要插入组信息。
ret_s 
ldapInfoDB::insertLdapGroup(in string json_GrouInfo){
	
	//解析json 
	vector<Group_json> groupNodes;
	praseJsonGroup(groupNodes,json_GrouInfo);
	
	if(groupNodes.size() > 1){
		return 66;//一次不能插入多个group，如果需要，后端在开放。
	}
	Group_json groupNode = groupNodes[0];
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row;
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select * from `Group` where group_id = %d;",groupNode.group_id);
	
	res = mysql_query(_my_con,_sql);
	if(!res){
		my_res = mysql_store_result(_my_con);
		if(my_res){
			rowNum = mysql_num_rows(my_res);
			if(rowNum == 0){
				checksql();
				sprintf(_sql,"insert into `Group`(group_name, creator_name, timestamp) value('%s', '%s', %ld);",groupNode.group_name.c_str(),groupNode.creator_name.c_str(),groupNode.timestamp);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
			}else{
				//已存在。。。
			}
		}
		mysql_free_result(my_res);
	}
	return 0;
}

//5.更新组信息
//@ domain		...
//@ json_groupInfo		要更新组信息。
ret_s 
ldapInfoDB::updateLdapGroup(in string json_GrouInfo){
	
	//解析json 
	vector<Group_json> groupNodes;
	praseJsonGroup(groupNodes,json_GrouInfo);
	
	if(groupNodes.size() > 1){
		return 66;//同理一次也不能更新多个group，如果需要，后端在开放。
	}
	Group_json groupNode = groupNodes[0];
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row;
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select * from `Group` where group_id = %d;",groupNode.group_id);
	
	res = mysql_query(_my_con,_sql);//查询有了才能更新
	if(!res){
		my_res = mysql_store_result(_my_con);
		if(my_res){
			rowNum = mysql_num_rows(my_res);
			if(rowNum == 0){  //不存在就插入进去。
				checksql();
				sprintf(_sql,"insert into `Group`(group_name, creator_name, timestamp) value('%s', '%s', %ld);",groupNode.group_name.c_str(),groupNode.creator_name.c_str(),groupNode.timestamp);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
			}else{//存在便更新
				checksql();
				sprintf(_sql,"update `Group` set group_name = '%s', creator_name = '%s', timestamp = '%ld' where group_id = %d;",groupNode.group_name.c_str(),groupNode.creator_name.c_str(),groupNode.timestamp,groupNode.group_id);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
			}
		}
		mysql_free_result(my_res);
	}
	return 0;
}

//6.删除组
//@ domain		...
//@ group_Id			要删除组信息。
ret_s 
ldapInfoDB::deleteLdapGroup(in int group_Id){
	//1.从数据库中删除。
	//2.从LDAP服务器中删除。
	int res;
	checksql();
	sprintf(_sql,"delete from `Group` where id = %d;",group_Id);
	res = mysql_query(_my_con, _sql);
	if(!res){
		//删除失败。
	}
	return 0;
}

//7.添加用户
//@ domain		...
//@ json_User			要插入用户的信息。
ret_s 
ldapInfoDB::insertLdapUser(in string json_User){
	
	//解析json 
	vector<User_json> UserNodes;
	praseJsonUSer(UserNodes,json_User);
	
	if(UserNodes.size() > 1){
		return 66;// 同组类似问题。
	}
	User_json UserNode = UserNodes[0];
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res; 
	MYSQL_ROW 			my_row;
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select * from EmailUser where id = %d;",UserNode.user_id);
	
	res = mysql_query(_my_con,_sql);
	if(!res){
		my_res = mysql_store_result(_my_con);
		if(my_res){
			rowNum = mysql_num_rows(my_res);
			if(rowNum == 0){
				checksql();
				sprintf(_sql,"insert into EmailUser(email, passwd, is_staff, is_active, ctime) value('%s', '%s', %d, %d, %ld);",UserNode.email.c_str(),UserNode.password.c_str(),UserNode.is_staff,UserNode.is_active,UserNode.ctime);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
				checksql();
				sprintf(_sql,"insert into UserRole(email, role) value('%s', 'default');",UserNode.email.c_str());
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
				checksql();
				sprintf(_sql,"insert into UserJur(email, jurisdiction) value('%s', %d);",UserNode.email.c_str(),UserNode.jurisdiction);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
			}else{
				//已存在。。。
			}
		}
		mysql_free_result(my_res);
	}
	return 0;
}

//8.更新用户信息
//@ domain		...
//@	json_UserInfo		要插入用户的信息。
ret_s 
ldapInfoDB::updateLdapUserInfo(in string json_UserInfo){
	
	//解析json 
	vector<User_json> UserNodes;
	praseJsonUSer(UserNodes,json_UserInfo);
	
	if(UserNodes.size() > 1){
		return 66;// 同组类似问题。
	}
	User_json UserNode = UserNodes[0];
	
	
	int fieldNum,rowNum;
	int res;
	MYSQL_RES *			my_res;
	MYSQL_ROW 			my_row;
	MYSQL_FIELD *fd;
    char column[32][32];
	checksql();
	sprintf(_sql,"select * from EmailUser where id = %d;",UserNode.user_id);
	
	res = mysql_query(_my_con,_sql);//查询没有才能插入
	if(!res){
		my_res = mysql_store_result(_my_con);
		if(my_res){
			rowNum = mysql_num_rows(my_res);
			if(rowNum == 0){  //不存在便插入。
				checksql();
				sprintf(_sql,"insert into EmailUser(email, passwd, is_staff, is_active, ctime) value('%s', '%s', %d, %d, %ld);",UserNode.email.c_str(),UserNode.password.c_str(),UserNode.is_staff,UserNode.is_active,UserNode.ctime);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
				checksql();
				sprintf(_sql,"insert into UserRole(email, role) value('%s', 'default');",UserNode.email.c_str());
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
				checksql();
				sprintf(_sql,"insert into UserJur(email, jurisdiction) value('%s', %d);",UserNode.email.c_str(),UserNode.jurisdiction);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
			}else{ //存在便更新
				checksql();
				sprintf(_sql,"update  EmailUser set email = '%s', passwd = '%s', is_staff = '%d', is_active = '%d', ctime = '%ld' where id = %d;",UserNode.email.c_str(),UserNode.password.c_str(),UserNode.is_staff,UserNode.is_active,UserNode.ctime,UserNode.user_id);
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
				checksql();
				sprintf(_sql,"update UserRole set role = '%s' where email = '%s';","default",UserNode.email.c_str());
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
				
				checksql();
				sprintf(_sql,"update UserJur set jurisdiction = %d where email = '%s';",UserNode.jurisdiction,UserNode.email.c_str());
				res = mysql_query(_my_con, _sql);
				if(!res){
					//插入有问题。
				}
			}
		}
		mysql_free_result(my_res);
	}
	
	return 0;
}

//9.删除用户
//@ domain		...
//@ json_UserId			要插入用户的信息。
ret_s 
ldapInfoDB::deleteLdapUser(in string userEmail_name){
	//1.从数据库中删除。
	//2.从LDAP服务器中删除。
	int res;
	checksql();
	sprintf(_sql,"delete from EmailUser where email = %s;",userEmail_name.c_str());
	res = mysql_query(_my_con, _sql);
	if(!res){
		//删除失败。
	}
	
	checksql();
	sprintf(_sql,"delete from `GroupUser` where user_name = %s;",userEmail_name.c_str());
	res = mysql_query(_my_con, _sql);
	if(!res){
		//删除失败。
	}
	
	checksql();
	sprintf(_sql,"delete from UserRole where email = %s;",userEmail_name.c_str());
	res = mysql_query(_my_con, _sql);
	if(!res){
		//删除失败。
	}
	
	checksql();
	sprintf(_sql,"delete from UserJur where email = %s;",userEmail_name.c_str());
	res = mysql_query(_my_con, _sql);
	if(!res){
		//删除失败。
	}
	
	return 0;
}


// int main()
// {
	 // ldapInfoDB *test = new ldapInfoDB();
	
	 // string domain = "";
	 // string json_GroupNames;
	 // test->connectDB();
	 // test->getLdapAllUsers(json_GroupNames);
	 // //test->getLdapUserByGroup(2,json_GroupNames);
	 // printf("{{{{%s}}}}\n",json_GroupNames.c_str());
	 // return 0;
// }
