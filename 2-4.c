#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int coef;
  int exp;
  struct node* next;
} NODE;

void printPoly(NODE* pheader) {
  NODE* p;
  p = pheader->next;
  while (p != NULL) {
    printf(" %d %d", p->coef, p->exp);
    p = p->next;
  }
  printf("\n");
}

void appendTerm(NODE* pheader, int c, int e) {
  NODE* newnode = (NODE*)malloc(sizeof(NODE));
  NODE* p;
  p = pheader;
  while (p->next != NULL) {  // p가 마지막 노드까지 이동
    p = p->next;
  }
  newnode->coef = c;
  newnode->exp = e;
  newnode->next = NULL;
  p->next = newnode;
}

NODE* addPoly(NODE* pheader1, NODE* pheader2) {
  NODE* result = (NODE*)malloc(sizeof(NODE));
  result->next = NULL;
  NODE* p1 = pheader1->next;
  NODE* p2 = pheader2->next;
  int sum = 0;
  while (p1 != NULL && p2 != NULL) {
    if (p1->exp > p2->exp) {  // P1이 P2보다 차수가 클 때
      appendTerm(result, p1->coef, p1->exp);
      p1 = p1->next;

    } else if (p1->exp < p2->exp) {  // P1이 P2보다 차수가 작을 때
      appendTerm(result, p2->coef, p2->exp);
      p2 = p2->next;

    } else {  // P1 P2 차수가 같을 때
      sum = p1->coef + p2->coef;
      if (sum != 0) {
        appendTerm(result, sum, p1->exp);
      }
      p1 = p1->next;
      p2 = p2->next;
    }
  }
  while (p1 != NULL) {
    appendTerm(result, p1->coef, p1->exp);
    p1 = p1->next;
  }
  while (p2 != NULL) {
    appendTerm(result, p2->coef, p2->exp);
    p2 = p2->next;
  }
  return result;
}

int main() {
  NODE* polynimial1 = (NODE*)malloc(sizeof(NODE));
  NODE* polynimial2 = (NODE*)malloc(sizeof(NODE));
  NODE* result = (NODE*)malloc(sizeof(NODE));
  polynimial1->next = NULL;
  polynimial2->next = NULL;

  int n, m;
  int coef, exp;
  scanf(" %d", &n);
  for (int i = 0; i < n; i++) {
    scanf(" %d %d", &coef, &exp);
    appendTerm(polynimial1, coef, exp);
  }
  scanf(" %d", &m);
  for (int i = 0; i < m; i++) {
    scanf(" %d %d", &coef, &exp);
    appendTerm(polynimial2, coef, exp);
  }
  result = addPoly(polynimial1, polynimial2);

  printPoly(result);

  return 0;
}