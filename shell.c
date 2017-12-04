#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**------------------- PARSING AND REMOVING SPACES ------------------**/

/** parse_args(char * x, char * z)
    --takes in two chars, one is the arguments and the other is how to parse those args
    --separates the args from the args 
    --puts the args into an array
    --returns the array **/

char ** parse_args( char * line, char * delimeter ){
  char ** args = (char**)calloc(sizeof(char), 20);
  int iter = 0;
  while(line){
    args[iter] = line;
    strsep( &line, delimeter);
    iter ++;
  }
  return args;
}

/** remove_spaces_helper(char *s)
    --takes in a char that is an argument
    --removes spaces in the beginning of argument
    --removes spaces at the end of the argument
    --helper for getting rid of spaces in a list**/

char * remove_spaces_helper(char *arg) {
  char **arrs = parse_args(arg," ");
  return arrs[0];
}//end remove_spaces_helper

/** remove_spaces(char **x)
    --takes in a char that is a bunch of args
    --removes spaces in the beginning of all commands in the args
    --removes spaces in the end of all commands in the args**/

void remove_spaces(char **args) {
  int iter = 0;
  while ( *(args + iter) != NULL ) {
    *(args + iter) = remove_spaces_helper(*(args + iter));
    iter += 1;
  }
}//end remove_spaces

/**------------------- PARSING AND REMOVING SPACES ------------------**/

/**--------------------------- REDIRECTION --------------------------**/

/** file_open_w(char *x)
    --takes a char that is the name of the new file
    --creates a new file by the name
    --returns the file descriptor int **/

int file_open_w(char *file_name) {
  int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if(fd == -1){
    printf("error\n");
  }
  return fd;
}//end of file_open_w

/** file_open_r(char *x)
    --takes a car that is the name of the original file
    --reads the file
    --returns the file descriptor int **/

int file_open_r(char *file_name){
  int fd = open(file_name, O_RDONLY);
  if(fd == -1){
    printf("error\n");
  }
  return fd;
}//end of file_open_r

/** redirection(char *x)
    --takes in a char that is an arg
    --takes care of redirection with "<" or ">" **/

int redirection(char *arg) {
  //stdout
  int stat;
  if (strstr( str, ">") != NULL) {
    args = parse_args( str, ">");
    remove_spaces(args);
    char **args;
    int fd = file_open_w(args[1]);
    if(fd == -1){
      return 0;
    }
    int stdout_duplicate= dup(1);
    dup2(fd, 1);
    if (!fork()) {
      execvp(arg[0], arg);
    }
    else{
      wait(&stat);
      dup2(stdout_duplicate, 1);
    }
    close(fd);
    return 1;
  }
  //stdin
  else if (strstr(arg, "<") != NULL) {
    args = parse_args(arg, "<");
    remove_spaces(args);
    int fd = file_open_r(arg[1]);
    if(fd == -1){
      return 0;
    }
    int stdin_duplicate = dup(0);
    dup2(fd, 0);
    if(!fork()){
      execvp(args[1], args);
    }
    else{
      wait(&stat);
      dup2(stdin_duplicate, 0);
    }
    close(fd);
    return 1;
  }
  else{
    return 0;
  }
}//end of redirection

/**--------------------------- REDIRECTION --------------------------**/

/**------------------------------ PIPING ----------------------------**/

/**piping(char **x)
   --takes in a char of arguments
   --deploys piping**/

void piping(char **args){
  char **nextline = parse_args(args[1], " ");
  FILE *fp = popen(args[0], "r");
  if (fp == NULL) {
    printf("error\n");
  }
  else {
    int f = fork();
    if(f == 0){
      int copy_file = dup(STDIN_FILENO);
      dup2(fileno(fp), STDIN_FILENO);
      execvp(nextline[0], nextline);
      dup2(copy_file, STDIN_FILENO);
      pclose(copy_file);
    }
    else {
      int stat;
      wait(&stat);
    }
  }
}//end of piping

/**------------------------------ PIPING ----------------------------**/

/**-------------------------- FINAL EXECUTION -----------------------**/

/** final_execute(char **x)
    --takes in a char of arguments which are commands
    --executes commands **/

void final_execute(char **args){
  char *cd = "cd";
  char *pipe = "|";
  char *exit = "exit";
  char **arg;
  int iter = 0;
  while (*(args+iter) != NULL){
    if (redirection(*args+iter)){
    }
    else if (strstr( *(args + iter), pipe) != NULL) {
      arg = parse_args( *(args + iter) , pipe);
      piping(arg);
    }
    else{
      //if cd
      arg = parse_args( *(args+i)," ");
      if (strcmp (cd, arg[0]) == 0){ 
        chdir(arg[1]);
      }
      //if exit
      else if(strcmp(exit, arg[0]) == 0){
        printf("exited!\n");
        exit(1);
      }
      else{
	int f = fork();
        if (f == 0){ 
          execvp(arg[0], arg);
          exit(1);
        }
        else{
	  int stat;
	  wait(&stat);
	}
      }
      iter++;
    }
  }
}// end of final_execute
/**-------------------------- FINAL EXECUTION -----------------------**/

/**------------------------------- MAIN -----------------------------**/

int main() {
  char input[200];
  char **args;
  while( fgets(input,sizeof(input), stdin) ) {
    input[strlen(input)-1] = 0;
    args = parse_args(input, ";");
    final_execute(args);
  }
    return 0;
}

/**------------------------------- MAIN -----------------------------**/
