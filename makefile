objects = control_unit.o dat_manager.o stack.o ula.o memoria.o
all: $(objects)
	$(CC) -o mips minimipsmulti.c $(objects) -I headers/

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
