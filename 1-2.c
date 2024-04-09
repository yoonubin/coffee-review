#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_s {
  int elem;             // 노드의 데이터원소
  struct Node_s *prev;  // 이전 노드의 주소
  struct Node_s *next;  // 다음 노드의 주소
} Node;

typedef struct DoublelinkedList_s {
  Node *header;   // 리스트의 헤더
  Node *trailer;  // 리스트의 트레일러
  int n;          // 이중연결리스트 노드의 개수
} DoublelinkedList;

// 이중연결리스트 초기화
void initialize(DoublelinkedList *list) {
  list->header = (Node *)malloc(sizeof(Node));  // 헤더 노드 할당 getnode()
  list->trailer = (Node *)malloc(sizeof(Node));  // 트레일러 노드 할당 getnode()
  list->header->next =
      list->trailer;  // 헤더 노드의 다음 주소는 트레일러 노드의 주소
  list->trailer->prev =
      list->header;  // 트레일러 노드의 이전 주소는 헤더 노드의 주소

  list->header->elem = 0;  // 헤더와 노드의 원소 값은 0으로 초기화
  list->trailer->elem = 0;

  list->header->prev =
      NULL;  // 헤더의 이전 노드 주소와 트레일러의 다음 노드 주소는 null값
  list->trailer->next = NULL;

  list->n = 0;  // 노드 개수는 아직 하나도 없으므로 0

  return;
}

// 삽입
void add(DoublelinkedList *list, int r, char e) {
  if ((r < 1) || (r > (list->n + 1))) {
    printf("invalid position\n");
    return;
  }

  // 노드 개수가 0일때 (즉, 헤더와 트레일러 노드만 초기에 존재할 때)
  if (list->n == 0) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->elem = e;
    newNode->prev = list->header;
    newNode->next = list->trailer;
    list->header->next = newNode;
    list->trailer->prev = newNode;

    list->n += 1;  // 노드 개수 +1

    return;
  }

  Node *p = list->header;

  for (int i = 1; i < r + 1; i++) {
    p = p->next;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->elem = e;
  newNode->prev = p->prev;
  newNode->next = p;
  p->prev->next = newNode;
  p->prev = newNode;

  list->n += 1;

  return;
}

void delete(DoublelinkedList *list, int r) {
  if (r < 1 || r > list->n) {
    printf("invalid position\n");
    return;
  }

  Node *p = list->header;
  p = p->next;

  for (int i = 1; i < r; i++) {
    p = p->next;
  }

  p->prev->next = p->next;
  p->next->prev = p->prev;
  free(p);
  list->n -= 1;
  return;
}

// r 순위의 원소값 반환
char get(DoublelinkedList *list, int r) {
  if (r < 1 || r > list->n) {
    printf("invalid position\n");
    return '\n';
  }

  Node *p = list->header;

  for (int i = 1; i < r + 1; i++) {
    p = p->next;
  }

  return p->elem;
}

void print(DoublelinkedList *list) {
  Node *p = list->header;
  p = p->next;

  if (list->n == 0) {
    printf("invalid position\n");
    return;
  }

  for (int i = 1; i < list->n + 1; i++) {
    printf("%c", p->elem);
    p = p->next;
  }
  printf("\n");
}

int main() {
  DoublelinkedList *list = (DoublelinkedList *)malloc(sizeof(DoublelinkedList));

  initialize(list);

  int n;
  scanf("%d", &n);
  getchar();

  char menu, target;
  int r;
  for (int i = 0; i < n; i++) {
    scanf("%c", &menu);

    switch (menu) {
      case 'A':
        scanf("%d %c", &r, &target);
        getchar();
        add(list, r, target);

        break;
      case 'D':
        scanf("%d", &r);
        getchar();
        delete (list, r);
        break;
      case 'G':
        scanf("%d", &r);
        getchar();
        printf("%c\n", get(list, r));
        break;
      case 'P':
        getchar();
        print(list);
      default:
        break;
    }
  }

  Node *curr = list->header;
  Node *temp;

  while (curr->next != NULL) {
    temp = curr;
    free(temp);
    curr = curr->next;
  }
  free(curr);

  free(list->header);
  free(list->trailer);
  free(list);
  return 0;
}