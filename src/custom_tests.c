#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) {
  return x > 42;
}

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

/*
    Returns true if all test cases pass. False otherwise.
    The function is_tail(char c) will return true if c is a tail (i.e. c is w,a,s,d)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_tail() {
  char testcase_1 = 'w';
  bool output_1 = is_tail(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'a';
  bool output_2 = is_tail(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }
  
  char testcase_3 = 's';
  bool output_3 = is_tail(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'd';
  bool output_4 = is_tail(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'k';
  bool output_5 = is_tail(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  return true;
}

/*
    Returns true if all test cases pass. False otherwise.
    The function is_head(char c) will return true if c is a head (i.e. c is W,A,S,D,x)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_head() {
  char testcase_1 = 'W';
  bool output_1 = is_head(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'A';
  bool output_2 = is_head(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }
  
  char testcase_3 = 'S';
  bool output_3 = is_head(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'D';
  bool output_4 = is_head(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'x';
  bool output_5 = is_head(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'Q';
  bool output_6 = is_head(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}


/*
    Returns true if all test cases pass. False otherwise.
    The function is_snake(char c) will return true if c is part of the snake (i.e. c is a,w,s,d,^,<,v,>,W,A,S,D,x)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_snake() {
  char testcase_1 = 'w';
  bool output_1 = is_snake(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'a';
  bool output_2 = is_snake(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }
  
  char testcase_3 = 's';
  bool output_3 = is_snake(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'd';
  bool output_4 = is_snake(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'W';
  bool output_5 = is_snake(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'A';
  bool output_6 = is_snake(testcase_6);
  if (!assert_true("output_6", output_6)) {
    return false;
  }
  
  char testcase_7 = 'S';
  bool output_7 = is_snake(testcase_7);
  if (!assert_true("output_7", output_7)) {
    return false;
  }

  char testcase_8 = 'D';
  bool output_8 = is_snake(testcase_8);
  if (!assert_true("output_8", output_8)) {
    return false;
  }

  char testcase_9 = 'x';
  bool output_9 = is_snake(testcase_9);
  if (!assert_true("output_9", output_9)) {
    return false;
  }

  char testcase_10 = '^';
  bool output_10 = is_snake(testcase_10);
  if (!assert_true("output_10", output_10)) {
    return false;
  }

  char testcase_11 = '<';
  bool output_11 = is_snake(testcase_11);
  if (!assert_true("output_11", output_11)) {
    return false;
  }
  
  char testcase_12 = 'v';
  bool output_12 = is_snake(testcase_12);
  if (!assert_true("output_12", output_12)) {
    return false;
  }

  char testcase_13 = '>';
  bool output_13 = is_snake(testcase_13);
  if (!assert_true("output_13", output_13)) {
    return false;
  }

  char testcase_14 = 'B';
  bool output_14 = is_snake(testcase_14);
  if (!assert_false("output_14", output_14)) {
    return false;
  }

  char testcase_15 = '&';
  bool output_15 = is_snake(testcase_15);
  if (!assert_false("output_15", output_15)) {
    return false;
  }

  char testcase_16 = 'p';
  bool output_16 = is_snake(testcase_16);
  if (!assert_false("output_16", output_16)) {
    return false;
  }

  return true;
}


/*
    Returns true if all test cases pass. False otherwise.
    The function body_to_tail(char c) will return the matching tail character
    corresponding to the provided body character.
    Note: This test is NOT comprehensive
*/
bool test_body_to_tail() {
  char testcase_1 = '^';
  char output_1 = body_to_tail(testcase_1);
  if (output_1 != 'w') {
    return false;
  }

  char testcase_2 = '<';
  char output_2 = body_to_tail(testcase_2);
  if (output_2 != 'a') {
    return false;
  }

  char testcase_3 = 'v';
  char output_3 = body_to_tail(testcase_3);
  if (output_3 != 's') {
    return false;
  }

  char testcase_4 = '>';
  char output_4 = body_to_tail(testcase_4);
  if (output_4 != 'd') {
    return false;
  }

  char testcase_5 = '*';  // A non-matching character
  char output_5 = body_to_tail(testcase_5);
  if (output_5 != '?') {
    return false;
  }

  return true;
}


