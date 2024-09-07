/* 
    Same as gpioset.c but directly using libgpiod instead of forking and using gpioset
*/

#include <unistd.h>
#include <gpiod.h>

#define GPIO_BANK "/dev/gpiochip0"
#define GPIO_LINE 5

#define DELAY_S 1

int main(){

    struct gpiod_chip *chip = gpiod_chip_open(GPIO_BANK);
    struct gpiod_line *line = gpiod_chip_get_line(chip, GPIO_LINE);
    gpiod_line_request_output(line, "test", 0);

    for(;;){
        gpiod_line_set_value(line, 1);
        sleep(DELAY_S);
        gpiod_line_set_value(line, 0);
        sleep(DELAY_S);
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}