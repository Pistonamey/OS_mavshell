/*
    Name: Amey Shinde
    ID: 1001844387

    Comments for Grader - Code used is from msh.c and execl.c on professor's 
                          gihub repo. 
                          'a' used instead of 'i' and 'j' as loop variable 
                          because acc to prof, i and j are used for complex numbers
                          Minimzed comments from msh.c
                          history gives funny output for execl commands


*/



#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define WHITESPACE " \t\n"   //whitespace will be used as tokens

#define MAX_COMMAND_SIZE 255    

#define MAX_NUM_ARGUMENTS 11    // Mav shell only supports 10 arguments

#define MAXIMUM 15          // Maximum number of previous commands (HISTORY) to be recorded
                            // or PIDS to be displayed


int main(int argc, char **argv)
{

  char * command_string = (char*) malloc( MAX_COMMAND_SIZE );

  // command 'history' records
  // MAXIMUM is highest number of previous commands
  // that can be recorded and displayed/accessed
  char *history[MAXIMUM];

  //array of PIDS
  pid_t listpids[MAXIMUM];

  // locations that shell can access and execute the commands in,
  // according to the assignment description
  // (CONST used because the pointer array need not be changed)
  // "./" used for current location
  // "~" used for home/previous location
  const char *folders[] = {"./", "/usr/local/bin/", "~", "/usr/bin/", "..","/bin/"};


  // variable to keep track of command that executed
  int cnt = 0;

  // pid for forking
  pid_t pid;

  //always start with true
  while(1)
  {
    printf ("msh> ");

    //User gives the input, gets stored in command string
    while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );

    //store command
    char *token[MAX_NUM_ARGUMENTS];

    //pointer for command/token
    char *argument_pointer;

    //duplicate the command
    char *working_string  = strdup( command_string );

    //pointer to working string, for memory allocation
    char *head_ptr = working_string;

    //counter the number of executions
    int   token_count = 0;

    // seperate the string with whitespace used as token
    while ( ( (argument_pointer = strsep(&working_string, WHITESPACE ) ) != NULL) &&
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_pointer, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    if((strcmp("!1", token[0])==0) || (strcmp("!2", token[0])==0) || 
       (strcmp("!3", token[0])==0) || (strcmp("!4", token[0])==0) || (strcmp("!5", token[0])==0) 
       || (strcmp("!6", token[0])==0) || (strcmp("!7", token[0])==0) 
       || (strcmp("!8", token[0])==0) || (strcmp("!9", token[0])==0) || (strcmp("!10", token[0])==0)
       || (strcmp("!11", token[0])==0) || (strcmp("!12", token[0])==0) || (strcmp("!13", token[0])==0) 
       || (strcmp("!14", token[0])==0) || (strcmp("!15", token[0])==0) )
    {
      //unable to figure out because I did not use functions for commands :(
    }
    //'history' command displays the last commands < MAX_HISTORY
    //check if token is history and proceed
    if( strcmp("history", token[0]) == 0 )
    {
      //variables used for the loop
      int max_history;
      int a;
      

      // find last value of the number of Histories to be shown
      // initialised to cnt, but if > than MAX_HISTORY
      // max_history=MAX_HISTORY 
      max_history = cnt;
      if( max_history > MAXIMUM )
      {
        max_history = MAXIMUM;
      }
      
      // loop displays the list of commands recorded
      for( a = 0; a < max_history; a++ )
      {
        printf( "%d: %s\n" , a , history[a] );
      }
      history[cnt]=token[0];
    }

    // !n command for executing the desired command in the HISTORY LIST
    if((strcmp("!1", token[0])==0) || (strcmp("!2", token[0])==0) || 
       (strcmp("!3", token[0])==0) || (strcmp("!4", token[0])==0) || (strcmp("!5", token[0])==0) 
       || (strcmp("!6", token[0])==0) || (strcmp("!7", token[0])==0) 
       || (strcmp("!8", token[0])==0) || (strcmp("!9", token[0])==0) || (strcmp("!10", token[0])==0)
       || (strcmp("!11", token[0])==0) || (strcmp("!12", token[0])==0) || (strcmp("!13", token[0])==0) 
       || (strcmp("!14", token[0])==0) || (strcmp("!15", token[0])==0) )
    {
      //unable to figure out because I did not use functions for commands :(
    }

    // Do nothing when user does give input and presses enter
    if( token[0] == NULL )
    {
    }
    // 'cd token[1]' will check if directory/location parsed in exists
    //and change current directory/location if true
    if( (strcmp( "cd", token[0]) == 0) && token[1] != NULL)
    {
      // if location does not exist
      if(chdir(token[1]) == -1)
      {
        printf("%s: File or directory/location does not exist\n" , token[1] );
        
       
      }
      history[cnt]=token[0];
    }
    
    // 'listpids' command displays the PIDS of last 15 commands
    if( strcmp("listpids", token[0]) == 0 )
    {
      //variables used for the loop
      int m_pid;
      int a;
      
      // find last value of the number of PIDS to be shown
      // initialised to cnt, but if > than MAX_HISTORY
      // m_pid=MAX_PIDS
      m_pid = cnt;
      if( m_pid > MAXIMUM )
      {
        m_pid = MAXIMUM;
      }

      // loop displays the PIDs
      for( a = 0; a < m_pid; a++ )
      {
        printf( "%d: %d\n" , a , listpids[a] );
      }
      history[cnt]=token[0];
    }
    // 'quit' or 'exit' will exit from the mav_shell
    if( ( strcmp("quit", token[0]) == 0 ) || (strcmp("exit", token[0]) == 0 ) )
    {
      exit(0);
    }

    //fork the process
    pid = fork();

    // add current PID to PID list
    if(cnt <= MAXIMUM)
    {
      listpids[cnt] = pid;
    }
    // number of PIDS > 15, move all PIDs up by 1
    // in array and store latest in the last position
    else
    {
      // variables used in the loop
      int a;

      for(a = 0; a < MAXIMUM; a++)
      {
        listpids[a] = listpids[a+1];
      }
      listpids[MAXIMUM] = pid;
    }

    //child pid
    if(pid == 0)
    {

      // variable used in the loop
      int a;

      // execl will be true, if execl results in error acc to manual
      // Number of directories = 6, if execl returns 6 times,
      // command is not found
      // counter for execl return cnt
      int execl_count = 0;

      // current location or other directory or location where execl will be
      //tried to execute the commands
      char cd[MAX_COMMAND_SIZE];

      // search through all mentioned directories/locations
      for(a = 0; a < 6; a++)
      {
        // directory/location is copied to cd
        strcpy( cd , folders[a] );
        // join directory and command
        strcat( cd , token[0] );

        //execute the command 
        // 10 tokens (as listed in assignment)
        if( execl( cd, token[0], token[1], token[2], token[3], token[4],
                       token[5], token[6], token[7], token[8], token[9], NULL ) == -1 )
        {
          //increment execl_count
          execl_count++;
          
        }

      }
      history[cnt]=token[0];
      // all the 6 locations did not have the command
      if(execl_count == 6)
      {
        printf("%s: Command not found.\n", token[0]);
      }
      
      exit(0);
    }

    //parent pid
    else
    {
      //wait for child
      int status;
      wait(& status);
    }

    //increment counter
    cnt++;
    // free the memory allocated
    free( head_ptr );

  }

  return 0;
}

