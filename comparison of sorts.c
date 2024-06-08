#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <intrin.h>


#define nums 100000
#define tests 10

unsigned long long a = 184467440737095525;
int c = 45989;


unsigned long long random(unsigned long long prev) {
	unsigned long long new = (prev * a + c);
	return new;
}


struct dvusv_list {
	unsigned long long N;
	struct dvusv_list* next;
	struct dvusv_list* prev;
};


unsigned long long sortirovka_massiva() {
	unsigned long long* TESTS = (unsigned long long*)malloc(tests * sizeof(unsigned long long));
	unsigned long long* A = (unsigned long long*)malloc(nums * sizeof(unsigned long long));
	for (int k = 1; k <= tests; k++) {
		A[0] = k * 1000;
		for (int j = 1; j < nums; j++) {
			A[j] = random(A[j - 1]);
		}
		unsigned long long STARTTIME = __rdtsc();
		unsigned long long new_one;
		int pos;
		for (int i = 1; i < nums; i++) {
			new_one = A[i];
			pos = i - 1;
			while (pos >= 0 && A[pos] > new_one) {
				A[pos + 1] = A[pos];
				pos = pos - 1;
			}
			A[pos + 1] = new_one;
		}
		unsigned long long ENDTIME = __rdtsc();
		TESTS[k - 1] = ENDTIME - STARTTIME;

	}
	unsigned long long TOTAL_TIME = 0;
	for (int i = 0; i < tests; i++) {
		TOTAL_TIME += TESTS[i];
	}
	TOTAL_TIME = TOTAL_TIME / tests;
	return TOTAL_TIME;
}




unsigned long long sortirovka_dvusv_spiska() {
	unsigned long long* TESTS = (unsigned long long*)malloc(tests * sizeof(unsigned long long));
	struct dvusv_list* head = (struct dvusv_list*)malloc(sizeof(struct dvusv_list));
	struct dvusv_list* current = (struct dvusv_list*)malloc(sizeof(struct dvusv_list));
	head->next = current;
	current->next = NULL;
	current->prev = head;
	current->N = 0;
	for (int i = 1; i < nums; i++) {
		struct dvusv_list* new_one = (struct dvusv_list*)malloc(sizeof(struct dvusv_list));
		current->next = new_one;
		new_one->next = NULL;
		new_one->prev = current;
		new_one->N = 0;
		current = new_one;
	}
	for (int k = 1; k <= tests; k++) {
		struct dvusv_list* first_one = head->next;
		first_one->N = k * 1000;
		struct dvusv_list* current = first_one;
		for (int i = 1; i < nums; i++) {
			struct dvusv_list* last = current;
			current = current->next;
			current->N = random(last->N);

		}
		unsigned long long STARTTIME = __rdtsc();
		struct dvusv_list* pointer = head->next->next;
		for (pointer; pointer != NULL; pointer = pointer->next) {
			unsigned long long new_one = pointer->N;
			struct dvusv_list* pos = pointer->prev;
			while (pos->prev != NULL && pos->N > new_one) {
				pos->next->N = pos->N;
				pos = pos->prev;
			}
			pos->next->N = new_one;
		}
		unsigned long long ENDTIME = __rdtsc();
		TESTS[k - 1] = ENDTIME - STARTTIME;
	}
	unsigned long long TOTAL_TIME = 0;
	for (int i = 0; i < tests; i++) {
		TOTAL_TIME += TESTS[i];
	}
	TOTAL_TIME = TOTAL_TIME / tests;
	return TOTAL_TIME;
}


int main() {
	setlocale(LC_ALL, "ru");

	printf("Количество тактов на сортировку массива: %llu\n", sortirovka_massiva());
	printf("Количество тактов на сортировку линейного списка: %llu\n\n", sortirovka_dvusv_spiska());

	return 0;
}
