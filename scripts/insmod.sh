#!/bin/bash

set -x

module="GPIO_driver"
device="GPIO_dev"

rmmod $module
insmod ../out/$module.ko $* || exit 1

rm -f /dev/${device}

major=$(awk '/'$device'/ {print $1}' /proc/devices)

mknod /dev/${device} c $major 0

chmod 666 /dev/${device}