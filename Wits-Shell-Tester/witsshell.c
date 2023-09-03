// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <string.h>
// #include <assert.h>
// #include <fcntl.h>

// bool is_bash_mode() {
//     // Check if the SHELL environment variable contains "bash."
//     char *shell = getenv("SHELL");
//     if (shell && strstr(shell, "bash") != NULL) {
//         return true;
//     }
//     return false;
// }

// bool is_interactive() {
//     // Check if stdin is connected to a terminal.
//     return isatty(STDIN_FILENO);
// }

// int main(int MainArgc, char *MainArgv[]){
// 	if (is_bash_mode() && is_interactive()) {
//         printf("Your shell is in bash mode and running interactively.\n");
//     } else {
//         printf("Your shell is not in bash mode and/or not running interactively.\n");
//     }

// 	char *input = NULL;
//     size_t input_size = 0;

//     while (1) {
//         printf("witsshell> ");  // Print a shell prompt
//         ssize_t input_length = getline(&input, &input_size, stdin);

//         if (input_length == -1) {
//             //perror("getline");
//             exit(EXIT_FAILURE);
//         }

//         // Remove the newline character at the end of the input
//         input[input_length - 1] = '\0';

//         //To exit shell
//         if (strcmp(input, "exit") == 0) {
//             break;  // Exit the loop
//         }

// 		// Check if the user typed "ls" to show the contents of the current directory
// 		if (strcmp(input, "ls") == 0) {
// 			pid_t pid = fork();
// 			if (pid == -1) {
// 				perror("fork");
// 				exit(EXIT_FAILURE);
// 			}

// 			if (pid == 0) {
// 				// Child process
// 				execlp("ls", "ls", NULL);
// 				perror("execlp");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Parent process
// 			int status;
// 			if (wait(&status) == -1) {
// 				perror("wait");
// 				exit(EXIT_FAILURE);
// 			}

// 			continue;  // Go to the next iteration of the loop
// 		}
// 		// Check if the user typed "ls" to show the contents of the upper directory
// 		if (strcmp(input, "ls..") == 0) {
// 			pid_t pid = fork();
// 			if (pid == -1) {
// 				perror("fork");
// 				exit(EXIT_FAILURE);
// 			}

// 			if (pid == 0) {
// 				// Child process
// 				execlp("ls", "ls", "..", NULL);
// 				perror("execlp");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Parent process
// 			int status;
// 			if (wait(&status) == -1) {
// 				perror("wait");
// 				exit(EXIT_FAILURE);
// 			}

// 			continue;  // Go to the next iteration of the loop
// 		}

//         // Here, you can process the user's input as needed
//         // if((input[0] == 'c' && input[1] == 'd' && input[2] == ' ') || (input[0] == 'c' && input[1] == 'd' && input[2] == '\0')){
// 		// 	char *path = input + 3;
// 		// 	if(chdir(path) == -1){
// 		// 		perror("chdir");
// 		// 	}
// 		// 	continue;
// 		// }
//     }

//     free(input);  // Free the memory allocated by getline

// 	return(0);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <dirent.h>
// #define MAX_INPUT_LENGTH 1024

// bool is_bash_mode() {
//     // Check if the SHELL environment variable contains "bash."
//     char *shell = getenv("SHELL");
//     if (shell && strstr(shell, "bash") != NULL) {
//         return true;
//     }
//     return false;
// }

// bool is_interactive() {
//     // Check if stdin is connected to a terminal.
//     return isatty(STDIN_FILENO);
// }

// //ls command
// // void execute_ls() {
// //     pid_t pid = fork();
// //     if (pid == -1) {
// //         perror("fork");
// //         exit(EXIT_FAILURE);
// //     }

// //     if (pid == 0) {
// //         // Child process
// //         execlp("ls", "ls", NULL);
// //         perror("ls");
// //         exit(EXIT_FAILURE);
// //     }

// //     // Parent process
// //     int status;
// //     if (wait(&status) == -1) {
// //         perror("wait");
// //         exit(EXIT_FAILURE);
// //     }
// // }
// void ls(const char *directory) {
//     struct dirent *entry;
//     DIR *dp;

//     // Open the specified directory
//     dp = opendir(directory);

//     if (dp == NULL) {
//         perror("opendir");
//         exit(1);
//     }

//     // Read and print directory entries
//     while ((entry = readdir(dp))) {
//         // Skip hidden files and directories
//         if (entry->d_name[0] == '.')
//             continue;

