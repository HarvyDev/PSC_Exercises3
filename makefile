CFLAGS = -Wall -g
# LDFLAGS = $(shell pkg-config --cflags --libs glib-2.0)
LDFLAGS = `pkg-config --cflags --libs glib-2.0`


# gcc dictionary.o spell_check.o `pkg-config --libs glib-2.0` -o spell_check
prog: spell_check.o dictionary.o
	gcc $(CFLAGS) dictionary.o spell_check.o `pkg-config --libs glib-2.0` -o spell_check

# gcc `pkg-config --cflags glib-2.0` -c spell_check.c -o spell_check.o
spell_check.o: spell_check.c dictionary.h
	gcc $(LDFLAGS) -c spell_check.c -o spell_check.o

# gcc `pkg-config --cflags glib-2.0` -c dictionary.c -o dictionary.o
dictionary.o: dictionary.c dictionary.h
	gcc $(LDFLAGS) -c dictionary.c -o dictionary.o

clean:
	rm *.o
	rm spell_check

debug: a.out
	insight prog
