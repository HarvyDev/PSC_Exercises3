CFLAGS = -Wall -g
# LDFLAGS = $(shell pkg-config --cflags --libs glib-2.0)
LDFLAGS = `pkg-config --cflags --libs glib-2.0`

all: spell_check

spell_check: spell_check.o dictionary.o
	gcc $(CFLAGS) dictionary.o spell_check.o `pkg-config --libs glib-2.0` -o spell_check

spell_check.o: spell_check.c dictionary.h
	gcc $(LDFLAGS) -c spell_check.c -o spell_check.o

dictionary.o: dictionary.c dictionary.h
	gcc $(LDFLAGS) -c dictionary.c -o dictionary.o

clean:
	rm *.o
	rm spell_check

debug: spell_check
	insight spell_check
