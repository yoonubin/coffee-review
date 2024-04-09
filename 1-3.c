#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  char elem;
  struct Node *next;
  struct Node *prev;
} Node;

void add(Node *head, int r, char e) {
  Node *node_to_add = (Node *)malloc(sizeof(Node));
  node_to_add->elem = e;
  Node *current_node = head;
  for (int i = 0; i < r - 1; i++) {
    current_node = current_node->next;
    if (current_node->next == NULL) {
      printf("invalid position\n");
      return;
    }
  }

  node_to_add->next = current_node->next;
  current_node->next = node_to_add;
  node_to_add->prev = current_node;
  (node_to_add->next)->prev = node_to_add;
}

void deleteN(Node *head, int r) {
  Node *to_remove = head;
  for (int i = 0; i < r; i++) {
    to_remove = to_remove->next;
    if (to_remove->next == NULL) {
      printf("invalid position\n");
      return;
    }
  }
  to_remove->next->prev = to_remove->prev;
  to_remove->prev->next = to_remove->next;
  free(to_remove);
}

char get(Node *head, int r) {
  Node *current_node = head;
  for (int i = 0; i < r; i++) {
    current_node = current_node->next;
    if (current_node->next == NULL) {
      printf("invalid position\n");
      return ' ';
    }
  }
  return current_node->elem;
}

void print(Node *head) {
  Node *current_node = head->next;
  while (current_node->next != NULL) {
    printf("%c", current_node->elem);
    current_node = current_node->next;
  }
  printf("\n");
}

// 5
// A 1 S
// A 2 t
// A 3 r
// A 4 a
// P

int main() {
  Node *head = (Node *)malloc(sizeof(Node));
  Node *trailer = (Node *)malloc(sizeof(Node));
  head->next = trailer;
  trailer->prev = head;
  trailer->next = NULL;
  int n, r;
  char e;
  char command, tmp;
  scanf("%d", &n);
  getchar();

  for (int i = 0; i < n; i++) {
    scanf("%c%c", &command, &tmp);
    if (command == 'A') {
      scanf("%d %c", &r, &e);
      getchar();
      add(head, r, e);
    } else if (command == 'D') {
      int r;
      scanf("%d", &r);
      getchar();
      deleteN(head, r);
    } else if (command == 'G') {
      scanf("%d", &r);
      getchar();
      printf("%c", get(head, r));
    } else if (command == 'P') {
      print(head);
    }
  }
  Node *to_free = head->next;
  while (to_free->next != NULL) {
    to_free = to_free->next;
    free(to_free->prev);
  }
  free(head);
  free(trailer);
  return 0;
}
