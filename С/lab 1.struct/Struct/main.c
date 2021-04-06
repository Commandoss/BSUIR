#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>

// Лабораторная работа 1. Вариант 12
//1. Реализовать структуру “параграф”, которая содержит кол-во строк, длину строки, размер шрифта, междустрочный интервал, интервал до параграфа, интервал после параграфа (размер шрифта и интервалы - значения высоты в пикселях). Сделать возможность добавить произвольное число параграфов с клавиатуры, задавая при этом значения всех полей структуры. Сделать подсчет высоты всего текста в пикселях.
//2. Добавить структуру “страница”, которая имеет определенную высоту в пикселях. В зависимости от числа параграфов вычислять кол-во страниц текста. В структуру “параграф” добавить поле “цвет” (enum - черный, красный, синий и т.д.). Высчитать стоимость печать текста в зависимости от кол-ва страниц и кол-ва цветного текста.

enum color {
    red = 1,
    green,
    blue,
    yellow,
    white
};

struct textstatistics {
    float size_of_all_text_in_pixels; // размер всей страницы в пикселях
    int quantily_interval_line; // cуммарный интервал абс
    int max_size_paragraphs; // макс размер параграфа
    float size_page; // размер страницы
    int page_color; // цвет страницы
    int price_per_sheet; // цена за лист
    float price_of_all_text; //цена за все.
    float number_of_sheets; // количество листов
    int number_of_sheets_color; // количество цветных листов
}; struct textstatistics statistics;

struct paragraphs {
    int number_of_lines; // кол-во строк
    int size_lines; // длина строк
    int font_size; // размер ширифта
    int line_spacing; // интервал между строками
    int interval_after_paragraph; // интервал после абзаца
    int paragraph_spacing; // интервал до обзаца
};

void filling_struct(int number_of_paragraphs, struct paragraphs *structura_fil) {
    for(int i = 0, counter = 1; i < number_of_paragraphs; i++, counter++) {
        printf("Введите параграф #%d", counter);
        printf("\nКол-во строк: ");
        scanf("%d", &(structura_fil + i) -> number_of_lines);
        printf("Длина строки: ");
        scanf("%d", &(structura_fil + i) -> size_lines);
        printf("Размер ширифта: ");
        scanf("%d", &(structura_fil + i) -> font_size);
        printf("Интервал между строками: ");
        scanf("%d", &(structura_fil + i) -> line_spacing);
        printf("Интервал после обзаца: ");
        scanf("%d", &(structura_fil + i) -> interval_after_paragraph);
        printf("Интервал до обзаца: ");
        scanf("%d", &(structura_fil + i) -> paragraph_spacing);
    }
}

void data_counting (int number_of_paragraphs, struct paragraphs *structura) {
    int i = 0;
    float pixel = 3.8;
    while (i < number_of_paragraphs) { // размер всего текста в пикселях
        statistics.quantily_interval_line = (structura + i) -> number_of_lines - 1;
        
        statistics.max_size_paragraphs = (structura + i) -> interval_after_paragraph + (structura + i) -> paragraph_spacing;
        
        statistics.size_of_all_text_in_pixels += ((structura + i) -> number_of_lines * (structura + i) -> font_size) + ((structura + i) -> line_spacing * statistics.quantily_interval_line) + (statistics.max_size_paragraphs * pixel);
        i++;
    }
}
// будем делать целочисленно сколько покрасить и после буду высчитовать сколько стоит
void price_page (struct paragraphs *structura) {
    statistics.size_page = 50.0; // размер одного листа
    statistics.price_per_sheet = 10; // цена за один лист
    statistics.number_of_sheets = (statistics.size_of_all_text_in_pixels / statistics.size_page); // кол - во листов
    statistics.number_of_sheets = ceilf(statistics.number_of_sheets);
    printf("-----------------------------------------------------------\n");
    printf("Каким из предложенных цветов, вы будите печатать?\n");
    printf("1.Красный, 2.Зеленый, 3.Голубой, 4.Желтый 5.Ничего.\n");
    scanf("%d", &statistics.page_color);
    if (statistics.page_color < 5) {
        printf("-----------------------------------------------------------\n");
        printf("Страниц в итоге: %.0f\n", ceilf(statistics.number_of_sheets));
        printf("Сколько страниц будут цветными?\n");
        scanf("%d", &statistics.number_of_sheets_color);
        
        switch(statistics.page_color) {
            case (red) :
                statistics.price_of_all_text = ((statistics.number_of_sheets_color * 11.1) + ((ceilf(statistics.number_of_sheets - statistics.number_of_sheets_color) * statistics.price_per_sheet)));
                break;
                
            case (green) :
                
                statistics.price_of_all_text = ((statistics.number_of_sheets_color * 19.9) + ((ceilf(statistics.number_of_sheets - statistics.number_of_sheets_color) * statistics.price_per_sheet)));
                break;
                
            case (blue) :
                statistics.price_of_all_text = ((statistics.number_of_sheets_color * 13.5) + ((ceilf(statistics.number_of_sheets - statistics.number_of_sheets_color) * statistics.price_per_sheet)));
                break;
                
            case (yellow) :
                statistics.price_of_all_text = ((statistics.number_of_sheets_color * 17.7) + ((ceilf(statistics.number_of_sheets - statistics.number_of_sheets_color) * statistics.price_per_sheet)));
                break;
        }
    }
    else statistics.price_of_all_text = statistics.price_per_sheet * statistics.number_of_sheets;
    
}

void print_struct(struct paragraphs *structura) {
    printf("-----------------------------------------------------------");
    printf("\nРазмер всего текста в пикселях: %.3f px", statistics.size_of_all_text_in_pixels);
    printf("\nСтоимость печати: %.1f$", statistics.price_of_all_text);
    printf("\n");
}

int main()
{
    int line = 0;
    struct paragraphs *structura;
    printf("Сколько параграфов вы хотите задать: ");
    scanf("%d", &line);
    if ((structura = (struct paragraphs* ) malloc(line * sizeof(struct paragraphs ))) == 0) return 1;
    filling_struct(line, structura);
    data_counting(line, structura);
    price_page(structura);
    print_struct(structura);
    free(structura);
    printf("-----------------------------------------------------------\n");
    return 0;
}



