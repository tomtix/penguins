#ifndef D3_H
#define D3_H

#include <utils/vec.h>
#include <d3v/user_callback.h>
#include <utils/symbol_visibility.h>

int d3v_init(int) __export ;
int d3v_start(vec3 *pos) __export ;
int d3v_exit(void) __export ;

void d3v_post_redisplay(void);
void d3v_exit_main_loop(void);

#endif //D3_H
