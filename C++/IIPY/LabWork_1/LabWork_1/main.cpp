//
//  main.cpp
//  LabWork_1
//
//  Created by Belousov Ilya on 5.09.21.
//

#include <stdlib.h>
#include <iostream>

//Задания на лабораторные работы:


//4. Веб-камера Вывести информацию об установленной веб-камере. Осуществить захват изображения (фото и видео) с последующим сохранением в файл. Предусмотреть скрытый вариант видеонаблюдения, когда на мониторе и на панели задач не отображается информация о Вашем работающем приложении.

//5. Global Hooks Установить глобальные хуки на устройства ввода – клавиатуру и мышь. Предусмотреть реализацию перехвата сигналов, поступающих с этих
//устройств, и возможность последующей подмены этих сигналов. Приложение должно работать в скрытом режиме.

//6. USB Реализовать мониторинг USB-портов: - отслеживать появление нового USB-устройства в системе; - события безопасного и небезопасного извлечения устройства; - отказ в безопасном извлечении. Для всех извлекаемых USB-устройств предусмотреть возможность программного безопасного извлечения.
//Приложение должно корректно работать с модифицированными USB- устройствами – например, разбитыми на пару дисков или смонтированными как CD-ROM + Flash.

//1. Конфигурационное пространство PCI Вывести список всех устройств, подключенных к шине PCI, с их характеристиками (DevicedID и VendorID).
void pci_info() {
    
}

//2. HDD Вывести данные о жёстких дисках, подключённых к компьютеру: - модель; - изготовитель; - серийных номер; - версия прошивки (firmware); - сведения о памяти (свободно/занято/всего); - тип интерфейса; - список поддерживаемых режимов.
void hard_disk_information() {
    system("diskutil list /dev/disk0");
    system("diskutil info /dev/disk1s7s1");
}

//3. Энергопитание Вывести информацию об энергопитании компьютера: - в режиме реального времени показывать тип энергопитания; - уровень заряда батареи (если она присутствует); - текущий режим энергосбережения.
void battery_info() {
    system("system_profiler SPPowerDataType | grep -A3 -B7 \"Condition\" ");
}

int main() {
    
////    pci_info();
//    hard_disk_information();
//    battery_info();
//
//    FILE *f = fopen("/dev/mem", "r");
    
}
