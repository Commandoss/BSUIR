#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>

// Лабораторная работа 3. Вариант 3
//1. Дан текстовый файл F1 и последовательность символов. В новый файл F2 записать данные из файла F1, исключая данную последовательность. Дополнительных коллекций не использовать.

//int main() {
//    FILE *f1;
//    FILE *f2;
//
//    if ((f1 = fopen("text1.txt","rt")) == NULL) {
//        printf("Ошибка открытия файла.");
//        return 1;
//    }
//
//    if ((f2 = fopen("text2.txt","wt+")) == NULL) {
//        printf("Ошибка открытия файла.");
//        return 1;
//    }
//
//    printf("Какую строку символов вы хотите удалить?\n");
//    printf("Введите строку (для окончания ввода нажмите <enter>):\n");
//
//
//    char ch = '\0', ck = '\0';
//    rewind(stdin);
//    char str[256];
//    int r = 0;
//    fgets(str, 256, stdin);
//    while (!feof(f1)) {
//        ch = fgetc(f1);
//        if (ck != EOF) {
//            ck = fgetc(f1);
//            fseek(f1, -1, SEEK_CUR);
//            if ((ck == str[r+1] || str[r+1] == '\n') && ch == str[r]) {
//                r++;
//                if (ck == ' ')
//                    fseek(f1, 1, SEEK_CUR);
//                continue;
//            }
//        }
//        if (ck != EOF)  {
//            r = 0;
//        fprintf(f2, "%c", ch);
//        }
//    }
//    fclose(f1);
//    fclose(f2);
//    printf("-----------------------------------------------------------\n");
//    printf("Данные из файла 1 были перенесены в файл 2. Была исключена заданная последовательность\n");
//    printf("-----------------------------------------------------------\n");
//
//
//    if ((f2 = fopen("text2.txt", "r")) == NULL) {
//        printf("Ошибка открытия файла.\n"); return 1;
//    }
//
//    printf("Содержимое файла 2: \n");
//    printf("-----------------------------------------------------------\n");
//    fflush(f2);
//
//    while (!feof(f2)) {
//        fscanf(f2, "%c", &ch);
//        printf("%c", ch);
//    }
//
//    fclose(f2);
//    printf("\n\n");
//    return 0;
//}

//2. Дан текстовый файл F1. В файле записана матрица целочисленных элементов. По запросу с клавиатуры удалить столбец или строку с минимальной суммой элементов. Дополнительных коллекций и файлов не использовать.

