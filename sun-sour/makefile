
# makefile fuer jobshop

CC		= gcc
CFLAGS		= -O3

o		= main.o table.o list.o stack.o block.o branch.o fix.o headtail.o heur.o init.o low.o readdata.o select.o sort.o

jobshop.exe:	$o
		$(CC) -O3 -o $@ $o

clean:
		-rm *.o jobshop.exe

main.o:		main.cpp datastruct.hpp table.hpp list.hpp stack.hpp block.hpp branch.hpp fix.hpp headtail.hpp heur.hpp init.hpp low.hpp readdata.hpp select.hpp

block.o:	block.cpp block.hpp datastruct.hpp table.hpp list.hpp

branch.o:	branch.cpp branch.hpp datastruct.hpp table.hpp list.hpp

fix.o:		fix.cpp fix.hpp datastruct.hpp table.hpp list.hpp

headtail.o:	headtail.cpp headtail.hpp datastruct.hpp table.hpp list.hpp sort.hpp

heur.o:		heur.cpp heur.hpp datastruct.hpp table.hpp list.hpp low.hpp

init.o:		init.cpp init.hpp datastruct.hpp table.hpp

list.o:		list.cpp list.hpp datastruct.hpp table.hpp

low.o:		low.cpp low.hpp datastruct.hpp table.hpp list.hpp sort.hpp

readdata.o:	readdata.cpp readdata.hpp datastruct.hpp table.hpp list.hpp

select.o:	select.cpp select.hpp datastruct.hpp

sort.o:		sort.cpp sort.hpp datastruct.hpp

