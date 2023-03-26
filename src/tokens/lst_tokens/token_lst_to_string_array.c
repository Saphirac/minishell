/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_to_string_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:16:04 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/27 01:32:57 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Sum the given array of size_t.
 * 
 * @param	nbs The array to sum.
 * @param	size The size of the array to sum.
 * 
 * @return	The sum of the array.
 */
inline static size_t	__sum(size_t const *nbs, size_t size)
{
	size_t	sum;

	sum = 0LU;
	while (size)
	{
		sum += *nbs;
		++nbs;
		--size;
	}
	return (sum);
}

/**
 * @brief	Fill the given array of strings with the strings from the given
 * 			token list.
 * 
 * @param	array The array to fill.
 * @param	ptr A pointer to the first string of the array.
 * @param	node The first node of the token list.
 * @param	sizes The sizes of the strings in the token list.
 */
inline static char	**__fill(
	char **array,
	char *ptr,
	t_token const *node,
	size_t const *sizes)
{
	char **const	backup = array;

	while (node)
	{
		*array = ptr;
		ft_memcpy(ptr, node->str, *sizes);
		ptr += *sizes;
		++array;
		++sizes;
		node = node->next;
	}
	*array = NULL;
	return (backup);
}

/**
 * @brief	Allocate a new array of strings, and fill it with the strings
 * 			from the given token list. The new array is NULL-terminated.
 * 
 * @param	list The token list to convert.
 * 
 * @return	The new array of strings, or NULL if an error occured.
 */
char	**token_lst_to_string_array(t_token_lst const *const list)
{
	t_token const	*node = list->head;
	size_t			*sizes;
	char			**array;

	sizes = malloc(list->size * sizeof(size_t));
	if (!sizes)
		return (NULL);
	while (node)
	{
		*sizes = ft_strlen(node->str) + 1LU;
		++sizes;
		node = node->next;
	}
	sizes -= list->size;
	array = malloc((list->size + 1) * sizeof(char *)
			+ __sum(sizes, list->size) * sizeof(char));
	if (!array)
		return (free(sizes), NULL);
	array = __fill(array, (char *)(array + list->size + 1), list->head, sizes);
	free(sizes);
	return (array);
}