//         printf("%s\n", entry->d_name);
//     }

//     closedir(dp);
// }

// //ls.. command
// void execute_ls_upper_files(){
// 	pid_t pid = fork();
// 	if (pid == -1) {
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0) {
// 		// Child process
// 		execlp("ls", "ls ", "..", NULL);
// 		perror("ls");
// 		exit(EXIT_FAILURE);
// 	}

// 	// Parent process
// 	int status;
// 	if (wait(&status) == -1) {
// 		perror("wait");
// 		exit(EXIT_FAILURE);
// 	}
// }

// //echo command
// void execute_echo(char *message) {
//     // Implement the 'echo' command logic here.
//     printf("%s\n", message);
// }

// //cd command
// void execute_cd(char *path) {
//     if (chdir(path) == -1) {
//         char error_message[30] = "An error has occurred\n";
//         write(STDERR_FILENO, error_message, strlen(error_message));
//     }
// }

// int main(int argc, char *argv[]) {
//     if (argc > 1) {
//         // Batch mode: Read commands from the specified file.
//         char *input_file_name = argv[1];
//         FILE *input_file = fopen(input_file_name, "r");
//         if (input_file == NULL) {
//             perror("Error opening input file");
//             return 1;
//         }

//         char *input = NULL;
//         size_t input_length = 0;
//         ssize_t read;

//         while ((read = getline(&input, &input_length, input_file)) != -1) {
//             // Remove the trailing newline character.
//             if (input[read - 1] == '\n') {
//                 input[read - 1] = '\0';
//             }
// 			//ls commanc
// 			// if (strcmp(input, "ls") == 0)
// 			// {
// 			// 	execute_ls();
// 			// 	continue; // Go to the next iteration of the loop
// 			// }
// 			//exit command
// 			if (input_length == -1) {
// 				//perror("getline");
// 				exit(EXIT_FAILURE);
// 			}
// 			//ls .. command
// 			if (strcmp(input, "ls ..") == 0)
// 			{
// 				execute_ls_upper_files();
// 				continue;
// 			}
// 			// Check if the user typed "echo" to print a message.
// 			if (strncmp(input, "echo ", 5) == 0) {
//                 char *message = input + 5;
//                 execute_echo(message);
//                 continue;
//             }

// 			//cd command
// 			if ((input[0] == 'c' && input[1] == 'd' && input[2] == ' ') || (input[0] == 'c' && input[1] == 'd' && input[2] == '\0')) {
// 				char *path = input + 3;
// 				execute_cd(path);
// 				continue;
// 			}

// 			// Clear the input buffer for the next iteration.
//             free(input);
//             input = NULL;
//             input_length = 0;
//         }

//         // Clean up and exit.
//         free(input);
//         fclose(input_file);

// 	// Interactive mode: Read commands from stdin.
//     } else if (is_interactive()) {
// 		char *input = NULL;
//         size_t input_size = 0;
//         while (1) {
// 			printf("witsshell> ");  // Print a shell prompt
// 			ssize_t input_length = getline(&input, &input_size, stdin);

// 			if (input_length == -1) {
// 				//perror("getline");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Remove the newline character at the end of the input
// 			input[input_length - 1] = '\0';

// 			//To exit shell
// 			if (strcmp(input, "exit") == 0) {
// 				break;  // Exit the loop
// 			}

// 			//ls command
// 			// if (strcmp(input, "ls") == 0)
// 			// {
// 			// 	execute_ls();
// 			// 	continue; // Go to the next iteration of the loop
// 			// }
// 			const char *directory = "."; // Default to current directory

// 			// Check for a directory argument (if any)
// 			if (argc > 1)
// 			{
// 				directory = argv[1];
// 			}

// 			ls(directory);

// 			//ls.. command
// 			if (strcmp(input, "ls ..") == 0)
// 			{
// 				execute_ls_upper_files();
// 				continue; // Go to the next iteration of the loop
// 			}
// 			// Check if the user typed "echo" to print a message.
// 			if (strncmp(input, "echo ", 5) == 0) {
//                 char *message = input + 5;
//                 execute_echo(message);
//                 continue;
//             }

// 			//cd command
// 			if ((input[0] == 'c' && input[1] == 'd' && input[2] == ' ') || (input[0] == 'c' && input[1] == 'd' && input[2] == '\0')) {
// 				char *path = input + 3;
// 				execute_cd(path);
// 				continue;
// 			}

// 			// Here, you can process the user's input as needed

// 			free(input);
// 		}

// 		  // Free the memory allocated by getline
// 	}
// 	return(0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

#define MAX_INPUT_LENGTH 1024

bool is_interactive()
{
	// Check if stdin is connected to a terminal.
	return isatty(STDIN_FILENO);
}

bool is_bash_mode()
{
	// Check if the SHELL environment variable contains "bash."
	char *shell = getenv("SHELL");
	if (shell && strstr(shell, "bash") != NULL)
	{
		return true;
	}
	return false;
}

// excutes ls command
void execute_ls(const char *directory)
{
	// Implement the 'ls' command logic here.
	struct dirent *entry;
	DIR *dp;

	// Open the specified directory
	dp = opendir(directory);

	if (dp == NULL)
	{
		fprintf(stderr, "ls: cannot access '%s': %s\n", directory, strerror(errno));
		return;
	}

	// Read and print directory entries
	while ((entry = readdir(dp)))
	{
		// Skip hidden files and directories
		if (entry->d_name[0] == '.')
			continue;

		printf("%s\n", entry->d_name);
	}

	closedir(dp);
}
// excutes ls.. command
void execute_ls_upper_files()
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// Child process
		execlp("ls", "ls ", "..", NULL);
		perror("ls");
		exit(EXIT_FAILURE);
	}

	// Parent process
	int status;
	if (wait(&status) == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
}

