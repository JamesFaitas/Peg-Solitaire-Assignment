/* 
 * File:   main.c
 * Author: marwan
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "my_strings.h"
#include "my_pyramid_game.h"
#include "pyramid_helpers.h"


/*
 * 
 */
int main(int argc, char** argv)
{
   if (argc != 2) {
      fprintf(stderr, "Usage: %s [s|p|f]\n"
                      "  where:\n "
                      "    s - executes your string test (Task 1)\n "
                      "    p - executes the *interactive* pyramid game\n "
                      "    f - executes the file-input pyramid game\n "
                      "        (Note that file must be \"text_input.txt\")\n",
              argv[0]);
      exit(EXIT_FAILURE);
   }

   switch (argv[1][0]) {
      case 's':
         printf("You asked for string routines to be tested.\n");
         main_strings();
         break;
      case 'p':
         printf("You asked for the *interactive* pyramid game!\n");
         main_pyramid();
         break;
      case 'f':
         printf("You asked for file_input version of the pyramid game.\n");
         freopen("test_input.txt", "r", stdin);
         set_quiet(true);
         main_pyramid();
         break;
      default:
         ;
   }

   return (EXIT_SUCCESS);
}