if [ $(getconf WORD_BIT) = '32' ] && [ $(getconf LONG_BIT) = '64' ] ; then
cp libcgi.so /usr/local/lib
cp libcgi.so /usr/local/lib64
cp libcgi.so /usr/lib
cp libcgi.so /usr/lib64
else
cp libcgi.so /usr/local/lib
cp libcgi.so /usr/lib
fi
