#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_SIZE 101

typedef struct node {
  struct node * next;
  char * name;
  char * content;
} nlist;

static nlist * hash_table[HASH_SIZE];

unsigned hash(char * s){
  unsigned hash_value;
  for (hash_value = 0; *s != '\0'; ++s){
    hash_value = hash_value * 31 + *s;
  }
  return hash_value % HASH_SIZE;
}

nlist *
lookup(char * name){
  nlist * np;
  for(np = hash_table[hash(name)]; np != NULL; np = np->next)
    if(strcmp(name, np->name) == 0)
      return np;
  return NULL;
}

char * lookup_content(char * name){
  nlist * np;
  for(np = hash_table[hash(name)]; np != NULL; np = np->next)
    if(strcmp(name, np->name) == 0)
      return np->content;
  return NULL;
}

char *
_strdup(char * content){
  char * p = (char *)malloc(sizeof(content) + 1);
  if(p)
    strcpy(p, content);
  return p;
}

nlist *
install(char * name, char * content){
  nlist * np;
  unsigned hash_value;

  if( (np = lookup(name)) == NULL ){
    np = (nlist *)malloc(sizeof(nlist));
    if( np == NULL || (np->name = _strdup(name)) == NULL)
      return NULL;
    hash_value = hash(name);
    np->next = hash_table[hash_value];
    hash_table[hash_value] = np;
  } else
    free((void *) np->content);
  if((np->content = _strdup(content)) == NULL)
    return NULL;
  return np;
}

int
main(){
  install("first_name", "david");
  install("last_name", "qhr");

  printf("first_name is: %s\n", lookup_content("first_name"));
  printf("last_name is: %s\n", lookup_content("last_name"));

  install("first_name", "davidqhr");
  printf("first_name has changed, now it is: %s\n", lookup_content("first_name"));
  return 0;
}

