Documentation for Cypto Assignment 2
=====================================
AUTHOR
Name  : Kavyashree Mysore Jagadeesh
USC ID: 3554137619
Email : mysoreja@usc.edu

The purpose of this assignment is to get familiar with visual cryptography.
The commandline syntax for hw2 is as follows:
    hw2 stream -p=pphrase -l=len
    hw2 encrypt -p=pphrase -out=name [pbmfile]
    hw2 merge pbmfile1 pbmfile2
    hw2 decrypt [pbmfile]

Stream:
A simple stream cipher.
The ASCII string pphrase contains the passphrase for key generation and len is the number of bytes to output.

Encrypt:
Encrypts an input PBM file with the simple stream cipher. Generates stream used as key in encryption based on given passphrase. This creates 2 output files having the filename given with -out command option but one with .1.pbm appended and the other with .2.pbm appended to the filenames.4x expansion ratio of input to ouput files.

Merge:
Create an output PBM file by merging the bits of PBM files pbmfile1 and pbmfile2. A bit value of 1 is treated as a black pixel and a bit value of 0 is treated as a white pixel. When merging a bit of 1 and a bit of 0, the output is 1.

Decrypt:
Treats the input PBM file as the result of the merge command and perform the reverse of the encryption algorithm. The resulting image size is 1/4 of the original input.

BUILD
Comments:
"make" - to compile
"make clean" - to clear executable files

Steps to include openSSL Library:
In terminal:
set path=(/usr/include/openssl/bin $path)
rehash

setenv LD_LIBRARY_PATH /usr/include/openssl/lib:/usr/lib:/lib
setenv MANPATH /usr/include/openssl/ssl/man:$MANPATH

In Makefile:
-I/usr/include/openssl/include
-L/usr/include/openssl/lib -lcrypto -lm

TEST
set p0="yesnomaybe"
set p1="cs531-f09"
set p2="vcrypto"
set p3="password"
set p4="emptyString"
set p5="applied"
set p6="cryptography"
set p7="publickey"

set len0=320
set len1=241
set len2=202
set len3=803
set len4=724

(A) stream: 
        set srcdir=test
		rm bar-s?.stream

		./hw2 stream -p="$p0" -l=$len0 > bar-s0.stream
		./hw2 stream -p="$p1" -l=$len1 > bar-s1.stream
		./hw2 stream -p="$p2" -l=$len2 > bar-s2.stream
		./hw2 stream -p="$p3" -l=$len3 > bar-s3.stream
		./hw2 stream -p="$p4" -l=$len4 > bar-s4.stream

		foreach f (0 1 2 3 4)
			echo "==>$srcdir/s$f.stream"
			diff $srcdir/bar-s$f.stream bar-s$f.stream
		end

(B) encrypt: 
        set srcdir=test
		/bin/rm bar*.pbm

		cat $srcdir/small.pbm | ./hw2 encrypt -p="$p0" -out=bar-small
		cat $srcdir/money.pbm | ./hw2 encrypt -p="$p1" -out=bar-money
		cat $srcdir/bowtie.pbm | ./hw2 encrypt -p="$p2" -out=bar-bowtie
		cat $srcdir/cross.pbm | ./hw2 encrypt -p="$p3" -out=bar-cross
		./hw2 encrypt -p="$p4" -out=bar-hello $srcdir/hello.pbm
		./hw2 encrypt -p="$p5" -out=bar-nouturn $srcdir/nouturn.pbm
		./hw2 encrypt -p="$p6" -out=bar-stop $srcdir/stop.pbm
		./hw2 encrypt -p="$p7" -out=bar-viterbi $srcdir/viterbi.pbm

		foreach f (small money bowtie cross hello nouturn stop viterbi)
			echo "==> $srcdir/$f.pbm"
			diff $srcdir/bar-$f.1.pbm bar-$f.1.pbm 
			diff $srcdir/bar-$f.2.pbm bar-$f.2.pbm 
		end

(C) merge: 
        set srcdir=test
		/bin/rm bar*.pbm

		foreach f (small money bowtie cross hello nouturn stop viterbi)
			./hw2 merge $srcdir/bar-$f.1.pbm $srcdir/bar-$f.2.pbm > bar-merged.pbm
			echo "==> $srcdir/$f"
			diff $srcdir/bar-$f-merged.pbm bar-merged.pbm
			/bin/rm bar-merged.pbm
		end

(D) decrypt: 
        set srcdir=test
		/bin/rm bar*.pbm

		foreach f (small money bowtie cross)
			cat $srcdir/bar-$f-merged.pbm | ./hw2 decrypt > bar.pbm
			echo "==> $srcdir/$f.pbm"
			diff $srcdir/bar-$f.pbm bar.pbm
			/bin/rm bar.pbm
		end

		foreach f (hello nouturn stop viterbi)
			./hw2 decrypt $srcdir/bar-$f-merged.pbm > bar.pbm
			echo "==> $srcdir/$f.pbm"
			diff $srcdir/bar-$f.pbm bar.pbm
			/bin/rm bar.pbm
		end

(E) 

	(1) small.pbm: 
        set srcdir=test
		/bin/rm bar*.pbm

		./hw2 encrypt -p="$p0" -out=bar $srcdir/small.pbm
		./hw2 merge bar.1.pbm bar.2.pbm > bar-merged.pbm
		./hw2 decrypt bar-merged.pbm > bar.pbm

		echo "==> $srcdir/small.pbm "
		diff $srcdir/small.pbm bar.pbm

	(2) hello.pbm:  
        set srcdir=test
		/bin/rm bar*.pbm

		cat $srcdir/hello.pbm | ./hw2 encrypt -p="$p1" -out=bar
		./hw2 merge bar.1.pbm bar.2.pbm | ./hw2 decrypt > bar.pbm

		echo "==> $srcdir/hello.pbm "
		diff $srcdir/hello.pbm bar.pbm

	(3) bowtie.pbm:  
        set srcdir=test
		/bin/rm bar*.pbm

		cat $srcdir/bowtie.pbm | ./hw2 encrypt -p="$p2" -out=bar
		./hw2 merge bar.1.pbm bar.2.pbm | ./hw2 decrypt > bar.pbm

		echo "==> $srcdir/bowtie.pbm "
		diff $srcdir/bowtie.pbm bar.pbm


