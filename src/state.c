#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

/* Task 1 */
game_state_t* create_default_state() {
 
  game_state_t* game = malloc(sizeof(game_state_t));
  game->board = malloc(18 * sizeof(char*));
  game->snakes = malloc(sizeof(snake_t));
  game->num_rows = 18;
  game->num_snakes = 1;

  game->snakes->head_row = 2;
  game->snakes->head_col = 4;
  game->snakes->tail_row = 2;
  game->snakes->tail_col = 2;
  game->snakes->live = true;


  for(int i = 0; i < 18; i++){
    game->board[i] = malloc(21 * sizeof(char));
    strcpy(game->board[i],"                    ");
    if(i == 0 || i == 17){
      strcpy(game->board[i],"####################");
    }
    else if(i == 2){
        strcpy(game->board[i],"# d>D    *         #");
    }
    else{
      strcpy(game->board[i],"#                  #");                
    }
  }

  return game;
}

/* Task 2 */
void free_state(game_state_t* state) {
  for(int i = 0; i < state->num_rows; i++){
    free(state->board[i]);
  }
  free(state->board);
  free(state->snakes);
  free(state);
  //printf("%s\n", "hello5");
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  for(int i = 0; i < state->num_rows; i++){
      fprintf(fp, "%s\n", state->board[i]);
    }
        //printf("%s\n", "hello4");
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  const char* snake_chars = "wasd";
  if (strchr(snake_chars, c)) {
    return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  const char* snake_chars = "WASDx";
  if (strchr(snake_chars, c)) {
    return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  const char* snake_chars = "wasd^<v>WASDx";
  if (strchr(snake_chars, c)) {
    return true;
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  switch(c){
    case '^':
      return 'w';
      break;
    case '<':
      return 'a';
      break;
    case 'v':
      return 's';
      break;
    case '>':
      return 'd';
      break;
    default:
      return '?';
  }
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  switch(c){
    case 'W':
      return '^';
      break;
    case 'A':
      return '<';
      break;
    case 'S':
      return 'v';
      break;
    case 'D':
      return '>';
      break;
    default:
      return '?';
  }
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  if(c == 'v'|| c == 's' || c =='S'){
    return cur_row + 1;
  }
  else if(c == '^' || c == 'w' || c == 'W'){
    return cur_row - 1;
  }
  else {
    return cur_row;
  }
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  if(c == '>' || c == 'd' || c== 'D'){
    return cur_col + 1;
  }
  else if(c == '<' || c == 'a' || c == 'A'){
    return cur_col - 1;
  }
  else{
    return cur_col;
  }
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  unsigned int head_row = state->snakes[snum].head_row;
  unsigned int head_col = state->snakes[snum].head_col;

  char head_pos = get_board_at(state, head_row, head_col);
  if(head_pos == 'W'){
    return get_board_at(state, head_row - 1, head_col);
  }
  else if(head_pos == 'S'){
    return get_board_at(state, head_row + 1, head_col);
  }
  else if(head_pos == 'A'){
    return get_board_at(state, head_row, head_col - 1);
  }
  else if(head_pos == 'D'){
    return get_board_at(state, head_row, head_col + 1);
  }
  return ' ';
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  unsigned int head_row = state->snakes[snum].head_row;
  unsigned int head_col = state->snakes[snum].head_col;

  char head_pos = get_board_at(state, head_row, head_col);
  if(head_pos == 'W'){
    state->snakes[snum].head_row = head_row - 1;
    set_board_at(state, head_row, head_col, '^');
    set_board_at(state, head_row - 1, head_col, 'W');
  }
  else if(head_pos == 'S'){
    state->snakes[snum].head_row = head_row + 1;
    set_board_at(state, head_row, head_col, 'v');
    set_board_at(state, head_row + 1, head_col, 'S');
  }
  else if(head_pos == 'A'){
    state->snakes[snum].head_col = head_col - 1;
    set_board_at(state, head_row, head_col, '<');
    set_board_at(state, head_row, head_col - 1, 'A');
  }
  else if(head_pos == 'D'){
    state->snakes[snum].head_col = head_col + 1;
    set_board_at(state, head_row, head_col, '>');
    set_board_at(state, head_row, head_col + 1, 'D');
  }
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
    unsigned int tail_row = state->snakes[snum].tail_row;
    unsigned int tail_col = state->snakes[snum].tail_col;
    char tail_dir = get_board_at(state, tail_row, tail_col);

    // Blank out the current tail
    set_board_at(state, tail_row, tail_col, ' ');

    // Determine the new tail position based on its current direction
    switch(tail_dir) {
        case 'w':
            tail_row--;
            break;
        case 'a':
            tail_col--;
            break;
        case 's':
            tail_row++;
            break;
        case 'd':
            tail_col++;
            break;
    }

    // Get the character at the new tail position (should be a body character)
    char new_tail_pos = get_board_at(state, tail_row, tail_col);

    // Convert body character into corresponding tail character and update on the board
    char new_tail_dir;
    switch(new_tail_pos) {
        case '^':
            new_tail_dir = 'w';
            break;
        case '<':
            new_tail_dir = 'a';
            break;
        case 'v':
            new_tail_dir = 's';
            break;
        case '>':
            new_tail_dir = 'd';
            break;
        default:
            // Handle unexpected characters
            new_tail_dir = ' ';
            break;
    }
    set_board_at(state, tail_row, tail_col, new_tail_dir);

    // Update the tail position in the snake struct
    state->snakes[snum].tail_row = tail_row;
    state->snakes[snum].tail_col = tail_col;

}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  for(unsigned int snum = 0; snum < state->num_snakes; snum++){
    if(state->snakes[snum].live == true){
      unsigned int head_row = state->snakes[snum].head_row;
      unsigned int head_col = state->snakes[snum].head_col;

      char next_char = next_square(state,snum);
      // Head crashes into wall or body of another snake
      if(next_char == '#' || is_snake(next_char)){
        set_board_at(state, head_row, head_col, 'x');
        state->snakes[snum].live = false;
      }
      //Head moves into a fruit
      else if(next_char == '*'){
        update_head(state, snum);
        int add_result = add_food(state); // Add food when the snake eats a fruit
        if (add_result == 0) {
          printf("Food added successfully!\n");
        } else {
          printf("Failed to add food. Error code: %d\n", add_result);
        }
      }
      else {
        // The snake is just moving, update both its head and tail
        update_head(state, snum);
        update_tail(state, snum);
      }
    }
  }
  //printf("%s\n", "hello3");
}

/* Task 5 */
game_state_t* load_board(FILE* fp) {
    game_state_t* state = malloc(sizeof(game_state_t));
    if (state == NULL) {
        return NULL; 
    }
    state->num_snakes = 0;
    state->snakes = NULL;
  
    state->board = NULL;
    state->num_rows = 0;

    int ch;
    unsigned int num_cols = 0;
    unsigned int capacity = 1;  
    char* row = malloc(capacity * sizeof(char));  // pointer to the current row
    if (row == NULL) {
        free(state);
        return NULL;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') { // If character reaches the end of current line
            row[num_cols] = '\0'; 
            state->num_rows++;
            state->board = realloc(state->board, state->num_rows * sizeof(char*));
            if (state->board == NULL) {
                free(row); 
                return NULL; 
            }
            state->board[state->num_rows - 1] = row;
            num_cols = 0;
            capacity = 1;
            row = malloc(capacity * sizeof(char));  // Reallocate memory for next row
            if (row == NULL) { // If failed to allocate memory for next row
                for (unsigned int i = 0; i < state->num_rows; i++) {
                    free(state->board[i]);
                }
                free(state->board);
                free(state);
                return NULL;
            }
        } else {
            // If character within the current line
            if (num_cols >= capacity) {
                capacity = capacity * 2 + 1;
                row = realloc(row, (capacity + 1) * sizeof(char)); 
                if (row == NULL) { 
                    for (unsigned int i = 0; i < state->num_rows; i++) {
                        free(state->board[i]);
                    }
                    free(state->board);
                    free(state);
                    return NULL;
                }
            }
            row[num_cols] = (char)ch;
            num_cols++;
        }
    }

    //printf("%s\n", "hello1");
    return state;
}



/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  unsigned int row = state->snakes[snum].tail_row;
  unsigned int col = state->snakes[snum].tail_col;
  char current_char = get_board_at(state, row, col);

  while(!is_head(current_char)){
    if(get_next_row(row, current_char) != row){
      row = get_next_row(row, current_char);
    }
    else{
      col = get_next_col(col, current_char);
    }
    current_char = get_board_at(state, row, col);
  }

  state->snakes[snum].head_row = row;
  state->snakes[snum].head_col = col;

}


/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // Count the number of snake heads on the board
  unsigned int num_snakes = 0;
  for (unsigned int row = 0; row < state->num_rows; row++) {
    for (unsigned int col = 0; col < strlen(state->board[row]); col++) {
      if (is_head(state->board[row][col])) {
        num_snakes++;
      }
    }
  }

  // Allocate memory for the snakes array
  state->num_snakes = num_snakes;
  state->snakes = (snake_t*) malloc(num_snakes * sizeof(snake_t));
  if (state->snakes == NULL) {
    return NULL;
  }

  // Initialize each snake
  unsigned int snake_index = 0;
  for (unsigned int row = 0; row < state->num_rows; row++) {
    for (unsigned int col = 0; col < strlen(state->board[row]); col++) {
      if (is_tail(state->board[row][col])) {
        state->snakes[snake_index].tail_row = row;
        state->snakes[snake_index].tail_col = col;
        find_head(state, snake_index);
        state->snakes[snake_index].live = true;

        snake_index++;
      }
    }
  }
  //printf("%s\n", "hello2");
  return state;
}

