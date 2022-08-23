#ifndef MINISHELL_H
# define MINISHELL_H

# define QUOT	39
# define DQUOT	34
# define SLASH	92
# define PIPE	124
# define MINUS	60
# define MAYUS	62

typedef struct s_token
{
    int type;
	int start;
    int end;	
}	t_token;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_minishell
{
    t_list  *token;
    char    *line;

}   t_minishell;

#endif