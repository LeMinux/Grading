#include <stdio.h>
#include <stdlib.h>

#define PRINT_RED     "\x1b[31m"
#define PRINT_GREEN   "\x1b[32m"
#define PRINT_RESET   "\x1b[0m"

typedef struct AnswerArray{
	char** array2D;
	int arrayLength;
}AnswerArray;

AnswerArray getAnswers(FILE*);
//int checkMalloc(void**);
//
int main(int argc, char** argv){
	if(argc < 2){
		puts("Need to have at least one argument to run");
		exit(1);
	}

	FILE* caseFile = fopen("answers.txt", "r");
	if(caseFile == NULL){
		puts("File for answers does not exist can not run");
		exit(1);
	}
	AnswerArray answerKey = getAnswers(caseFile);
	
	int p = 0;
	for(;p < answerKey.arrayLength; ++p){
		printf("%s\n", answerKey.array2D[p]);
	}
}

AnswerArray getAnswers(FILE* fileKey){
	int data = '\0';
	int stringLength = 0;
	AnswerArray answers;
	answers.array2D =  malloc(sizeof(char*));
	answers.arrayLength = 0;
	while((data = fgetc(fileKey)) != EOF){
		if(data == '\n' && stringLength != 0){
			char** temp2D = realloc(answers.array2D, sizeof(char*) * answers.arrayLength  + 1);
			//Out of Memory check
			if(temp2D != NULL){
				answers.array2D = temp2D;
				answers.array2D[answers.arrayLength] = malloc(sizeof(char) * stringLength + 1);
				printf("before %ld\n", ftell(fileKey));
				fseek(fileKey, -1 * (stringLength + 1), SEEK_CUR);
				fread(answers.array2D[answers.arrayLength], 1, stringLength + 1, fileKey);
				printf("after %ld\n", ftell(fileKey));
				++answers.arrayLength;
				stringLength = 0;
			}else{
				puts("Not enough memory to create 2D string array");
				free(answers.array2D);
				free(temp2D);
				exit(1);
			}
		}else{
			++stringLength;
		}
	}
	return answers;
}
/*
int checkMalloc(void** memory){
	if(**memory == NULL){
		puts("Not enough memory to malloc");
		exit(1);
	}
}*/
