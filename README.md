# Minishell - 42 School Project

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

<img src="img/minishell_banner.png" width="900px" align="center">

This is the Minishell project for Hive Helsinki (42 School). Minishell is a shell implementation that provides a basic command-line interface, offering various features and functionalities while adhering to most Unix shell standards.
This project was done in collaboration with [Dorian Jagusch](https://github.com/dorianjagusch) 

## Features

- **Command Execution:** Run various shell commands and programmes found via users' PATH environment variable.
- **Environment Variables:** Support for manipulating environment variables.
- **Redirection:** Implement input and output redirection.
- **Pipes:** Allow for the use of pipes to connect commands.
- **Signal Handling:** Handle signals such as Ctrl-C and Ctrl-\.
- **Built-in Commands:** Implement a set of built-in shell commands:
    - `cd`: Change the current directory.
    - `echo`: Print arguments to the standard output.
    - `pwd`: Print the current working directory.
    - `export`: Set or modify environment variables.
    - `unset`: Remove environment variables.
    - `env`: Display the environment.
    - `exit`: Terminate the shell.
- **Error Handling:** Display meaningful error messages and codes when necessary.
- **Line Editing:** Implement line editing and history using the GNU Readline library.
- **Custom Prompt:** Set a custom prompt for the shell.
- **Command Line Parsing:** Parse and tokenize the command line input.

## Getting Started

Follow these instructions to get the Minishell project up and running on your local machine.

### Prerequisites

Before you begin, make sure you have the following installed:

- `gcc` (GNU Compiler Collection)
- `make`
- `readline` library

### Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/dorianjagusch/minishell.git
   cd minishell
   ```

2. Build the project using the provided Makefile:

   ```bash
   make
   ```

3. Run Minishell:

   ```bash
   ./minishell
   ```

## Usage

Minishell works similarly to other Unix shells. You can run various shell commands, utilise built-in commands, set environment variables, and perform other shell-related tasks.
You will be greeted with a very colourful welcome message upon running the shell. Overall, the projects visual design is inspired by [Dorian's](https://github.com/dorianjagusch) and my shared identity as members of the LGBTQ community.

## Devision of labour

All parts have been done in collaboration, yet each of us focused on different aspects of the project.

 [me](https://github.com/azarSarikhani):
  - Parsing, checking and tokenisation of the input
  - Signal handling
  - `exit`command
  - `heredoc`

  [Dorian](https://github.com/dorianjagusch):
  - Search for and execute commands
  - Redirections and piping
  - Built-in commands

## Roadmap for improvements

- Support for wildcards
- Support for `&&` and `||`
