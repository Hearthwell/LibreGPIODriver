gpioset: examples/gpioset.c
	gcc -Wall -Wextra $< -o $@

libgpiod: examples/libgpiod.c
	gcc -g -Wall -Wextra $< -o $@ -lgpiod

clean:
	rm -f gpioset libgpiod