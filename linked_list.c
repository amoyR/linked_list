#include <stdio.h>
#include <stdlib.h>

typedef struct user_data_tag
{
  int id;
  struct user_data_tag *next_user;
} user_data;


user_data *fetch_node (user_data *initial_node, int index)
{
  user_data *target;
  int i = 0;

  for (target = initial_node; i < index; target = target->next_user) {
    i++;

    if (target->next_user == NULL) {
      break;
    }
  }

  return target;
}


user_data *insert_node (user_data *initial_node, int index, int new_node_id)
{
  user_data *new_node;
  new_node = (user_data*)malloc(sizeof(user_data));
  new_node->id = new_node_id;

  if (index == 0) {

    new_node->next_user = initial_node;

  } else {
    user_data *pre_node;
    pre_node = fetch_node(initial_node, index - 1); 

    new_node->next_user = pre_node->next_user;
    pre_node->next_user = new_node;
  }

  return new_node;
}


user_data *delete_node (user_data *initial_node, int index)
{
  user_data *delete_node;
  delete_node = fetch_node(initial_node, index);

  user_data *next_node;
  next_node = fetch_node(initial_node, index + 1);

  if (index == 0) {
    free(delete_node);
  } else {
    user_data *pre_node;
    pre_node = fetch_node(initial_node, index - 1);

    pre_node->next_user = delete_node->next_user;

    free(delete_node);
  }

  return next_node;
}


int delete_all_node (user_data *initial_node)
{
  user_data *delete_node;
  user_data *next_delete_node;

  for (delete_node = initial_node; ; delete_node = next_delete_node) {
    next_delete_node = delete_node->next_user;
    free(delete_node); 
    if (next_delete_node == NULL) {
      break;
    }
  }

  printf("completed delete all\n");

  return 0;
}


int print_linked_list (user_data *initial_node)
{
  for (user_data *current_node = initial_node; ; current_node = current_node->next_user) {
    printf("id -> %d\n", current_node->id);

    if (current_node->next_user == NULL) {
      break;
    }
  }

  return 0;
}


int main (void)
{
  user_data *head;
  head = (user_data*)malloc(sizeof(user_data));
  head->id = 0;
  head->next_user = NULL;


  for (int i = 1; i < 6; i++) {
    insert_node(head, i, i);
  }

  print_linked_list(head);

  insert_node(head, 3, 100);
  print_linked_list(head);

  head = insert_node(head, 0, 200);
  print_linked_list(head);

  head = delete_node(head, 0);
  delete_node(head, 3);
  print_linked_list(head);

  delete_all_node(head);
  return 0;
}

