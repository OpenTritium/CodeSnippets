#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_SIZE 64
#define GET_LEFT(i) (2*i+1)
#define GET_RIGHT(i) (2*i+2)
#define GET_PARENT(i) ((i-1)/2)

typedef int Element_t;

typedef struct {
	size_t size;
	Element_t data[MAX_SIZE];
}Heap, * pHeap;

bool push_back(pHeap ph, const int val) {
	if (ph->size == MAX_SIZE) {
		printf("装不下咧");
		return false;
	}
	ph->data[ph->size++] = val;
	size_t current_compare_index = ph->size - 1;
	bool status = true;
	while (status) {
		if (current_compare_index == 0) {
			break;
		}
		else if (ph->data[GET_PARENT(current_compare_index)] < ph->data[current_compare_index]) {
			status = !status;
		}
		else {
			Element_t tmp = ph->data[GET_PARENT(current_compare_index)];
			ph->data[GET_PARENT(current_compare_index)] = ph->data[current_compare_index];
			ph->data[current_compare_index] = tmp;
			current_compare_index = GET_PARENT(current_compare_index);
		}
	}
	return true;
}

void print_tree(const pHeap ph) {
	for (int i = 0; i < ph->size; i++) {
		for (int j = 0; j < floor(log2(i + 1)) * 2; j++) {
			printf(" ");
		}
		printf("%d\n", ph->data[i]);
	}
}

int main() {
	Heap h = { 1,{3} };
	push_back(&h, 0);
	push_back(&h, 9);
	push_back(&h, 10);
	push_back(&h, 7);
	push_back(&h, 2);
	push_back(&h, 8);
	push_back(&h, 1);
	push_back(&h, 5);
	print_tree(&h);
}
