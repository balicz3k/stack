//===================================//
//			stack deklarations		//
//=================================//

#pragma once
#pragma warning (disable : 4996)

enum SEARCHDATA{
	SURNAME,YEAR,
	FIELD_OF_STUDY,NUMBER
};
const static char* SearchList[]{
	"1 - Surname.",
	"2 - Birth year.",
	"3 - Field of study."
};
struct Stack{
	void* data;
	struct Stack* next;
};
typedef void(*EmptyData)(void* dat_ptr);
typedef void(*PrintElement)(void* dat_ptr);
typedef int(*File)(void* pdat, FILE* file);
typedef void* (*load)(FILE* file);
typedef int(find)(void* Current_Data, void* Search_Data);
void StackInit(EmptyData ptr, PrintElement display, File save, load load);
void DisplayStack();
Stack* PushStack(void* ptrData);
void* PopStack();
void FreeStack();
void* SearchStack(void* Search_Data, find search_ptr, int if_first);
void SaveStack();
void LoadStack();

