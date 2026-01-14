# MINISHELL

A **simple shell** mirroring a classic *bash* shell.

![minishell](/assets/mini_0.jpg)

# INSTRUCTIONS

We use the `readline` library to get the user prompts and build the user's history. You might need to install it in order
to compile minishell. Just paste this command: `sudo apt-get install -y libreadline-dev`.

With that out of the way, clone the repo and type in `make`. Now `./minishell` is ready to go.

# FEATURES

1. Access to all the system's commands (ls, grep, etc.).
2. The following built-ins are available:
    - `echo` with option -n
    - `cd` with only a relative or absolute path
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options
3. Expansions with `$`
4. Pipes and redirections
5. Signals: ctrl-D, ctrl-C, ctrl-\
6. Working user history that persists after exiting the session.

![some funny commands](/assets/mini_1.jpg) 