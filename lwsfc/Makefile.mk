installwebserver : 
	gcc ./lwsfc/main.c ./lwsfc/src/*.c -o ./lwsfc/lwsfc
	mkdir /var/log/lwsfc/cgi
