if [ $1 == "dlt" ];then
	cp ./makefile.dlt ./Makefile
	make clean
	make all
elif [ $1 == "clr" ];then
	make clean
else
	cp ./makefile.ssq ./Makefile
	make clean
	make all