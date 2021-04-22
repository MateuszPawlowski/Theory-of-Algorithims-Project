# This is my Makefile

EXECS=sha512

sha512: sha512.c
	cc -o sha512 sha512.c
	echo "Everything Working"

clean:
	rm -f $(EXECS)