#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>
#define MAXNAME 15
#define MAXSURNAME 20
#define MAXCOUNTRY 30
#define MAXCLUB 20
#define MAXMONTH 15


union months {
	int number;
	char name[MAXMONTH];
};


enum shoot_foot { Правая = 1, Левая = 0 };


struct date_of_born {
	int date;
	union months month;
	int year;
};


struct footballers {
	int id;
	char name[MAXNAME];
	char surname[MAXSURNAME];
	struct date_of_born born;
	char country_of_born[MAXCOUNTRY];
	char club[MAXCLUB];
	char position[3];
	enum shoot_foot foot;
	float price;
	struct footballers* next;
};


void add_from_console(struct footballers* head) {
	struct footballers* new_one = (struct footballers*)malloc(sizeof(struct footballers));
id_again: printf("Напишите ID футболиста:\n");
	printf("--> ");
	int id_to_add;
	scanf("%d", &id_to_add);
	struct footballers* tmp = head;
	while (tmp->id != id_to_add && tmp->next != NULL) tmp = tmp->next;
	if (tmp->id == id_to_add) {
		printf("Игрок с таким ID уже существует, введите другой:\n\n");
		goto id_again;
	}
	else {
		new_one->id = id_to_add;
	}
	printf("Его имя:\n");
	printf("--> ");
	scanf("%s", new_one->name);
	printf("Его фамилия:\n");
	printf("--> ");
	scanf("%s", new_one->surname);
	printf("Напишите его дату рождения в формате ДД ММ ГГГГ:\n");
	printf("--> ");
	scanf("%d %d %d", &new_one->born.date, &new_one->born.month.number, &new_one->born.year);
	printf("Страна, в которой он родился:\n");
	printf("--> ");
	scanf("%s", new_one->country_of_born);
	printf("Клуб, за который он сейчас играет:\n");
	printf("--> ");
	scanf("%s", new_one->club);
	printf("Позиция, на которой он играет:\n");
	printf("--> ");
	scanf("%s", new_one->position);
	printf("Его ударная нога:\n");
	printf("--> ");
	scanf("%d", &new_one->foot);
	printf("Его стоимость (в млн евро):\n");
	printf("--> ");
	scanf("%F", &new_one->price);
	struct footballers* last = head;
	while (last->next != NULL) last = last->next;
	new_one->next = NULL;
	last->next = new_one;
	printf("\n");
	printf("Игрок успешно добавлен!\n\n");
	printf("--------------------------\n\n");

}


void print_data(struct footballers* head) {
	printf("--------------------------\n\n");
	int *pointer = head->next;
	struct footballers* current = pointer;
	for (; pointer != NULL; pointer = current->next) {
		current = pointer;
		printf("ID игрока: %d\n", current->id);
		printf("Имя игрока: %s\n", current->name);
		printf("Фамилия игрока: %s\n", current->surname);
		printf("Дата рождения: %d.%d.%d\n", current->born.date, current->born.month.number, current->born.year);
		printf("Страна рождения: %s\n", current->country_of_born);
		printf("Текущий клуб: %s\n", current->club);
		printf("Позиция игрока: %s\n", current->position);
		if (current->foot) printf("Ударная нога: Правая\n");
		else printf("Ударная нога: Левая\n");
		printf("Текущая стоимость: %.1F миллионов евро\n\n", current->price);
		printf("--------------------------\n\n");
	}
}

void deleting(int id_to_remove, struct footballers* head) {
	struct footballers* current = head->next;
	struct footballers* last = head;

	while (current->id != id_to_remove && current->next != NULL) {
		current = current->next;
		last = last->next;
	}
	printf("\n");
	if (current->next == NULL && current->id != id_to_remove) {
		printf("ID игрока введен неверно или не существует\n\n");
		printf("--------------------------\n\n");
	}
	else if (current->next == NULL && current->id == id_to_remove) {
		last->next = NULL;
		free(current);
		printf("Игрок успешно удален!\n\n");
		printf("--------------------------\n\n");
	}
	else {
		struct footballers* next_going = current->next;
		last->next = next_going;
		free(current);
		printf("Игрок успешно удален!\n\n");
		printf("--------------------------\n\n");

	}
}


void search_by_id(struct footballers* head, int id_to_find) {

	struct footballers* current = head->next;
	while (current->id != id_to_find && current->next != NULL) current = current->next;
	if (current->next == NULL && current->id != id_to_find) printf("Игрок с таким ID не найден\n\n");
	else {
		printf("\n");
		printf("Найден игрок!\n\n");
		printf("--------------------------\n\n");
		printf("ID игрока: %d\n", current->id);
		printf("Имя игрока: %s\n", current->name);
		printf("Фамилия игрока: %s\n", current->surname);
		printf("Дата рождения: %d.%d.%d\n", current->born.date, current->born.month.number, current->born.year);
		printf("Страна рождения: %s\n", current->country_of_born);
		printf("Текущий клуб: %s\n", current->club);
		printf("Позиция игрока: %s\n", current->position);
		if (current->foot) printf("Ударная нога: Правая\n");
		else printf("Ударная нога: Левая\n");
		printf("Текущая стоимость: %.1F миллионов евро\n\n", current->price);
		printf("--------------------------\n\n");
	}
}


