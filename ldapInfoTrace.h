/////
/////  trace
/////
#include<iostream>
#include<string.h>
#include<stdio.h>
#include <stdarg.h>

using namespace std;

class Trace{
	public:
	static void trace (const char* fmt, ...);
};


class EntryTrace {
public:
    EntryTrace(const char* file, 
               const char* func,
               const unsigned int& line);
    ~EntryTrace(void);

private:
   const char* _file;
   const char* _func;
};

#ifdef WIN32 

#define LDAP_ENTRY_TRACE  EntryTrace \
	trace(__FILE__, __FUNCTION__, __LINE__)

#define LDAP_TRACE(...) \
	    Trace::trace(__VA_ARGS__)
#else

#define LDAP_ENTRY_TRACE  EntryTrace \
	trace(__FILE__, __FUNCTION__, __LINE__)

#define VMWARE_NFS_BACKUP_TRACE(args...) \
	trace(args)
#endif
