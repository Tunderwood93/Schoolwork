#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <sysexits.h>

#define BUF_SIZE 512

void print_dir(char *dir, int depth){		//Function used for the recursive option

   DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	
	if((dp = opendir(dir)) == NULL){
	  fprintf(stderr,"cannot open directory: %s\n", dir);
	  return;
	}

   chdir(dir);
	while((entry = readdir(dp)) != NULL){
	  lstat(entry ->d_name,&statbuf);
	  if(S_ISDIR(statbuf.st_mode)){
		 if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0){
			continue;
		 }
		 printf("%s:\n",entry->d_name);
		 printf("%*s%s\n",depth, "",entry->d_name);
		 print_dir(entry->d_name, depth+1);
	  }

	  else printf("%*s%s\n\n",depth,"",entry->d_name);
  }

  chdir("..");
  closedir(dp);
}

int main(int argc, char *argv[]){
  
  DIR *dir;
  struct dirent* direntp;
  int option = 0;
  int a_count = 1;	//Used for starting at argv[1]
  int d_count = 1;	//Used for starting at argc[1]
  int l_count = 1;   //Used for starting at argc[1]
  struct stat buffer;
  struct tm *display;
  char t_buff[BUF_SIZE];

  if(argc==1){		//If there are no options used on command prompt
  
    dir = opendir (".");
    
    while((direntp = readdir(dir)) != NULL){
       if(!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, "..")){
	 		continue;
       }

       printf("%s\n", direntp->d_name);
    }

    closedir(dir);
  }

  while ((option = getopt(argc, argv, "adlR")) != -1){	//To check the for the options
      
    switch(option){
      case 'd':{
		   if(argc == 2){
      	  printf(".\n");
	  		  continue;
	      }

			while(d_count < argc){	// While going through the command prompt

     		  if(stat(argv[d_count],&buffer) == 0){
        		 printf("%s\n",argv[d_count]);
     		  }

	  		  d_count++;
   		}

        break;
      }

      case 'a':{
		  dir = opendir(".");	//Opens current directory

			 if(argc==2){		//Prints out everything if no arguements

	  			while((direntp = readdir(dir)) != NULL){
	    		  printf("%s\n",direntp->d_name);
	  			}
	  		   closedir(dir);
	  		   break;
			} 

			 while(a_count < argc){

	  			if(stat(argv[a_count],&buffer) == 0){	//Checks to see if the arguement is a file
	 	
	    		  if(S_ISDIR(buffer.st_mode)){	//Checks to see if it is a directory
	      		 dir = opendir(argv[a_count]);
	      		 printf("%s:\n",argv[a_count]);

	      	  	 while((direntp = readdir(dir)) != NULL){
	        		   printf("%s\n",direntp->d_name);
	      		 }
	      		closedir(dir);
	    		  }

	    		  else{
	      		 printf("%s\n",argv[a_count]);
	    		  }
	  		  }

	  		  a_count++;

			 } 
 
        break;
      }

      case 'l':{
		  dir = opendir(".");
		  if(argc == 2){
		  while((direntp = readdir(dir)) != NULL){
            if(!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, "..")){
               continue;
            }

				 if(stat(direntp->d_name,&buffer) == 0){
					 display = localtime(&buffer.st_mtim.tv_sec);       //Used to get the correct time
             	 strftime(t_buff, BUF_SIZE," %b %d %H:%M", display);
 
           		 switch(buffer.st_mode & S_IFMT){               //switch case used to print out appropriate info
             		case S_IFREG:
                		printf("-");
                		printf( (buffer.st_mode & S_IRUSR) ?"r" : "-");
                		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
                		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
                		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
                		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
                		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
                		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
                		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
                		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
                		printf(" %zu", buffer.st_nlink);
                		printf(" %u", buffer.st_uid);
                		printf(" %zu", buffer.st_size);
                		printf(" %s", t_buff);
                		printf(" %s\n",direntp->d_name);
                		break;
             
					   case S_IFDIR:
		               printf("d");
      		         printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
            		   printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
              			printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
              			printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
               		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
               		printf( " %zu", buffer.st_nlink);
               		printf( " %u", buffer.st_uid);
               		printf( " %zu", buffer.st_size);
               		printf( "%s", t_buff);
               		printf(" %s\n",direntp->d_name);
               		break;

					   case S_IFLNK:
							printf("l");
               		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
               		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
               		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
               		printf( " %zu", buffer.st_nlink);
               		printf( " %u", buffer.st_uid);
               		printf( " %zu", buffer.st_size);
               		printf( "%s", t_buff);
               		printf(" %s\n",direntp->d_name);
               		break;

					   case S_IFCHR:
               		printf("c");
               		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
               		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
               		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
               		printf( " %zu", buffer.st_nlink);
               		printf( " %u", buffer.st_uid);
               		printf( " %zu", buffer.st_size);
               		printf( "%s", t_buff);
               		printf(" %s\n",direntp->d_name);
               		break;
            		case S_IFIFO:
               		printf("f");
               		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
               		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
               		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
               		printf( " %zu", buffer.st_nlink);
               		printf( " %u", buffer.st_uid);
               		printf( " %zu", buffer.st_size);
               		printf( " %s", t_buff);
               		printf(" %s\n",direntp->d_name);
            		break;

						case S_IFBLK:
		               printf("b");
		               printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
		               printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
		               printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
		               printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
		               printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
		               printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
		               printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
		               printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
		               printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
   		            printf( " %zu", buffer.st_nlink);
      		         printf( " %u", buffer.st_uid);
      		         printf( " %zu", buffer.st_size);
      		         printf( " %s", t_buff);
      		         printf(" %s\n",direntp->d_name);
      			   break;

            		case S_IFSOCK:
               		printf("s");
               		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
               		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
               		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
               		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
               		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
               		printf( " %zu", buffer.st_nlink);
               		printf( " %u", buffer.st_uid);
               		printf( " %zu", buffer.st_size);
               		printf( " %s", t_buff);
               		printf(" %s\n",direntp->d_name);
            		break;

						default: perror("NOT VALID");
               }
				}		    
			}
		  
		 }

	 	  if(argc > 2){											//When there are no arguements 

			while(l_count < argc){
	    	 if(stat(argv[l_count],&buffer ) == 0){

		 		display = localtime(&buffer.st_mtim.tv_sec);			//Used to get the correct time
		 		strftime(t_buff, BUF_SIZE," %b %d %H:%M", display);
			 
	    	 switch(buffer.st_mode & S_IFMT){					//switch case used to print out appropriate info
		  		case S_IFREG: 
		    	  	printf("-");
		    	  	printf( (buffer.st_mode & S_IRUSR) ?"r" : "-");
    		     	printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
    		     	printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
    	 		  	printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
    			  	printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
    		 	  	printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
    		 	  	printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
    		 	  	printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
    		 	  	printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
		    	  	printf(" %zu", buffer.st_nlink);
		    	  	printf(" %u", buffer.st_uid);
		    	  	printf(" %zu", buffer.st_size);
	  		 	  	printf(" %s", t_buff);
			 	  	printf(" %s\n",argv[l_count]);
		    	   break;

		  		case S_IFDIR: 
		   		printf("d");
		   		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
         		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
        		 	printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
		   		printf( " %zu", buffer.st_nlink);
		   		printf( " %u", buffer.st_uid);
		   		printf( " %zu", buffer.st_size);
		   		printf( "%s", t_buff);
					printf(" %s\n",argv[l_count]);
		  			break;

		  		case S_IFLNK: 
		   		printf("l");
		   		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
         		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
         		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
		   		printf( " %zu", buffer.st_nlink);
		   		printf( " %u", buffer.st_uid);
		   		printf( " %zu", buffer.st_size);
					printf( "%s", t_buff);
         		printf(" %s\n",argv[l_count]);
		  			break;
		  		case S_IFCHR: 
		   		printf("c");
		   		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
         		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
         		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
		   		printf( " %zu", buffer.st_nlink);
		   		printf( " %u", buffer.st_uid);
		   		printf( " %zu", buffer.st_size);
					printf( "%s", t_buff);
         		printf(" %s\n",argv[l_count]);
		  			break;
		  		case S_IFIFO: 
		   		printf("f");
		   		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
         		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
         		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
		   		printf( " %zu", buffer.st_nlink);
		   		printf( " %u", buffer.st_uid);
		   		printf( " %zu", buffer.st_size);
					printf( " %s", t_buff);
         		printf(" %s\n",argv[l_count]);
		  		break;
		  		case S_IFBLK: 
		   		printf("b");
		   		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
         		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
         		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
		   		printf( " %zu", buffer.st_nlink);
		  		 	printf( " %u", buffer.st_uid);
		   		printf( " %zu", buffer.st_size);
					printf( " %s", t_buff);
         		printf(" %s\n",argv[l_count]);
		  		break;
		  		case S_IFSOCK: 
		   		printf("s");
		   		printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
         		printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
         		printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
         		printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
         		printf( (buffer.st_mode & S_IXOTH) ? "x" : "-");
		   		printf( " %zu", buffer.st_nlink);
		   		printf( " %u", buffer.st_uid);
		   		printf( " %zu", buffer.st_size);
					printf( " %s", t_buff); 
         		printf(" %s\n",argv[l_count]);
		  		   break;

		  		   default: perror("NOT VALID");
			      } 
	  	
	           }
		       l_count ++;
	        }
	      closedir(dir);
         } 
		break;
		}

      case'R':{
       print_dir(".",0);

		}	
      
		break;	
     
		case 'S':{
			return -1;
			break;
		}
		case 't':{
			return -1;
			break;
		}

      default:{
        printf("No file found");
      }

    }
  }

 return 0;
}
