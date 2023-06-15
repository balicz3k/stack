//================================//
//		 menu definitions		 //
//==============================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.hpp"
#include "alert.hpp"
#include "student.hpp"
#include "stos.hpp"
#include "menu.hpp"

int OptionInput(int First, int Last) {
	int Option, input = 1;
	while (input) {
		if (scanf_s("%d", &Option, sizeof(Option)) == 1 && Option >= First && Option < Last)
			input = 0;
		else
			Message(INPUT_ERROR);
		while (getchar() != '\n');
	}
	return Option;
}
int YearInput(int Min, int Max) {
	int Year, input = 1;
	while (input) {
		if (scanf_s("%d", &Year, sizeof(Year)) == 1 && Year >= Min && Year <= Max)
			input = 0;
		else
			Message(INPUT_ERROR);
		while (getchar() != '\n');
	}
	return Year;
}
int FieldInput(int First, int Last) {
	int Major, input = 1;
	while (input) {
		if (scanf_s("%d", &Major, sizeof(Major)) == 1 && Major >= First && Major < Last)
			input = 0;
		else
			Message(INPUT_ERROR);
		while (getchar() != '\n');
	}
	return Major - 1;
}
void ShowMainMenu() {
	printf("Choose operation which you want to do:\n\n");
	printf("1 - Show all elements from the stack.\n");
	printf("2 - Add to the stack.\n");
	printf("3 - Remove last added element.\n");
	printf("4 - Clear the stack.\n");
	printf("5 - Search in stack.\n");
	printf("6 - Save the stack to file.\n");
	printf("7 - Load the stack from file.\n");
	printf("8 - Exit program.\n");
}
void FieldsPrint() {
	size_t i;
	for (i = 0; i < 5; i++) {
		printf("%s\n", Fields[i]);
	}
}
void SearchMenu() {
	size_t i;
	for (i = 0; i < NUMBER; i++)
		printf("%s\n", SearchList[i]);
}
void ShowStack() {
	DisplayStack();
	system("PAUSE");
	system("cls");
}
void Push() {
	char Surname_Buff[256];
	int Year, Major;
	printf("\nSurname: ");
	scanf_s("%s", Surname_Buff, sizeof(Surname_Buff));
	printf("Year: ");
	Year = YearInput(0, 2500);
	FieldsPrint();
	printf("Field of study: ");
	Major = FieldInput(1, 6);
	printf("\n");
	void* pData = PushData(Surname_Buff, Year, (Field_Of_Study)Major);
	PushStack(pData);
	printf("Element was added to the stack.\n");
	system("pause");
	system("cls");
}
void Pop() {
	void* Temp = PopStack();
	if (Temp != NULL) {
		printf("Elemet which has been poped:\n");
		PrintData(Temp);
		printf("\n");
	}
	FreeData(Temp);
	system("PAUSE");
	system("cls");
}
void Clear() {
	FreeStack();
	Message(STACK_CLEARED);
	system("PAUSE");
	system("cls");
}
void ClearExit() {
	FreeStack();
	Message(EXIT);
}
void Find() {
	int Option = 0;
	system("cls");
	printf("Search by:\n");
	SearchMenu();
	printf("\nChoose your option: ");
	Option = OptionInput(SURNAME + 1, NUMBER + 1);
	Option--;
	Student* Temp = (Student*)malloc(sizeof(Student));
	if (!Temp) {
		Message(MEM_ERROR);
		return;
	}
	else {
		memset(Temp, 0, sizeof(Student));
		size_t Length;
		void* Ptr;
		switch (Option) {
		case SURNAME:
			char Surname_Buff[256];
			printf("Surname: ");
			scanf_s("%s", Surname_Buff, sizeof(Surname_Buff));
			Length = strlen(Surname_Buff) + 1;
			Temp->surname = (char*)malloc(Length * sizeof(char));
			if (!Temp->surname) {
				Message(MEM_ERROR);
				return;
			}
			else {
				system("cls");
				strcpy(Temp->surname, Surname_Buff);
				Ptr = SearchStack(Temp, SurnameData, 1);
				if (Ptr) {
					printf("Found:\n\n");
					PrintData(Ptr);
					printf("\n");
				}
				else
					printf("No elements match to the criterias.\n");
				while (Ptr) {
					Ptr = SearchStack(Temp, SurnameData, 0);
					if (Ptr) {
						PrintData(Ptr);
						printf("\n");
					}
				}
				printf("\n");
				FreeData(Temp);
			}
			break;
		case YEAR:
			int Year_Buff;
			printf("Year: ");
			Year_Buff = YearInput(0, 2500);
			Temp->birth_year = Year_Buff;
			Ptr = SearchStack(Temp, YearData, 1);
			system("cls");
			if (Ptr) {
				printf("Found elements:\n\n");
				PrintData(Ptr);
				printf("\n");
			}
			else
				printf("No elements match to the criterias.\n");
			while (Ptr) {
				Ptr = SearchStack(Ptr, YearData, 0);
				if (Ptr) {
					PrintData(Ptr);
					printf("\n");
				}
			}
			printf("\n");
			FreeData(Temp);
			break;
		case FIELD_OF_STUDY:
			int Major_Buff;
			printf("\n");
			FieldsPrint();
			printf("\nField of study: ");
			Major_Buff = FieldInput(1, 6);
			Temp->field = (Field_Of_Study)Major_Buff;
			Ptr = SearchStack(Temp, FieldOfStudyData, 1);
			system("cls");
			if (Ptr) {
				printf("Found elements:\n\n");
				PrintData(Ptr);
				printf("\n");
			}
			else
				printf("No elements match to the criterias.\n\n");
			while (Ptr) {
				Ptr = SearchStack(Temp, FieldOfStudyData, 0);
				if (Ptr) {
					PrintData(Ptr);
					printf("\n");
				}
			}
			printf("\n");
			FreeData(Temp);
			break;
		default:
			printf("Input Error\n");
		};
		system("PAUSE");
		system("cls");
	}
}
void Save() {
	SaveStack();
	system("PAUSE");
	system("cls");
}
void Load() {
	LoadStack();
	printf("Data loaded.\n");
	system("PAUSE");
	system("cls");
}
