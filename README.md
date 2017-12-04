# project01
###Implemented Stuffs:
  * parsing
  * fork()
  * execution
  * redirection
  * piping
  * exit and cd implementation
  * separating and executing multiple commands with the semicolon
### Attempted but Failed Stuffs:
### Stuffs that Bugs
  * redirection 
  * `cd` only works for directories
### Files that Stuffs
  * shell.c
  * shell.h
### Function headers
## PARSE_ARGS
/** parse_args(char * x, char * z)
    --takes in two chars, one is the arguments and the other is how to parse those args
    --separates the args from the args 
    --puts the args into an array
    --returns the array **/
## REMOVE_SPACES_HELPER
/** remove_spaces_helper(char *s)
    --takes in a char that is an argument
    --removes spaces in the beginning of argument
    --removes spaces at the end of the argument
    --helper for getting rid of spaces in a list**/

## REMOVE_SPACES
/** remove_spaces(char **x)
    --takes in a char that is a bunch of args
    --removes spaces in the beginning of all commands in the args
    --removes spaces in the end of all commands in the args**/

## FILE_OPEN_W
/** file_open_w(char *x)
    --takes a char that is the name of the new file
    --creates a new file by the name
    --returns the file descriptor int **/

## FILE_OPEN_R
/** file_open_r(char *x)
    --takes a car that is the name of the original file
    --reads the file
    --returns the file descriptor int **/

## REDIRECTION
/** redirection(char *x)
    --takes in a char that is an arg
    --takes care of redirection with "<" or ">" **/

## PIPING
/**piping(char **x)
   --takes in a char of arguments
   --deploys piping**/

## FINAL_EXECUTE
/** final_execute(char **x)
    --takes in a char of arguments which are commands
    --executes commands **/