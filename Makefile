.PHONY : all clean test

all : libchio.so generate check damage

src/murmur3.o : src/murmur3.c
	$(CC) -fPIC -c src/murmur3.c -o src/murmur3.o -Iinclude/

src/chio.o : src/chio.c
	$(CC) -fPIC -c src/chio.c -o src/chio.o -Iinclude/

# The main library
libchio.so : src/chio.o src/murmur3.o
	$(CC) -shared src/*.o -o libchio.so

# Utilities for generating and checking files
generate : src/generate.c libchio.so
	$(CC) src/generate.c ./libchio.so -o generate -Iinclude/

check : src/check.c libchio.so
	$(CC) src/check.c ./libchio.so -o check -Iinclude/

damage : src/damage.c libchio.so
	$(CC) src/damage.c ./libchio.so -o damage -Iinclude/

test : generate check damage test.sh
	bash test.sh

clean :
	rm -f src/*.o generate check damage *.so
