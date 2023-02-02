/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_append_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 05:18:43 by fra           #+#    #+#                 */
/*   Updated: 2023/02/02 15:30:42 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_char(char to_add, char **str)
{
	size_t	length;
	char	*tmp;

	if (! to_add)
		return (*str);
	else if (! str)
		return (NULL);
	length = ft_strlen(*str);
	tmp = malloc((length + 2) * sizeof(char));
	if (tmp)
	{
		ft_memcpy(tmp, *str, length);
		tmp[length++] = to_add;
		tmp[length] = 0;
	}
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	*str = tmp;
	return (tmp);
}