//#include <time.h>
//#include <limits.h>
//#include <curses.h>
//#include <unistd.h>
//
//int main () {
//    FILE *file;
//
//    int answer = 0, chek = 0, delete = 0;
//    printf("Создать марицу в файле?\n");
//    printf("1. Yes      2. No\nAnswer: ");
//    scanf("%d", &answer);
//    int size_i = 0, size_j, range_number;
//    switch (answer) {
//        case 1 :
//
//            if ((file = fopen("matrix.txt", "wt+")) == NULL) {
//                printf("Не удалось создать файл.");
//                return 1;
//            }
//
//            long ltime = time (NULL);
//            int stime = (unsigned int) ltime/2;
//            srand(stime);
//            printf("Задавйте размер матрицы [] []: ");
//            scanf("%d %d", &size_i, &size_j);
//            printf("Задайте диапозон чисел: ");
//            scanf("%d", &range_number);
//            for (int i = 0; i < size_i; i++) {
//                int num = 0;
//                for (int j = 0; j < size_j; j++) {
//                    num = rand() % range_number;
//                    fprintf(file, "%d ", num);
//                }
//                fseek(file, -1, SEEK_CUR);
//                fprintf(file, "\n");
//            }
//            fclose(file);
//            break;
//    }
//
//    printf("-----------------------------------------------------------\n");
//
//    if ((file = fopen("matrix.txt", "rt")) == NULL) {
//        printf("Неудалосб прочитать файл");
//        return 1;
//    }
//    fseek(file, 0, SEEK_SET);
//    int number = 0, sym = 0, line_i = 0, min_sym = INT_MAX;
//
//    while (!feof(file)) {
//        char symbol = getc(file);
//        if (((symbol != ' ') && (symbol != '\n'))) {
//            number = (number * 10) + atoi(&symbol);
//        }
//
//        if (symbol == ' ' || symbol == '\n') {
//            sym += number;
//            number = 0;
//        }
//
//        if (symbol == '\n' && symbol != EOF) {
//            if (sym < min_sym) {
//                min_sym = sym;
//                delete = line_i;
//                chek = 1;
//
//            }
//            printf("Сумма строки [%d] = %d\n", line_i, sym);
//            sym = 0; number = 0; line_i++;
//
//        }
//    }
//    printf("-----------------------------------------------------------\n");
//    fseek(file, 0, SEEK_SET);
//
//    int colom = 0, flag = 0, counter = 0, per = 0, quantity_colom = 0;
//    sym = 0;
//    number = 0;
//
//    while (!feof(file)) {
//        char symbol = getc(file);
//        if (per == counter) {
//            if (flag == 0){
//                if (isdigit(symbol)) {
//                    number = (10 * number) + atoi(&symbol);
//                }
//
//                else {
//                    sym += number;
//                    flag++;
//                    number = 0;
//                }
//            }
//        }
//
//        if (symbol == ' ') {
//            per++;
//        }
//
//        if (symbol == '\n' && symbol != EOF) {
//            flag = 0;
//            quantity_colom = per + 1;
//            per = 0;
//        }
//        if (symbol == EOF) {
//            if (sym < min_sym) {
//                min_sym = sym;
//                delete = counter;
//                chek = 2;
//            }
//
//            printf("Сумма столбца [%d] = %d\n", colom, sym);
//            fseek(file, 0, SEEK_SET);
//            sym = 0; colom++; number = 0; flag = 0; counter++; per = 0;
//            if (colom == quantity_colom) break;
//        }
//
//    }
//
//    fclose(file);
//    answer = 0;
//    printf("-----------------------------------------------------------\n");
//    printf("Минимальная сумма = %d\n", min_sym);
//    printf("-----------------------------------------------------------\n");
//    printf("Хотите удалить стоку/столбец с минимальной суммой?\n");
//    printf("1. Yes       2. No\nОтвет: ");
//    scanf("%d", &answer);
//
//    per = 0; flag = 0; counter = 0;
//    if (answer == 1) {
//
//        if ((file = fopen("matrix.txt", "r+t")) == NULL) {
//            printf("Неудалось открыть файл.");
//            return 1;
//        }
//
//        fpos_t pos_del = 0, pos_cop = 0, pos_save = 0, pos_und = 0;
//        int exit = 0;
//        char symbol = '\0';
//        switch (chek) {
//
//            case 1 :
//                while (symbol != EOF) {
//                    symbol = getc(file);
//                    if (symbol == '\n') {
//                        if (per > delete)
//                            pos_del++;
//                        per++;
//
//                        if (delete == 0 && flag == 0) {
//
//                            fgetpos(file, &pos_cop);
//                            fseek(file, 0, SEEK_SET);
//                            fgetpos(file, &pos_del);
//                            fsetpos(file, &pos_cop);
//                            flag++;
//                        }
//
//                        else if (per == delete && flag == 0) {
//                            fgetpos(file, &pos_del);
//                            fgetpos(file, &pos_cop);
//                            flag++;
//                        }
//
//
//                        continue;
//                    }
//
//                    if (per == line_i + 1 || symbol == EOF) {
//                        off_t end = pos_del;
//                        truncate("matrix.txt", end);
//                        break;
//                    }
//
//                    if (per > delete) {
//                        fgetpos(file, &pos_cop);
//                        fsetpos(file, &pos_del);
//                        fputc(symbol, file);
//                        fgetpos(file, &pos_del);
//                        fsetpos(file, &pos_cop);
//
//                    }
//
//                }
//                break;
//
//            case 2 :
//                while (TRUE) {
//                    symbol = getc(file);
//                    if (counter == 0) {
//                        if (symbol == ' ' || symbol == '\n') {
//                            per++;
//                        }
//                        if (symbol == ' ') {
//                            fseek(file, -1, SEEK_CUR);
//                            fgetpos(file, &pos_und);
//                            fseek(file, 1, SEEK_CUR);
//                        }
//
//                        if (symbol != ' ') {
//
//
//                            if (per == delete) {
//                                fseek(file, -1, SEEK_CUR);
//                                fgetpos(file, &pos_del);
//                                fseek(file, 1, SEEK_CUR);
//                                continue;
//                            }
//
//                            if (per > delete && symbol == '\n') {
//                                pos_del = pos_und;
//                            }
//
//                            if (per > delete || symbol == '\n'){
//                                fseek(file, -1, SEEK_CUR);
//                                fgetpos(file, &pos_cop);
//                                pos_save = pos_cop;
//                                fsetpos(file, &pos_del);
//                                fputc(symbol, file);
//                                pos_del = pos_cop;
//                                fsetpos(file, &pos_cop);
//                                fseek(file, 1, SEEK_CUR);
//                            }
//
//                            if (per > delete && symbol == '\n') {
//                                pos_del = pos_und + 1;
//                            }
//
//                        }
//                    }
//
//                    if (counter > 0) {
//                        fseek(file, -1, SEEK_CUR);
//                        fgetpos(file, &pos_cop);
//                        fsetpos(file, &pos_del);
//                        fputc(symbol, file);
//                        fgetpos(file, &pos_del);
//                        fsetpos(file, &pos_cop);
//                        fseek(file, 1, SEEK_CUR);
//
//                    }
//
//                    if (symbol == '\n' || symbol == EOF) {
//                        per = 0; counter++; flag++;
//                    }
//
//                    if (counter != 0) {
//                        if (flag == colom || symbol == EOF) {
//                            fseek(file, -1, SEEK_CUR);
//                            if (exit == delete) pos_del--;
//                            off_t end = pos_del;
//                            truncate("matrix.txt", end);
//                            fsetpos(file, &pos_save);
//                            counter = 0; exit++; flag = 0;
//                            colom--;
//                            if (colom == 0) {
//                                break;
//                            }
//                        }
//                    }
//                }
//
//            default:
//                break;
//        }
//    }
//    fclose(file);
//    printf("\n");
//
//    return 0;
//}


