// test.c for lab6 by Joseph Schechter

#include <stdio.h>

#include "show.h"

int main() {
  int size = 0;
  char buffer[] = "Hello World";
  printf("You entered: ");
  size = show_string(buffer);
  printf("\nSize: %d\n", size);

  char buffer2[] = "Zip 123 @#.} fL09PeIoU";
  printf("You entered: ");
  size = show_string(buffer2);
  printf("\nSize: %d\n", size);
  
  char buffer3[] = "tEstIng AeIoUaEiOu";
  printf("You entered: ");
  size = show_string(buffer3);
  printf("\nSize: %d\n", size);
  
  char buffer4[] = "1234567890-_+=/|?.,";
  printf("You entered: ");
  size = show_string(buffer4);
  printf("\nSize: %d\n", size);
  
  char buffer5[] = "This is Joseph Schechter's Lab6 test.c file for cs220";
  printf("You entered: ");
  size = show_string(buffer5);
  printf("\nSize: %d\n", size);

  return 0;
  }
