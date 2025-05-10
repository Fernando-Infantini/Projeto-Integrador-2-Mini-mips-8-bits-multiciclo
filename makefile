objects = minimipsmulti.o control_unit.o dat_manager.o stack.o ula.o memoria.o
stdio_menu: libmips.a
	$(CC) -o mips menus/menu.c -lmips -L ./ -I ./ -I headers/

libmips.a: $(objects)
	ar rs libmips.a $(objects)

minimipsmulti.o:
	$(CC) -c minimipsmulti.c -I headers/

control_unit.o:
	$(CC) -c components/control_unit.c -I headers/

dat_manager.o:
	$(CC) -c components/dat_manager.c -I headers/

stack.o:
	$(CC) -c components/stack.c -I headers/

ula.o:
	$(CC) -c components/ula.c -I headers/

memoria.o:
	$(CC) -c components/memoria.c -I headers/

clean:
	rm $(objects)
