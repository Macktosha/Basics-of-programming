#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996)
#define MAXLINE 1000
int main(void)
{
	FILE* fptr;
	fopen_s(&fptr, "file1.txt", "r");
	if (fptr == NULL)
	{
		printf("Error\n");
		return 1;
	}

	int second_flag = 0;
	char* mas = (char*)calloc(MAXLINE, MAXLINE * sizeof(char*));
	while (fgets(mas, MAXLINE, fptr))
	{
		if (*(mas + strlen(mas) - 2) == 41)
		{
			char* arr = (char*)calloc(MAXLINE, MAXLINE * sizeof(char*));
			fgets(arr, MAXLINE, fptr);
			if (*(arr + 0) == 123)
			{
				int i = 0;
				while (*(mas + i) != 32)
				{
					i++;
				}
				while (*(mas + i) == 32)
				{
					i++;
				}
				while (*(mas + i) != '\0')
				{
					printf("%c", *(mas + i));
					i++;
				}

			}
			int flag = 0;
			while (flag != 1 && fgets(arr, MAXLINE, fptr))
			{

				if (*(arr + 0) == 125)
				{
					flag = 1;
				}
				char* istr;
				if ((istr = strstr(arr, "int ")) != NULL)
				{
					int j = 0;
					while (*(arr + j) != 32)
					{
						j++;
					}
					while (*(arr + j) == 32)
					{
						j++;
					}
					while (*(arr + j) != '\n')
					{
						if (*(arr + j) == 32 || *(arr + j) == 59)
						{
							break;
						}
						printf("%c", *(arr + j));
						j++;
					}




					printf("\n");
				}

				if ((istr = strstr(arr, "char ")) != NULL)
				{
					int j = 0;
					while (*(arr + j) != 32)
					{
						j++;
					}
					while (*(arr + j) == 32)
					{
						j++;
					}
					while (*(arr + j) != '\n')
					{
						if (*(arr + j) == 32 || *(arr + j) == 59)
						{
							break;
						}
						printf("%c", *(arr + j));
						j++;
					}




					printf("\n");
				}

				if ((istr = strstr(arr, "float ")) != NULL)
				{
					int j = 0;
					while (*(arr + j) != 32)
					{
						j++;
					}
					while (*(arr + j) == 32)
					{
						j++;
					}
					while (*(arr + j) != '\n')
					{
						if (*(arr + j) == 32 || *(arr + j) == 59)
						{
							break;
						}
						printf("%c", *(arr + j));
						j++;
					}




					printf("\n");
				}

				if ((istr = strstr(arr, "double ")) != NULL)
				{
					int j = 0;
					while (*(arr + j) != 32)
					{
						j++;
					}
					while (*(arr + j) == 32)
					{
						j++;
					}
					while (*(arr + j) != '\n')
					{
						if (*(arr + j) == 32 || *(arr + j) == 59)
						{
							break;
						}
						printf("%c", *(arr + j));
						j++;
					}




					printf("\n");
				}

			}
		}
	}
	fclose(fptr);
}

/*

*/