//main.cpp

#include "Sputnic.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(0, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА SPUTNIK ===\n" << endl;

    // 1. Создание объекта
    cout << "1. Создание спутника:" << endl;
    Sputnik sputnik("Katarsis", 400, 7.6, 80, 1.5, true);
    sputnik.printInfo();

    // 2. Работа с динамическими данными
    cout << "\n2. Работа с динамическими данными (телеметрия):" << endl;

    // Добавление записей телеметрии
    sputnik.addTelemetryRecord(0.0, 80.0, 25.0);
    sputnik.addTelemetryRecord(1.0, 78.5, 26.0);
    sputnik.addTelemetryRecord(2.0, 77.0, 27.0);
    sputnik.addTelemetryRecord(3.0, 80.0, 28.0);

    // Вывод истории телеметрии
    sputnik.printTelemetryHistory();

    // 3. Демонстрация перегруженных операций
    cout << "\n3. Демонстрация перегруженных операций:" << endl;

    // Оператор +=
    cout << "- Оператор += (добавление энергии):" << endl;
    sputnik += 10.5;
    cout << "Результат: " << sputnik << endl;

    // Оператор []
    cout << "\n- Оператор [] (доступ к телеметрии):" << endl;
    cout << "Запись телеметрии [1]: время=" << sputnik[1].timestamp << "с, заряд=" << sputnik[1].batteryLevel << "%, температура=" << sputnik[1].temperature << endl;



    // Оператор <<
    cout << "\n- Оператор << (вывод в поток):" << endl;
    cout << sputnik << endl;

    // 4. Демонстрация работы основных методов
    cout << "\n4. Работа основных методов:" << endl;

    // Операция спутника
    sputnik.operate(5.0);
    cout << "После работы: " << sputnik << endl;

    // Расчет орбитального периода
    cout << "Орбитальный период: " << sputnik.getOrbitalPeriod() << " секунд" << endl;

    // Получение состояния
    cout << "Состояние спутника: " << (sputnik.getIsOn() ? "включен" : "выключен") << endl;

    // Изменение состояния
    cout << "Выключаем спутник:" << endl;
    sputnik.setPowerState(false);
    cout << "Состояние: " << (sputnik.getIsOn() ? "включен" : "выключен") << endl;

    // Включаем обратно и заряжаем
    cout << "Включаем и заряжаем спутник:" << endl;
    sputnik.setPowerState(true);
    sputnik.recharge(0.8, 5.0);
    cout << "После зарядки: " << sputnik << endl;

    // 5. Демонстрация конструктора копирования и оператора присваивания
    cout << "\n5. Копирование и присваивание:" << endl;

    // Конструктор копирования
    Sputnik sputnikCopy(sputnik);
    cout << "Скопированный спутник: " << sputnikCopy << endl;

    // Оператор присваивания
    Sputnik sputnik3;
    sputnik3 = sputnik;
    cout << "Присвоенный спутник: " << sputnik3 << endl;

    return 0;
}