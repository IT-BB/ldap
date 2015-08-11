#include "ldapInfoTrace.h"

#define GET_FILE_NAME(file)    \
    strrchr(file, '/') ? strrchr(file, '/') + 1:file
		
void
Trace::trace (const char* fmt, ...){
	va_list ap;
	va_start (ap, fmt);
		
	/*string msg;
	msg.format(fmt, ap);*/
	char msg[1024];
	vsnprintf(msg,1024,fmt,ap);
	
	FILE* log = fopen("./log", "a");
	if (log == NULL){
		return;
	}
	int ret = 0;
	ret = fwrite(msg, strlen(msg), 1, log);
	if (ret < 0){
		fclose(log);
		return;
	}
	ret = fwrite("\n", strlen("\n"), 1, log);

	fclose(log);
}

EntryTrace::EntryTrace(const char* file, 
                       const char* func,
                       const unsigned int& line)
    :_file(GET_FILE_NAME(file)),_func(func) {
    Trace::trace("%s:%d, %s begin.", _file,line,_func);
}

EntryTrace::~EntryTrace(void) {
    Trace::trace("%s, %s end.",_file,_func);
}

//int addll( int a, int b){
//	LDAP_ENTRY_TRACE;
//	return a + b;
//}
//
//int main()
//{
//	int sum = 0;
//	sum = addll(2,5);
//	LDAP_TRACE("my name is [%s]","ykj");
//	cout<<sum<<endl;
//	return 0;
//}
