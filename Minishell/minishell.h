/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:55 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/14 15:34:16 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BEFORE 0
# define AFTER 1

# define BASH "bash"

# include <stdio.h>
// printf, readline, perror

# include <readline/readline.h>
// readline

# include <readline/history.h>
// readline

# include <stddef.h>
// NULL

# include <stdlib.h>
// malloc, free, getenv

# include <unistd.h>
// write, access, read, close, fork, exit, getcwd, 
// chdir, execve, dup, dup2, pipe

# include <sys/wait.h>
// wait, waitpid

# include <signal.h>
// signal

# include <string.h>
// strerror

# include <errno.h>
// errno

# include <fcntl.h> 
// open

# include "libft.h"

typedef struct s_data
{
	int				last_exit_status;
	char			**env;
	int				pid1;
	pid_t			*pid;
	struct s_pipe	*pipe;
	struct s_hd		*hd;
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

typedef struct s_pipe
{
	int	**pipefd;
	int	nb_pipe;
}				t_pipe;

typedef struct s_hd
{
	int	**hdfd;
	int	nb_hd;
	int	num_hd;
}				t_hd;

typedef struct s_token
{
	char			*base;
	char			*str;
	int				op;
	int				file;
	struct s_token	*next;
	struct s_token	*before;
}					t_token;

/*minishell.c*/
void	prompt(t_data *data);
void	handler_interractive(int sig);
void	handler(int sig);
int		main(int argc, char **argv, char **envp);

/*env.c*/
char	**create_env(char **envp);
int		add_env(t_data *data, char *var);
char	**env_alloc(char **env);
int		supp_env(t_data *data, char *var, int i, int j);
int		modif_env(t_data *data, char *str);

/*paths.c*/
char	**make_paths(char **envp);
char	*ft_access(char **paths, char *cmd);
char	*verif_path(char **paths, char *cmd);

/*parsing.c*/
int		parsing(char *input);
int		is_close(char *input, char c);
int		is_all_wp(char *str);
int		is_format(char c);

/*characters.c*/
int		is_name_var(char c);
int		is_whitespace(char c);
int		is_redirection(char *str);
int		is_pairs(char c);
int		is_all_num(char *str);

/*tokenisation.c*/
char	*howsub(char *s, int i);
char	*formatting(t_data *data, char *base, t_token *token);
t_token	**tokenisation(t_data *data, char *str);
t_token	**create_list(t_data *data, t_token **p_token, char *str, int i);

/*concatenation.c*/
char	*replacement(t_data *data, char *base, char *result);
char	*final_replacement(t_data *data, char *base, char *result);
char	*single_quote(char *base, char *result);
char	*double_quote(t_data *data, char *base, char *result, int is_ok);

/*sorting_utils.c*/
int		is_file(t_token *token);
int		is_operator(char *str);
void	sorting(t_token *token);

/*checking.c*/
int		checking(t_token *token);
int		is_double(t_token *token);
int		is_red_ok(t_token *token);
int		is_pipe_ok(t_token *token);

/*execution.c*/
void	execution(t_data *data);
void	exec_pipe(t_data *data, t_token *token, char *result, int i);
void	simple_exec(t_data *data, t_token *token);
void	exec_builtin(t_data *data, t_token *token, int info, int exit_status);

/*execution_utils.c*/
void	ft_execute(char **cmdoption, char **paths, char **env);
void	ft_wait(t_data *data, int i);

/*here_doc.c*/
void	fill_hd(int **hdfd, int i, char *delimiter);
int		redir_hd(t_data *data, t_token *token, int i);
int		is_hd_alone(char *str);
void	next_hd(t_data *data, t_token *token);
void	free_hd(t_data *data);

/*redirection.c*/
int		redirection(t_data *data, t_token *token, int i);
int		redir_base(t_data *data, int i);
int		redir_in(t_data *data, t_token *token, int i);
int		redir_out(t_data *data, t_token *token, int i);
int		redir_append(t_data *data, t_token *token, int i);

/*builtins.c*/
int		ft_echo(t_token *token);
int		pwd(void);
int		cd(t_data *data, t_token *token, char *home);
int		cd_shortcuts(t_data *data, t_token *token, char *home);
int		ft_exit(t_data *data, t_token *token);

/*builtins_env.c*/
int		export(t_data *data, t_token *token);
int		unset(t_data *data, t_token *token);
int		env(char **env, t_token *token);
int		printf_sorted(t_data *data);

/*builtins_utils.c*/
int		is_valid_opt_echo(char *str);
int		update_pwd(t_data *data);
int		is_builtin(char *str);
int		too_many_arg(t_token *token, char *cmd);

/*get.c*/
char	*getname(char *str);
char	*ft_getenv(char	*name, t_data *data);
char	*grab_var(char *base, t_data *data);
int		prep_tab(char *array, int num);
char	*get_last_exit_status(int num);

/*lst_util.c*/
t_token	*lstnew(char *base, char *str);
void	lstadd_back(t_token	**token, t_token *new);
t_token	*lstlast(t_token *token);
void	lstdel(t_token **token);
void	printlst(t_token **p_token);

/*utils.c*/
int		length(char const *s, char c);
char	*strjoin(char *s1, char *s2, int len);
int		count_pipe(t_token *token);
void	syntax_error(t_token *token);
int		count_hd(t_token *token);

/*double_tab.c*/
void	print_tab(char **table);
int		find_len(t_token *token);
char	**build_command_tab(t_token *token);
void	swap_pchar(char **p1, char **p2);
void	bubble_sort_tab(char **sorted);

/*init.c*/
int		init(t_data *data, char **envp);
int		init_structs(t_data *data);
int		*pid_alloc(int nb_commands);
int		**pipefd_alloc(int nb_pipes);
int		**make_pipefds(int **pipefd, int nb_pipes);

/*preps.c*/
void	prep_exec(t_data *data, char *input);
int		prep_pipe(t_data *data);
int		prep_hd(t_data *data);

/*close_and_free.c*/
void	close_unused_fd(int **pipefd, int nb_pipes, int i);
void	close_all(int **pipefd, int nb_pipes);
void	free_data(t_data *data);
void	free_dtab(char **array);
void	free_pipe(t_data *data);

#endif