//1. Дан текстовый файл F1. Ввести с клавиатуры число N. Определить сколько в файле имеется слов, состоящих из N символов, и записать это число в новый файл F2.

#define Error_open -100;
int main () {
    FILE *file, *new_file;
    
    int Answer = 0, counter = 0, coun_ch = 0;
    if ((file = fopen("text.txt", "wt+")) == NULL) {
        printf("Error cannot open file.\n");
        return Error_open;
    }
    
    char text[912] = "Yesterday I visited my Granny in the countryside. We go there every weekend and I enjoy these trips. But not this time. It was raining cats and dogs, our car broke several times and we all were very tired. But when we saw the Granny, I forgot about the difficulties.";
    
    fwrite(text, sizeof(char), 912, file);
    fclose(file);
    
    if ((file = fopen("text.txt", "rt")) == NULL) {
        printf("Error cannot open file.\n");
        return Error_open;
    }
    
    printf("set n: ");
    scanf("%d", &Answer);
    
    char symbol = '\0';
    while (!feof(file)) {
        symbol = fgetc(file);
        if (symbol == ' ') {
            if (Answer == counter) coun_ch++;
            counter = 0;
        }
        else counter++;
    }
    
    if ((new_file = fopen("nub_sym.txt", "w+t")) == NULL) {
        printf("Error cannot open file.\n");
        return Error_open;
    }
    fprintf(new_file, "%d", coun_ch);
    symbol = '\0';
    fseek(new_file, 0, SEEK_SET);
    fscanf(new_file, "%s", &symbol);
    printf("Words given length: %c\n", symbol);
    fclose(file); fclose(new_file);
}

//2. Даны текстовый файл и символьная строка s. Удалить из файла все строки, кроме тех, которые содержат в качестве фрагмента строку s. Дополнительных файлов и коллекций не использовать.
