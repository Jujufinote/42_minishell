/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:55 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/06 16:07:24 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STD "\033["
# define RES "\033[0m"

# define RED ";31m"
# define GREEN ";32m"
# define YELLOW ";33m"
# define BLUE ";34m"
# define WHITE ";37m"

# define NO "0"
# define BOLD "1"
# define IT "3"

# define BEFORE 0
# define AFTER 1

# define HD "heredoc.txt"

# include <stdio.h> // printf, readline, perror
# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <stddef.h> // NULL
# include <stdlib.h> // malloc, free, getenv
# include <unistd.h> // write, access, read, close, fork, exit, getcwd, chdir, stat, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot, tcsetattr, tcgetattr
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/types.h> // stat, opendir, closedir
# include <dirent.h> // opendir, readdir, closedir
# include <termios.h> // tcsetattr, tcgetattr
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <string.h> // strerror
# include <errno.h> // errno
# include <sys/ioctl.h> // ioctl
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <fcntl.h> // open

# include "libft.h"

typedef struct s_data
{
	int				last_exit_status; //WIFEXITED(status) WEXITSTATUS(status) dans parent apres waitpid
	char			**env;
	char			**paths;
	int				nb_pipe;
	int				pid1;
	pid_t			*pid;
	int				**pipefd;
	struct s_files	*files;
	struct s_token	**tokens;
}				t_data;

typedef struct s_files
{
	int	saved_in;
	int	saved_out;
	int	file_in;
	int	file_out;
}				t_files;

typedef struct s_token
{
	char			*str;
	int				command;
	int				option;
	int				op;
	int				file;
	struct s_token	*next;
	struct s_token	*before;
}					t_token;

/*minishell.c*/
void	prompt(t_data *data);
void	handler(int sig);
int		main(int argc, char **argv, char **envp);

/*env.c*/
char	**create_env(char **envp);
int		add_env(t_data *data, char *var);
char	**env_alloc(char **env);
int		supp_env(t_data *data, char *var);
int		modif_env(t_data *data, char *str);

/*paths.c*/
char	**make_paths(char **envp);
char	*ft_access(char **paths, char *cmd);

/*parsing.c*/
int		parsing(char *input);
int		is_close(char *input, char c);

/*characters.c*/
int		is_name_var(char c);
int		is_whitespace(char c);
int		is_redirection(char *str);
int		is_pairs(char c);
int		is_format(char c);

/*tokenisation.c*/
char	*howsub(char *s, int i);
void	sorting(t_token *token);
t_token	**tokenisation(t_data *data, char *str);

/*formatting.c*/
char	*formatting(t_data *data, char *base);
char	*replacement(t_data *data, char *base, char *result);
char	*single_quote(char *base, char *result);
char	*double_quote(t_data *data, char *base, char *result);

/*checking.c*/
int		checking(t_token *token);

/*is_token_ok.c*/
int		is_double(t_token *token);
int		is_red_ok(t_token *token);
int		is_pipe_ok(t_token *token);

/*execution.c*/
void	execution(t_data *data);
void	exec_pipe(t_data *data, t_token *token, int i);
void	simple_exec(t_data *data, t_token *token);
void	exec_builtin(t_data *data, t_token *token);

/*execution_utils.c*/
void	ft_execute(char **cmdoption, char **paths, char **env);
void	ft_wait(t_data *data, int i);

/*here_doc.c*/
int		exec_heredoc(t_data *data, t_token *token, int i);
void	redir_hd(t_data *data, int i);

/*redirection.c*/
int		redirection(t_data *data, t_token *token, int i);
int		redir_base(t_data *data, int i);
int		redir_in(t_data *data, t_token *token, int i);
int		redir_out(t_data *data, t_token *token, int i);
int		redir_append(t_data *data, t_token *token, int i);

/*builtins.c*/
int		ft_echo(t_token *token);
int		pwd(t_data *data);
int		cd(t_data *data, t_token *token);
int		ft_exit(t_data *data);

/*builtins_env.c*/
int		export(t_data *data, t_token *token);
int		unset(t_data *data, t_token *token);
int		env(char **env, t_token *token);

/*builtins_utils.c*/
int		is_valid_opt_echo(char *str);
int		update_pwd(t_data *data, t_token *token);

/*get.c*/
char	*getname(char *str);
char	*ft_getenv(char	*name, t_data *data);
char	*grab_var(char *base, t_data *data);

/*lst_util.c*/
t_token	*lstnew(char *str);
void	lstadd_back(t_token	**token, t_token *new);
t_token	*lstlast(t_token *token);
void	lstdel(t_token **token);
void	printlst(t_token **p_token);

/*sorting_utils.c*/
int		is_command(t_token *token);
int		is_option(t_token *token);
int		is_file(t_token *token);
int		is_operator(char *str);
int		is_builtin(char *str);

/*utils.c*/
int		length(char const *s, char c);
char	*strjoin(char *s1, char *s2, int len);
int		count_pipe(t_token *token);

/*double_tab.c*/
void	print_tab(char **table);
int		find_len(t_token *token);
char	**build_command_tab(t_token *token);

/*init.c*/
int		init(t_data *data, char **envp);
int		*pid_alloc(int nb_commands);
int		**pipefd_alloc(int nb_pipes);
int		**make_pipefds(int **pipefd, int nb_pipes);
int		prep_pipe(t_data *data);

/*free.c*/
void	free_data(t_data *data);
void	free_dtab(char **array);
void	free_pipe(t_data *data);

/*close.c*/
void	ft_close(t_data *data);
void	close_unused_fd(int **pipefd, int nb_pipes, int i);
void	close_all(int **pipefd, int nb_pipes);

/*error.c*/
void	syntax_error(t_token *token, int where);

#endif
