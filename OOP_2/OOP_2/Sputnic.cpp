//sputnic.cpp
#include "Sputnic.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Конструктор по умолчанию
Sputnik::Sputnik()
    : name("Unnamed"), orbit(0), speed(0), batteryCharge(0),
    energyDemandInSeconds(0), isOn(false),
    telemetryHistory(nullptr), telemetryCapacity(0), telemetryCount(0) {

    telemetryCapacity = 2;
    telemetryHistory = new RecordTelemetry[telemetryCapacity];
}

// Параметризованный конструктор
Sputnik::Sputnik(std::string n, double o, double s, double bat, double energy, bool on)
    : name(n), orbit(o), speed(s), batteryCharge(bat),
    energyDemandInSeconds(energy), isOn(on),
    telemetryHistory(nullptr), telemetryCapacity(0), telemetryCount(0) {

    telemetryCapacity = 2;
    telemetryHistory = new RecordTelemetry[telemetryCapacity];
}

// Конструктор копирования
Sputnik::Sputnik(const Sputnik& other)
    : name(other.name), orbit(other.orbit), speed(other.speed),
    batteryCharge(other.batteryCharge), energyDemandInSeconds(other.energyDemandInSeconds),
    isOn(other.isOn), telemetryCapacity(other.telemetryCapacity),
    telemetryCount(other.telemetryCount) {

    // Глубокое копирование динамического массива
    telemetryHistory = new RecordTelemetry[telemetryCapacity];
    for (int i = 0; i < telemetryCount; i++) {
        telemetryHistory[i] = other.telemetryHistory[i];
    }
}

// Оператор присваивания
Sputnik& Sputnik::operator=(const Sputnik& other) {
    if (this != &other) {
        delete[] telemetryHistory;

        name = other.name;
        orbit = other.orbit;
        speed = other.speed;
        batteryCharge = other.batteryCharge;
        energyDemandInSeconds = other.energyDemandInSeconds;
        isOn = other.isOn;
        telemetryCapacity = other.telemetryCapacity;
        telemetryCount = other.telemetryCount;


        telemetryHistory = new RecordTelemetry[telemetryCapacity];
        for (int i = 0; i < telemetryCount; i++) {
            telemetryHistory[i] = other.telemetryHistory[i];
        }
    }
    return *this;
}

// Деструктор
Sputnik::~Sputnik() {
    delete[] telemetryHistory;
}


void Sputnik::setPowerState(bool state) {                   //мой основной метод из задания - Установка состояния питания
    if (state && batteryCharge <= 0) {
        cout << "Нельзя включить спутник " << name << " - батарея разряжена!" << endl;
        return;
    }
    isOn = state;
}


void Sputnik::operate(double seconds) {    //мой основной метод из задания - Операция спутника в течение заданного времени 
    if (!isOn) {
        cout << "Спутник " << name << " выключен и не потребляет энергию" << endl;
        return;
    }

    double energyConsumed = energyDemandInSeconds * seconds;
    double newEnergy = batteryCharge - energyConsumed;

    if (newEnergy <= 0) {
        batteryCharge = 0;
        setPowerState(false);
        cout << "Спутник " << name << " выключен из-за недостатка энергии" << endl;
    }
    else {
        batteryCharge = newEnergy;
        cout << "Спутник " << name << " проработал " << seconds << " секунд. Остаток энергии: " << newEnergy << "%" << endl;
    }
}


double Sputnik::getOrbitalPeriod() const {    // мой основной метод из задания - Расчет орбитального периода
    const double earthRadius = 6371.0;
    double totalRadius = orbit + earthRadius;
    double circumference = 2 * 3.1415926535 * totalRadius;
    return circumference / speed;
}


void Sputnik::recharge(double efficiency, double sunlightSeconds) {    // мой основной метод из задания - зарядка от солнечных панелей
    if (!isOn) {
        cout << "Спутник " << name << " выключен - зарядка невозможна" << endl;
        return;
    }

    double chargeAmount = energyDemandInSeconds * efficiency * sunlightSeconds;
    batteryCharge += chargeAmount;

    if (batteryCharge > 100) {
        batteryCharge = 100;
    }

    cout << "Спутник " << name << " заряжен до " << fixed << setprecision(2) << batteryCharge << "%" << endl;
}











