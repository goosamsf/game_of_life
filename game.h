
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wchar.h>
#include <omp.h>

#define INIT_ALIVE 100
#define NUMROW 1000
#define NUMCOL 1000 
#define GHOST 2

#define ALIVE 0x25A0
#define DEAD 0x25A1

void print_grid(wchar_t grid[NUMROW + GHOST][NUMCOL + GHOST]);
void place_alive_cell();
void serial_method();
void place_ghost_cell(wchar_t lc[NUMROW+GHOST][NUMCOL+GHOST]);
wchar_t alive_or_dead(wchar_t lc[NUMROW+GHOST][NUMCOL+GHOST], int r, int c);
void parallel_method();
