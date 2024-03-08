all: dir date myshell

# word: word
# 	alias word='/mnt/c/Users/ASUS/Desktop/OSq2/wordB'

# dir: dir
# 	alias dir='/mnt/c/Users/ASUS/Desktop/OSq2/dirB'

dir: dir.c
	gcc dir.c -o dir

date: date.c
	gcc date.c -o date

myshell: myshell.c
	gcc -fno-lto myshell.c -o myshell

run_myshell: myshell
	./myshell

clean:
	rm dir date myshell