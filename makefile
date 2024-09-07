
gpioset: examples/gpioset.c
	gcc -Wall -Wextra $< -o $@

clean:
	rm -f gpioset