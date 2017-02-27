hw2: hw2.o decrypt.o merge.o encrypt.o stream.o 
	gcc -o hw2 -g hw2.o decrypt.o merge.o encrypt.o stream.o -L/usr/include/openssl/lib -lcrypto -lm

hw2.o: hw2.c stream.h encrypt.h merge.h decrypt.h 
	gcc -g -c -Wall hw2.c

decrypt.o: decrypt.c decrypt.h
	gcc -g -c -Wall decrypt.c

merge.o: merge.c merge.h
	gcc -g -c -Wall merge.c

encrypt.o: encrypt.c encrypt.h
	gcc -g -c -Wall encrypt.c

stream.o: stream.c stream.h
	gcc -g -c -Wall stream.c -I/usr/include/openssl/include

clean:
	rm -rf *.o hw2