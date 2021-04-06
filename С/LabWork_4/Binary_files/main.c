#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <curses.h>

// Лабораторная работа 4. Вариант 8
//1. В бинарном файле записаны целочисленные значения. Сделать циклический сдвиг элементов, записанных в файле, на один элемент вправо. Вывести результат на экран. Дополнительных коллекций и файлов не использовать. Пример. Изначально файл содержит числа 1, 2, 3, 4, 5, 6. В результате файл содержит числа 6, 1, 2, 3, 4, 5.

int main () {
    FILE *file;
    
    if ((file = fopen("Cyclic shift.data", "wb+")) == NULL) {
        printf("Error cannot open file.");
        return 1;
    }

    int SIZE = 0, input = 0;
    printf("How long will the sequence be?\nAnswer: ");
    scanf("%d", &SIZE);
    if (SIZE == 0) return 0;
    else {
//        long ltime = time (NULL);
//        int stime = (unsigned int) ltime/2;
//        srand(stime);
        for (int i = 0; i < SIZE; i++) {
//            input = rand () % 9;
            input = 1 + i;
            fwrite(&input, sizeof(int), 1, file);
        }
    }
    fclose(file);

    int shift = 0;
    printf("--------------------------------------------------------\n");
    printf("How many elements will there be a shift?\nAnswer: ");
    scanf("%d", &shift);
    if (shift == 0) return 0;

    if ((file = fopen("Cyclic shift.data", "r+b")) == NULL) {
        printf("Error cannot open file.");
        return 1;
    }

    int Answer = 1, counter = 1, number_first = 0, number_second = 0;

    while (Answer == 1) {
        if (counter == 1) {
            fread(&number_first, sizeof(int), 1, file);
        }

        else {
            number_first = number_second;
        }

        fread(&number_second, sizeof(int), 1, file);
        fseek(file, -sizeof(int), SEEK_CUR);
        fwrite(&number_first, sizeof(int), 1, file);
        counter++;

        if (counter == SIZE) {
            fseek(file, 0, SEEK_SET);
            fread(&number_first, sizeof(int), 1, file);
            fseek(file, -sizeof(int), SEEK_CUR);
            fwrite(&number_second, sizeof(int), 1, file);
            shift--;
            if (shift != 0) {
                counter = 1;
                fseek(file, 0, SEEK_SET);
                continue;
            }

            else {
//
                printf("--------------------------------------------------------\n");
                printf("Want to continue?\n1)Yes   2)No\nAnswer: ");
                scanf("%d", &Answer);
                printf("--------------------------------------------------------\n");
                if (Answer == 1) {
                    printf("How many elements will there be a shift?\nAnswer: ");
                    scanf("%d", &shift);
                    counter = 1;
                    fseek(file, 0, SEEK_SET);
                    continue;
                }
            }
        }
    }

    int buffer;
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < SIZE; i++) {
        fread(&buffer, sizeof(int), 1, file);
        printf("%d ", buffer);
        
    }
    printf("\n");
    fclose(file);
    return 0;
}

// короче можно добавить pointer который будет следить за тем какое это большое число и перемещать,
// так же может возникнуть проблема с их внесением,
// так что можно будет делать чтоб он перезаписывал файл.

//2. В бинарном файле F1 записана одна структура, в которой хранится состояние системы: флаг успешности последнего запуска, язык, дата последнего запуска, кол-во свободного места на диске, объем диска, версия системы, дата обновления. Вывести размер файла и все данные, находящиеся в нем. Задать максимальный размер файла.
//После этого разбить файл F1 на несколько файлов так, чтобы размер каждого файла не превышал максимальный. По запросу с клавиатуры отменить ограничения по максимальному размеру, объединить созданные файлы в исходный, удалить созданные файлы.

