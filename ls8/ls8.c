#include <stdio.h>
#include "cpu.h"
#include <stdlib.h>

/**
 * Main
 */
int main(int argc, char **argv)
// int main(int arc, char *argv[]) // This is the same thing as above.
// argc is the number of arguments the user has typed on the command line
// argv is an array of strings. One for each argument.
{
  printf("\n");
  printf("** argc: %d **\n", argc);
  struct cpu cpu;

  if (argc != 2) // This will check to make sure the user typed the correct things
    {
        printf("\n"); // If the user hasn't typed the correct things this tells them how to use it.
        fprintf(stderr, "** You must include the correct number of args! Please provide the name of the file you would like to run. **\n");
        printf("\n");
        exit(1); // And then quit.
    }

  cpu_init(&cpu);
  cpu_load(&cpu, argv[1]);
  cpu_run(&cpu);

  return 0;
}