.PHONY: build clean run-var1 run-var2 run-var3 run-var4

build: 2-var1 2-var2 2-var3 2-var4

2-var1: 2-var1.o
	gcc -Wall 2-var1.o -o 2-var1
2-var2: 2-var2.o
	gcc -Wall 2-var2.o -o 2-var2
2-var3: 2-var3.o
	gcc -Wall 2-var3.o -o 2-var3
2-var4: 2-var4.o
	gcc -Wall 2-var4.o -o 2-var4
2-var1.o: 2-var1.c
	gcc -c 2-var1.c -o 2-var1.o
2-var2.o: 2-var2.c
	gcc -c 2-var2.c -o 2-var2.o
2-var3.o: 2-var3.c
	gcc -c 2-var3.c -o 2-var3.o
2-var4.o: 2-var4.c
	gcc -c 2-var4.c -o 2-var4.o

clean:
	rm -rf 2-var1.o 2-var1 2-var2.o 2-var2 2-var3.o 2-var3 2-var4.o 2-var4

run-var1:
	./2-var1
run-var2:
	./2-var2
run-var3:
	./2-var3
run-var4:
	./2-var4