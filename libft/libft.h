/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:07:45 by safandri          #+#    #+#             */
/*   Updated: 2025/04/03 06:01:10 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>

int					ft_isalpha(char c);
int					ft_isdigit(int num);
int					ft_isalnum(int num);
int					ft_is_number(char *str);
int					ft_isascii(int num);
int					ft_isprint(int num);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *ptr, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memswap(void *dest, void *src);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strcmp3(const char *s1, const char *s2, const char *s3);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *str, const char *sub, size_t len);
int					ft_atoi(const char *str);
long int			ft_atoi_long(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				**ft_split_space(const char	*input);
int					ft_isspace(int c);
int					ft_arr_len(void **a);
char				*ft_itoa(int n);
char				*ft_itoa_base(long int nbr, char *base);
char				*ft_itoa_unsigned_base(unsigned int nbr, char *base);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr_err(char *s);
void				ft_putstr(char *s);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr_base_fd(int nbr, char *base);
void				ft_put_unsigned_nbr_base_fd(long long int nbr, char *base);
size_t				ft_nbr_base_len(long long int nbr, char *base);
char				*ft_strrev(const char *s);
char				*ft_join_str_char(char *s, char c);
char				*ft_join_char_str(char c, char *s);
int					ft_power(int nb, int power);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lst_id(t_list *lst, int id);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_content_back(t_list **lst, void *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));

#endif
