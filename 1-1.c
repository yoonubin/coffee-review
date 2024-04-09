// 실습문제 1번
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Node {
  char elem;
  struct Node *prev;
  struct Node *next;
} node;

void add(node *list, int rank, char ch);
void delete(node *list, int rank);
void get(node *list, int rank);
void print(node *list);

int main() {
  int N;
  scanf("%d", &N);
  getchar();
  char ch1, ch2;
  int rank;

  node *header = (node *)malloc(sizeof(node));
  if (header == NULL) {
    printf("not enough memory!");
    return -1;
  }
  node *trailer = (node *)malloc(sizeof(node));
  if (trailer == NULL) {
    printf("not enough memory!");
    return -1;
  }

  header->elem = NULL;
  header->prev = NULL;
  header->next = NULL;

  trailer->elem = NULL;
  trailer->next = NULL;
  trailer->prev = NULL;

  header->next = trailer;
  trailer->prev = header;

  while (N > 0) {
    scanf("%c", &ch1);
    getchar();
    if (ch1 == 'A')  // list의 rank순위에 원소 ch2 추가
    {
      scanf("%d %c", &rank, &ch2);
      getchar();
      add(header, rank, ch2);
      N--;
    } else if (ch1 == 'D')  // list의 순위 rank에 위치한 원소 삭제
    {
      scanf("%d", &rank);
      getchar();
      delete (header, rank);
      N--;
    } else if (ch1 == 'G')  // list의 순위 rank에 위치한 원소 반환
    {
      scanf("%d", &rank);
      getchar();
      get(header, rank);
      N--;
    } else {
      print(header);  // list의 모든 원소를 저장 순위대로 공백없이 출력
      N--;
    }
  }
  while (header != NULL) {
    free(header);
    header = header->next;
  }
  return 0;
}

void add(node *list, int rank, char ch) {
  node *newnode;
  node *tmp = list;

  newnode = (node *)malloc(sizeof(node));
  if (newnode == NULL) {
    printf("not enough memory!");
    return -1;
  }

  newnode->elem = ch;
  newnode->prev = NULL;
  newnode->next = NULL;
  int i, j;
  int flag = 0;

  if (rank == 1) {
    newnode->next = tmp->next;  // 새로운 노드 다음 노드 연결
    newnode->prev = tmp;        // 새로운 노드 이전 노드 연결
    tmp->next->prev = newnode;
    tmp->next = newnode;
  } else {
    for (i = 0; i < rank; i++) {
      tmp = tmp->next;
      if (tmp == NULL) {
        printf("invalid position\n");
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      newnode->next = tmp;
      newnode->prev = tmp->prev;
      tmp->prev->next = newnode;
      tmp->prev = newnode;
    }
  }
}
void delete(node *list, int rank) {
  node *tmp = list;

  int flag = 0;
  int i, j;

  for (i = 0; i < rank; i++) {
    tmp = tmp->next;
    if (tmp->elem == NULL) {
      printf("invalid position");
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    free(tmp);
  }
}
void get(node *list, int rank) {
  node *tmp = list;
  int flag = 0;
  int i, j;

  for (i = 0; i < rank; i++) {
    tmp = tmp->next;
    if (tmp->elem == NULL) {
      printf("invalid position\n");
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    printf("%c\n", tmp->elem);
  }
}
void print(node *list) {
  node *tmp = list;
  int flag = 0;
  while (1) {
    tmp = tmp->next;
    if (tmp->elem == NULL) {
      if (flag == 0) {
        printf("invalid position");
      }
      break;
    } else {
      printf("%c", tmp->elem);
      flag = 1;
    }
  }
  printf("\n");
}
