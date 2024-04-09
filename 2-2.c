#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 노드 */
typedef struct Node_s {
  int coef;             // 항의 계수 (데이터 원소 같은 느낌)
  int exp;              // 항의 지수
  struct Node_s *next;  // 다음 노드를 가리키는 링크
} Node;

/* 헤더 단일연결리스트 */
typedef struct linkedList_s {
  Node *header;  // 리스트의 헤더
} linkedList;

/* 리스트 초기화 */
void initialize(linkedList *list) {
  list->header = (Node *)malloc(sizeof(Node));
  list->header->coef = 0;
  list->header->exp = 0;
  list->header->next = NULL;
  return;
}

/* 다항식에 항 추가 */
void appendTerm(Node *k, int c, int e) {
  Node *newNode = (Node *)malloc(sizeof(Node));  // k 다음 더해지는 노드
  newNode->coef = c;
  newNode->exp = e;
  newNode->next = NULL;
  k->next = newNode;

  return;
}

/* 리스트 출력 */
void print(linkedList *list) {
  Node *p = list->header;

  while (p->next != NULL) {
    p = p->next;
    printf(" %d %d", p->coef, p->exp);
  }
  printf("\n");
  return;
}

/* 다항식 덧셈 -> 더해진 다항식 반환 */
linkedList *addPoly(Node *x, Node *y) {
  // 두 다항식을 더한 결과 다항식
  linkedList *result = (linkedList *)malloc(sizeof(linkedList));
  initialize(result);
  Node *r = result->header;
  r->next = NULL;
  Node *i = x->next;  // x의 헤더 건너뛰기
  Node *j = y->next;  // y의 헤더 건너뛰기

  Node *k = r;
  while ((i != NULL) && (j != NULL)) {
    if (i->exp > j->exp) {
      appendTerm(k, i->coef, i->exp);
      i = i->next;
      k = k->next;
    } else if (i->exp < j->exp) {
      appendTerm(k, j->coef, j->exp);
      j = j->next;
      k = k->next;
    } else {
      int sum = i->coef + j->coef;
      if (sum != 0) {
        appendTerm(k, sum, i->exp);
        k = k->next;
      }
      i = i->next;
      j = j->next;
    }
  }

  while (i != NULL) {
    appendTerm(k, i->coef, i->exp);
    i = i->next;
    k = k->next;
  }

  while (j != NULL) {
    appendTerm(k, j->coef, j->exp);
    j = j->next;
    k = k->next;
  }
  k = NULL;

  return result;
}

void freeList(Node *header) {
  Node *p = header;
  Node *prev;
  while (p->next != NULL) {
    prev = p;
    p = p->next;
    free(prev);
  }
}

int main() {
  /* firstList */
  linkedList *firstList = (linkedList *)malloc(sizeof(linkedList));
  initialize(firstList);

  Node *p = firstList->header;

  int n1;
  scanf("%d", &n1);

  int c, e;
  for (int i = 0; i < n1; i++) {
    scanf("%d %d", &c, &e);

    appendTerm(p, c, e);
    p = p->next;
  }

  /* secondList */
  linkedList *secondList = (linkedList *)malloc(sizeof(linkedList));
  initialize(secondList);

  Node *q = secondList->header;

  int n2;
  scanf("%d", &n2);

  for (int i = 1; i < n2 + 1; i++) {
    scanf("%d %d", &c, &e);

    appendTerm(q, c, e);
    q = q->next;
  }

  p = firstList->header;
  q = secondList->header;
  linkedList *result = addPoly(p, q);

  print(result);

  freeList(p);
  freeList(q);
  free(firstList);
  free(secondList);
  return 0;
}