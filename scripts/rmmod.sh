#!/bin/bash

set -x

module="GPIO_driver"
device="GPIO_dev"

rm -f /dev/$module

rmmod $module