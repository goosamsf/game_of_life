#include "game.h"

wchar_t cellular[NUMROW + GHOST][NUMCOL + GHOST];
int leftrow_output = 2;
std::vector<std::vector<int>> directions = { {0,1}, {1,0}, {0,-1},{-1,0}, {1,1}, {-1,-1} , {1,-1}, {-1,1}};
WINDOW *prompt_win;
WINDOW *left_win;
WINDOW *right_win;

int main(int argc, char* argv[]){
  bool parallel;
  if (argc == 1){
    parallel = false;
  }else {
    parallel = true;
  }

  setlocale(LC_ALL, "");
  initscr();
  
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  wbkgd(left_win, COLOR_PAIR(1));

  border('|', '|', '-', '-', '+', '+', '+', '+');
  refresh();
  
  if((left_win = newwin(LINES-3,COLS/4 , 1, 3)) == NULL){
    perror("newwin");
    exit(EXIT_FAILURE);
  }
  if((right_win = newwin(LINES-3,COLS/2-10 + COLS/4, 1, COLS/2- COLS/5)) == NULL){
    perror("newwin");
    exit(EXIT_FAILURE);
  }
  if(!parallel) {
    mvwprintw(left_win, leftrow_output++, 1, "This is Serial Code");
  }else {
    mvwprintw(left_win, leftrow_output++, 1, "This is Parallel Code");
  }

  /* Initialize ALIVE CELLS according to INIT_ALIVE */
  place_alive_cell();
  place_ghost_cell(cellular);
  
  refresh();

  box(left_win, 0, 0);
  wrefresh(left_win);
  while(1){
   if(parallel) 
     parallel_method();
   else
     serial_method();
  }

  endwin();
  return 0;
}

void serial_method(){
  double start_time, end_time;
  wchar_t local_cellular[NUMROW+GHOST][NUMCOL + GHOST];
  wchar_t result_cellular[NUMROW+GHOST][NUMCOL + GHOST];
  wchar_t rval;
  memcpy(local_cellular, cellular, sizeof(local_cellular));
  start_time = omp_get_wtime();
    for(int i = 1; i <= NUMROW; i++){
      for (int j = 1; j <= NUMCOL; j++){
        rval = alive_or_dead(local_cellular, i, j);
        result_cellular[i][j] = rval; 
      }
    }
    end_time = omp_get_wtime();
    mvwprintw(left_win, leftrow_output++, 1, "Elapsed : %lf seconds", end_time-start_time);
    wrefresh(left_win);

    place_ghost_cell(result_cellular);
    print_grid(result_cellular);
    memcpy(cellular, result_cellular, sizeof(result_cellular));
}

void parallel_method(){
  double start_time, end_time;
  wchar_t local_cellular[NUMROW+GHOST][NUMCOL + GHOST];
  wchar_t result_cellular[NUMROW+GHOST][NUMCOL + GHOST];
  wchar_t rval;
  memcpy(local_cellular, cellular, sizeof(local_cellular));
  start_time = omp_get_wtime();
  #pragma omp parallel for
    for(int i = 1; i <= NUMROW; i++){
      for (int j = 1; j <= NUMCOL; j++){
        rval = alive_or_dead(local_cellular, i, j);
        result_cellular[i][j] = rval; 
      }
    }
    
    end_time = omp_get_wtime();
    mvwprintw(left_win, leftrow_output++, 1, "Elapsed : %lf seconds", end_time-start_time);
    wrefresh(left_win);

    place_ghost_cell(result_cellular);
    print_grid(result_cellular);
    memcpy(cellular, result_cellular, sizeof(result_cellular));
}

wchar_t alive_or_dead(wchar_t lc[NUMROW+GHOST][NUMCOL+GHOST], int r, int c){
  wchar_t curr = lc[r][c];
  int alive_count = 0; 
  if(curr == DEAD){
    /* currently dead */
    for(auto i : directions){
      /* directions vector is globally defined */
      int cr = i[0];
      int cc = i[1];
      if(lc[r+cr][c +cc] == ALIVE){
        //if neighbor is alive
        alive_count++;
      }
    }
    if(alive_count == 3){
      return ALIVE;
    }else{
      return DEAD;
    }
  }else{
    /* currently alive */
    for(auto i : directions){
      int cr = i[0];
      int cc = i[1];
      if(lc[r + cr][c+ cc] == ALIVE){
        /* if neighbor is alive */
        alive_count++;
      }
    }
    if(alive_count == 2 || alive_count == 3){
      return ALIVE;
    }else{
      return DEAD;
    }
  }
}

void place_ghost_cell(wchar_t lc[NUMROW+GHOST][NUMCOL+GHOST]){
  /* get ghost cell from lc */
  lc[0][0] = cellular[NUMROW][NUMCOL];
  lc[NUMROW+1][NUMCOL+1] = cellular[1][1];
  lc[0][NUMCOL + 1] = cellular[NUMROW][1];
  lc[NUMROW+1][0] = cellular[1][NUMCOL];
  for(int i = 1; i<= NUMCOL; i++){
    lc[0][i] = cellular[NUMROW][i];
    lc[NUMROW + GHOST -1][i] = cellular[1][i];
  }
  for(int i = 1; i<= NUMROW; i++){
    lc[i][0] = cellular[i][NUMCOL];
    lc[i][NUMCOL+GHOST -1] = cellular[i][1];
  }
}

void place_alive_cell(){
  int rannum;
  int i = 0;
  srand(time(NULL));
  for (int row = 0; row < NUMROW + GHOST; row++){
    for(int col = 0; col < NUMCOL + GHOST; col++){
      cellular[row][col] = DEAD;
    }
  }
  while(i < INIT_ALIVE){
    /* Place ALIVE element per row */
    /* if INIT_ALIVE = 3 , place 3ALIVE element per row */
    for(int i = 1; i < NUMROW + GHOST -1; i ++){
      rannum = (rand() % (NUMCOL-2) + 1);
      cellular[i][rannum] = ALIVE;  
    }
    i++;
  }
}

void print_grid(wchar_t grid[NUMROW + GHOST][NUMCOL + GHOST]){
  int i,j;
  wchar_t row[NUMROW*2+1];
  row[0] = (wchar_t)' '; 
  for(i = 1; i < NUMROW+GHOST-1; i++){
    for(j = 1; j < NUMCOL+GHOST-1; j++){
      row[j*2-1] = grid[i][j];
      row[j*2] = (wchar_t)' ';
    }
    mvwaddnwstr(right_win, i, 0, row, NUMROW*2+1);
  }
  wrefresh(right_win);

  sleep(1);
  return;
}







