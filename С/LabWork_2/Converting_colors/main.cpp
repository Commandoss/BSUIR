#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Лабораторная работа 2. Вариант 5
//1. Реализовать структуру, представляющую цвет. Структура содержит тип цветовой модели (RGB, HSV, CMYK) и объединение, хранящее соответствующие структуры с необходимыми значениями компонент с плавающей точкой (например, красный, зеленый и синий для RGB). Добавить возможность задать цвет и перевести из любой модели в любую.
//2. При помощи полей бит добавить возможность упаковать каждую из моделей в два байта (с потерей диапазона цветов). Выводить разницу между оригинальным и упакованным значением. Добавить в структуру “цвет” значение alpha - прозрачность. Вывести результирующий цвет при наложении одного цвета на другой. Добавить выбор из нескольких алгоритмов смешивания.

enum model {
    RGB = 1,
    HSV,
    CMYK
};

struct RGB_t {
    float Red;
    float Green;
    float Blue;
};

struct HSV_t {
    float Hue; // цветовой тон
    float Saturation; // насыщенность
    float Value;  // яркость
};

struct CMYK_t {
    float Cyan; // голубой
    float Magenta; // пурпурный
    float Yellow;
    float Key;
};

struct color {
    float alpha; // прозрачность
};

struct garbage {
    int color_model;
    float MAX;
    float MIN;
    
}; struct garbage Garbage;

struct packaging {
    unsigned int P1_1:16;
    unsigned int P1_2:16;
    
    unsigned int P2_1:16;
    unsigned int P2_2:16;
    
    unsigned int P3_1:16;
    unsigned int P3_2:16;
    
    unsigned int P4_1:16;
    unsigned int P4_2:16;
};

union Color_Model {
    struct RGB_t RGB;
    struct HSV_t HSV;
    struct CMYK_t CMYK;
    
};

void RGB_transformations_to_HSV (union Color_Model *UC) {
    Garbage.MAX = UC -> RGB.Red;
    Garbage.MIN = UC -> RGB.Red;
    if (UC -> RGB.Green > Garbage.MAX)
        Garbage.MAX = UC -> RGB.Green;
    
    if (Garbage.MIN > UC -> RGB.Green)
        Garbage.MIN = UC -> RGB.Green;
    
    if (Garbage.MIN > UC -> RGB.Blue)
        Garbage.MIN = UC -> RGB.Blue;
    
    if (UC -> RGB.Blue > Garbage.MAX)
        Garbage.MAX = UC -> RGB.Blue;
    
    if (Garbage.MAX == Garbage.MIN) UC -> HSV.Hue = 0;
    
    if (Garbage.MAX == UC -> RGB.Red && UC -> RGB.Green >= UC -> RGB.Blue)
        UC -> HSV.Hue = ((60 * (UC -> RGB.Green - UC -> RGB.Blue)) / (Garbage.MAX - Garbage.MIN)) + 0;
    
    if (Garbage.MAX == UC -> RGB.Red && UC -> RGB.Blue >= UC -> RGB.Green)
        UC -> HSV.Hue = ((60 * (UC -> RGB.Green - UC -> RGB.Blue)) / (Garbage.MAX - Garbage.MIN)) + 360;
    
    if (Garbage.MAX == UC -> RGB.Green)
        UC -> HSV.Hue = ((60 * (UC -> RGB.Blue - UC -> RGB.Red)) / (Garbage.MAX - Garbage.MIN)) + 120;
    
    if (Garbage.MAX == UC -> RGB.Blue)
        UC -> HSV.Hue = ((60 * (UC -> RGB.Red - UC -> RGB.Green)) / (Garbage.MAX - Garbage.MIN)) + 240;
    
    if (Garbage.MAX == 0) UC -> HSV.Saturation = 0;
    else UC -> HSV.Saturation = (1 - (Garbage.MIN / Garbage.MAX));
    
    UC -> HSV.Value = Garbage.MAX / 255;
    if (UC -> HSV.Saturation <= 1) UC -> HSV.Saturation *= 100;
    if (UC -> HSV.Value <= 1) UC -> HSV.Value *= 100;
    if (UC -> RGB.Red == UC -> RGB.Blue && UC -> RGB.Blue  == UC -> RGB.Green) UC -> HSV.Hue = 0;
}

