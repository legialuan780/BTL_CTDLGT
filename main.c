#include <stdio.h>
#include <stdlib.h>


struct Dictionary{
	char en[100];// tieng anh
	char vi[100];// nghia tieng viet
	int order; // so thu tu  
};

typedef struct node
{
  Dictionary data;
  struct node *next;
} Node;


int main(int argc, char *argv[]) {
	return 0;
}
