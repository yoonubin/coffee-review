
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char element;
  struct node* prev;
  struct node* next;
} NODE;

/* 리스트 초기화 함수 */
void init(NODE* phead, NODE* ptrail, int* plen) {
  phead->next = ptrail;  // header 와 trailer 연결
  phead->prev = NULL;
  ptrail->prev = phead;  // trailer 와 header 연결
  ptrail->next = NULL;
  *plen = 0;  // 리스트 길이 0으로 설정
}

/* 리스트 출력 함수 */
void printList(NODE* pheader, NODE* ptrailer) {
  NODE* p;
  p = pheader->next;       // p는 hearder 다음 노드 주소
  while (p != ptrailer) {  // p가 trailer 가 될 때까지 반복
    printf("%c", p->element);
    // printf("<-| %c |-> ", p->element);
    p = p->next;  // p는 다음 노드로 이동
  }
  printf("\n");
}

/* 노드 추가 함수 */
void addNode(NODE* pheader, int r, char element, int* plen) {
  /* 인덱스 오류 */
  if (r < 1 ||
      r > *plen +
              1) {  // 리스트 길이보다 크거나 1보다 작은 랭크가 들어오면 오류
    printf("invalid position\n");
    return;
  }
  /* r번째노드 구하기 */
  NODE* p;
  p = pheader;
  for (int i = 0; i < r; i++) {
    p = p->next;  // 현재노드를 다음노드로 r번 이동
  }
  /* 신규 노드 r번째에 추가 */
  NODE* newnode = (NODE*)malloc(sizeof(NODE));  // 신규노드 선언 후 초기화
  newnode->element = element;
  newnode->prev =
      p->prev;  // 신규노드의 이전노드 = 현재노드(r번째노드)의 이전노드
  newnode->next = p;  // 신규노드의 다음노드 = 현재노드
  p->prev->next =
      newnode;  // 현재노드의 이전노드(r-1번째노드)의 다음노드 = 신규노드
  p->prev = newnode;  // 현재노드의 이전노드 = 신규노드
  /* 리스트 길이 증가 */
  *plen += 1;
}

/* 노드 삭제 함수 */
void removeNode(NODE* pheader, int r, int* plen) {
  /* 인덱스 오류 */
  if (r < 1 || r > *plen) {
    printf("invalid position\n");
    return;
  }
  /* r번째 노드 구하기 */
  NODE* p;
  p = pheader;
  for (int i = 0; i < r; i++) {
    p = p->next;
  }
  /* r번째 노드 제거 */
  p->prev->next = p->next;
  p->next->prev = p->prev;
  free(p);
  /* 리스트 길이 감소 */
  *plen -= 1;
}

/* 노드 출력 함수 */
void getNode(NODE* pheader, int r, int* plen) {
  /* 인덱스 오류 */
  if (r < 1 || r > *plen) {
    printf("invalid position\n");
    return;
  }
  /* r번째 노드 구하기 */
  NODE* p;
  p = pheader;
  for (int i = 0; i < r; i++) {
    p = p->next;
  }
  /* 노드 문자로 출력하기 */
  printf("%c\n", p->element);
}

int main() {
  NODE* header = (NODE*)malloc(sizeof(NODE));
  NODE* trailer = (NODE*)malloc(sizeof(NODE));
  int len = 0;
  int rank, N;
  char command, element;

  init(header, trailer, &len);

  scanf(" %d", &N);
  for (int i = 0; i < N; i++) {
    scanf(" %c", &command);
    if (command == 'A') {
      scanf(" %d %c", &rank, &element);
      addNode(header, rank, element, &len);
    } else if (command == 'D') {
      scanf(" %d", &rank);
      removeNode(header, rank, &len);
    } else if (command == 'G') {
      scanf("%d", &rank);
      getNode(header, rank, &len);
    } else {
      printList(header, trailer);
    }
  }

  free(header);
  free(trailer);
  return 0;
}