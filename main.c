#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <getopt.h>

int number_of_iterations = 0 ;

extern float f1(float);
extern float f2(float);
extern float f3(float);
int count = 0;
/*float f1(float x)
{
    float y;
    y = (1.5/(x+1)) +3;
    return y;
}
float f2(float x)
{
    float y;
    y = 2.5*x-9.5;
    return y;

}
float f3(float x)
{
    float y;
    y = 5/x;
    return y;
}*/

float absolute(float x)
{
    if( x < 0 )
        x *= (-1);
    return x;
}

float root(float (*f)(float), float (*g)(float), float a, float b, float eps1) //Вычисление с точностью esp1 корня уравнения f(x) = g(x) на отрезке [a, b]
{
    number_of_iterations = 0 ;
    int flag;
    if (((f(a) - g(a) < 0) && (f((a+b)/2) - g((a+b)/2) <= (f(a) - g(a) + f(b) - g(b))/2)) || ((f(a) - g(a) > 0) && (f((a+b)/2) - g((a+b)/2) > (f(a) - g(a) + f(b) - g(b))/2)))
    {
        flag = 1;
    } //приближение слева
    else{
        flag = 0;//приближение справа
   }

    float c = (a*(f(b) - g(b)) - b*(f(a) - g(a)))/((f(b) - g(b)) - (f(a) - g(a)));
    while (flag*(f(c) - g(c))*(f(c + eps1) - g(c + eps1)) + (1 - flag)*(f(c) - g(c))*(f(c - eps1) - g(c - eps1)) > 0)
    {
        c = (a*(f(b) - g(b)) - b*(f(a) - g(a)))/((f(b) - g(b)) - (f(a) - g(a)));
        if (flag)
            a = c;
        else
            b = c;
        number_of_iterations++;
    }
    return c;
}

float integral(float (*f)(float), float a, float b, float eps2) //Вычисление с точностью esp2 величины определенного интеграла от функции f(x) на отрезке [a, b]
{
    float i0 = 0.0;
    float i, in;
    int n = 10;
    float h = (b - a);
    h /= 10.0 ;

    float curr_sum = (f(a) + f(b))/2.0;
    float x = a;
    for (i = 1; i <= 9; i++)
    {
        curr_sum += f(x);
        x += h;
    }
    in = curr_sum * h;
    i0 = in - 3*eps2 - 1;
    while( absolute(in - i0)/3 > eps2/5)
    {
        i0 = in; //значение in в предыдущем цикле
        h /= 2;
        x = a + h;
        n *= 2;
        for  (i = 1; i <= n/2 ; i++)
        {
            curr_sum += f(x);
            x += h/0.5;
        }
        in = curr_sum * h; // новый член последовательности
    }
    return in;
}

//-------------outputting--------------------------
void num_of_iterations(int number_of_iterations) //выводит число итераций
{
    printf("%d \n", number_of_iterations);
}

void root_abs(float x1, float x2, float x3){//вывод абсцисс точек перечесения трех функций

    printf("Abscissas of interseptionpoints of graphs\n");
    printf("f1 = 1.5/(x+1)+3 f2 = 2.5x-9.5  : %f \n",  x1);
    printf("f3 = 5/x         f2 = 2.5x-9.5  : %f \n",  x3);
    printf("f1 = 1.5/(x+1)+3 f3 = 5/x       : %f \n",  x2);
}

//-------------testing block-----------------------
float f4 (float x)  //три функции для реализации тестирования нахождения корня и интегрирования
{
    return x;
}
float f5 (float x)
{
    return 1/x;
}
float f6 (float x)
{
    float y = x*x - 3*x + 3;
    return y;
}

