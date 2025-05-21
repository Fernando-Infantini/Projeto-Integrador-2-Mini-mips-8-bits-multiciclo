sources = mips_instance.c control_unit.c stack.c ula.c memoria.c nameing.c
objects = $(sources:.c=.o)

stdio_menu: libmips.so
	$(CC) -o mips menus/menu.c -lmips -L ./ -Wl,-rpath='$${ORIGIN}' -I headers/

gdb: $(objects:.o=D.o)
	$(CC) -o mips menus/menu.c $(objects:.o=D.o) -I headers/ -g

libmips.so: $(objects)
	$(CC) -shared -o libmips.so $(objects)

$(objects): %.o: %.c
	$(CC) -c -fPIC components/$< -I headers/

$(objects:.o=D.o): %D.o: %.c
	$(CC) -o $@ -c components/$< -I headers/ -g

$(sources): %c:

clean:
	-rm $(objects) $(objects:.o=D.o)
