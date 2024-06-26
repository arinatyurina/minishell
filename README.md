# Minishell

## Introduction

The Minishell project, part of the 42 School curriculum, aims to provide an in-depth understanding of shell functionality and system calls in Unix-like operating systems.
This group project was divided into two main parts: the parser and the executor.
The parser is responsible for interpreting and structuring user input, while the executor manages the execution of commands, including handling pipes and redirections.
Our implementation is based on the behavior of Bash, ensuring a user experience that is both familiar and functional.

## Setup

1. Clone the repository:

    ```sh
    git clone https://github.com/arinatyurina/minishell.git
    ```

2. Compile the program:

    ```sh
    make
    ```
## Usage
To run the minishell program, simply execute the compiled binary:

```sh
./minishell
```

Once running, you can enter commands as you would in a typical Unix shell. For example:

```sh
minishell$ ls -l
minishell$ cat file.txt
minishell$ echo "Hello, World!"
minishell$ exit
```

Example

```sh
minishell$ ls -l | grep minishell > output.txt
```
This command will list files in the current directory, pipe the output to grep minishell, and write the result to output.txt.

## Features Overview
### Command Execution

Execute basic commands such as ls, grep, wc, cat, etc.
Support command-line arguments and options.

### Redirections
Redirect input and output using **<, >, >>**.
Manage complex operations with redirections using pipes (|).

### Built-in Commands

+ **cd (Change Directory)**: Navigate through directories using cd.  
*Examples:* 
cd /path/to/directory: Change to a specific directory.  
cd ..: Move up one directory level.  

+ **pwd (Print Working Directory)**: Show the current working directory path.  
*Example:*
pwd: Output the current directory path.  

+ **echo (Output)**: Display messages and variable values with echo.  
*Examples:*
echo Hello, World!: Output a simple message.  
echo $PATH: Display the current value of the PATH variable.  

+ **export**: Set environment variables for use in subsequent commands.  
*Example:*
export PATH=/usr/bin: Set the PATH variable to /usr/bin.  

+ **unset**: Remove environment variables from the current shell session.  
*Example:*
unset PATH: Remove the PATH variable from the environment.  

+ **env**: Display all environment variables.  
*Example:*
env: List all environment variables and their values.   

+ **exit**: Terminate the shell session.  
*Example:*
exit: Exit the shell.  

### Error Handling

Provide clear and **informative error messages** across various scenarios.  
Ensure proper handling of **exit statuses** for child processes.  
### Control Flow

Integration of commands with support for **pipes**.  
Manage command execution within pipelines for efficient processing.  
### Heredoc  
Implement heredoc functionality to support multiline input and scripting.  
Manage interruptions with support for Ctrl+C and Ctrl+\.  
### Signal Handling  
Responsively handle signal **Ctrl+C**.  
