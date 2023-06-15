//============================================//
//			student deklarations			 //
//==========================================//

#pragma once
#pragma warning (disable : 4996)

enum FieldOfStudy {
	ARCHITEKTURE, COMPUTER_SCIENCE, MATH, PHYSICS, BIOTECHNOLOGY
};
const static char* Fields[]{
	"1 - Architecture.",
	"2 - Computer Science.",
	"3 - Maths.",
	"4 - Physics.",
	"5 - Biotechnology."
};
struct Student {
	char* surname;
	int birth_year;
	enum Field_Of_Study field;
	size_t length;
};

void* InitData(char* SSurname, int YYear, enum Field_Of_Study FField);
void* PushData(char* SSurname, int YYear, enum Field_Of_Study FField);
void FreeData(void* Ptr);
void PrintData(void* Ptr);
int SurnameData(void* CurrentData, void* SearchData);
int YearData(void* CurrentData, void* SearchData);
int FieldOfStudyData(void* Current, void* SearchData);
int FieldOfStudyData(void* CurrentData, void* SearchData);
int SaveData(void* Ptr, FILE* File_Name);
void* LoadData(FILE* File_Name);