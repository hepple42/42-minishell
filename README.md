# 42-minishell

This repository contains one of my projects of the core curriculum at [42 Heilbronn], done together with [tjensen42].

The project minishell is about creating a simple, bash-like shell.
As with all C projects at 42 Heilbronn, the code has to be written according to the 42 Norm (maximum 25 lines per function, no for loops, a certain set of allowed functions, ...).

## Description

The task in this project is to write a small shell with several features.
The requirements include:

- a prompt
- history of previous input
- launch executables (based on `PATH` variable, using relative or absolute path)
- single (`'`) and double (`"`) quotes to prevent the interpretation of meta-characters
- redirections:
  - input (`<`)
  - output (`>`)
  - here document (`<<`)
  - output append (`>>`)
- pipes (`|`) to connect commands
- expand environment variables (`$` followed by a sequence of characters)
- last exit status (`$?`)
- signal handling (`ctrl`+`C`, `ctrl`+`D`, `ctrl`+`\`)
- builtins:
  - `echo` with option `-n`
  - `cd` with relative or absolute path, `-` for `OLDPWD`, no argument for `HOME`
  - `pwd` without options
  - `export` without options
  - `unset` without options
  - `env` without options
  - `exit` with specific exit status
- wildcards (`*`) in the current working directory _(bonus)_
- AND (`&&`) and OR (`||`) groups of commands with parentheses for priorities _(bonus)_

The behavior of bash is to be considered as a general reference.

The use of GNU's readline library is allowed for handling terminal interaction (input reading, history).

## Approach

We decided to split the handling of user input into four basic parts:

- lexer: split input into basic tokens, implemented as list elements
- parser: interpret tokens and rearrange them into sublists
- expander: expand environment variables and wildcards
- executer: execute commands

In order to be able to handle groups of commands for the bonus part, we had the parser and the executer work recursively.
For this purpose, we also decided to implement a system of subshells.

As a general rule, we tried to reproduce the bahavior of bash as closely as possible, checking the [bash manual] a lot.
To facilitate the comparison between our minishell and the original bash, we also built a small tester, which compares the output and the exit status of both shells (see Testing).

For debugging purposes, we decided to implement a printing function, which shows the different parsing steps with some syntax highlighting (see Debug Mode).

## How to Use

The current version of minishell is developed and tested on macOS, but it should work on all UNIX/LINUX based systems as well.

Requirements: GCC / CLANG Compiler, GNU Make, GNU Readline Library

Clone this repository:
```
git clone https://github.com/hepple42/42-minishell.git
```
Change to the cloned directory and build the project:
```
cd 42-minishell && make
```
Run the minishell:
```
./minishell
```

## Dependencies

### Install Readline with [Brew]

<details>
  <summary>How to install readline using brew.</summary>
  
```
brew install readline
```

```
brew link --force readline
```

```
echo 'export C_INCLUDE_PATH="/usr/local/opt/readline/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```
  
```
echo 'export LIBRARY_PATH="/usr/local/opt/readline/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
  
```
source ~/.zshrc
```
  
</details>

### Install Readline on 42 Macs

<details>
  <summary>How to install readline at 42HN.</summary>

Install brew if it is not already installed:

```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

Install readline library:
```
brew install readline
```

```
brew link --force readline
```

```
echo 'export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```

```
echo 'export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```
source ~/.zshrc
```
  
</details>

## Testing

To test our minishell, a small tester is included in this repository.
It compares most of the shell's features with the current bash installation.
The output (stdout) and the exit-code are compared directly.
In test cases which produce an error, the tester only makes sure that both shells print some error output (stderr). 

Run tester:
```
make test
```

## Debug Mode

To visualize the different steps of the lexing and parsing process, we implemented a debug mode.
It can be activated by exporting an environment variable.

Enter the minishell and export the `DEBUG` environment variable:
```
export DEBUG=printer
```

## Change Prompt

The prompt displayed in the command line of our minishell can be customized by exporting an environment variable.

Enter the minishell and export the `PS1` environment variable:
```
export PS1='[prompt]$ '
```

[42 Heilbronn]: https://www.42heilbronn.de/learncoderepeat
[tjensen42]: https://github.com/tjensen42

[bash manual]: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

[brew]: https://brew.sh/

