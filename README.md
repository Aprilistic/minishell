# minishell

We made a simple shell.

## How we coded?
### Input handling
1. User inputs are tokenized by IFS(Internal Field Separator). IFS is fixed to space and tab. 
2. If a token is extension parameter(e.g. $PWD), replace it with matching value in environment parameters.

### fork() and pipe()
To implement pipe('|'), we used an anonymous pipe. This program only supports sequential command processing. Sadly, we didn't implement parenthesis and background operation.
1. Open pipe()
2. fork()
3. exec() in child process except for builtin function.

### built-in functions
We implemented cd, pwd, export, unset, echo, exit. These functions don't require fork().

## How to run?
Enter command 'make' in the cloned folder. Then executable named 'minishell' will appear. Run it!
'./minishell'
