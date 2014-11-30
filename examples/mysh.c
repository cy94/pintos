// mysh.c
// a command line terminal for PintOS

#include <stdio.h>
#include <syscall.h>

static void read_line (char line[], size_t);
static bool backspace (char **pos, char line[]);


int
main (int argc, char **argv)
{
  char command[20];

  printf("Starting PintOS shell\n");

  for(;;) {
	  printf("\nuser@pintos$ ");
	  read_line (command, 20);
	  printf("\nExecuting %s\n", command);

	  int pid = exec(command);
	  printf("%s: exit with status %d\n", command, pid);

  }
  return EXIT_SUCCESS;
}

static void
read_line (char line[], size_t size)
{
  char *pos = line;
  int val;
  char c, d;

  for (;;)
    {
      c = (char) read (STDIN_FILENO, &d, 1);
      val = (int) c;

      if(val == 13)
        return;
	
      switch (c)
        {
	/*
        case '\r':
          *pos = '\0';
          return;

        case '\b':
          backspace (&pos, line);
          break;

        case ('U' - 'A') + 1:       
          while (backspace (&pos, line))
            continue;
          break;
        */
        default:
          /* Add character to line. */
          if (pos < line + size - 1)
            {
	      //putchar((char) val);
              *pos++ = c;
            }
	  /*
	  else
	    {
		return;
	    }
	  */
          break;
        }
    }
}

static bool
backspace (char **pos, char line[])
{
  if (*pos > line)
    {
      /* Back up cursor, overwrite character, back up
         again. */
      printf ("\b \b");
      (*pos)--;
      return true;
    }
  else
    return false;
}

                    
