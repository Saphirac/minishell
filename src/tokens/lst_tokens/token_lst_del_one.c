/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_del_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:34:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/03/08 19:47:09 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  token_lst_del_one(t_token_lst *const list, t_token *const node)
{
  if (list->size == 1)
  {
    list->head = NULL;
    list->tail = NULL;
  }
  else if (node == list->head)
  {
    list->head = node->next;
    list->head->prev = NULL;
  }
  else if (node == list->tail)
  {
    list->tail = node->prev;
    list->tail->next = NULL;
  }
  else
  {
    node->next->prev = node->prev;
    node->prev->next = node->next;
  }
  --list->size;
  free(node);
}
