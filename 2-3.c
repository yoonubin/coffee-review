#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int coef;
  int exp;
  struct Node *next;
} Node;

void appendTerm(Node **k, int c, int e) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->coef = c;
  new_node->exp = e;
  new_node->next = NULL;

  (*k)->next = new_node;
  *k = new_node;
}

Node *addPoly(Node *poly1, Node *poly2) {
  Node *result = (Node *)malloc(sizeof(Node));
  result->next = NULL;
  Node *result_init = result;
  Node *i = poly1->next;
  Node *j = poly2->next;
  int sum;
  while ((i != NULL) && (j != NULL)) {
    if (i->exp > j->exp) {
      appendTerm(&result_init, i->coef, i->exp);
      i = i->next;
    } else if (i->exp < j->exp) {
      appendTerm(&result_init, j->coef, j->exp);
      j = j->next;
    } else {
      sum = i->coef + j->coef;
      if (sum != 0) appendTerm(&result_init, sum, i->exp);
      i = i->next;
      j = j->next;
    }
  }
  while (i != NULL) {
    appendTerm(&result_init, i->coef, i->exp);
    i = i->next;
  }
  while (j != NULL) {
    appendTerm(&result_init, j->coef, j->exp);
    j = j->next;
  }
  return result;
}

void freePoly(Node *poly) {
  Node *current = poly;
  while (current != NULL) {
    Node *nextNode = current->next;
    free(current);
    current = nextNode;
  }
}

int main() {
  Node *poly1_head = (Node *)malloc(sizeof(Node));
  Node *poly2_head = (Node *)malloc(sizeof(Node));
  Node *poly1_init = poly1_head;
  Node *poly2_init = poly2_head;
  int poly1_size, poly2_size, c, e;
  scanf("%d", &poly1_size);
  for (int i = 0; i < poly1_size; i++) {
    scanf("%d %d", &c, &e);
    appendTerm(&poly1_init, c, e);
    // poly1_init = poly1_init->next;
  }
  scanf("%d", &poly2_size);
  for (int i = 0; i < poly2_size; i++) {
    scanf("%d %d", &c, &e);
    appendTerm(&poly2_init, c, e);
    // poly2_init = poly2_init->next;
  }

  Node *result = addPoly(poly1_head, poly2_head);
  Node *result_print = result->next;

  while (result_print != NULL) {
    printf(" %d %d", result_print->coef, result_print->exp);
    result_print = result_print->next;
  }

  freePoly(poly1_head);
  freePoly(poly2_head);
  freePoly(result);
}