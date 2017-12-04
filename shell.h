char ** parse_args(char * line, char * delimiter );
char * remove_spaces_helper(char *arg);
void remove_spaces(char **args);
int file_open_w(char *file_name);
int file_open_r(char *file_name);
int redirection(char **arg);
void piping(char **args); 
void final_execute(char **args);
