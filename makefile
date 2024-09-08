ATI_DRIVER_NAME:=GPIO_driver
ATI_KERNEL_DEVEL_DIR:=/lib/modules/$(shell uname -r)

ATI_MODULE_SRC:=$(wildcard src/*.c)
ATI_MODULE_SRC:=$(ATI_MODULE_SRC:src/%.c=out/%.c)

ATI_MODULE_OBJ:=$(ATI_MODULE_SRC:out/%.c=%.o)

out/%.c:src/%.c
	rm -f $@
	ln -s ../$< $@

module: $(ATI_MODULE_SRC)
	echo "obj-m += $(ATI_DRIVER_NAME).o\n$(ATI_DRIVER_NAME)-y += $(ATI_MODULE_OBJ)\n" > out/Makefile
	make -C $(ATI_KERNEL_DEVEL_DIR)/build M=$(PWD)/out modules

gpioset: examples/gpioset.c
	gcc -Wall -Wextra $< -o $@

libgpiod: examples/libgpiod.c
	gcc -g -Wall -Wextra $< -o $@ -lgpiod

clean:
	rm -f gpioset libgpiod
	rm -rf out/* out/.[!.]* out/..?*