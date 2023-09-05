

//CODE WITHOUT REDIRECT

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// #define MAX_INPUT_SIZE 1024
// #define MAX_PATH_COUNT 50
// #define MAX_PATH_SIZE 150

// // Use a 2D character array to store the paths
// char paths[MAX_PATH_COUNT][MAX_PATH_SIZE];


// int path_count = 0; // Keep track of the number of paths

// void add_path(const char *new_path) {
//     if (path_count < MAX_PATH_COUNT) {
//         strcpy(paths[path_count++], new_path);
//     } else {
//         fprintf(stderr, "Max path count reached\n");
//     }
// }

// void execute_command(char *args[]) {
//     // Rest of your execute_command code here, using the paths array
//     // You can iterate over paths and try to execute the command using each path
//     for (int i = 0; i < path_count; i++) {
//         char full_path[MAX_PATH_SIZE];
//         snprintf(full_path, sizeof(full_path), "%s%s", paths[i], args[0]);

//         // Check if the executable exists
//         if (access(full_path, X_OK) == 0) {
//             // Execute the command
//             pid_t pid = fork();
//             if (pid == 0) {
//                 execv(full_path, args);
//                 perror("execv failed");
//                 exit(EXIT_FAILURE);
//             } else if (pid < 0) {
//                 perror("fork failed");
//                 exit(EXIT_FAILURE);
//             } else {
//                 wait(NULL); // Wait for child process to complete
//                 return; // Exit the function after executing the command
//             }
//         }
//     }
//     // If no executable was found in any path, print an error
//     char error_message[30] = "An error has occurred\n";
//     write(STDERR_FILENO, error_message, strlen(error_message));
// }

// void path_command(char *args[]) {
//     // Check if there are arguments
//     // if (args[1] == NULL) {
//     //     fprintf(stderr, "An error occurred\n");
//     //     path_count = 0; // Clear all paths
//     // } else {
//         // Clear the existing paths
//         path_count = 0;

//         // Append each argument to the paths array
//         for (int i = 1; args[i] != NULL; i++) {
//             add_path(args[i]);
//         }
//     //}
// }


// void cd_command(char *args[]) {
//     if (args[1] == NULL) {
//         char error_message[30] = "An error has occurred\n";
//         write(STDERR_FILENO, error_message, strlen(error_message));
//     } else {
//         if (chdir(args[1]) != 0) {
//             char error_message[30] = "An error has occurred\n";
//             write(STDERR_FILENO, error_message, strlen(error_message));
//         }
//     }
// }

// void exit_command(char *args[]) {
//     if (args[1] == NULL) {
//         exit(EXIT_SUCCESS);
//     } else {
//         char error_message[30] = "An error has occurred\n";
//         write(STDERR_FILENO, error_message, strlen(error_message));
//     }
// }

// int main(int argc, char *argv[]) {
// 	// Add /bin/ to the paths array
//     strcpy(paths[0], "/bin/");
//     path_count++;

//     // Add the home directory to the paths array
//     char *home_directory = getcwd(NULL, 0);
//     if (home_directory != NULL) {
//         strcat(home_directory, "/");
//         add_path(home_directory);
//     } else {
//         fprintf(stderr, "Failed to get home directory\n");
//     }
//     if (argc == 2) {
//         // Batch mode: Read commands from the specified file
//         FILE *batch_file = fopen(argv[1], "r");
//         if (batch_file == NULL) {
//             perror("Failed to open batch file");
//             exit(EXIT_FAILURE);
//         }

//         char input[MAX_INPUT_SIZE];
//         char *args[MAX_INPUT_SIZE];

//         while (fgets(input, sizeof(input), batch_file) != NULL) {
//             // Remove newline character
//             input[strcspn(input, "\n")] = '\0';

//             // Parse the input into arguments
//             int arg_count = 0;
//             char *token = strtok(input, " ");
//             while (token != NULL) {
//                 args[arg_count++] = token;
//                 token = strtok(NULL, " ");
//             }
//             args[arg_count] = NULL;

//             if (arg_count > 0) {
//                 if (strcmp(args[0], "exit") == 0) {
//                     exit_command(args);
//                 } else if (strcmp(args[0], "cd") == 0) {
//                     cd_command(args);
//                 } else if (strcmp(args[0], "path") == 0) {
//                     path_command(args);
//                 } else {
//                     execute_command(args);
//                 }
//             }
//         }

//         fclose(batch_file);
//     } else if (argc == 1) {
//         // Interactive mode
//         char input[MAX_INPUT_SIZE];
//         char *args[MAX_INPUT_SIZE];
        
//         while (1) {
//             printf("witsshell> ");
//             fflush(stdout);

//             if (fgets(input, sizeof(input), stdin) == NULL) {
//                 perror("Failed to read input");
//                 exit(EXIT_FAILURE);
//             }

