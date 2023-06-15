//================================================//
//				student definitions				 //
//==============================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.hpp"
#include "alert.hpp"
#include "student.hpp"
#include "stos.hpp"
#include "menu.hpp"

void* InitData(char* SSurname, int YYear, enum Field_Of_Study FField) {
	Student* pData = (Student*)malloc(sizeof(Student));
	if (!pData) {
		Message(MEM_ERROR);
		return NULL;
	}
	else {
		size_t Len = strlen(SSurname) + 1;
		pData->length = Len;
		pData->surname = (char*)malloc(Len * sizeof(char));
		if (!pData->surname) {
			Message(MEM_ERROR);
			return NULL;
		}
		strcpy(pData->surname, SSurname);
		pData->birth_year = YYear;
		pData->field = FField;
	}
	return(void*)(pData);
}
void* PushData(char* SSurname, int YYear, enum Field_Of_Study FField) {
	return InitData(SSurname, YYear, FField);
}
void FreeData(void* Ptr) {
	Student* pData = (Student*)Ptr;
	if (pData) {
		free(pData->surname);
		pData->surname = NULL;
		free(pData);
		pData = NULL;
	}

}
void PrintData(void* Ptr) {
	Student* Temp = (Student*)Ptr;
	if (Temp) {
		printf("%s\n", Temp->surname);
		printf("%d\n", Temp->birth_year);
		switch (Temp->field) {
		case ARCHITEKTURE:
			printf("Architecture\n");
			break;
		case COMPUTER_SCIENCE:
			printf("Computer Science\n");
			break;
		case MATH:
			printf("Math\n");
			break;
		case PHYSICS:
			printf("Physics\n");
			break;
		case BIOTECHNOLOGY:
			printf("Biotechnology\n");
			break;
		default:
			printf("ERROR\n");
			break;
		}
	}
}
int SurnameData(void* CurrentData, void* SearchData) {
	Student* pCurrent = (Student*)CurrentData;
	Student* pSearch = (Student*)SearchData;
	if (strcmp(pCurrent->surname, pSearch->surname) == 0)
		return 1;
	else
		return 0;
}
int YearData(void* CurrentData, void* SearchData) {
	Student* pCurrent = (Student*)CurrentData;
	Student* pSearch = (Student*)SearchData;
	if (pCurrent->birth_year == pSearch->birth_year)
		return 1;
	else
		return 0;
}
int FieldOfStudyData(void* CurrentData, void* SearchData) {
	Student* pCurrent = (Student*)CurrentData;
	Student* pSearch = (Student*)SearchData;
	if (pCurrent->field == pSearch->field)
		return 1;
	else
		return 0;
}
int SaveData(void* Ptr, FILE* filename) {
	Student* pData = (Student*)Ptr;
	if (fwrite(pData, sizeof(Student), 1, filename) != 1)
		return 0;
	if (fwrite(pData->surname, pData->length * sizeof(char), 1, filename) != 1)
		return 0;
	return 1;
}
void* LoadData(FILE* filename) {
	Student* pData = (Student*)malloc(sizeof(Student));
	if (!pData)
		FileMessage(FILE_ERROR, pData, filename);
	else {
		memset(pData, 0, sizeof(Student));
		if (fread(pData, sizeof(Student), 1, filename) != 1)
			return 0;
		pData->surname = (char*)malloc(pData->length * sizeof(char));
		if (!(pData->surname)) {
			FileMessage(FILE_ERROR, pData->surname, filename);
		}
		if (fread(pData->surname, pData->length * sizeof(char), 1, filename) != 1)
			return 0;
		void* tmpData = PushData(pData->surname, pData->birth_year, pData->field);
		if (pData)
			free(pData);
		return tmpData;
	}
}