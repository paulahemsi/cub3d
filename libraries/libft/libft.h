/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 19:02:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2021/04/19 21:39:30 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/param.h>
# include <sys/resource.h>
# include <stdarg.h>

# define READ_LINE		1
# define NEW_LINE		1
# define NO_NEW_LINE	0
# define TRUE			1
# define FALSE			0
# define ERROR			-1
# define POINTER		'p'

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

typedef struct s_ft_printf
{
	char		*ptr;
	int			length;
	int			left_align;
	int			zero_padding;
	int			min_width;
	int			precision;
}				t_flags;

typedef struct s_split
{
	size_t		sub_length;
	size_t		i_array;
	size_t		words;
	size_t		i;
}				t_split;

typedef struct s_get_next_line
{
	char		read[BUFFER_SIZE + 1];
	char		*temp;
	char		*break_line_ptr;
	int			read_return;
}				t_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_itoa_hex
{
	char	*hex;
	int		to_hex;
	int		length;
	int		case_c;
	char	temp;
}				t_itoa_hex;

/*
**  PART 1
*/
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
/*
**  PART 2
*/
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s, char const *set);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strnstr(const char	*big, const char *little, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
/*
**  BONUS
*/
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
/*
**  EXTRAS
*/
void			ft_strclr(char *s);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putnbr(int nb);
void			ft_putendl(char const *s);
int				ft_isspace(int c);
int				ft_isblank(int c);
int				ft_isxdigit(int c);
int				ft_countdigit(unsigned int number);
int				ft_isnegative(int number);
int				get_next_line(int fd, char **line);
int				get_next_line_multfd(int fd, char **line);
int				ft_add(int args, ...);
int				ft_numlen(int number);
char			*ft_itoa_hex(unsigned long int number, char case_char);
void			ft_putnbr_unsigned(unsigned int nb);
/*
**  FT_PRINTF
*/
int				ft_printf(const char *str, ...);
size_t			flags_parser(char **ptr, va_list args, size_t length);
void			print_char(t_flags *flag, va_list args);
int				print_string(t_flags *flag, va_list args);
void			print_integer(t_flags *flag, va_list args);
int				print_hex(t_flags *flag, va_list args);

#endif
