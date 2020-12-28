#include<stdio.h>
#include<stdlib.h>

int compVals(const void * a, const void * b);
void argHandler(char argument);

int main(int argc, char* argv[]) { 
}



void* fileToArray(char* file_name){
    FILE* fp = fopen(file_name, "r"); 
    if(fp == NULL){
		fprintf(stderr, "cat: can't open %s\n", file_name);
        return NULL;
	}

    char** arrayOf_line_pointers =  malloc(10 * sizeof(char*));
    int line_capacity = 10;
    int current_line = 1;

    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        char* line_pt =  malloc(sizeof(line));

        if (current_line >= line_capacity){
            arrayOf_line_pointers =  realloc(arrayOf_line_pointers, 2 * sizeof(arrayOf_line_pointers));
            line_capacity = line_capacity * 2;
            current_line ++ ;
        }

        arrayOf_line_pointers[current_line] = line_pt;
        printf("%s", line); 
    }


    fclose(fp);
    return arrayOf_line_pointers;


return 0;

}
int compVals(const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

