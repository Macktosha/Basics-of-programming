#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI    3.14159265358979323846

double my_length(int x1, int x2, int y1, int y2)// функция считает длину стороны
{
    double side_length = 0;
    side_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return side_length;
}

double my_angle(double a, double b, double c)// функция считает арккосинус углов 
{
    double angle_value = 0;
    angle_value = acos(((a * a + b * b - c * c)) / (2 * a * b));
    angle_value = (angle_value * 180) / M_PI;
    return angle_value;
}


int main(void)
{
       int X_a, Y_a, X_b, Y_b, X_c, Y_c;// координаты точек A,B,C
         X_a = Y_a = X_b = Y_b = X_c = Y_c = 0;
                                                        printf("Hello, let's define your triangle type\n");
                FILE* file1 = fopen("file1.txt", "w+");

                printf("Please, enter coordinates of A point [x,y]:  \n");
                    scanf("%d %d", &X_a, &Y_a);
                fprintf(file1, "%d %d\n", X_a, Y_a);


                 printf("Please, enter coordinates of B point [x,y]:  \n");
                    scanf("%d %d", &X_b, &Y_b);
                fprintf(file1, "%d %d\n", X_b, Y_b);


                printf("Please, enter coordinates of C point [x,y]:  \n");
                     scanf("%d %d", &X_c, &Y_c);
                 fprintf(file1, "%d %d\n", X_c, Y_c);


    FILE* file2 = fopen("file2.txt", "w"); 

         fscanf(file1, "%d %d\n%d %d\n%d %d", X_a, Y_a, X_b, Y_b, X_c, Y_c);
         fprintf(file2, "%d %d\n%d %d\n%d %d", X_a, Y_a, X_b, Y_b, X_c, Y_c);

    fclose(file1);

    fprintf(file2, "\n\n");

    // определяем не прямая ли заданные точки?
    int cnt_praym = 0;

    if ((X_a - X_b) * (Y_c - Y_b) == (X_c - X_b) * (Y_a - Y_b))
        cnt_praym++;
    

    if (cnt_praym > 0)
    {
        fprintf(file2, "This triangle doesn't exist because it is a point or a line");
        return 0;
    }
   

    double L_AB = 0;
    double L_BC = 0;
    double L_AC = 0;

    L_AB = my_length(X_a, X_b, Y_a, Y_b);//определяем длину стороны
     L_BC = my_length(X_b, X_c, Y_b, Y_c);
      L_AC = my_length(X_a, X_c, Y_a, Y_c);


    double alpha = 0;
    double betta = 0;
    double gamma = 0;

    alpha = my_angle(L_BC, L_AC, L_AB);// определим углы треугольника
     betta = my_angle(L_AB, L_AC, L_BC);
      gamma = my_angle(L_AB, L_BC, L_AC);

    if (L_AB == L_BC == L_AC)
    {
        fprintf(file2, "Your triangle is equilateral\n");// равносторонний треугольнимк
        return 0;
    }
    if ((L_AB == L_BC) || (L_AB == L_AC) || (L_AC == L_BC))  
        {
            fprintf(file2, "Your triangle is isosceles\n");// равнобедренный треугольник
            return 0;
        }
    

        if ((alpha == 90) || (betta == 90) || (gamma == 90))
            fprintf(file2, " This is a rectangular triangle\n");// прямоугольный треугольник
        else
            if ((alpha > 90) || (betta > 90) || (gamma > 90))
                fprintf(file2, "This is an obtuse triangle\n");//тупоугольный треугольник
            else
                fprintf(file2, "This is an acute-angle triangle\n"); //остроугольный треугольник
            
    fclose(file2);
    return 0;
}