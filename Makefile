
CFLAGS = -Wall -Wstrict-prototypes -Dlinux -DSSQ     \
	-I/usr/include/mysql/    \
	-L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lm -lrt -ldl

OFILES = Algorithm.o Main.o MySqlOperator.o StringUtil.o

LIBFILES = -L

OBJ = tickets

$(OBJ) : ${OFILES}
	g++ -o $(OBJ) $(OFILES) $(CFLAGS)

.PHONY : clean
clean:
	$(RM) $(OBJ) $(OFILES)
