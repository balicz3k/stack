//================================//
//				main			 //
//==============================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.hpp"
#include "alert.hpp"
#include "student.hpp"
#include "stos.hpp"
#include "menu.hpp"

int main(){
	StackInit(FreeData, PrintData, SaveData, LoadData);
	int choose = -1;
	while (true){
		ShowMainMenu();
		choose = OptionInput(1,9);
		switch (choose){
		case 1: 
			ShowStack();
			break;
		case 2: 
			Push();
			break;
		case 3: 
			Pop();
			break;
		case 4: 
			Clear();
			break;
		case 5: 
			Find();
			break;
		case 6: 
			Save();
			break;
		case 7: 
			Load();
			break;
		case 8: 
			ClearExit();
			return 0;
		default:
			printf("ERROR.\n");
		};
	}
	return 0;
}
