CC = g++
CFLAGS = -std=c++11 -fPIC
ALL = cgiHeader.o cgiError.o cgiFile.o cgiParameter.o
include ./lwsfc/Makefile.mk
install : cgiHeader.o cgiError.o cgiFile.o cgiParameter.o
	$(CC) -shared  -o libcgi.so $(ALL)
	sh conf.sh
	cp -R cgi /usr/local/include
	cp cgi.h /usr/local/include
	cp -R cgi /usr/include
	cp cgi.h /usr/include
cgiHeader.o : cgi/cgiHeader.cpp
	$(CC) $(CFLAGS) -c cgi/cgiHeader.cpp

cgiError.o : cgi/cgiError.cpp
	$(CC) $(CFLAGS) -c cgi/cgiError.cpp

cgiFile.o : cgi/cgiFile.cpp
	$(CC) $(CFLAGS) -c cgi/cgiFile.cpp

cgiParameter.o : cgi/cgiParameter.cpp
	$(CC) $(CFLAGS) -c cgi/cgiParameter.cpp

clean :
	rm *.o libcgi.so
 
