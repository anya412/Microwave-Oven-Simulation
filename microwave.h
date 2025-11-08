/* 
 * File:   microwave.h
 */

#ifndef MICROWAVE_H
#define MICROWAVE_H

void power_on_screen(void);
void clear_screen(void);
void display_menu_screen(void);
void set_time(unsigned char key,unsigned char reset_flag);
void time_display(void);
void set_temp(unsigned char key,unsigned char reset_flag);
void heat_food(void);

#endif