//             // Remove newline character
//             input[strcspn(input, "\n")] = '\0';

//             // Parse the input into arguments
//             int arg_count = 0;
//             char *token = strtok(input, " ");
//             while (token != NULL) {
//                 args[arg_count++] = token;
//                 token = strtok(NULL, " ");
//             }
//             args[arg_count] = NULL;

//             if (arg_count > 0) {
//                 if (strcmp(args[0], "exit") == 0) {
// 					//print path
					
//                     exit_command(args);
//                 } else if (strcmp(args[0], "cd") == 0) {
					
//                     cd_command(args);
//                 } else if (strcmp(args[0], "path") == 0) {
					
//                     path_command(args);
//                 } else {
					
//                     execute_command(args);
//                 }
//             }
//         }
//     } else {
//         fprintf(stderr, "Usage: %s [batch_file]\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }

//     return 0;
// }


//CODE WITH REDIRECT working but with spaces


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <fcntl.h>
// #define MAX_INPUT_SIZE 1024
// #define MAX_PATH_COUNT 50
// #define MAX_PATH_SIZE 150

// // Use a 2D character array to store the paths
// char paths[MAX_PATH_COUNT][MAX_PATH_SIZE];


// int path_count = 0; // Keep track of the number of paths

// void add_path(const char *new_path) {
//     if (path_count < MAX_PATH_COUNT) {
//         strcpy(paths[path_count++], new_path);
//     } else {
//         fprintf(stderr, "Max path count reached\n");
//     }
// }

// // void handle_embedded_redirection(char **args) {
// //     for (int i = 0; args[i] != NULL; i++) {
// //         char *redirection = strchr(args[i], '>');
// //         if (redirection != NULL) {
// //             *redirection = '\0';
// //             char *output_file = redirection + 1;
            
// //             // If the next argument exists, we need to shift every subsequent argument down
// //             if(args[i + 1] != NULL) {
// //                 for(int j = i + 2; args[j - 1] != NULL; j++) {
// //                     args[j] = args[j - 1];
// //                 }
// //             }
            
// //             args[i + 1] = output_file;
// //             args[i + 2] = args[i + 1]; // Shift down subsequent arguments
// //             args[i] = args[i];
// //             break;  // Assuming only one redirection symbol in the command.
// //         }
// //     }
// // }

// void execute_command(char *args[]) {
//     // Add this line to handle the embedded redirection symbol
//     int stdout_fd = dup(STDOUT_FILENO);
//     int stderr_fd = dup(STDERR_FILENO);

//     int redirect_index = -1;
//     for (int i = 0; args[i] != NULL; i++) {
//         if (strcmp(args[i], ">") == 0) {
//             if (args[i + 1] == NULL || args[i + 2] != NULL) {
//                 char error_message[100] = "An error has occurred\n";
//                 write(STDERR_FILENO, error_message, strlen(error_message));
//                 return;
//             }
//             redirect_index = i;
//             break;
//         }
//     }

//     if (redirect_index != -1) {
//         char *output_file = args[redirect_index + 1];
//         int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fd < 0) {
//             perror("Failed to open output file");
//             return;
//         }

//         dup2(fd, STDOUT_FILENO);
//         dup2(fd, STDERR_FILENO);
//         close(fd);

//         args[redirect_index] = NULL;
//     }

//     for (int i = 0; i < path_count; i++) {
//         char full_path[MAX_PATH_SIZE];
//         snprintf(full_path, sizeof(full_path), "%s%s", paths[i], args[0]);

//         if (access(full_path, X_OK) == 0) {
//             pid_t pid = fork();
//             if (pid == 0) {
//                 execv(full_path, args);
//                 perror("execv failed");
//                 exit(EXIT_FAILURE);
//             } else if (pid < 0) {
//                 perror("fork failed");
//                 exit(EXIT_FAILURE);
//             } else {
//                 wait(NULL);
                
//                 // Restore stdout and stderr right after execution
//                 dup2(stdout_fd, STDOUT_FILENO);
//                 dup2(stderr_fd, STDERR_FILENO);
//                 close(stdout_fd);
//                 close(stderr_fd);

//                 return;  // Exit function after executing command
//             }
//         }
//     }

//     char error_message[30] = "An error has occurred\n";
//     write(STDERR_FILENO, error_message, strlen(error_message));

//     // In case no redirection happened, restoring stdout and stderr here.
//     dup2(stdout_fd, STDOUT_FILENO);
//     dup2(stderr_fd, STDERR_FILENO);
//     close(stdout_fd);
//     close(stderr_fd);
// }


// void path_command(char *args[]) {
//     // Check if there are arguments
//     // if (args[1] == NULL) {
//     //     fprintf(stderr, "An error occurred\n");
//     //     path_count = 0; // Clear all paths
//     // } else {
//         // Clear the existing paths
//         path_count = 0;

