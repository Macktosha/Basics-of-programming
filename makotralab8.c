	#include <stdio.h>
#include <conio.h>
	#include <stdlib.h>

	int main()
	{
   int z, k, i; //счетчики для циклов
   int g = 0;
   int overall_size = 128; //общий выделяемый размер
   int counter = 0;
    char *line;//строки
    char *line2;
        i = 0;
        z = 0;
	    k = 0;
	     printf("Please, enter your line to delete words after ','  .\n\n");
	 line = (char*)malloc(overall_size); //динамическое выделение памяти по необходимости
	    while ((line[counter++] = getchar()) != '\n')
    {
        if (counter >= overall_size)
	        {
            overall_size += 64;
           line = (char*)realloc(line, overall_size);
	        }
    }


   for (i = 0; i < counter; i++)
	    {
	        if (*(line + i) == ',')
	        {
	            i++;
	            while (*(line+i) == ' ') 
					i++;

	            if ((*(line + (i - 1)) == ' ') && i != 0)
					*(line + (i - 1)) = 42;// вспомогательный маркер в виде символа'*' для поиска 

	            while (*(line + i) != ' ' && *(line + i) != ',' && *(line + i) != '\0')
			            {
	                line[i++] = 42;

           }
				*(line + i) = 42;
          i -= 1;
  }
		
				    }
		    line2 = (char*)malloc(counter);
		        for (k = 0, z = 0; k < counter; k++)
		            if (*(line + k) != 42)
			                line2[z++] = line[k];
		        line2[z] = '\0';
	
		    printf("Result:   %s", line2);

	    return 0; 
}