/*
	Oryx Simple Shell - Trevor Underwood
	Class : CS4328 - Operating Systems
	Date: Oct 12th 2015

	Compilation Instructions: Compile like normal.
	Execution Instrctions: Type help for basic usage instructions
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int oryxCD(char **tokInput);
int oryxExit(char **tokInput);
int oryxPrintHistory(char **tokInput);
int oryxHelp(char **tokInput);

//YOUR COMMANDS AND FUNCTIONS MUST BE IN THE SAME ORDER. 
char *built_in_cmds[] = {"cd","quit","logout","exit","history", "help"}; // THIS IS A MACRO FOR PRE-DEFINED COMMANDS. 
int (*built_in_functions[]) (char**) = {&oryxCD, &oryxExit, &oryxExit, &oryxExit, &oryxPrintHistory, &oryxHelp}; //THIS IS A FUNCTION POINTER. 

int oryxNumBuiltins()  //function used for calculating the # of built in cmds currently present. 
{
	return sizeof(built_in_cmds) / sizeof(char*);
}

int oryxCD(char **tokInput) //change directory function. 
{
	if(tokInput[1] == NULL)
	{
		printf("Oryx> Expected arguments to \"cd\"\n");  
	}
	else
	{
		if(chdir(tokInput[1]) != 0)
		{
			perror("Oryx");
		}
	}
	return 1; 
}

int oryxExit(char **tokInput)
{
	return 0; 
}

#define ORYX_HISTORY_COUNT 30
#define ORYX_CMD_LENGTH 256 
char history[ORYX_HISTORY_COUNT][ORYX_CMD_LENGTH];
int cmdNum = 0;
void oryxAddHistory(char *userInput)
{
	if(cmdNum >= 30)
	{
		cmdNum = 0;
	}

	if(strcmp(userInput, "") != 0 && strcmp(userInput, "history") != 0)
	{
		snprintf(history[cmdNum],ORYX_CMD_LENGTH, userInput, NULL);
		cmdNum++;
	}

}


int oryxPrintHistory(char **tokInput)
{
	int i;
	int cmds = cmdNum;

	for(i = 0; i < cmds; i++)
	{
		printf("%d) %s \n", i, history[i]);
	}

	return 1;
}

int oryxHelp(char **tokInput)
{
	printf("\n \t\t Welcome to the Oryx Shell - Written by: Trevor Underwood \n");
	printf("\t This is a basic shell that supports execution of single commmands with arguments \n");
	printf("   Unfortunately piping, input/output redirection, and no-wait(&) are not currently implemented \n");
	printf("\t There are several built in commands: \"cd\", \"history\", \"logout\", \"exit\", \"quit\" \n");
	printf("\t\t For help with a specific command I suggest using \"man\" eg: man ls \n\n");
	return 1;
}

#define ORYX_RL_BUFFSIZE 1024 
char *oryxReadLine ()
{
	int buffSize = ORYX_RL_BUFFSIZE;
	int buffPosition = 0, inputChar; 
	char *inputBuffer = malloc(buffSize * sizeof(char)); // Allocate the inputBuffer using buffSize * sizeof(char)

	if(!inputBuffer) //Exit on failure to allocate buffer space. 
	{
		printf("Oryx> inputBuffer allocation error in oryxReadLine. The shell will now terminate. \n");
		exit(EXIT_FAILURE);
	}

	while(1) // Infinite loop used for reading in user input 
	{
		inputChar = getchar(); //input char is an int because EOF and newLine are ints in C 

		if(inputChar == EOF || inputChar == '\n')
		{
			inputBuffer[buffPosition] = '\0';
			return inputBuffer; 
		}
		else
		{
			inputBuffer[buffPosition] = inputChar; //Typecast the int back to a char and store it into the inputBuffer at correct positon. 
		}
		buffPosition++; 

		if(buffSize <= buffPosition) // Statement used to reallocate the buffer if buffSize <= buffPosition 
		{
			buffSize += ORYX_RL_BUFFSIZE;
			inputBuffer = realloc(inputBuffer, buffSize);
			if(!inputBuffer) // Exit on failure to reallocate the input buffer 
			{
				printf("Oryx> inputBuffer re-allocation error in oryxReadLine. The shell will now terminate. \n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

#define ORYX_TOK_BUFFSIZE 64
#define ORYX_TOK_DELIMS " \t\r\n\a" // list of delimiters for oryxTokenize to use. 
int numPipes = 0;
int inputRedirection = 0;
int outputRedirection = 0;
int inFilePos = 0, outFilePos = 0; 
char **oryxTokenize(char *userInput) 
{
	int buffSize = ORYX_TOK_BUFFSIZE;
	int buffPosition = 0; 
	char *token;
	char **tokenList = malloc(buffSize * sizeof(char*)); // allocate a tokenList using buffSize * sizeof(char*)
	int i;

	if(!tokenList) // if tokenList buffer fails to allocate, exit. 
	{
		printf("Oryx> tokenList buffer allocation error in oryxTokenize. The shell will now terminate. \n");
		//exit(SYSTEM_FAILURE);
		return 0; 
	}

	token = strtok(userInput, ORYX_TOK_DELIMS); // Call strtok and assign to token, strtok returns pointers within the string you pass it 
	while(token != NULL)					  // placing \0 at the end of each token. This continues until strtok returns NULL.  
	{
		tokenList[buffPosition] = token;
		buffPosition++;

		if(buffPosition >= buffSize)
		{
			buffSize += ORYX_TOK_BUFFSIZE;
			tokenList = realloc(tokenList, buffSize * sizeof(char*)); // reallocate if you exceed the standard buffSize
			if(!tokenList) // exit if you fail to reallocate. 
			{
				printf("Oryx> tokenList buffer re-allocation error in oryxTokenize. The shell will now terminate. \n");
				//exit(SYSTEM_FAILURE);
				return 0;
			}
		}
		token = strtok(NULL, ORYX_TOK_DELIMS); //strtok is a "multiple call function". The second call expects NULL and continues 
	}											 // where the previous strtok function left off. 

	tokenList[buffPosition] = NULL;

	for(i = 0; i < buffPosition; i++)
	{
		if(strcmp(tokenList[i], "|") == 0)
			numPipes++;
		if(strcmp(tokenList[i], "<") == 0)
		{
			inFilePos = i + 1; 
			inputRedirection = 1;
		}
		if(strcmp(tokenList[i], ">") == 0)
		{
			outFilePos = i + 1;
			outputRedirection = 1;
		}
	}

	return tokenList; 
}
int inFile, outFile;
int oryxForkLaunch(char **tokInput)
{
	pid_t pid, wpid;
	int shellStatus; 

	//pid = fork();
	if((numPipes == 0 && inputRedirection == 1) || (numPipes == 0 && outputRedirection == 1))
	{
		printf("Not implemented \n");
		printf("The number of pipes is %d \n", numPipes);
		printf("The input flag is currently set to %d \n", inputRedirection);
		printf("The output flag is currently set to %d \n", outputRedirection);
		numPipes = 0;
		inputRedirection = 0;
		outputRedirection = 0; 
	}
	else
	{
		pid = fork();
		if(pid == 0)
		{
			//child process
			if(execvp(tokInput[0], tokInput) == -1)
			{
				perror("Oryx");
			}
			exit(EXIT_FAILURE); //Will only get run on failure. 
		}
		else if(pid < 0)
		{
			//error state
			perror("Oryx");
		}
		else
		{
			//parent process 
			do
			{
				wpid = waitpid(pid, &shellStatus, WUNTRACED); 
			}
			while(!WIFEXITED(shellStatus) && !WIFSIGNALED(shellStatus)); 

		return 1; 
	}

}

int oryxExecute(char **tokInput)
{
	int i; 

	if(tokInput[0] == NULL)
	{
		//If user inputs nothing, ie accadently pressing enter
		return 1;
	}

	for(i = 0; i < oryxNumBuiltins(); i++)
	{
		if(strcmp(tokInput[0], built_in_cmds[i]) == 0)
		{
			return (*built_in_functions[i])(tokInput);
		}
	}

	return oryxForkLaunch(tokInput);
}

void oryxLoop()
{
	char *userInput;
	char **tokInput;
	int shellStatus; 

	do
	{
		printf("Oryx> ");


		userInput = oryxReadLine();
		oryxAddHistory(userInput);
		tokInput = oryxTokenize(userInput);
		shellStatus = oryxExecute(tokInput);

		free(userInput);
		free(tokInput);
	}
	while(shellStatus);
}

int main(int argc, char **argv)
{

	oryxLoop();
	return EXIT_SUCCESS; 
}