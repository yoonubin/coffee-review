// 연결리스트 실습 2번문제
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Node {
  int coef;           // 항의 계수
  int exp;            // 항의 차수
  struct Node *next;  // 다음 항 연결포인터
} node;

int *appendTerm(node *k, int c, int e) {
  node *newnode = (node *)malloc(sizeof(node));
  if (newnode == NULL) {
    printf("not enough memory!");
    return -1;
  }
  newnode->coef = c;
  newnode->exp = e;
  newnode->next = NULL;

  k->next = newnode;  // 다음 항 연결
  k = newnode;        // 다음 항으로 넘어가기

  return k;
}
int *addPoly(node *x, node *y) {
  node *header = (node *)malloc(sizeof(node));
  if (header == NULL) {
    printf("not enough memory!");
    return -1;
  }
  header->coef = NULL;  // 헤더노드 설정
  header->exp = NULL;
  header->next = NULL;

  node *i, *j;
  i = x->next;
  j = y->next;

  node *k = header;

  while ((i != NULL) && (j != NULL)) {
    if (i->exp > j->exp)  // 항의 차수가 높은 항을 채우기
    {
      k = appendTerm(k, i->coef, i->exp);
      i = i->next;
    } else if (i->exp < j->exp)  // 항의 차수가 높은 항을 채우기
    {
      k = appendTerm(k, j->coef, j->exp);
      j = j->next;
    } else  // 항의 차수가 같다면
    {
      int sum = i->coef + j->coef;  // 항의 계수를 더하고
      if (sum != 0) {
        k = appendTerm(k, sum, i->exp);  // 항 채우기
      }
      i = i->next;
      j = j->next;
    }
  }
  while (i != NULL)  // 남은 항 처리
  {
    k = appendTerm(k, i->coef, i->exp);
    i = i->next;
  }
  while (j != NULL)  // 남은 항 처리
  {
    k = appendTerm(k, j->coef, j->exp);
    j = j->next;
  }

  return header;
}
int main() {
  int N1, N2;

  node *x_header = (node *)malloc(sizeof(node));
  if (x_header == NULL) {
    printf("nor enough memory!");
    return -1;
  }
  x_header->coef = NULL;
  x_header->exp = NULL;
  x_header->next = NULL;

  int coef, exp;
  int i, j;

  scanf("%d", &N1);  // 항의 개수
  node *x = x_header;
  for (i = 0; i < N1; i++) {
    scanf("%d %d", &coef, &exp);   // 항의 계수와 차수 입력
    x = appendTerm(x, coef, exp);  // 첫번째 항 채우기
  }

  node *y_header = (node *)malloc(sizeof(node));
  if (y_header == NULL) {
    printf("nor enough memory!");
    return -1;
  }
  y_header->coef = NULL;
  y_header->exp = NULL;
  y_header->next = NULL;

  scanf("%d", &N2);  // 항의 개수
  node *y = y_header;
  for (i = 0; i < N2; i++) {
    scanf("%d %d", &coef, &exp);   // 항의 계수와 차수
    y = appendTerm(y, coef, exp);  // 두번째 항 채우기
  }

  node *result;
  result = addPoly(x_header, y_header);  // 다항식 합 계산
  result = result->next;

  while (result != NULL)  // 다항식 출력
  {
    printf(" %d %d", result->coef, result->exp);
    result = result->next;
  }

  // 동적할당 해제하기
  node *tmp;
  while (x_header != NULL) {
    tmp = x_header;
    x_header = x_header->next;
    free(tmp);
  }
  while (y_header != NULL) {
    tmp = y_header;
    y_header = y_header->next;
    free(tmp);
  }
  /*while (result != NULL)
  {
     result = result->next;
     free(result);
  }*/

  return 0;
}