void edit(struct footballers* head, int id_to_edit) {
	struct footballers* current = head->next;
	while (current->id != id_to_edit && current->next != NULL) current = current->next;
	if (current->next == NULL && current->id != id_to_edit) printf("Игрок с таким ID не найден\n\n");
	else {
		printf("Найден игрок:\n\n");
		printf("--------------------------\n");
		printf("ID игрока: %d\n", current->id);
		printf("Имя игрока: %s\n", current->name);
		printf("Фамилия игрока: %s\n", current->surname);
		printf("Дата рождения: %d.%d.%d\n", current->born.date, current->born.month.number, current->born.year);
		printf("Страна рождения: %s\n", current->country_of_born);
		printf("Текущий клуб: %s\n", current->club);
		printf("Позиция игрока: %s\n", current->position);
		if (current->foot) printf("Ударная нога: Правая\n");
		else printf("Ударная нога: Левая\n");
		printf("Текущая стоимость: %.1F миллионов евро\n\n", current->price);
		printf("--------------------------\n\n");
		printf("Что вы хотите изменить?\n\n");
		printf("1. ID игрока\n");
		printf("2. Имя игрока\n");
		printf("3. Фамилия игрока\n");
		printf("4. Дата рождения\n");
		printf("5. Страна рождения\n");
		printf("6. Текущий клуб\n");
		printf("7. Позиция игрока\n");
		printf("8. Ударная нога\n");
		printf("9. Текущая стоимость\n");
		printf("10. Выйти из меню редактирования\n\n");
		int vibor;
		printf("--> ");
		scanf("%d", &vibor);
		printf("\n");
		switch (vibor) {
		case 1:
			int new_id;
			printf("Напишите новый ID игрока:\n");
			printf("--> ");
			scanf("%d", &new_id);
			current->id = new_id;
			printf("\n");
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 2:
			char new_name[MAXNAME];
			printf("Напишите новое имя игрока:\n");
			printf("--> ");
			scanf("%s", new_name);
			memcpy(current->name, new_name, MAXNAME);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 3:
			char new_surname[MAXSURNAME];
			printf("Напишите новую фамилию игрока:\n");
			printf("--> ");
			scanf("%s", new_surname);
			memcpy(current->surname, new_surname, MAXSURNAME);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 4:
			printf("Напишите новую дату рождения игрока в формате ДД ММ ГГГГ:\n");
			printf("--> ");
			scanf("%d %d %d", &current->born.date, &current->born.month.number, &current->born.year);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 5:
			char new_country[MAXCOUNTRY];
			printf("Напишите новую страну рождения игрока:\n");
			printf("--> ");
			scanf("%s", new_country);
			memcpy(current->country_of_born, new_country, MAXCOUNTRY);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 6:
			char new_club[MAXCLUB];
			printf("Напишите новый клуб, за который выступает игрок:\n");
			printf("--> ");
			scanf("%s", new_club);
			memcpy(current->club, new_club, MAXCLUB);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 7:
			char new_position[3];
			printf("Напишите новую позицию, на которой выступает игрок:\n");
			printf("--> ");
			scanf("%s", new_position);
			memcpy(current->position, new_position, 3);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 8:
			printf("Напишите новую ударную ногу игрока:\n");
			printf("--> ");
			scanf("%d", &current->foot);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 9:
			printf("Напишите новую текущую стоимость игрока:\n");
			printf("--> ");
			scanf("%F", &current->price);
			printf("Данные изменены успешно\n\n");
			printf("--------------------------\n\n");
			break;
		case 10:
			printf("\n\n");
			break;
		default:
			printf("Неправильно выбран номер, попробуйте еще раз\n\n");
		}
	}
}


void output_in_file(struct footballers* head, FILE* output) {
	struct footballers* current = head->next;
	while (current != NULL) {
		fprintf(output, "%d\n", current->id);
		fprintf(output, "%s\n", current->name);
		fprintf(output, "%s\n", current->surname);
		fprintf(output, "%d %d %d\n", current->born.date, current->born.month.number, current->born.year);
		fprintf(output, "%s\n", current->country_of_born);
		fprintf(output, "%s\n", current->club);
		fprintf(output, "%s\n", current->position);
		if (current->foot) fprintf(output, "%s\n", "Правая");
		else fprintf(output, "%s\n", "Левая");
		fprintf(output, "%.1F\n", current->price);
		current = current->next;
	}
	printf("Вывод базы данных завершен\n\n");
	printf("--------------------------\n\n");
	fclose(output);

}


