#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct node {
  char *word;
  int count;
  struct node * left;
  struct node * right;
} Word;

int get_word(FILE *, char *);
void tree_print(Word *);
Word * add_tree(Word *, char *);

int
main(int argc, char *argv[]){
  FILE *f = NULL;
  f = fopen(argv[1], "r");

  if(!f){
    printf("Open file failed!\n");
    return 1;
  }

  char word_buffer[20];
  Word *root = NULL;

  while(get_word(f, word_buffer)){
    // printf("%s\n", word_buffer);
    if(strlen(word_buffer))
      root = add_tree(root, word_buffer);
  }

  tree_print(root);

  fclose(f);
  return 0;
}

int
get_word(FILE* f, char *word_buffer){
  char ch;

  while( !feof(f) && isalpha(ch = fgetc(f)) ){
    *(word_buffer++) = ch;
  }

  *word_buffer = '\0';

  if(feof(f)) return 0;
  return 1;
}

Word *
add_tree(Word * p, char * word_buffer){
  // printf("insdfsdf\n");
  int cond;

  if(p == NULL){
    p = (Word * )malloc(sizeof(Word));
    p->count = 1;
    p->word = (char *)malloc(sizeof(word_buffer) + 1);
    strcpy(p->word, word_buffer);
    p->left = p->right = NULL;
  }
  else if ( (cond = strcmp(word_buffer, p->word)) == 0 )
    p->count++;
  else if ( cond < 0 )
    p->left = add_tree(p->left, word_buffer);
  else
    p->right = add_tree(p->right, word_buffer);

  return p;
}

void
tree_print(Word * root){
  if(root){
    tree_print(root->left);
    printf("%3d %s\n", root->count, root->word);
    tree_print(root->right);
  }
}

