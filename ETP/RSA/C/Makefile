CC = gcc

INCLUDE = -I/usr/local/include -I/usr/include
LIB = -L/usr/local/lib -L/usr/lib -lgmp

all: rsa

rsa: rsa.c
	$(CC) -o rsa $(INCLUDE) rsa.c $(LIB)

clean:
	-rm *.o
	-rm rsa

zip:
	(tar zcvf ../RSA-C_cor.tar.gz *.c Makefile *.txt ;)