// excutes echo command
void execute_echo(char *message)
{
	// Implement the 'echo' command logic here.
	printf("%s\n", message);
}

// excutes cd command
void execute_cd(char *path) {
    if (chdir(path) == -1) {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
}




int main(int argc, char *argv[])
{
	char *input = NULL;
	size_t input_size = 0;

	if (is_interactive() || (argc > 1 && is_bash_mode()))
	{
		if (argc > 1)
		{
			// Batch mode: Read commands from the specified file.
			char *input_file_name = argv[1];
			FILE *input_file = fopen(input_file_name, "r");
			if (input_file == NULL)
			{
				perror("Error opening input file");
				return 1;
			}

			char *input = NULL;
			size_t input_length = 0;
			ssize_t read;

			while ((read = getline(&input, &input_length, input_file)) != -1)
			{
				// Remove the trailing newline character.
				if (input[read - 1] == '\n')
				{
					input[read - 1] = '\0';
				}
				// To exit the shell
				if (strcmp(input, "exit") == 0)
				{
					break; // Exit the loop
				}

				if (strcmp(input, "ls") == 0)
				{
					execute_ls(".");
				}
				else if (strncmp(input, "ls ", 3) == 0)
				{
					execute_ls(input + 3);
				}
				else if (strncmp(input, "echo ", 5) == 0)
				{
					execute_echo(input + 5);
				}
				else if ((strncmp(input, "cd ", 3) == 0) || (strcmp(input, "cd") == 0))
				{
					char *path = (strcmp(input, "cd") == 0) ? getenv("HOME") : input + 3;
					execute_cd(path);
				}

				else if (strcmp(input, "ls ..") == 0)
				{
					execute_ls_upper_files();
					continue; // Go to the next iteration of the loop
				}
			}

			// Clean up and exit.
			free(input);
			fclose(input_file);
		}
		else
		{
			// Interactive mode
			while (1)
			{
				printf("witsshell> "); // Print a shell prompt

				ssize_t input_length = getline(&input, &input_size, stdin);

				if (input_length == -1)
				{
					perror("getline");
					exit(EXIT_FAILURE);
				}

				// Remove the newline character at the end of the input
				input[input_length - 1] = '\0';

				// To exit the shell
				if (strcmp(input, "exit") == 0)
				{
					break; // Exit the loop
				}

				if (strcmp(input, "ls") == 0)
				{
					execute_ls(".");
				}
				else if (strncmp(input, "ls ", 3) == 0)
				{
					execute_ls(input + 3);
				}
				else if (strncmp(input, "echo ", 5) == 0)
				{
					execute_echo(input + 5);
				}
				else if ((strncmp(input, "cd ", 3) == 0) || (strcmp(input, "cd") == 0))
				{
					char *path = (strcmp(input, "cd") == 0) ? getenv("HOME") : input + 3;
					execute_cd(path);
				}

				else if (strcmp(input, "ls ..") == 0)
				{
					execute_ls_upper_files();
					continue; // Go to the next iteration of the loop
				}
			}

			// Free the memory allocated by getline
			free(input);
		}
	}

	return 0;
}
