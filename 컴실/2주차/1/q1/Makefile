animal exe : dog.o blackcow.o turtle.o main.o
	gcc -o animal.exe dog.o blackcow.o turtle.o main.o
다음 오프젝트 파일을 기반으로한 실행 파일 animal.exe를 만든다

dog.o : dog.c
	gcc -c -o dog.o dog.c
dog.o를 목적파일name으로 하는 목적파일 만든다

blackcow.o : blackcow.c
	gcc -c -o blackcow.o blackcow.c

blackcow.o를 목적파일name으로 하는 목적파일 만든다

turtle.o : turtle.c
	gcc -c -o turtle.o turtle.c
	
turtle.o를 목적파일name으로 하는 목적파일 만든다

main.o : main.c
	gcc -c -o main.o main.c

main.o를 목적파일name으로 하는 목적파일 만든다

.phony:clean
clean : 
		rm *.o animal.exe
