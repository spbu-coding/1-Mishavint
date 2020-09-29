#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define error(...) (fprintf(stderr, __VA_ARGS__))

struct interval_t
{  // Создаем структуру с понятным названием
    double left_border;  // В которой будет два значения:
    double right_border; // Левая граница и правая граница
};

double rectangle_rule(double left_border, double right_border) {                           //Правило средних прямоугольников
    return (right_border - left_border) * sin((left_border + right_border) / 2);
}

double simpsons_rule(double left_border , double right_border)                             //Правило Симсона
{
    return (right_border - left_border) / 6 * (sin(left_border) + 4
                                                                  * sin((left_border + right_border) / 2) + sin(right_border));
}

int EnterAll( struct interval_t *interval) {
    if (printf("Please, enter LEFT BORDER: ") < 0 )
    {
        error("Can't write about left border");
        return -1;
    }
    if (scanf("%lf", &interval->left_border) !=1 )
    {
        error("Can't scan left border in 1st time");
        return -1;
    }//Считываем левую границу
    while (interval->left_border < 0 || interval->left_border > 3.14) {                     // Проверяем левую границу
        if(printf("\n Please enter LEFT BORDER that > 0 and < 3.14: ") < 0 )
        {
            error("Can't write about warn about left border");
            return -1;
        }
        if (scanf("%lf", &interval->left_border) !=1)
        {
            error("Can't scan left border");
            return -1;
        }
    }

    if (printf("Please, enter RIGHT border: ") < 0)
    {
        error("Can't write about right border");
        return -1;
    }
    if (scanf("%lf" , &interval -> right_border ) !=1 )
    {
        error("Can't scan right border in first time");
    }//Считываем правую границу
    while (interval->right_border < interval->left_border || interval->right_border > 3.14) {          //Проверяем правую границу
        if(printf("\n Please enter RIGHT BORDER that > LEFT BORDER and < 3.14: ") <0)
        {
            error("Can't write warn about right border");
            return -1;
        }
        if (scanf("%lf", &interval->right_border) !=1 )
        {
            error("Can't scan right border");
            return -1;
        }
    }
    return 0;
}

//void FinalResult( struct interval_t *interval )
//{
//    printf("~~~~~~~~~~~~~~~~~~~ \n |Rectangle rule: %0.9lf | \n |Simpsons_rule:  %0.9lf | \n ~~~~~~~~~~~~~~~~~~~ \n \n Now i will work with"
//           " arrays \n \n" ,  // Для красоты и понятности добави пару символов
//           rectangle_rule(interval->left_border , interval->right_border ) ,  // Возвращаем результат методом средних прямоугольников
//           simpsons_rule(interval->left_border , interval->right_border ) );  // Возвращаем результат методом Симпсона
//}

//void Array(struct interval_t *interval , int *rectangle_count )
//{
//    printf("---------%d rectangles---------\n", *rectangle_count);
//    double ResultOfRectRule = 0;
//    double ResultOfSimpsRule = 0;
//    double difference = interval->right_border - interval->left_border;
//    for(int i = 0 ; i < *rectangle_count ; i++)
//    {
//        ResultOfRectRule += rectangle_rule(interval->left_border+((difference / *rectangle_count) * i )  ,
//                                           interval->left_border+((difference / *rectangle_count) * (i + 1) ) );
//        ResultOfSimpsRule += simpsons_rule(interval->left_border+((difference / *rectangle_count) * i )  ,
//                                           interval->left_border+((difference / *rectangle_count) * (i + 1) ) );
//    }
//    printf("Rectangle rule: %0.5lf \nSimpson's rule: %0.5lf" , ResultOfRectRule , ResultOfSimpsRule);
//
//    printf("\n\n");
//}


char **array( struct interval_t *interval, int *rectangle_count , int ExperimentCount )
{

    char **results = (char **)malloc(sizeof(char * ) * ExperimentCount); // отводим память для указателей на указатели
    if(!results)                                                         // если что-то пошло не так, прекращаем работу
    {
        return NULL;
    }
    double difference = interval->right_border - interval->left_border ; // узнаем разницу между правой и левой границами
    double ResultOfRectRule = 0;                                         // вводим переменную для ответа
    double ResultOfSimpsRule = 0;                                        // вводим переменную для ответа
    for(int i = 0 ; i < ExperimentCount ; i++)
    {
        for(int j = 0 ; j < (*(rectangle_count + i))  ; j++)                      // считаем для каждого случая в отдельности
        {

            ResultOfRectRule += rectangle_rule(interval->left_border+((difference / *(rectangle_count + i)) * j )  ,
                                               interval->left_border+((difference / *(rectangle_count + i)) * (j + 1) ) );
            ResultOfSimpsRule += simpsons_rule(interval->left_border+((difference / *(rectangle_count + i)) * j )  ,
                                               interval->left_border+((difference / *(rectangle_count + i)) * (j + 1) ) );
        }
        results[i] = (char *)malloc(sizeof(char) * 32);                                                                         // выделяем память для  кождого ответа
        if(!sprintf(results[i] , "%d SimpRule: %0.5lf RectRule: %0.5lf " , *(rectangle_count+i) , ResultOfSimpsRule , ResultOfRectRule )) // вбиваем в каждый result ответ
        {
            free(results[i]);                                                   // если что-то пошло не так, то очищяем всё
            error("Cannot write results to string in %d experiment\n", i);
            return NULL;
        }
        ResultOfRectRule = 0;
        ResultOfSimpsRule =0;
    }
    return results;                                 // возваращаем указатель на указатели
}

int main(){

    struct interval_t interval = { 0.0 , 0.0 }; // Ввели произовдную
    if(EnterAll( &interval) != 0)
    {
        return 30;
    }// Нормально ввели производную
    //FinalResult( &interval);                    // Функция, которая нормально выводит всё, что надо


    unsigned int rectangle_count[] = {5, 10, 20, 100, 500, 1000}; // unsigned int - так как мы не использьуем отрицательное количество прямоугольников
    unsigned int numberOfExperiments = sizeof(rectangle_count) / sizeof(rectangle_count[0]); // Получаем количество экспериментов


    char **answer = array(&interval , &rectangle_count , numberOfExperiments); //создаем указатели на какую-то ячейку памяти, в которой будут ответы
    for(int i = 0 ; i < numberOfExperiments ; i++)
    {
        printf ("%s\n" , answer[i]);                        // выводим ответы
        free(answer[i]);                                    // очищаем память
    }



//    for(int i = 0 ; i < numberOfExperiments ; i++)
//    {
//        Array(&interval , &(rectangle_count[i]) );
//    }

}