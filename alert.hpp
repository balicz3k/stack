//============================================//
//				alert deklarations			 //
//==========================================//

#pragma once
#pragma warning (disable : 4996)

enum MessagesList {
	MEM_ERROR, EMPTY_STACK, FATAL_ERROR,
	FILE_ERROR, STACK_CLEARED,
	EXIT, INPUT_ERROR, ELEMENTS_NUMBER
};
const static char* MyMessage[] = {
	"Memory error.",
	"Stack is empty.",
	"Fatal error.",
	"File operation error.",
	"Stack has been cleared.",
	"Program exited.",
	"Invalid input, try again: "
};
void Message(enum MessagesList Mes);
void FileMessage(enum MessagesList mes, void* pos, FILE* ptrFile);
