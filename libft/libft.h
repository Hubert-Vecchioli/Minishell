/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:01:54 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/18 15:12:14 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# define MAX_FD 64

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer
{
	char	content[BUFFER_SIZE];
	ssize_t	size;
}	t_buffer;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*ft_clean(char *line, t_buffer *buffer, size_t line_len, char to_find);
char	*ft_bfrjoin(char *line, t_buffer *buffer, size_t line_len);
int		ft_strchr_oth(char *str, char to_find, size_t line_len);
size_t	ft_max(size_t a, size_t b);
char	*ft_itoa(int n);
char	*ft_strchr(const char *str, int to_find);
char	*ft_strrchr(const char *str, int to_find);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, int wordlen);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	*ft_strnstr_end(const char *str, const char *to_find, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_split_charset(char const *s, char *charset);
char	*ft_realpath(const char *path, char *resolved_path);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_iswhitespace(int c);
int		ft_lstsize(t_list *lst);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_tablen(char **tab);
void	ft_bzero(void *ptr, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	*ft_realloc(void *ptr, size_t size);
void	*ft_calloc(size_t n, size_t size);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_memset(void *ptr, int x, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *str1, const void *str2, size_t n);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
