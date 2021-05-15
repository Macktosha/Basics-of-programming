#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX 256

enum ConsoleColor { //разные цвета
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

int main()
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//получаем хэндл консоли
 
  
    FILE* file = fopen("file1.txt", "r");
    char* line = (char*)calloc(MAX, sizeof(char*));//динамически выделяем память

    if (file == NULL)
    {
        printf("Error\n");
        return 1;
    }
    int k=0,j=0;
    int flag1 = 0,flag2=0;

    while (fgets(line, MAX, file)) {

        int i = 0;

        if (flag2) { //для многострочного комментария 
            SetConsoleTextAttribute(hStdout, (WORD)((Yellow << 4) | LightGreen));
            if (strstr(line, "*/")) {//если он заканчивается на следующей строке то выделяем ее
                printf("%s", line);
                flag2 = 0;
                SetConsoleTextAttribute(hStdout, (WORD)((Black << 4) | White));//возвращаем обычный цвет консоли 
               continue;
            }
            else {
                for (j = i; line[j] != '\n'; j++) //если еще есть строка то ее тоже нужно выделить 
                    printf("%c", line[j]);
                i = j;
                SetConsoleTextAttribute(hStdout, (WORD)((Black << 4) | White));
            }

        }

       while(line[i]!='\0')
       {
          
           
            if (line[i] == '/')
                flag1 = 1;
      
            if (flag1) {//рассматриваем случаи,где после / идет какой-то символ
                switch (line[i + 1])
                {
                case '/': SetConsoleTextAttribute(hStdout, (WORD)((Yellow << 4) | LightGreen));//однострочный комментарий
                    for (k = i; line[k] != '\n'; k++)
                        printf("%c", line[k]);
                    i = k;
                    SetConsoleTextAttribute(hStdout, (WORD)((Black << 4) | White));
                    flag1 = 0;
                    break;
                case '*':  SetConsoleTextAttribute(hStdout, (WORD)((Yellow << 4) | LightGreen));
                    for (k = i; line[k] != '\n'; k++)
                        printf("%c", line[k]);
                    i = k;
                    SetConsoleTextAttribute(hStdout, (WORD)((Black << 4) | White));
                    flag1 = 0;
                    flag2 = 1;
                    break;

                default: break;
                }

            }
            printf("%c", line[i]);

            i++;
        }
   
    }

    free(line); 
    fclose(file);
    return 0;
}