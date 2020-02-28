#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

int string_length(char* str){
  int i =0;
  int counter = 0;
  while(str[i]){
    if(str[i]!=' '){
      counter++;}
    i++;
    }
    return counter;
}
/* convert the char into an integer to get
 the ascii value compare to the actuall ascii 
 table values and return 0 or 1*/
char is_valid_character(char c){
  int value = (int)c;
  if(value >32 && value <127){
    return '1';
  }
  return '0';

}
/*if it starts with a space it returns the 
  pointer to the first valid char*/
char* find_word_start(char* str){
  int counter=0;
  while(str[counter]){
    if(is_valid_character(str[counter])=='0'){
      counter++;}
    else{
      return &str[counter];
    }
  }
  return str;
}
/*traverse the array until the space after
  the first word is passed*/
char* find_word_end(char* str){
  int counter =0;
  while(str[counter]){
    if(is_valid_character(str[counter])=='0'){
      return &str[counter];
      }
      else{
	counter++;
      }
    }
    return str;
}

/*traverses the string and keeps a boolean int to save
if there was already a space before reaching a beginning 
of a word then counts one word for each space next to a valid char*/
int count_words(char* str){
  int valid = 1;
  int counter =0;
  int words =0;
  while(str[counter]){
    if(str[counter]==' '){
      valid = 1;
    }else if(is_valid_character(str[counter])=='1'&& valid==1){
      words++;
      valid =0;
    }
    counter++;
    
  }
  return words;
}/*get length of string which is how many characterers then get the sizeof one char and multiply it times # of chars
malloc to get mem then alloc to access*/
char* copy_word(char *str){
  int size= string_length(str);
  char *c= (char *)malloc(((sizeof(char)) * size) +1);
  if(c !=NULL){
    int counter = 0;
    while(str[counter]){
	c[counter]=str[counter];
	counter++;
      }
    c[counter]='\0';
  }
    return c;

}
void print_tokens(char** tokens){
  int  counter =0;
  char** p = tokens;
  for(;*p!=NULL;p++){
    printf("tokens[%d]:%s\n",counter,(*p));
     counter++;
  }
}
void free_tokens(char** tokens){
  int counter =0;
  while(tokens[counter]){
    free(tokens[counter]);
    counter++;
  }
}
//takes string and tokenizes it
char** tokenize(char* str){
  char** tokens = (char **)malloc((sizeof(char *))*(count_words(str)+1));
  int counter =0;
  //creates a pointer of the first word and pointer to end of word
  char* first = find_word_start(str);
  char* end = find_word_end(first);
  //saves a string with the word to be copied and send that to the copy word function
  //repeats for each word in sentence
  while(counter<count_words(str)){
    int size = string_length(first)-string_length(end);
    if(size ==0){
      size = string_length(first);
    }
    char word[size];
    int i =0;
    while(i<size){ 
      word[i]=(first[i]);
      i++;
    }
    word[i]='\0';
    tokens[counter]=(copy_word(word));
    first = find_word_start(end);
    end = find_word_end(first);
    counter++;
  }
  tokens[counter]='\0';
	    
  return tokens;
}
 