void input_from_file(struct footballers* head, FILE* input) {
	for (struct footballers* current = head->next; current != NULL; )
	{
		struct footballers* temp = current;
		current = current->next;
		free(temp);
	}
	head->next = NULL;
	while (!feof(input)) {
		struct footballers* new_one = (struct footballers*)malloc(sizeof(struct footballers));
		fscanf(input, "%d", &new_one->id);
		fscanf(input, "%s", new_one->name);
		fscanf(input, "%s", new_one->surname);
		fscanf(input, "%d %d %d", &new_one->born.date, &new_one->born.month.number, &new_one->born.year);
		fscanf(input, "%s", new_one->country_of_born);
		fscanf(input, "%s", new_one->club);
		fscanf(input, "%s", new_one->position);
		fscanf(input, "%d", &new_one->foot);
		fscanf(input, "%F", &new_one->price);
		struct footballers* last = head;
		while (last->next != NULL) last = last->next;
		//new_one->prev = last;
		new_one->next = NULL;
		last->next = new_one;
	}
	
	printf("Ввод данных завершен успешно\n\n");
	printf("--------------------------\n\n");
	fclose(input);
}


void clear(struct footballers* head) {
	for (struct footballers* current = head->next; current != NULL; )
	{
		struct footballers* temp = current;
		current = current->next;
		free(temp);
	}
	head->next = NULL;
	printf("База данных успешно удалена\n\n");
	printf("--------------------------\n\n");
}


int main() {
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");
	struct footballers* head = (struct footballers*)malloc(sizeof(struct footballers)); //самый первый элемент, от которого будем отталкиваться в будущем
	head->next = NULL;
	int k, quit = 0;
	while (!quit) {
		printf("Выберите действие:\n\n1. Добавить футболиста\n2. Удалить футболиста\n3. Загрузить данные из файла\n4. Выгрузить данные в файл\n5. Отредактировать данные футболиста\n6. Найти футболиста\n7. Вывести базу данных\n8. Очистить базу данных\n9. Выйти\n\n");
		printf("--> ");
		scanf("%d", &k);
		printf("\n");
		switch (k) {
			case 1:
				add_from_console(head);
				break;
			case 2:
				if (head->next == NULL) { printf("Ошибка удаления: база данных пуста!\n\n"); printf("--------------------------\n\n"); }
				else {
					printf("Напишите, ID какого игрока вы бы хотели удалить\n");
					printf("--> ");
					int id_to_remove;
					scanf("%d", &id_to_remove);
					deleting(id_to_remove, head);
				}
				break;
			case 3:
				char c;
				FILE* input = fopen("database_in.txt", "r");
				if (c = getc(input) == EOF) { printf("Ошибка чтения: входной файл пуст!\n\n"); fclose(input); printf("--------------------------\n\n");
				}
				else {
					FILE* input = fopen("database_in.txt", "r");
					input_from_file(head, input);
				}
				break;
			case 4:
				if (head->next == NULL) { printf("Ошибка вывода: база данных пуста!\n\n"); printf("--------------------------\n\n"); }
				else {
					FILE* output = fopen("database_out.txt", "w");
					output_in_file(head, output);
				}
				break;
			case 5:
				if (head->next == NULL) { printf("Ошибка редактирования: база данных пуста!\n\n"); printf("--------------------------\n\n"); }
				else {
					printf("Напишите ID игрока, информацию о котором вы бы хотели отредактировать:\n");
					printf("--> ");
					int id_to_edit;
					scanf("%d", &id_to_edit);
					edit(head, id_to_edit);
				}
				break;
			case 6:
				if (head->next == NULL) { printf("Ошибка поиска: база данных пуста!\n\n"); printf("--------------------------\n\n"); }
				else {
					printf("Введите ID игрока, которого хотите найти:\n");
					printf("--> ");
					int id_to_find;
					scanf("%d", &id_to_find);
					search_by_id(head, id_to_find);
				}
				break;
			case 7:
				if (head->next == NULL) { printf("Ошибка вывода: база данных пуста!\n\n"); printf("--------------------------\n\n"); }
				else {
					print_data(head);
				}
				break;
			case 8:
				if (head->next == NULL) { printf("Ошибка удаления: база данных уже пуста!\n\n"); printf("--------------------------\n\n"); }
				else clear(head);
				break;
			case 9:
				quit = 1;
				break;
			default:
				printf("Неверно введен номер операции, попробуйте еще раз!\n\n");
				break;
		}

	}

}
//final version
