#ifndef __LDAP_EXCEPTION_H__
#define __LDAP_EXCEPTION_H__

#include<cstdio>
#include<ctime>
#include<exception>
#include<string>
#include <boost/smart_ptr.hpp>

#ifdef WIN32
#define snprintf _snprintf
#endif

using namespace std;

#define EXCEPTION_BUF_LEN 1024

#define LDAP_PROVIDER_INFO  "ldapinfo"


enum ldapExceptionType{
	LDAP_FATAL = 0,        //致命错误，必须退出程序。
	LDAP_CRITICAL = 1,     //严重错误，必须放弃当前步骤。
	LDAP_WARN = 2,         //警告。
	LDAP_INFO = 3,         //信息。
	LDAP_UNKOWN = 4,       //未知类型。
};

class ldapException :public exception
{
public:
	ldapException(ldapExceptionType type,
				  const int errorNo,
				  const string& msg,
				  const time_t& time,
				  const char* provider,
				  const char* fileName,
				  const int& codeLine) throw()
				  :_exceptionType(type),
				   _errno(errorNo),
				   _exceptionInfo(new char[EXCEPTION_BUF_LEN]){
					   snprintf(_exceptionInfo.get(),EXCEPTION_BUF_LEN,
						"Provider : %s, Time : %ld, ExceptionType : %d, ErrorNo : %d, Message : %s, File : %s, Line : %d.",
						provider,time,type,errorNo,msg.c_str(), fileName,codeLine);
					}

	ldapException(ldapExceptionType type,
		const int errorNo,
		const char* msg,
		const time_t& time,
		const char* provider,
		const char* fileName,
		const int& codeLine) throw()
		:_exceptionType(type),
		_errno(errorNo),
		_exceptionInfo(new char[EXCEPTION_BUF_LEN]){
			snprintf(_exceptionInfo.get(),EXCEPTION_BUF_LEN,
				"Provider : %s, Time : %ld, ExceptionType : %d, ErrorNo : %d, Message : %s, File : %s, Line : %d.",
				provider,time,type,errorNo,msg, fileName,codeLine);
	}

	virtual const char* what() const throw() {
			return _exceptionInfo.get();
	}

	virtual ~ldapException() throw()
	{}

public:
	const int _exceptionType;
	const int _errno;

private:
	boost::shared_array<char> _exceptionInfo;
};


#define THROW_EXCEPTION_LDAP_FATAL(errno, msg)           \
	throw ldapException(LDAP_FATAL, (errno), (msg), time(NULL), LDAP_PROVIDER_INFO, __FILE__, __LINE__)

#define THROW_EXCEPTION_LDAP_CRITICAL(errno, msg)           \
	throw ldapException(LDAP_CRITICAL, (errno), (msg), time(NULL), LDAP_PROVIDER_INFO, __FILE__, __LINE__)

#define THROW_EXCEPTION_LDAP_WARN(errno, msg)           \
	throw ldapException(LDAP_WARN, (errno), (msg), time(NULL), LDAP_PROVIDER_INFO, __FILE__, __LINE__)

#define THROW_EXCEPTION_LDAP_INFO(errno, msg)           \
	throw ldapException(LDAP_INFO, (errno), (msg), time(NULL), LDAP_PROVIDER_INFO, __FILE__, __LINE__)


///get ldap info errno

#define LDAP_INFO_SUCCESS             1200
#define LDAP_INFO_FAILURE             1201
#define LDAP_INFO_UNKNOW              1203



#endif
