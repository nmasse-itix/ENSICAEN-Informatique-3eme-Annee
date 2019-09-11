all: shellcode test serverbuf exploit

shellcode: shellcode.S shellcode.c
	gcc -Wall -m32 -o $@ $^

test: test.c
	gcc -Wall -g -m32 -o $@ $^

serverbuf: serverbuf.c
	gcc -Wall -g -m32 -o $@ $^

exploit: exploit.c
	gcc -Wall -g -m32 -o $@ $^

clean:
	rm -f shellcode test

