/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_string_array.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:16:04 by jodufour          #+#    #+#             */
/*   Updated: 2023/03/27 19:41:03 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_lengths	t_lengths;

struct s_lengths
{
	size_t	name;
	size_t	equal;
	size_t	value;
};

/**
 * @brief	Sum the given array of t_sizes.
 * 
 * @param	nbs The array to sum.
 * @param	size The size of the array to sum.
 * 
 * @return	The sum of the array.
 */
inline static size_t	__sum(t_lengths const *nbs, size_t size)
{
	size_t	sum;

	sum = 0LU;
	while (size)
	{
		sum += nbs->name + nbs->equal + nbs->value;
		++nbs;
		--size;
	}
	return (sum);
}

/**
 * @brief	Fill the given array of strings with the strings from the given
 * 			env list.
 * 
 * @param	array The array to fill.
 * @param	ptr A pointer to the first string of the array.
 * @param	node The first node of the env list.
 * @param	lengths The lengths of the strings in the env list.
 */
inline static char	**__fill(
	char **array,
	char *ptr,
	t_env const *node,
	t_lengths const *lengths)
{
	char **const	backup = array;

	while (node)
	{
		*array = ptr;
		ft_memcpy(ptr, node->name, lengths->name);
		lengths->equal && (ptr[lengths->name] = '=');
		lengths->value && ft_memcpy(ptr + lengths->name + lengths->equal,
			node->value, lengths->value);
		ptr += lengths->name + lengths->equal + lengths->value;
		*ptr = 0;
		++ptr;
		++array;
		++lengths;
		node = node->next;
	}
	*array = NULL;
	return (backup);
}

/**
 * @brief	Allocate a new array of strings, and fill it with the strings
 * 			from the given env list. The new array is NULL-terminated.
 * 
 * @param	list The env list to convert.
 * 
 * @return	The new array of strings, or NULL if an error occured.
 */
char	**env_lst_to_string_array(t_env_lst const *const list)
{
	t_env const	*node = list->head;
	t_lengths	*lengths;
	char		**array;

	lengths = malloc(list->size * sizeof(t_lengths));
	if (!lengths)
		return (NULL);
	while (node)
	{
		lengths->name = ft_strlen(node->name);
		lengths->equal = !!node->value;
		lengths->value = 0LU;
		node->value && (lengths->value = ft_strlen(node->value));
		++lengths;
		node = node->next;
	}
	lengths -= list->size;
	array = malloc((list->size + 1) * sizeof(char *)
			+ (__sum(lengths, list->size) + list->size) * sizeof(char));
	if (!array)
		return (free(lengths), NULL);
	array = __fill(array, (char *)(array + list->size + 1), list->head,
			lengths);
	return (free(lengths), array);
}
