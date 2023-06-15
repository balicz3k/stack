//============================================//
//				alert definitions			 //
//==========================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.hpp"
#include "alert.hpp"
#include "student.hpp"
#include "stos.hpp"
#include "menu.hpp"

void Message(enum MessagesList mes) {
	printf("%s\n", MyMessage[mes]);
}
void FileMessage(enum MessagesList mes, void* pos, FILE* ptrFile) {
	if (ptrFile)
		fclose(ptrFile);
	printf("%s", MyMessage[mes]);
	if (pos)
		free(pos);
	Message(FILE_ERROR);
	exit(1);
}