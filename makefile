

all:Semaphore
Semaphore:Semaphore.c
	gcc $^ -o $@

.phone :clean
clean:
	rm -i Semaphore
