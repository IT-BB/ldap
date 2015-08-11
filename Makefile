OBJ = ldapAPI.o interface.o ldapTrace.so
CC = g++ 
CFLAGS = -O -g -shared -fPIC  
LIB =-L. -ljson-c -lmysqlclient
ldapAPI : $(OBJ)
        $(CC) $(CFLAGS) $(OBJ) -o libldapInfoAPI.so $(LIB)
        
ldapAPI.o : ldapInfoAPI.cpp ldapInfoAPI.h ldapException.hpp
        $(CC) $(CFLAGS) -c  ldapInfoAPI.cpp -o ldapAPI.o
interface.o : ldapInfoAPI.h
        $(CC) $(CFLAGS) -c  interface.cpp -o interface.o 
ldapTrace,so : ldapInfoTrace.cpp ldapInfoTrace.hpp
		$(CC) $(CFLAGS) -c  ldapInfoTrace.cpp ldapTrace.so
        
clean:
        rm -f *.o libldapInfoAPI.so