void HSV_transformations_to_RGB (union Color_Model *UC) {
    if (UC -> HSV.Saturation >= 1) (UC -> HSV.Saturation = UC -> HSV.Saturation / 100);
    
    if (UC -> HSV.Value >= 1) (UC -> HSV.Value = UC -> HSV.Value / 100);
    
    float fC = UC -> HSV.Value * UC -> HSV.Saturation;
    float fHPrime = fmod(UC -> HSV.Hue / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = UC -> HSV.Value - fC;
    
    if(0 <= fHPrime && fHPrime < 1) {
        UC -> RGB.Red = fC;
        UC -> RGB.Green = fX;
        UC -> RGB.Blue = 0;
    }
    else if (1 <= fHPrime && fHPrime < 2) {
        UC -> RGB.Red = fX;
        UC -> RGB.Green = fC;
        UC -> RGB.Blue = 0;
    }
    else if (2 <= fHPrime && fHPrime < 3) {
        UC -> RGB.Red = 0;
        UC -> RGB.Green = fC;
        UC -> RGB.Blue = fX;
    }
    else if (3 <= fHPrime && fHPrime < 4) {
        UC -> RGB.Red = 0;
        UC -> RGB.Green = fX;
        UC -> RGB.Blue = fC;
    }
    else if (4 <= fHPrime && fHPrime < 5) {
        UC -> RGB.Red = fX;
        UC -> RGB.Green = 0;
        UC -> RGB.Blue = fC;
    }
    else if (5 <= fHPrime && fHPrime < 6) {
        UC -> RGB.Red = fC;
        UC -> RGB.Green = 0;
        UC -> RGB.Blue = fX;
    }
    else {
        UC -> RGB.Red = 0;
        UC -> RGB.Green = 0;
        UC -> RGB.Blue = 0;
    }
    
    UC -> RGB.Red = (fM + UC -> RGB.Red) * 255;
    UC -> RGB.Green = (fM + UC -> RGB.Green) * 255;
    UC -> RGB.Blue = (fM + UC -> RGB.Blue) * 255;
}

void CMYK_transformations_to_RGB (union Color_Model *UC) {
    if (UC -> CMYK.Cyan >= 1) UC -> CMYK.Cyan /= 100;
    
    if (UC -> CMYK.Magenta >= 1) UC -> CMYK.Magenta /= 100;
    
    if (UC -> CMYK.Yellow >= 1) UC -> CMYK.Yellow /= 100;
    
    if (UC -> CMYK.Key >= 1) UC -> CMYK.Key /= 100;
    
    UC -> RGB.Red = 255 * (1 - UC -> CMYK.Cyan) * (1 - UC -> CMYK.Key);
    UC -> RGB.Green = 255 * (1 - UC -> CMYK.Magenta) * (1 - UC -> CMYK.Key);
    UC -> RGB.Blue = 255 * (1 - UC -> CMYK.Yellow) * (1 - UC -> CMYK.Key);
}

void RGB_transformations_to_CMYK (union Color_Model *UC) {
    if (UC -> CMYK.Cyan < 1) UC -> CMYK.Cyan *= 100;
    
    if (UC -> CMYK.Magenta < 1) UC -> CMYK.Magenta *= 100;
    
    if (UC -> CMYK.Yellow < 1) UC -> CMYK.Yellow *= 100;
    
    if (UC -> CMYK.Key < 1) UC -> CMYK.Key *= 100;
    
    float w = fmax(fmax(UC -> RGB.Red / 255, UC -> RGB.Green / 255), UC -> RGB.Blue / 255);;
    
    if (UC -> RGB.Red == 0 && UC -> RGB.Green == 0 && UC -> RGB.Blue == 0)  {
        UC -> CMYK.Cyan = 0;
        UC -> CMYK.Magenta = 0;
        UC -> CMYK.Yellow = 0;
        UC -> CMYK.Key = 1;
    }
    
    else  {
        UC -> CMYK.Cyan = (w - (UC -> RGB.Red / 255)) / w;
        UC -> CMYK.Magenta = (w - (UC -> RGB.Green / 255)) / w;
        UC -> CMYK.Yellow = (w - (UC -> RGB.Blue / 255)) / w;
        UC -> CMYK.Key = 1 - w;
    }
    
    if (UC -> CMYK.Cyan < 1) UC -> CMYK.Cyan *= 100;
    
    if (UC -> CMYK.Magenta < 1) UC -> CMYK.Magenta *= 100;
    
    if (UC -> CMYK.Yellow < 1) UC -> CMYK.Yellow *= 100;
    
    if (UC -> CMYK.Key < 1) UC -> CMYK.Key *= 100;
}

void packaging (union Color_Model *UC, int transformation_color_model) {
    printf("-----------------------------------------------------------\n");
    struct packaging Pac;
    
    switch (transformation_color_model)
    {
        case RGB :
            Pac.P1_1 = UC -> RGB.Red;
            Pac.P1_2 = (UC -> RGB.Red - Pac.P1_1) * pow(10, 6);
            Pac.P2_1 = UC -> RGB.Green;
            Pac.P2_2 = (UC -> RGB.Green - Pac.P2_1) * pow(10,6);
            Pac.P3_1 = UC -> RGB.Blue;
            Pac.P3_2 = (UC -> RGB.Blue - Pac.P3_1) * pow(10,6);
            printf("Packaging RGB = (%d.%d, %d.%d, %d.%d)", Pac.P1_1, Pac.P1_2, Pac.P2_1, Pac.P2_2, Pac.P3_1, Pac.P3_2);
            break;
            
        case HSV :
            Pac.P1_1 = UC -> HSV.Hue;
            Pac.P1_2 = (UC -> HSV.Hue - Pac.P1_1) * pow(10, 6);
            Pac.P2_1 = UC -> HSV.Saturation;
            Pac.P2_2 = (UC -> HSV.Saturation - Pac.P2_1) * pow(10, 6);
            Pac.P3_1 = UC -> HSV.Value;
            Pac.P3_2 = (UC -> HSV.Value - Pac.P3_1) * pow(10, 6);
            printf("Packaging HSV = (%d.%d, %d.%d%%, %d.%d%%)", Pac.P1_1, Pac.P1_2, Pac.P2_1, Pac.P2_2, Pac.P3_1, Pac.P3_2);
            break;
            
        case CMYK :
            Pac.P1_1 = UC -> CMYK.Cyan;
            Pac.P1_2 = (UC -> CMYK.Cyan - Pac.P2_1) * pow(10, 6);
            Pac.P2_1 = UC -> CMYK.Magenta;
            Pac.P1_2 = (UC -> CMYK.Magenta - Pac.P2_1) * pow(10, 6);
            Pac.P3_1 = UC -> CMYK.Yellow;
            Pac.P1_2 = (UC -> CMYK.Yellow - Pac.P3_1) * pow(10, 6);
            Pac.P4_1 = UC -> CMYK.Key;
            Pac.P1_2 = (UC -> CMYK.Key - Pac.P4_1) * pow(10, 6);
            printf("Packaging CMYK = (%d.%d%%, %d.%d%%, %d.%d%%, %d.%d%%)", Pac.P1_1, Pac.P1_2, Pac.P2_1, Pac.P2_2, Pac.P3_1, Pac.P3_2, Pac.P4_1, Pac.P4_2);
            break;
            
        default:
            break;
    }
}

void customization_of_models (union Color_Model *UC, int *color_model) {
    puts("Какую цветовую модель вы будите задавать?");
    printf("1.RGB  2.HSV  3.CMYK\nОтвет: ");
    scanf("%d", color_model);
    printf("-----------------------------------------------------------\n");
    
    switch (*color_model)
    {
        case RGB :
            //            for (int i = 0; i < 1; i++) {
            printf("Задайте цвет RGB (0.0.0): ");
            //                rewind(stdin);
            scanf("%f", &UC -> RGB.Red); //|| (scanf("%f", &RGB_t -> Red) <= 0))) {
            //                    puts("Ошибка ввода"); i--;
            
            scanf("%f", &UC -> RGB.Green);
            scanf("%f", &UC -> RGB.Blue);
            
            break;
            
        case HSV :
            printf("Задайте цвет HSV H:0, S:0, V:0 : ");
            scanf("%f %f %f", &UC -> HSV.Hue, &UC -> HSV.Saturation, &UC -> HSV.Value);
            break;
            
        case CMYK :
            printf("Задайте цвет CMYK C:0, M:0, Y:0, K:0 : ");
            scanf("%f %f %f %f", &UC -> CMYK.Cyan, &UC -> CMYK.Magenta, &UC -> CMYK.Yellow, &UC -> CMYK.Key);
            break;
        default:
            break;
    }
}

void mixing_algorithms (union Color_Model *UC) {
    int y = 1;
    while (y == 1 || y == 3) {
        struct color C;
        int color_m;
        
        if (y == 3) {
            UC -> RGB.Red = 0;
            UC -> RGB.Green = 0;
            UC -> RGB.Blue = 0;
        }
        
        float R = UC -> RGB.Red, G = UC -> RGB.Green, B = UC -> RGB.Blue;
        customization_of_models(UC, &color_m);
        printf("-----------------------------------------------------------\n");
        printf("Задайте прозрачность: ");
        scanf("%f", &C.alpha);
        if (C.alpha >= 1) C.alpha /= 100;
        
        switch (color_m)
        {
            case HSV :
                HSV_transformations_to_RGB(UC);
                color_m = RGB;
                break;
                
            case CMYK :
                CMYK_transformations_to_RGB(UC);
                color_m = RGB;
                break;
                
            default:
                break;
                
        }
        
        if (color_m == RGB) {
            printf("-----------------------------------------------------------\n");
            printf("RGB #1 = (%f , %f , %f)", R, G, B);
            printf("\nRGB #2 = (%f , %f , %f)", UC -> RGB.Red, UC -> RGB.Green, UC -> RGB.Blue);
            UC -> RGB.Red = R * C.alpha + UC -> RGB.Red * (1 - C.alpha);
            UC -> RGB.Green = G * C.alpha + UC -> RGB.Green * (1 - C.alpha);
            UC -> RGB.Blue = B * C.alpha + UC -> RGB.Blue * (1 - C.alpha);
            printf("\nMixing RGB = (%f , %f , %f)", UC -> RGB.Red, UC -> RGB.Green, UC -> RGB.Blue);
        }
        
        printf("\n-----------------------------------------------------------\n");
        printf("Хотите продолжить смешивание?\n1)Да. 2)Нет. 3)Да, но с нулевыми значениями.\nОтвет: ");
        scanf("%d", &y);
    }
}

int main () {
    union Color_Model UC;
    int transformation_color_model, color_model;
    customization_of_models(&UC, &color_model);
    
    printf("-----------------------------------------------------------\n");
    puts("В какую цветовую модель вы будите переводить?");
    printf("1.RGB  2.HSV  3.CMYK\nОтвет: ");
    scanf("%d", &transformation_color_model);
    
    if (transformation_color_model == color_model) { puts("Ошибка трансформации."); return 1; }
    
    switch (transformation_color_model)
    {
        case RGB :
            if (color_model == HSV) HSV_transformations_to_RGB(&UC);
            
            if (color_model == CMYK) CMYK_transformations_to_RGB(&UC);
            
            packaging(&UC, transformation_color_model);
            printf("\nOriginal RGB = (%f , %f , %f)", UC.RGB.Red, UC.RGB.Green, UC.RGB.Blue);
            break;
            
        case HSV :
            if (color_model == RGB) RGB_transformations_to_HSV(&UC);
            if (color_model == CMYK) {
                CMYK_transformations_to_RGB(&UC);
                RGB_transformations_to_HSV(&UC);
            }
            packaging(&UC, transformation_color_model);
            printf("\nOriginal HSV = (%f ,%f%% ,%f%%)", UC.HSV.Hue, UC.HSV.Saturation, UC.HSV.Value);
            HSV_transformations_to_RGB(&UC);
            break;
            
        case CMYK :
            if (color_model == RGB) RGB_transformations_to_CMYK(&UC);
            
            if (color_model == HSV) {
                HSV_transformations_to_RGB(&UC);
                RGB_transformations_to_CMYK(&UC);
            }
            packaging(&UC, transformation_color_model);
            printf("\nOriginal CMYK = (%f%% ,%f%% ,%f%% ,%f%%)", UC.CMYK.Cyan, UC.CMYK.Magenta, UC.CMYK.Yellow, UC.CMYK.Key);
            CMYK_transformations_to_RGB(&UC);
            break;
        default:
            break;
    }
    printf("\n-----------------------------------------------------------\n");
    mixing_algorithms(&UC);
    printf("-----------------------------------------------------------\n");
    return 0;
}
