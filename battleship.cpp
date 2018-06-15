/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

CellContent my_field[FIELDSIZE][FIELDSIZE];
CellContent opposite_field[FIELDSIZE][FIELDSIZE];
CellContent guesses[FIELDSIZE][FIELDSIZE];

void load_game(){
  FILE* my_fd = fopen("battleship.my", "r");
  FILE* opposit_fd = fopen("battleship.op", "r");
  for(int i = 0; i < FIELDSIZE; i++){
    for(int a = 0; a < FIELDSIZE; a++){
      fread(&my_field[a][i], 4, 1, my_fd);
        fread(&opposite_field[a][i], 4, 1, opposit_fd);
      guesses[a][i] = Unknown;
    }
  }
  fclose(opposit_fd);
  fclose(my_fd);
}
/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col){
  if(row < 0 || col < 0 || row == FIELDSIZE || col == FIELDSIZE){return OutOfRange;}
  return my_field[col][row];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if(get_shot(row, col) != OutOfRange){
    guesses[col][row] = opposite_field[col][row];
    for (int i = -1; i < 2; i++) {
      for (int a = -1; a < 2; a++) {
        if(get_my_guess(row+a, col+i) == Unknown){
          guesses[col+i][row+a] = Water;
        }
      }
    }
    return true;
  }
  return false;
}
/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col){
  if(row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE){return OutOfRange;}
  return guesses[col][row];
}
