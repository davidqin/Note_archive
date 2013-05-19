#include<stdio.h>
typedef struct Node {
  int data;
  struct Node * next;
} Node;

struct Node * init_list_old(){
  Node * head;
  Node first, second, third;
  head = &first;

  first.data = 1;
  first.next = &second;

  second.data = 2;
  second.next = &third;

  third.data = 3;
  third.next = NULL;

  return head;
}

Node * init_list(){
  Node * head = NULL;
  Node * tail = NULL;

  int i;
  for(i=0;i<10;i++){
    Node tmp;
    if(!head) head = &tmp;

    tmp.data = i + 1;
    tmp.next = NULL;

    tail->next = &tmp;
  }

  return head;
}

void print_list(Node * head){
  Node * pointer = head;




  // pointer = head;

  // printf("%d ", pointer->data);
  // pointer = pointer->next;


  // printf("%d ", pointer->data);


  // pointer = pointer->next;
  // printf("%d\n", pointer->data);
  // while(pointer != NULL){
    // printf("%d ", pointer->data);
    // pointer = pointer->next;
    // printf("%d ", pointer->data);
    // pointer = pointer->next;
  // }
}

int main(){
  Node * head = init_list();

  printf("%d %d %d\n", head->data, head->next->data, head->next->next->data);
  // printf("%d %d %d\n", head->data, head->next->data, head->next->next->data);
  // print_list(head);
  return 0;
}
