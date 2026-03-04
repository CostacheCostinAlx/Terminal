#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void check_command(char *commandstr,int *loop)
{
  char *tok;
  int found = 0;

  tok=strtok(commandstr," ");

  if(tok==NULL) return;

  if(strcmp(tok,"exit") ==0 )
  {
    *loop=0;
  }
  else if(strcmp(tok,"echo") ==0 )
  {
    while(tok)
    {
        tok=strtok(NULL," ");
        if(tok!=NULL)
        printf("%s ",tok);
        
    }
    printf("\n");
    
  }
  else if(strcmp(tok,"type") ==0 )
  {
    tok=strtok(NULL," ");
    if(tok==NULL) return;

    if(strcmp(tok,"echo") == 0 || strcmp(tok,"type") == 0 || strcmp(tok,"exit") == 0)
      printf("%s is a shell builtin\n",tok);
    else 
    {
        char *env_value=getenv("PATH");
        
        if(env_value!=NULL)
        {
            char aux[4096];
            char *dir;

            strcpy(aux,env_value);

            dir=strtok(aux,":");

            while(dir!=NULL)
            {
                char full_path[1024];
                
                strcpy(full_path,dir);
                strcat(full_path,"/");
                strcat(full_path,tok);

                if(access(full_path,X_OK)== 0)  //Checks if it is executable
                {
                    printf("%s is %s\n",tok,full_path);
                    found = 1;
                    break;
                }
                dir = strtok(NULL,":");
            }                    
        }
        if(found==0) printf("%s: not found\n",tok);
    }
  } 
  else
  {   
    printf("%s: command not found\n", tok);
  } 
}


int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  int loop=1;
  char command[100];
  while(loop)
  {
    printf("$ ");
    fgets(command, sizeof(command), stdin);
    //Eliminated "\0" from the string
    command[strcspn(command, "\n")] = 0;  

    check_command(command,&loop);
  }
  return 0;

}