/*
    Returns true if all test cases pass. False otherwise.
    The function head_to_body(char c) will return the matching body character
    corresponding to the provided head character.
    Note: This test is NOT comprehensive
*/
bool test_head_to_body() {
  char testcase_1 = 'W';
  char output_1 = head_to_body(testcase_1);
  if (output_1 != '^') {
    return false;
  }

  char testcase_2 = 'A';
  char output_2 = head_to_body(testcase_2);
  if (output_2 != '<') {
    return false;
  }

  char testcase_3 = 'S';
  char output_3 = head_to_body(testcase_3);
  if (output_3 != 'v') {
    return false;
  }

  char testcase_4 = 'D';
  char output_4 = head_to_body(testcase_4);
  if (output_4 != '>') {
    return false;
  }

  char testcase_5 = 'K';  // A non-matching character
  char output_5 = head_to_body(testcase_5);
  if (output_5 != '?') {
    return false;
  }

  return true;
}


/*
    Returns true if all test cases pass. False otherwise.
    The function get_next_row(unsigned int cur_row, char c) will return true 
    if function return cur_row + 1 if c is 'v' or 's' or 'S'
    if function return cur_row - 1 if c is '^' or 'w' or 'W'
    if function return cur_row otherwise, 
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_get_next_row() {
  unsigned int cur_row = 5;  // Arbitrary starting row
  unsigned int expected, actual;

  expected = cur_row + 1;
  actual = get_next_row(cur_row, 'v');
  if (actual != expected) {
    return false;
  }

  expected = cur_row + 1;
  actual = get_next_row(cur_row, 's');
  if (actual != expected) {
    return false;
  }

  expected = cur_row + 1;
  actual = get_next_row(cur_row, 'S');
  if (actual != expected) {
    return false;
  }

  expected = cur_row - 1;
  actual = get_next_row(cur_row, '^');
  if (actual != expected) {
    return false;
  }

  expected = cur_row - 1;
  actual = get_next_row(cur_row, 'w');
  if (actual != expected) {
    return false;
  }

  expected = cur_row - 1;
  actual = get_next_row(cur_row, 'W');
  if (actual != expected) {
    return false;
  }

  // Any other character
  char other_char = 'x';  // Arbitrarily chosen non-special character
  expected = cur_row;
  actual = get_next_row(cur_row, other_char);
  if (actual != expected) {
    return false;
  }

  return true;
}

/*
    Returns true if all test cases pass. False otherwise.
    The function get_next_col(unsigned int cur_col, char c) will return true 
    if function return cur_col + 1 if c is '>' or 'd' or 'D'
    if function return cur_col - 1 if c is '<' or 'a' or 'A'
    if function return cur_col otherwise, 
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_get_next_col() {
  unsigned int cur_col = 5;  // Arbitrary starting column
  unsigned int expected, actual;

  expected = cur_col + 1;
  actual = get_next_col(cur_col, '>');
  if (actual != expected) {
    return false;
  }

  expected = cur_col + 1;
  actual = get_next_col(cur_col, 'd');
  if (actual != expected) {
    return false;
  }

  expected = cur_col + 1;
  actual = get_next_col(cur_col, 'D');
  if (actual != expected) {
    return false;
  }

  expected = cur_col - 1;
  actual = get_next_col(cur_col, '<');
  if (actual != expected) {
    return false;
  }

  expected = cur_col - 1;
  actual = get_next_col(cur_col, 'a');
  if (actual != expected) {
    return false;
  }

  expected = cur_col - 1;
  actual = get_next_col(cur_col, 'A');
  if (actual != expected) {
    return false;
  }

  // Any other character
  char other_char = 'x';  // Arbitrarily chosen non-special character
  expected = cur_col;
  actual = get_next_col(cur_col, other_char);
  if (actual != expected) {
    return false;
  }

  return true;
}


bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
