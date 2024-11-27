#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_line
{
	char	buffer[BUFFER_SIZE];
	char	*next;
	ssize_t	ret;
	ssize_t	len_res;
	ssize_t	len_buf;
}	t_line;

// Random functions
int		ft_strlen(char *str);
char	*ft_strdup(const char *s);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(char *s1, char *s2, int n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size);

// Get Next Line Functions
char	*get_next_line(int fd);
ssize_t	find_end_line(char const *str, ssize_t len);
char	*fill_result(t_line *line, int fd, char *res, ssize_t len);
char	*ft_strjoin(t_line *line, char *begin, char *res);
char	*exception(t_line *line, char *res, ssize_t len);

#endif
