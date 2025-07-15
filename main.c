#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Dictionary{
	char en[100];
	char vi[100];
	int order; 
};

typedef struct node
{
  Dictionary data;
  struct node *next;
} Node;


int main(int argc, char *argv[]) {
	return 0;
}
