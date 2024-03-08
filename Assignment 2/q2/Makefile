all: A_fifo B_other C_rr count1

A_fifo: A_fifo.c
	gcc -o A_fifo A_fifo.c -pthread

B_other: B_other.c
	gcc -o B_other B_other.c -pthread

C_rr: C_rr.c
	gcc -o C_rr C_rr.c -pthread

count1: count1.c
	gcc -o count1 count1.c

run: A_fifo B_other C_rr
	sudo ./A_fifo & ./B_other & sudo ./C_rr
	python3 histogram.py
	
clean: 
	rm -f A_fifo B_other C_rr count1