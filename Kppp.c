#include <stdio.h>
#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

double f1(double x);
double f2(double x);
double f3(double x);
double cal_f(double x);
double derivative(double x, double h);// Функция вычисления производной по формуле 
double second_derivative(double x, double h);
void graph();

int main() {
    int choice, count;
    double x, y, start, end, step, deriv, h, Vtor_pro;


    setlocale(LC_ALL, "RUS");

    printf("|                      КУСОЧНАЯ ФУНКЦИЯ                        |\n");
    printf("|--------------------------------------------------------------|\n");
    printf("|Определена как:                                               |\n");
    printf("|f(x) = ln(1+|x|) / (1+e^(-x))           при x < -0.5          |\n");
    printf("|f(x) = cosh(3x-1)          _______      при -0.5 <= x <= 0.5  |\n");
    printf("|f(x) = sin(x^2)·cos(x) / -/(1+x^6)      при x > 0.5           |\n");
    printf("|______________________________________________________________|\n");
    graph();
    do {
        printf("|                      Меню программы                          |\n");
        printf("|Команда 1. Значение f(x) в точке                              |\n");
        printf("|Команда 2. Таблица значений x и f (x)                         |\n");
        printf("|Команда 3. Точки перегиба                                     |\n");
        printf("|Команда 4. Производная в точке                                |\n");
        printf("|Команда 0. Выход из программы                                 |\n");
        printf("|______________________________________________________________|\n");
        printf("|Необходимо выбрать команду:");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("|Значение функции в точке                                      |\n");
            printf("|Введите x = ");
            scanf("%lf", &x);
            printf("|f(%.2f) = %.6f                                            |\n", x, cal_f(x));
            printf("|--------------------------------------------------------------|\n");
            break;

        case 2:
            printf("Начало интервала: ");
            scanf("%lf", &start);
            printf("Шаг: ");
            scanf("%lf", &step);
            printf("Количество отсчетов: ");
            scanf("%d", &count);
            if (count <= 0) {
                printf("Ошибка! Количество отсчетов должно быть положительным.\n");
                break;
            }

            printf("\n|================================|\n");
            printf("|  Таблица значений функции      |\n");
            printf("|================================|\n");
            printf("|   x              f(x)          |\n");
            printf("|================================|\n");

            x = start;
            for (int i = 0; i < count; i++) {
                y = cal_f(x);
                printf("|%10.6f   %12.8f       |\n", x, y);
                x += step;
            }
            printf("|================================|\n");
            printf("Всего значений: %d\n", count);
            printf("|--------------------------------------------------------------|\n");
            break;
        case 3:
            printf("Начало интервала: ");
            scanf("%lf", &start);
            printf("Шаг: ");
            scanf("%lf", &step);
            printf("Количество отсчетов: ");
            scanf("%d", &count);
            if (count <= 0) {
                printf("Ошибка! Количество отсчетов должно быть положительным.\n");
                break;
            }
            printf("Введите точность для вычисления второй производной: ");
            scanf("%lf", &h);
            if (h <= 0) {
                printf("Ошибка! Шаг h должен быть положительным.\n");
                break;
            }


            x = start;
            double prev_fpp = second_derivative(x, h);  // значение f''(x) в первой точке
            int found = 0;

            printf("\nТочки перегиба (интервалы):\n");

            // Перебираем точки, сравнивая текущую f''(x) с предыдущей
            for (int i = 1; i < count; i++) {
                x += step;
                double curr_fpp = second_derivative(x, h);

                // Если знаки f''(x) изменились — есть точка перегиба на [x_prev, x_curr]
                if (prev_fpp * curr_fpp < 0) {
                    found = 1;
                    printf("Между x = %.6f и x = %.6f\n", x - step, x);
                }

                prev_fpp = curr_fpp;  // сохраняем текущее значение для следующей итерации
            }

            if (!found) {
                printf("Точки перегиба на заданном интервале не обнаружены.\n");
                break;
            }

            break;
        case 4:
            printf("Введите значение x: ");
            scanf("%lf", &x);
            printf("Введите точность для вычисления производной: ");
            scanf("%lf", &h);
            if (h <= 0) {
                printf("Ошибка! Шаг h должен быть положительным.\n");
                break;
            }
            deriv = derivative(x, h);

            printf("f'(%.6f) = %.6f\n", x, deriv);
            printf("|--------------------------------------------------------------|\n");
            break;
        case 0:
            printf("Выход! Работа программы завершена!\n");
            break;
        default:
            printf("Неверный выбор!\n");
        }
    } while (choice != 0);
}
//Функция вывода графика
void graph() {
    printf("|                      *                                       |\n");
    printf("|                       *                                      |\n");
    printf("|                        *                                     |\n");
    printf("|                         *                                    |\n");
    printf("|                          *                                   |\n");
    printf("|                           *   *                              |\n");
    printf("|                             *                                |\n");
    printf("|                                   *                          |\n");
    printf("|                    **           *   *   *   *                |\n");
    printf("| ******************                    *    *   *             |\n");
    printf("|______________________________________________________________|\n");
}

// Функция вычисления f(x) для x < -0.5
double f1(double x) {
    return log(1 + fabs(x)) / (1 + exp(-x));
}

// Функция вычисления f(x) для x > 0.5
double f2(double x) {
    return sin(x * x) * cos(x) / sqrt(1 + pow(x, 6));
}

// Функция вычисления f(x) для -0.5 <= x <= 0.5 
double f3(double x) {
    return cosh(3 * x - 1);
}

// Основная функция вычисления f(x)
double cal_f(double x) {
    if (x < -0.5) {
        return f1(x);
    }
    if (x > 0.5) {
        return f2(x);
    }
    if (x >= -0.5 && x <= 0.5) {
        return f3(x);
    }

}

// Функция вычисления производной в точке
double derivative(double x, double h) {
    double f1 = cal_f(x + h);
    double f2 = cal_f(x - h);

    return (f1 - f2) / (2.0 * h);
}
// Функция вычисления двойной производной в точке
double second_derivative(double x, double h) {


    double f_plus = cal_f(x + h);
    double f_center = cal_f(x);
    double f_minus = cal_f(x - h);

    return (f_plus - 2.0 * f_center + f_minus) / (h * h);
}