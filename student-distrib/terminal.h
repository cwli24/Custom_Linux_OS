#ifndef TERMINAL_H
#define TERMINAL_H

#include "driver.h"
#include "keyboard.h"

extern int32_t terminal_open(const uint8_t* filename);
extern int32_t terminal_close(int32_t fd);
extern int32_t terminal_read(int32_t fd, void *buf, int32_t nbytes);
extern int32_t terminal_write(int32_t fd, const void *buf, int32_t nbytes);

extern struct f_ops_table stdin;
extern struct f_ops_table stdout;

#endif