//struct state {
//    char Flag_run[255];
//    char language[50];
//    char last_run[255];
//    char disk_capacity[255];
//    char quantity_memory[255];
//    char system_version[250];
//    char day_update[255];
//};
//
//int file_creation () {
//    FILE *main_file;
//
//    struct state st;
//    int capacity = 256000, quantity = 133698;
//    long int ttime = time(NULL);
//    if ((main_file = fopen("main_file.data", "wb+")) == NULL) {
//        printf("Error cannot open file");
//
//        return 1;
//    }
//    else {
//        strcpy(st.Flag_run, "Successful launch flag: YES.\n");
//    }
//
//    strcpy(st.language, "Language: English.\n");
//    strcpy(st.last_run, "Last run: ");
//    strncat(st.last_run, ctime(&ttime), sizeof(st.last_run));
//    sprintf(st.disk_capacity, "Disk capacity: %d\n", quantity);
//    sprintf(st.quantity_memory, "Quantity memory: %d\n", capacity);
//    strcpy(st.system_version, "System version: Windows 10 Pro\n");
//    strcpy(st.day_update, "Last update date: Fri Apr 11 13:52:40 2019\n");
//    fwrite(st.Flag_run, sizeof(char), strlen(st.Flag_run), main_file);
//    fwrite(st.language, sizeof(char), strlen(st.language), main_file);
//    fwrite(st.last_run, sizeof(char), strlen(st.last_run), main_file);
//    fwrite(&st.disk_capacity, sizeof(char), strlen(st.disk_capacity), main_file);
//    fwrite(&st.quantity_memory, sizeof(char), strlen(st.quantity_memory), main_file);
//    fwrite(st.system_version, sizeof(char), strlen(st.system_version), main_file);
//    fwrite(st.day_update, sizeof(char), strlen(st.day_update), main_file);
//
//    fclose(main_file);
//    return 0;
//}
//
//int additional_file_creation (int size_all_file, long Smain_file) {
//    FILE *fi;
//
//    FILE *main_file;
//    if ((main_file = fopen("main_file.data", "rb")) == 0){
//        printf("Error cannot open file.");
//        return 1;
//    }
//
//    char name[] = "file_1.data";
//    char *buffer;
//    buffer = (char*) malloc(sizeof(char));
//
//    int size = 1, size_for_read = size_all_file;
//    long Smain = Smain_file;
//    for (int i = 1; i <= size; i++) {
//        name[5] = i + '0'; //???
//        if ((fi = fopen(name, "wb+")) == 0){
//            printf("Error cannot open file.");
//            return 1;
//        }
//
//        if (Smain < size_for_read && Smain > 0)
//            size_for_read = (int) Smain;
//        fread(buffer, sizeof(char), size_for_read, main_file);
//        fwrite(buffer, sizeof(char), size_for_read, fi);
//        Smain -= size_all_file;
//        fclose(fi);
//
//        if (!feof(main_file) && Smain > 0) {
//            size++;
//        }
//        else if (Smain < 0) {
//            break;
//        }
//    }
//    remove("main_file.data");
//
//    int Answer = 0;
//    puts("--------------------------------------------------------");
//    printf("Cancel restriction?\n1) Yes.      2) No.\nAnswer: ");
//    scanf("%d", &Answer);
//    puts("--------------------------------------------------------");
//
//    if ((main_file = fopen("main_file.data", "wb+")) == 0){
//         printf("Error cannot open file.");
//         return 1;
//    }
//
//    Smain = Smain_file;
//    size_for_read = size_all_file;
//    for (int i = 1; i <= size; i++) {
//        name[5] = i + '0';
//        if ((fi = fopen(name, "rb")) == 0){
//            printf("Error cannot open file.");
//            return 1;
//        }
//        long check = ftell(main_file);
//        if (Answer == 1 || check < size_for_read) {
//            if (Smain < size_for_read && Smain > 0)
//                size_for_read = (int) Smain;
//            fread(buffer, sizeof(char), size_for_read, fi);
//            fwrite(buffer, sizeof(char), size_for_read, main_file);
//            Smain -= size_all_file;
//        }
//        remove(name);
//    }
//    free(buffer);
//    buffer = (char*) malloc(sizeof(char));
//    printf("File contents: \n\n");
//    fseek(main_file, 0, SEEK_SET);
//    fread(buffer, 1, Smain_file, main_file);
//    puts(buffer);
//    fclose(main_file);
//    free(buffer);
//    return 0;
//}
//
//int main () {
//    file_creation();
//    FILE *main_file;
//
//    if ((main_file = fopen("main_file.data", "rb+")) == NULL) {
//        printf("Error cannot open file.");
//        return 1;
//    }
//    fseek(main_file, 0, SEEK_END);
//    long Smain_file = ftell(main_file);
//    puts("--------------------------------------------------------");
//    printf("Header file size: %ld bytes.\n", Smain_file);
//    fseek(main_file, 0, SEEK_SET);
//
//    char buffer[Smain_file];
//    puts("--------------------------------------------------------");
//    puts("File contents:\n");
//    fread(buffer, sizeof(char), Smain_file, main_file);
//    puts(buffer);
//    fclose(main_file);
//
//    puts("--------------------------------------------------------");
//    int Sadditional_f = 0;
//    printf("Maximum size of additional files: ");
//    scanf("%d", &Sadditional_f);
//    additional_file_creation(Sadditional_f, Smain_file);
//    return 0;
//}
