//main.cpp   

#include "Sputnic.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(0, "Russian");

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА SPUTNIK ===\n" << endl;

    // 1. Создание объекта
    cout << "1. Создание спутника:" << endl;
    Sputnik sputnik("Katarsis-1", 400, 7.6, 80, 1.5, true);
    sputnik.printInfo();

    // 2. Работа с динамическими данными
    cout << "\n2. Работа с динамическими данными (телеметрия):" << endl;

    // Добавление записей телеметрии
    sputnik.addTelemetryRecord(0.0, 80.0, 25.0);
    sputnik.addTelemetryRecord(1.0, 78.5, 26.0);
    sputnik.addTelemetryRecord(2.0, 77.0, 27.0);

    // Автоматическая запись состояния
    sputnik.recordCurrentState();
    sputnik.recordCurrentState();

    // Вывод истории телеметрии
    sputnik.printTelemetryHistory();

    // 3. Демонстрация перегруженных операций
    cout << "\n3. Демонстрация перегруженных операций:" << endl;

    // Оператор +=
    cout << "- Оператор += (добавление энергии):" << endl;
    sputnik += 10.5;
    cout << "Текущий спутник: " << sputnik << endl;

    // Оператор +
    cout << "\n- Оператор + (создание нового спутника с большей энергией):" << endl;
    Sputnik sputnik2 = sputnik + 5.0;
    cout << "Новый спутник: " << sputnik2 << endl;

    // Оператор []
    cout << "\n- Оператор [] (доступ к телеметрии):" << endl;
    cout << "Запись телеметрии [0]: время=" << sputnik[0].timestamp
        << "с, заряд=" << sputnik[0].batteryLevel
        << "%, температура=" << sputnik[0].temperature << "°C" << endl;

    // Оператор <<
    cout << "\n- Оператор << (вывод в поток):" << endl;
    cout << sputnik << endl;

    // 4. Демонстрация работы основных методов
    cout << "\n4. Работа основных методов:" << endl;

    // Операция спутника
    sputnik.operate(10.0);
    cout << "После работы: " << sputnik << endl;

    // Зарядка
    sputnik.recharge(0.8, 5.0);
    cout << "После зарядки: " << sputnik << endl;

    // Расчет орбитального периода
    cout << "\nОрбитальный период: " << sputnik.getOrbitalPeriod() << " секунд" << endl;

    // Средняя температура
    cout << "Средняя температура по телеметрии: "
        << sputnik.getAverageTemperature() << "°C" << endl;

    // 5. Демонстрация конструктора копирования и оператора присваивания
    cout << "\n5. Копирование и присваивание:" << endl;

    // Конструктор копирования
    Sputnik sputnikCopy(sputnik);
    cout << "Скопированный спутник: " << sputnikCopy << endl;

    // Оператор присваивания
    Sputnik sputnik3;
    sputnik3 = sputnik;
    cout << "Присвоенный спутник: " << sputnik3 << endl;

    // 6. Проверка изменения динамического массива
    cout << "\n6. Изменение динамического массива:" << endl;

    // Добавим больше записей для демонстрации расширения массива
    for (int i = 0; i < 10; i++) {
        sputnik.recordCurrentState();
    }

    cout << "Количество записей телеметрии: " << sputnik.getTelemetryCount() << endl;
    sputnik.printTelemetryHistory();

    cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << endl;

    return 0;
}