void root_testing()
{
    int i1, i2;   // номера функций, точки пересечения которых будут найдены
    float a, b, e, correct;
    printf("Insert index of the function to find the root:\n");
    printf("y = x (1)\ny = 1/x (2)\ny = x^2 - 3x + 3 (3)  \n");
    printf(" number of two functions                      \n");
    printf("a,b - interval ( a < b, type float)           \n");
    printf("e - eps, correct answer                       \n");

    scanf( "%d %d %f %f %f %f", &i1, &i2, &a, &b, &e, &correct);

    float dx, result;
    if ( i1 + i2 == 3 )
    {
        result = root(f4, f5, a, b, e);//[0.5;1.5] 1
    }
    if ( i1 + i2 == 4 )
    {
        result = root(f4, f6, a, b, e);//[0; 1.5] 1
    }
    if ( i1 + i2 == 5 )
    {
        result = root(f5, f6, a, b, e);//[0.5; 2.0] 1
    }
    dx = absolute(correct-result);
    if( dx <= e)
        printf("correct root_test  \n");

    else
        printf("incorrect root_test\n");

}

void integral_testing() // функция тестирования integral, работает с функциями test_f1, test_f2, test_f3, заданными ранее
{
    int i;
    float a, b, e, correct;
    float dx;
    float result;
    printf("\nInsert index of the function to find the integral:\n");
    printf("y = x (1)\ny = 1/x (2)\ny = x^2 - 3x + 3 (3)        \n");
    printf("i - number of function                              \n");
    printf("a,b - interval ( a < b, type float)                 \n");
    printf("e - eps, correct answer                             \n");

    scanf("%d %f %f %f %f", &i, &a, &b, &e, &correct);

    if(i == 1)
    {
        result = integral(f4, a, b, e);
    }
    if(i == 2)
    {
        result = integral(f5, a, b, e);
    }
    if(i == 3)
    {
        result = integral(f6, a, b, e);
    }

    dx = absolute(correct-result);
    if( dx <= e)
        printf("correct integral_test\n");
    else
        printf("incorrect integral_test\n");

    //return 0;
}


int main(int argc, char **argv)
{
   if(argc == 1){
    printf("Insert --help for help\n");
    return 0;
   }
  if(!strcmp(argv[1], "--help")){
    printf("The area of the figure bounded by the graphs : f1 = 1.5/(x+1)+3 f2 = 2.5x-9.5  f3 = 5/x   is calculated.\n");
    printf("--root   abs \n");
    printf("--num_of_iterations   number of iterations in function of root\n");
    printf("--test_root  root function testing\n");
    printf("--integral_test   integral function testing \n");
    return 0;
  }


    int i;
    int number_of_iterations1, number_of_iterations2, number_of_iterations3;
    float eps = 0.0001;
    float a, b;

    a = 5.0;
    b = 6.0;
    float x1 = root(f1, f2, a, b, eps); // точка пересечения f1 и f2, x1 = 5.098...
    number_of_iterations1 = number_of_iterations;

    a = 1.0;
    b = 2.0;
    float x2 = root(f1, f3, a, b, eps); // точка пересечения f1 и f3, x2 = 1.377...
     number_of_iterations2 = number_of_iterations;

    a = 4.0;
    b = 5.0;
    float x3 = root(f2, f3, a, b, eps); // точка пересечения f2 и f3, x3 = 4.269...
     number_of_iterations2 = number_of_iterations;

  if(!strcmp(argv[1], "--root")){
    printf("Abscissas of interseptionpoints of graphs\n");
    printf("f1 = 1.5/(x+1)+3 f2 = 2.5x-9.5  : %f \n",  x1);
    printf("f3 = 5/x         f2 = 2.5x-9.5  : %f \n",  x3);
    printf("f1 = 1.5/(x+1)+3 f3 = 5/x       : %f \n",  x2);
    return 0;
  }
   if(!strcmp(argv[1], "--num_of_iterations")){
    printf("%d \n", number_of_iterations);
    return 0;
  }
   if(!strcmp(argv[1], "--root_testing")){
    root_testing();
    return 0;
  }
   if(!strcmp(argv[1], "--integral_testing")){
    integral_testing();
    return 0;
   }
   if(!strcmp(argv[1], "--integral")){
     float square = integral(f1, x2, x1, eps) - integral(f2, x3, x1, eps) - integral(f3, x2, x3, eps); // в соответсвтвии с графиками функций f1, f2, f3
    printf("\nSquare: %f", square);
    return 0;
   }

    return 0;
}
