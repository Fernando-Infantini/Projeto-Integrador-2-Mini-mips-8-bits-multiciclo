objects = mips_instance.o control_unit.o stack.o ula.o memoria.o nameing.o
stdio_menu: libmips.a
	$(CC) -g -o mips menus/menu.c -lmips -L ./ -I ./ -I headers/

libmips.a: $(objects)
	ar rs libmips.a $(objects)

mips_instance.o:
	$(CC) -g -c components/mips_instance.c -I headers/

control_unit.o:
	$(CC) -g -c components/control_unit.c -I headers/

stack.o:
	$(CC) -g -c components/stack.c -I headers/

ula.o:
	$(CC) -g -c components/ula.c -I headers/

memoria.o:
	$(CC) -g -c components/memoria.c -I headers/

nameing.o:
	$(CC) -g -c components/nameing.c -I headers/

clean:
	rm $(objects)
