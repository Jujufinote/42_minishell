/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:22:55 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/05 15:28:42 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# include <sys/stat.h>
// stat

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
	int				last_exit;
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
	char			*post_str;
	char			*str;
	int				op;
	int				file;
	struct s_token	*next;
	struct s_token	*before;
}					t_token;

/*minishell.c*/
void	prompt(t_data *data);
int		main(int argc, char **argv, char **envp);

/*signals.c*/
void	handler_interractive(int sig);
void	handler(int sig);
void	signal_handler(int info, int sig);
void	is_interractive(struct sigaction sa, int info);

/*env.c*/
char	**create_env(char **envp);
int		add_env(t_data *data, char *var);
int		supp_env(t_data *data, char *var, int i, int j);
int		modif_env(t_data *data, char *str, int i);
int		is_env(char **env, char *str);

/*paths.c*/
char	**make_paths(char **envp);
int		ft_is_file(char *path);
char	*ft_access(char **paths, char *cmd);
char	*verif_path(char **paths, char *cmd, int i);

/*parsing.c*/
int		parsing(char *input);
int		is_close(char *input, char c);

/*characters.c*/
int		is_name_var(char c);
int		is_whitespace(char c);
int		is_redirection(t_token *token);
int		is_pairs(char c);

/*is_all.c*/
int		is_all_wp(char *str);
int		is_all_num(char *str);
int		is_all_name_var(char *str);

/*tokenisation.c*/
char	*formatting(t_data *data, char *base, t_token *token);
char	*final_replacement(t_data *data, char *base, char *result);
t_token	**tokenisation(t_data *data, char *str);
char	*replacement(t_data *data, char *base, char *result);
t_token	**create_list(t_data *data, t_token **p_token, char *str, int i);

/*concatenation.c*/
char	*final_replacment_next(t_data *data, char *base, int *i, char *result);
char	*single_quote(char *base, char *result);
char	*double_quote(t_data *data, char *base, char *result, int is_ok);
int		first_len(char *base, int is_ok);
char	*replace_var(t_data *data, char *base, char *result, int i);

/*sorting_utils.c*/
int		is_file(t_token *token);
int		is_operator(char *str);
int		is_operator_final(t_token *token);
void	sorting(t_token *token);

/*checking.c*/
int		checking(t_token *token);
int		is_double(t_token *token);
int		is_red_ok(t_token *token);
int		is_pipe_ok(t_token *token);
void	syntax_error(t_token *token);

/*execution.c*/
void	execution(t_data *data);
void	exec_pipe(t_data *data, t_token *token, char *result, int i);
void	simple_exec(t_data *data, t_token *token);
void	exec_builtin(t_data *data, t_token *token, int info, int exit_status);
void	exec_builtin_base(t_data *data, t_token *token);

/*execution_utils.c*/
void	ft_execute(t_data *data, char **cmdoption);
void	is_ok(t_data *data, char **cmdoption);
void	ft_wait(t_data *data, int i);
void	what_exit(t_data *data, int exit_status);
int		is_builtin(char *str);

/*here_doc.c*/
void	fill_hd(t_token *token, int **hdfd, int i, char *delimiter);
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
int		ft_exit(t_data *data, t_token *token, int status);

/*builtins_env.c*/
int		export(t_data *data, t_token *token, int exit_status, int err);
int		unset(t_data *data, t_token *token);
int		env(char **env, t_token *token);
int		search_supp(t_data *data, t_token *token, char *var, int i);

/*builtins_utils.c*/
int		is_valid_opt_echo(char *str);
int		update_pwd(t_data *data);
int		too_many_arg(t_token *token, char *cmd);
t_token	*pass_arg(t_token *token);
int		find_next_arg(t_token *token);

/*get.c*/
char	*getname(char *str);
char	*ft_getenv(char	*name, t_data *data);
char	*grab_var(char *base, t_data *data);
char	*get_last_exit_status(int num);

/*lst_util.c*/
t_token	*lstnew(char *base, char *str);
void	lstadd_back(t_token	**token, t_token *new);
t_token	*lstlast(t_token *token);
void	lstdel(t_token **token);

/*utils.c*/
int		length(char const *s, char c);
char	*strjoin(char *s1, char *s2, int len);
int		count_pipe(t_token *token);
int		count_hd(t_token *token);
char	*howsub(char *s, int i);

/*double_tab.c*/
int		find_len(t_token *token);
char	**build_command_tab(t_token *token);
void	swap_pchar(char **p1, char **p2);
void	bubble_sort_tab(char **sorted);

/*print.c*/
void	printlst(t_token **p_token);
int		print_sorted(t_data *data, char **sorted, int i);
void	print_tab(char **table);
void	print_token_echo(t_token *token);

/*init.c*/
int		init(t_data *data, char **envp);
int		init_structs(t_data *data);
int		**make_pipefds(int **pipefd, int nb_pipes);

/*preps.c*/
void	prep_exec(t_data *data, char *input);
int		prep_pipe(t_data *data);
int		prep_hd(t_data *data);
int		prep_tab(char *array, int num);

/*mallocs.c*/
char	**env_alloc(char **env);
int		*pid_alloc(int nb_commands);
int		**pipefd_alloc(int nb_pipes);

/*close_and_free.c*/
void	close_unused_fd(int **pipefd, int nb_pipes, int i);
void	close_all(int **pipefd, int nb_pipes);
void	free_data(t_data *data);
void	free_dtab(char **array);
void	free_pipe(t_data *data);

#endif