//         // Append each argument to the paths array
//         for (int i = 1; args[i] != NULL; i++) {
//             add_path(args[i]);
//         }
//     //}
// }


// void cd_command(char *args[]) {
//     if (args[1] == NULL) {
//         char error_message[30] = "An error has occurred\n";
//         write(STDERR_FILENO, error_message, strlen(error_message));
//     } else {
//         if (chdir(args[1]) != 0) {
//             char error_message[30] = "An error has occurred\n";
//             write(STDERR_FILENO, error_message, strlen(error_message));
//         }
//     }
// }

// void exit_command(char *args[]) {
//     if (args[1] == NULL) {
//         exit(EXIT_SUCCESS);
//     } else {
//         char error_message[30] = "An error has occurred\n";
//         write(STDERR_FILENO, error_message, strlen(error_message));
//     }
// }

// int main(int argc, char *argv[]) {
// 	// Add /bin/ to the paths array
//     strcpy(paths[0], "/bin/");
//     path_count++;

//     // Add the home directory to the paths array
//     char *home_directory = getcwd(NULL, 0);
//     if (home_directory != NULL) {
//         strcat(home_directory, "/");
//         add_path(home_directory);
//     } else {
//         fprintf(stderr, "Failed to get home directory\n");
//     }
//     if (argc == 2) {
//         // Batch mode: Read commands from the specified file
//         FILE *batch_file = fopen(argv[1], "r");
//         if (batch_file == NULL) {
//             perror("Failed to open batch file");
//             exit(EXIT_FAILURE);
//         }

//         char input[MAX_INPUT_SIZE];
//         char *args[MAX_INPUT_SIZE];

//         while (fgets(input, sizeof(input), batch_file) != NULL) {
//             // Remove newline character
//             input[strcspn(input, "\n")] = '\0';

//             // Parse the input into arguments
//             int arg_count = 0;
//             char *token = strtok(input, " ");
//             while (token != NULL) {
//                 args[arg_count++] = token;
//                 token = strtok(NULL, " ");
//             }
//             args[arg_count] = NULL;

//             if (arg_count > 0) {
//                 if (strcmp(args[0], "exit") == 0) {
//                     exit_command(args);
//                 } else if (strcmp(args[0], "cd") == 0) {
//                     cd_command(args);
//                 } else if (strcmp(args[0], "path") == 0) {
//                     path_command(args);
//                 } else {
//                     execute_command(args);
//                 }
//             }
//         }

//         fclose(batch_file);
//     } else if (argc == 1) {
//         // Interactive mode
//         char input[MAX_INPUT_SIZE];
//         char *args[MAX_INPUT_SIZE];
        
//         while (1) {
//             printf("witsshell> ");
//             fflush(stdout);

//             if (fgets(input, sizeof(input), stdin) == NULL) {
//                 perror("Failed to read input");
//                 exit(EXIT_FAILURE);
//             }

//             // Remove newline character
//             input[strcspn(input, "\n")] = '\0';

//             // Parse the input into arguments
//             int arg_count = 0;
//             char *token = strtok(input, " ");
//             while (token != NULL) {
//                 args[arg_count++] = token;
//                 token = strtok(NULL, " ");
//             }
//             args[arg_count] = NULL;

//             if (arg_count > 0) {
//                 if (strcmp(args[0], "exit") == 0) {
// 					//print path
					
//                     exit_command(args);
//                 } else if (strcmp(args[0], "cd") == 0) {
					
//                     cd_command(args);
//                 } else if (strcmp(args[0], "path") == 0) {
					
//                     path_command(args);
//                 } else {
					
//                     execute_command(args);
//                 }
//             }
//         }
//     } else {
//         fprintf(stderr, "Usage: %s [batch_file]\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }

//     return 0;
// }

//CODE WITH REDIRECTION WITHOUT SPACES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX_INPUT_SIZE 1024
#define MAX_PATH_COUNT 50
#define MAX_PATH_SIZE 150

// Use a 2D character array to store the paths
char paths[MAX_PATH_COUNT][MAX_PATH_SIZE];


int path_count = 0; // Keep track of the number of paths

void add_path(const char *new_path) {
    if (path_count < MAX_PATH_COUNT) {
        strcpy(paths[path_count++], new_path);
    } else {
        fprintf(stderr, "Max path count reached\n");
    }
}

