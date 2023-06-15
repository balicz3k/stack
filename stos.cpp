//===================================//
//			stack definitions		//
//=================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.hpp"
#include "alert.hpp"
#include "student.hpp"
#include "stos.hpp"

static Stack* TopElement = NULL;
char Filename[] = "file.bin";
EmptyData EmptyDataPtr;
PrintElement Display;
File SaveFile;
load LoadFile;

void StackInit(EmptyData pointer, PrintElement show, File save, load read){
	TopElement = NULL;
	EmptyDataPtr = pointer;
	Display = show;
	SaveFile = save;
	LoadFile = read;
}
void DisplayStack(){
	Stack* Temp = TopElement;
	if (Temp != NULL){
		printf("\nStack elements:");
		printf("\n=============\n");
		while (Temp != NULL){
			Display(Temp->data);
			printf("=============\n");
			Temp = Temp->next;
		}
		printf("\n");
	}
	else{
		printf("\n");
		Message(EMPTY_STACK);
	}
}
Stack* PushStack(void* ptrData){
	Stack* Next = (Stack*)malloc(sizeof(Stack));
	if (!Next){
		Message(MEM_ERROR);
		return NULL;
	}
	else{
		Next->data = ptrData;
		Next->next = TopElement;
		TopElement = Next;
		return Next;
	}
}
void* PopStack(){
	Stack Pop;
	if (!TopElement){
		Message(EMPTY_STACK);
		return NULL;
	}
	else{
		Stack* Next = TopElement->next;
		Pop.data = TopElement->data;
		free(TopElement);
		TopElement = Next;
		return Pop.data;
	}
}
void FreeStack(){
	Stack* Ptr = TopElement;
	Stack* Temp = NULL;
	while (Ptr){
		(*EmptyDataPtr)(Ptr->data);
		Temp = Ptr;
		Ptr = Ptr->next;
		free(Temp);
	}
	TopElement = NULL;
}
void* SearchStack(void* Search_Data, find search_ptr, int if_first){
	static Stack* Ptr;
	Stack* Temp = NULL;
	if (TopElement == NULL){
		Message(EMPTY_STACK);
		return NULL;
	}
	if (if_first)
		Ptr = TopElement;
	while (Ptr){
		if (!(*search_ptr)(Ptr->data, Search_Data))
			Ptr = Ptr->next;
		else{
			Temp = Ptr;
			Ptr = Ptr->next;
			return Temp->data;
		}
	}
	return NULL;
}
void SaveStack(){
	Stack* Temp = TopElement;
	if (Temp == NULL){
		Message(EMPTY_STACK);
		return;
	}
	size_t elements = 0;
	FILE* file = fopen(Filename, "wb");
	if (!file)
		FileMessage(FILE_ERROR, NULL, file);
	while (Temp != NULL) {
		Temp = Temp->next;
		elements++;
	}
	fwrite(&elements, sizeof(size_t), 1, file);
	int check = fseek(file, elements * sizeof(size_t), SEEK_CUR);
	if (check != 0)
		return;
	size_t* filePosition = NULL;
	filePosition = (size_t*)malloc(elements * sizeof(size_t));
	if (!filePosition)
		FileMessage(MEM_ERROR, filePosition, file);
	Temp = TopElement;
	int pos = 0;
	while (Temp != NULL) {
		filePosition[pos] = ftell(file);
		pos++;
		if (SaveData(Temp->data, file) != 1)
			FileMessage(MEM_ERROR, filePosition, file);
		Temp = Temp->next;
	}
	fseek(file, sizeof(size_t), SEEK_SET);
	fwrite(filePosition, sizeof(size_t), elements + 1, file);
	if (file){
		printf("Data saved\n");
		fclose(file);
		file = NULL;
	}
	if (filePosition)
		free(filePosition);
}
void LoadStack(){
	FreeStack();
	size_t elements = 0;
	FILE* file = fopen(Filename, "rb");
	if (!file)
		FileMessage(FILE_ERROR, NULL, file);
	fread(&elements, sizeof(elements), 1, file);
	size_t* filePosition = (size_t*)malloc(elements * sizeof(size_t));
	if (!filePosition)
		FileMessage(MEM_ERROR, filePosition, file);
	for (int i = 0; i < elements; i++)
		fread(&filePosition[i], sizeof(size_t), 1, file);
	for (int i = elements - 1; i >= 0; i--){
		fseek(file, filePosition[i], SEEK_SET);
		void* data = LoadFile(file);
		if (!PushStack(data))
			FileMessage(MEM_ERROR, filePosition, file);
	}
	if (file){
		fclose(file);
		file = NULL;
	}
	if (filePosition)
		free(filePosition);
	
}





