all: first second secondBonus

first: first.c
	gcc -o first first.c

second: second.c
	gcc -o second second.c

secondBonus: secondBonus.c
	gcc -o secondBonus secondBonus.c

run_secondBonus: secondBonus
	./secondBonus

run_first: first
	./first

run_second: second
	./second


clean:
	rm -f first second secondBonus