void execute_command(char *args[]) {
    
    // Add this line to handle the embedded redirection symbol
    int stdout_fd = dup(STDOUT_FILENO);
    int stderr_fd = dup(STDERR_FILENO);

    int redirect_index = -1;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            if (args[i + 1] == NULL || args[i + 2] != NULL) {
                char error_message[100] = "An error has occurred\n";
                write(STDERR_FILENO, error_message, strlen(error_message));
                return;
            }
            redirect_index = i;
            break;
        }
    }

    if (redirect_index != -1) {
        if (redirect_index == 0) {
            char error_message[100] = "An error has occurred\n";
            write(STDERR_FILENO, error_message, strlen(error_message));
            return;
        }
        char *output_file = args[redirect_index + 1];
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("Failed to open output file");
            return;
        }

        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);

        args[redirect_index] = NULL;
    }

    for (int i = 0; i < path_count; i++) {
        char full_path[MAX_PATH_SIZE];
        snprintf(full_path, sizeof(full_path), "%s%s", paths[i], args[0]);

        if (access(full_path, X_OK) == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                execv(full_path, args);
                perror("execv failed");
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
                
                // Restore stdout and stderr right after execution
                dup2(stdout_fd, STDOUT_FILENO);
                dup2(stderr_fd, STDERR_FILENO);
                close(stdout_fd);
                close(stderr_fd);

                return;  // Exit function after executing command
            }
        }
    }

    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));

    // In case no redirection happened, restoring stdout and stderr here.
    dup2(stdout_fd, STDOUT_FILENO);
    dup2(stderr_fd, STDERR_FILENO);
    close(stdout_fd);
    close(stderr_fd);
}


void path_command(char *args[]) {
    // Check if there are arguments
    // if (args[1] == NULL) {
    //     fprintf(stderr, "An error occurred\n");
    //     path_count = 0; // Clear all paths
    // } else {
        // Clear the existing paths
        path_count = 0;

        // Append each argument to the paths array
        for (int i = 1; args[i] != NULL; i++) {
            add_path(args[i]);
        }
    //}
}


void cd_command(char *args[]) {
    if (args[1] == NULL) {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    } else {
        if (chdir(args[1]) != 0) {
            char error_message[30] = "An error has occurred\n";
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
    }
}

void exit_command(char *args[]) {
    if (args[1] == NULL) {
        exit(EXIT_SUCCESS);
    } else {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
}

void tokenize_input(char *input, char **args, int *arg_count) {
    char *token = strtok(input, " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            args[(*arg_count)++] = token;
        } else {
            char *redir = strchr(token, '>');
            if (redir) {
                *redir = 0;
                args[(*arg_count)++] = token;
                args[(*arg_count)++] = ">";
                token = redir + 1;
                if (*token != '\0') {  // If there's a filename directly after '>'
                    args[(*arg_count)++] = token;
                }
            } else {
                args[(*arg_count)++] = token;
            }
        }
        token = strtok(NULL, " ");
    }
    args[*arg_count] = NULL;
}


int main(int argc, char *argv[]) {
	// Add /bin/ to the paths array
    strcpy(paths[0], "/bin/");
    path_count++;

    // Add the home directory to the paths array
    char *home_directory = getcwd(NULL, 0);
    if (home_directory != NULL) {
        strcat(home_directory, "/");
        add_path(home_directory);
    } else {
        fprintf(stderr, "Failed to get home directory\n");
    }
    if (argc == 2) {
    FILE *batch_file = fopen(argv[1], "r");
    if (batch_file == NULL) {
        perror("Failed to open batch file");
        exit(EXIT_FAILURE);
    }

    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE];

    while (fgets(input, sizeof(input), batch_file) != NULL) {
        input[strcspn(input, "\n")] = '\0';

        // Use enhanced tokenization for batch mode as well
        int arg_count = 0;
        tokenize_input(input, args, &arg_count);

        if (arg_count > 0) {
            if (strcmp(args[0], "exit") == 0) {
                exit_command(args);
            } else if (strcmp(args[0], "cd") == 0) {
                cd_command(args);
            } else if (strcmp(args[0], "path") == 0) {
                path_command(args);
            } else {
                execute_command(args);
            }
        }
    }

    fclose(batch_file);
    } else if (argc == 1) {
        // Interactive mode
        char input[MAX_INPUT_SIZE];
        char *args[MAX_INPUT_SIZE];
        
        while (1) {
            printf("witsshell> ");
            fflush(stdout);

            if (fgets(input, sizeof(input), stdin) == NULL) {
                perror("Failed to read input");
                exit(EXIT_FAILURE);
            }

            input[strcspn(input, "\n")] = '\0';

            int arg_count = 0;
            tokenize_input(input, args, &arg_count);

            if (arg_count > 0) {
                if (strcmp(args[0], "exit") == 0) {
                    exit_command(args);
                } else if (strcmp(args[0], "cd") == 0) {
                    cd_command(args);
                } else if (strcmp(args[0], "path") == 0) {
                    path_command(args);
                } else {
                    execute_command(args);
                }
            }
        }
    } else {
        fprintf(stderr, "Usage: %s [batch_file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
