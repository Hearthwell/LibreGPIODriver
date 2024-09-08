# LibreGPIODriver

### GPIO Control Research on the Libre Computer Board (S950), How to interract with the GPIO and Basic Kernel Module Implementation.

## Build
### Make sure you have your kernel development headers and build files installed
```
mkdir out
make

# Insert module and make entry in /dev
cd scripts
sudo ./insmod.sh
```

## RoadMap
- [X] Example on gpioset Usage
- [X] Example on libgpiod Usage
- [ ] Example on gpio control using ioctl on the gpiochipX character device
- [ ] Implement Custom GPIO Kernel Driver
- [ ] Example on Custom driver usage from user space