// Расширение массива телеметрии
void Sputnik::expandTelemetryArray() {
    if (telemetryCount >= telemetryCapacity) {
        int newCapacity = telemetryCapacity * 2;

        RecordTelemetry* newArray = new RecordTelemetry[newCapacity];

        for (int i = 0; i < telemetryCount; i++) {
            newArray[i] = telemetryHistory[i];
        }

        delete[] telemetryHistory;
        telemetryHistory = newArray;
        telemetryCapacity = newCapacity;
    }
}

// Добавление записи телеметрии
void Sputnik::addTelemetryRecord(double timestamp, double battery, double temp) {
    expandTelemetryArray();

    RecordTelemetry newRecord(timestamp, battery, temp);
    telemetryHistory[telemetryCount] = newRecord;
    telemetryCount++;
}

// Вывод информации о спутнике
void Sputnik::printInfo() const {
    cout << "\n=== Информация о спутнике ===" << endl;
    cout << "Название: " << name << endl;
    cout << "Высота орбиты: " << orbit << " км" << endl;
    cout << "Скорость: " << speed << " км/с" << endl;
    cout << "Заряд батареи: " << batteryCharge << "%" << endl;
    cout << "Потребление энергии: " << energyDemandInSeconds << " %/с" << endl;
    cout << "Состояние: " << (isOn ? "Включен" : "Выключен") << endl;
    cout << "Записей телеметрии: " << telemetryCount << endl;
}

// Вывод истории телеметрии
void Sputnik::printTelemetryHistory() const {
    if (telemetryCount == 0) {
        cout << "История телеметрии пуста" << endl;
        return;
    }

    cout << "\n=== История телеметрии ===" << endl;
    cout << setw(12) << "Время (с)"
        << setw(15) << "Заряд (%)"
        << setw(15) << "Температура (°C)" << endl;
    cout << string(42, '-') << endl;

    for (int i = 0; i < telemetryCount; i++) {
        cout << setw(12) << fixed << setprecision(1) << telemetryHistory[i].timestamp
            << setw(15) << fixed << setprecision(2) << telemetryHistory[i].batteryLevel
            << setw(15) << fixed << setprecision(2) << telemetryHistory[i].temperature << endl;
    }
}

// Получение записи телеметрии
Sputnik::RecordTelemetry Sputnik::getTelemetryRecord(int index) const {
    if (index < 0 || index >= telemetryCount) {
        return RecordTelemetry();
    }
    return telemetryHistory[index];
}

// Перегруженные операторы

// Оператор += для добавления энергии
Sputnik& Sputnik::operator+=(double additionalEnergy) {
    batteryCharge += additionalEnergy;
    if (batteryCharge > 100) batteryCharge = 100;
    return *this;
}

/*
Sputnik::RecordTelemetry& Sputnik::operator[](int index) {
    if (index < 0) index = 0;
    if (index >= telemetryCount) index = telemetryCount - 1;

    return telemetryHistory[index];
}

const Sputnik::RecordTelemetry& Sputnik::operator[](int index) const {
    if (index < 0 || index >= telemetryCount) {
        static RecordTelemetry dummy;
        return dummy;
    }
    return telemetryHistory[index];
}*/

Sputnik::RecordTelemetry Sputnik::operator[](int index) const {
    if (index < 0 || index >= telemetryCount) {
        return RecordTelemetry();  // Возвращаем копию пустой структуры
    }
    return telemetryHistory[index];  // Возвращаем копию
}

// Оператор вывода
ostream& operator<<(ostream& os, const Sputnik& sputnik) {
    os << "Спутник \"" << sputnik.name << "\": ";
    os << "орбита="  << sputnik.orbit << " км, ";
    os << "скорость="  << sputnik.speed << " км/с, ";
    os << "заряд=" << sputnik.batteryCharge << "%, ";
    os << "состояние=" << (sputnik.isOn ? "вкл" : "выкл");
    return os;
}