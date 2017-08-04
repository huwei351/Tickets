
CFLAGS = -Wall -Wstrict-prototypes -Dlinux -DSSQ  -lpthread   \
	-I/usr/include/mysql/    \
	-L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lm -lrt -ldl    \
	-I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7     \
	-fno-strict-aliasing -D_FORTIFY_SOURCE=2 -g -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -lpthread -ldl  -lutil -lm  -lpython2.7    \
	-L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib -lpthread -ldl  -lutil -lm  -lpython2.7 -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

SRCFILES = Algorithm.cpp Main.cpp MySqlOperator.cpp StringUtil.cpp Callpy.cpp Config.cpp MyConfig.cpp

OFILES = Algorithm.o Main.o MySqlOperator.o StringUtil.o Callpy.o Config.o MyConfig.o

TARGET = tickets

#all:$(TARGET)
#$(TARGET) : ${OFILES}
all:
	g++ -g -c $(SRCFILES)
	g++ -o $(TARGET) $(OFILES) $(CFLAGS)

.PHONY : clean
clean:
	$(RM) $(TARGET) $(OFILES)
