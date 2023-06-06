linkedListtest: linkedList.o linkedListtest.c
	clang linkedList.o linkedListtest.c -o linkedListtest

linkedList.o: linkedList.c
	clang -c linkedList.c

clean:
	rm -f ./??*.o ./linkedList 
