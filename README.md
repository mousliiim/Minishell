![ezgif com-gif-maker](https://user-images.githubusercontent.com/101677651/230421757-56698791-2cd1-4439-b12c-b5211362fefd.gif)

<h3 align="center"># Final score of project</h1>
<p align="center"><a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/claeixas400540fmd89rtzoil/project/2978815" alt="mmourdal's 42 minishell Score" /></a></p>
<h1 align="center"># MINISHELL(🇬🇧)</h1>

Welcome to my Minishell github repository! Minishell is one of hardest and longest project at 42 (in the common core).
Project by @Mousliiim https://github.com/mousliiim and @Maxou-source https://github.com/Maxou-source !

The objective of this project is to recode a shell like Bash. A shell is the interface between the user and the computer core. We recoded this project in C. 
I did the execution part while Mouslim did the parsing, We also splitted differents tasks such as the builtins, the expand, the prompt and the tokenisation.

##Start the project on your computer

```bash
make && ./minishell
```

##Explanations of my work for exec (@Maxou-source)

Like I've mentioned before hand i took care if the execution! I will explain in this read me the basic mechanic of my execution!

Once the parsing is done, Mouslim sends me a structure table for each command. Each structure contains these 2 fundamental elements for each structure:
- a command in clear 
- a chained list containing in each node a file name and its associated redirection type
```C
typedef struct s_tab_struct
{
	// the command in clear
	char				**split_command;
	// the chained list
	t_list_mini			*head;

	// other variables used to build or exec
	char				**commands;
	int					type;
	int					prev_heredocs;
}						t_tab_struct;
```

The table of structure is contained in our other structure named t_global (yes i know it isn't a global but its named global). When I want to send a specific structure from the table of structure i will send the structure global along with the index of the structure tab_struct. 

For every command I create a pipe and send it as argument threw the function forking.
```C
while (++i < global->nb) // i is set at -1
{
	signal(SIGINT, SIG_IGN); // this ignores the CTRL+C in the execution
	pipe(global->link);
	forking(global, i);
    // where global is the structure t_global and i the index 
    // of the structure tab_struct I want to send over
}
```

The function ```forking``` makes a fork in which I will execute the command. In the just created child process, I am checking out where i need to write the command. 
```bash
ls | cat # this command will first write the command ls on the pipe and then cat the result on the standard output
```
The following code will check where the command needs to be written according to the index.
If I'm not on the first command the previous readable fd from the pipe becomes the standard input and if I am not on the last command the standard output will become the fd on which I can write. 
```C
	if (i != 0)
		dupnclose(glo->prev, STDIN_FILENO); // redirects STDIN on glo->prev and closes glo->prev
	if (i != (glo->nb - 1))
		dup2(glo->link[1], STDOUT_FILENO);
	close(glo->link[0]);
	close(glo->link[1]);
```
I need to thank @Mohazerro for comming up with this strategy and explaining it to me 😀
