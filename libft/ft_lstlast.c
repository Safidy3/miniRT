/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safandri <safandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 13:14:06 by safandri          #+#    #+#             */
/*   Updated: 2025/02/20 16:12:20 by safandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lst_id(t_list *lst, int id)
{
	int	i;

	i = -1;
	if (!lst || id < 0 || id > ft_lstsize(lst))
		return (NULL);
	while (++i != id && lst->next)
		lst = lst->next;
	return (lst);
}
