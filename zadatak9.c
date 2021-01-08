#include <stdio.h>
#include <stdlib.h>

/*Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa*/

struct _node;
typedef struct _node* position;
struct _node{
	int number;
	position left;
	position right;
}node;

position createNode(int);
position insert(position, position);
void printInOrder(position);
position find(position, int);
position deleteNode(position, int);
position findMax(position);
position findMin(position);

int main(void)
{
	position root = NULL;
	position el = createNode(16);

	root = insert(root, el);

	return EXIT_SUCCESS;
}

position createNode(int number){
	position p = NULL;

	p = (position)malloc(sizeof(node));
	if(p == NULL){
		printf("Memory allocation failed\r\n");
		return NULL;
	}
	p->number = number;
	p->left = NULL;
	p->right = NULL;
}

position insert(position current, position el){
	if(current == NULL){
		return el;
	}
	if(current->number > el->number){
		current->left = insert(current->left, el);
	}else if(current->number < el->number){
		current->right = insert(current->right, el);
	}else{
		printf("Duplicated element %d", el->number);
		free(el);
	}
	return current;
}

void printInOrder(position current){
	if(current == NULL){
		return;
	}
	printInOrder(current->left);
	printf("%d ", current->number);
	printInOrder(current->right);
}

position find(position current, int number){
	if(current == NULL){
		return NULL;
	}
	if(current->number == number){
		return current;
	}
	else if(current->number > number){
		return find(current->left, number);
	}
	else{
		return find(current->right, number);
	}
}

position findMax(position current){
	if(current == NULL){
		return NULL;
	}
	while(current->right != NULL){
		current = current->right;
	}
	return current;
}

position findMin(position current){
	if(current == NULL){
		return NULL;
	}
	while(current->left != NULL){
		current = current->left;
	}
	return current;
}

position deleteNode(position current, int number){
	if(current == NULL){
		return NULL;
	}
	if(current->number == number){
		if(current->left == NULL && current->right == NULL){
			free(current);
			return NULL;
		}
		if(current->left != NULL){
			position temp = findMax(current->left);
			current->number = temp->number;
			current->left = deleteNode(current->left, temp->number);
		}
		else if(current->right != NULL){
			position temp = findMin(current->left);
			current->number = temp->number;
			current->right = deleteNode(current->right, temp->number);
		}
	}
	else if(current->number < number){
		current->left = deleteNode(current->left, number);
	}else{
		current->right = deleteNode(current->right, number);
	}
	return current;
}
