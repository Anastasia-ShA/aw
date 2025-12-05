// Sputnic.cpp    - реализация методов класса

#include "Sputnic.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Конструктор по умолчанию
Sputnik::Sputnik()
    : name("Unnamed"), orbit(0), speed(0), batteryCharge(0),
    energyDemandInSeconds(0), isOn(false),
    telemetryHistory(nullptr), telemetryCapacity(0), telemetryCount(0), lastTelemetryTime(0) {
    telemetryCapacity = 5;
    telemetryHistory = new RecordTelemetry[telemetryCapacity];
    cout << "Создан спутник по умолчанию" << endl;
}

// Параметризованный конструктор
Sputnik::Sputnik(std::string n, double o, double s, double bat, double energy, bool on)
    : name(n), orbit(o), speed(s), batteryCharge(bat),
    energyDemandInSeconds(energy), isOn(on),
    telemetryHistory(nullptr), telemetryCapacity(0), telemetryCount(0), lastTelemetryTime(0) {
    telemetryCapacity = 5;
    telemetryHistory = new RecordTelemetry[telemetryCapacity];

    // Записываем начальное состояние
    addTelemetryRecord(0.0, batteryCharge, 20.0);
    cout << "Создан спутник: " << name << endl;
}

// Конструктор копирования
Sputnik::Sputnik(const Sputnik& other)
    : name(other.name), orbit(other.orbit), speed(other.speed),
    batteryCharge(other.batteryCharge), energyDemandInSeconds(other.energyDemandInSeconds),
    isOn(other.isOn), telemetryCapacity(other.telemetryCapacity),
    telemetryCount(other.telemetryCount), lastTelemetryTime(other.lastTelemetryTime) {

    // Глубокое копирование динамического массива
    telemetryHistory = new RecordTelemetry[telemetryCapacity];
    for (int i = 0; i < telemetryCount; i++) {
        telemetryHistory[i] = other.telemetryHistory[i];
    }

    cout << "Вызван конструктор копирования для спутника: " << name << endl;
}

// Оператор присваивания
Sputnik& Sputnik::operator=(const Sputnik& other) {
    if (this != &other) {  // Защита от самоприсваивания
        // Освобождаем старую память
        delete[] telemetryHistory;

        // Копируем обычные поля
        name = other.name;
        orbit = other.orbit;
        speed = other.speed;
        batteryCharge = other.batteryCharge;
        energyDemandInSeconds = other.energyDemandInSeconds;
        isOn = other.isOn;
        telemetryCapacity = other.telemetryCapacity;
        telemetryCount = other.telemetryCount;

        // Копируем динамические данные
        telemetryHistory = new RecordTelemetry[telemetryCapacity];
        for (int i = 0; i < telemetryCount; i++) {
            telemetryHistory[i] = other.telemetryHistory[i];
        }

        cout << "Вызван оператор присваивания для спутника: " << name << endl;
    }
    return *this;
}

// Деструктор
Sputnik::~Sputnik() {
    delete[] telemetryHistory;
    cout << "Спутник " << name << " уничтожен" << endl;
}

// Установка состояния питания
void Sputnik::setPowerState(bool state) {
    if (state && batteryCharge <= 0) {
        cout << "Нельзя включить спутник " << name << " - батарея разряжена!" << endl;
        return;
    }
    isOn = state;

    if (state) {
        cout << "Спутник " << name << " включен" << endl;
    }
    else {
        cout << "Спутник " << name << " выключен" << endl;
    }

    // Записываем изменение состояния
    recordCurrentState();
}

// Операция спутника в течение заданного времени
void Sputnik::operate(double seconds) {
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
        cout << "Спутник " << name << " проработал " << seconds
            << " секунд. Остаток энергии: " << fixed << setprecision(2)
            << newEnergy << "%" << endl;
    }

    // Записываем состояние после работы
    recordCurrentState();
}

// Расчет орбитального периода
double Sputnik::getOrbitalPeriod() const {
    const double earthRadius = 6371.0;  // Радиус Земли в км
    double totalRadius = orbit + earthRadius;
    double circumference = 2 * 3.1415926535 * totalRadius;  // Длина орбиты
    return circumference / speed;  // Период в секундах
}

// Зарядка от солнечных панелей
void Sputnik::recharge(double efficiency, double sunlightSeconds) {
    if (!isOn) {
        cout << "Спутник " << name << " выключен - зарядка невозможна" << endl;
        return;
    }

    double chargeAmount = energyDemandInSeconds * efficiency * sunlightSeconds;
    batteryCharge += chargeAmount;

    if (batteryCharge > 100) {
        batteryCharge = 100;
    }

    cout << "Спутник " << name << " заряжен до " << fixed << setprecision(2)
        << batteryCharge << "%" << endl;

    // Записываем состояние после зарядки
    recordCurrentState();
}

// Расширение массива телеметрии
void Sputnik::expandTelemetryArray() {
    if (telemetryCount >= telemetryCapacity) {
        int newCapacity = telemetryCapacity * 2;
        if (newCapacity == 0) newCapacity = 1;

        RecordTelemetry* newArray = new RecordTelemetry[newCapacity];

        for (int i = 0; i < telemetryCount; i++) {
            newArray[i] = telemetryHistory[i];
        }

        delete[] telemetryHistory;
        telemetryHistory = newArray;
        telemetryCapacity = newCapacity;

        cout << "Массив телеметрии спутника " << name
            << " расширен до " << newCapacity << " элементов" << endl;
    }
}

// Добавление записи телеметрии
void Sputnik::addTelemetryRecord(double timestamp, double battery, double temp) {
    expandTelemetryArray();

    RecordTelemetry newRecord(timestamp, battery, temp);
    telemetryHistory[telemetryCount] = newRecord;
    telemetryCount++;

    cout << "Добавлена запись телеметрии #" << telemetryCount
        << " для спутника " << name << endl;
}

// Автоматическая запись текущего состояния
void Sputnik::recordCurrentState() {
    double temperature = 20.0 + (orbit / 1000.0) - (batteryCharge / 10.0);
    if (temperature < -50) temperature = -50;
    if (temperature > 100) temperature = 100;

    addTelemetryRecord(lastTelemetryTime, batteryCharge, temperature);
    lastTelemetryTime += 1.0;  // Увеличиваем ВРЕМЯ КОНКРЕТНОГО СПУТНИКА
}

// Получение записи телеметрии
Sputnik::RecordTelemetry Sputnik::getTelemetryRecord(int index) const {
    if (index < 0 || index >= telemetryCount) {
        cerr << "Ошибка: неверный индекс телеметрии" << endl;
        return RecordTelemetry();
    }
    return telemetryHistory[index];
}

// Очистка данных телеметрии
void Sputnik::clearTelemetryData() {
    telemetryCount = 0;
    cout << "Данные телеметрии спутника " << name << " очищены" << endl;
}

// Вывод информации о спутнике
void Sputnik::printInfo() const {
    cout << "\n=== Информация о спутнике ===" << endl;
    cout << "Название: " << name << endl;
    cout << "Высота орбиты: " << fixed << setprecision(2) << orbit << " км" << endl;
    cout << "Скорость: " << fixed << setprecision(2) << speed << " км/с" << endl;
    cout << "Заряд батареи: " << fixed << setprecision(2) << batteryCharge << "%" << endl;
    cout << "Потребление энергии: " << fixed << setprecision(2)
        << energyDemandInSeconds << " %/с" << endl;
    cout << "Состояние: " << (isOn ? "Включен" : "Выключен") << endl;
    cout << "Записей телеметрии: " << telemetryCount << endl;
}

// Вывод истории телеметрии
void Sputnik::printTelemetryHistory() const {
    if (telemetryCount == 0) {
        cout << "История телеметрии спутника " << name << " пуста" << endl;
        return;
    }

    cout << "\n=== История телеметрии спутника " << name << " ===" << endl;
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

// Расчет средней температуры
double Sputnik::getAverageTemperature() const {
    if (telemetryCount == 0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < telemetryCount; i++) {
        sum += telemetryHistory[i].temperature;
    }
    return sum / telemetryCount;
}

// Перегруженные операторы

// Оператор += для добавления энергии
Sputnik& Sputnik::operator+=(double additionalEnergy) {
    batteryCharge += additionalEnergy;
    if (batteryCharge > 100) batteryCharge = 100;
    if (batteryCharge < 0) batteryCharge = 0;

    cout << "Добавлено " << additionalEnergy << "% энергии спутнику "
        << name << ". Текущий заряд: " << batteryCharge << "%" << endl;

    recordCurrentState();
    return *this;
}

// Оператор + для создания копии с добавленной энергией
Sputnik Sputnik::operator+(double additionalEnergy) const {
    Sputnik result = *this;  // Используем конструктор копирования
    result += additionalEnergy;  // Используем уже реализованный оператор +=
    return result;
}

// Оператор [] для доступа к телеметрии
Sputnik::RecordTelemetry& Sputnik::operator[](int index) {
    if (index < 0 || index >= telemetryCount) {
        cerr << "Ошибка: индекс вне диапазона!" << endl;
        static RecordTelemetry dummy;
        return dummy;
    }
    return telemetryHistory[index];
}

// Константная версия оператора []
const Sputnik::RecordTelemetry& Sputnik::operator[](int index) const {
    if (index < 0 || index >= telemetryCount) {
        cerr << "Ошибка: индекс вне диапазона!" << endl;
        static RecordTelemetry dummy;
        return dummy;
    }
    return telemetryHistory[index];
}

// Оператор вывода
ostream& operator<<(ostream& os, const Sputnik& sputnik) {
    os << "Спутник \"" << sputnik.name << "\": ";
    os << "орбита=" << fixed << setprecision(2) << sputnik.orbit << " км, ";
    os << "скорость=" << fixed << setprecision(2) << sputnik.speed << " км/с, ";
    os << "заряд=" << fixed << setprecision(2) << sputnik.batteryCharge << "%, ";
    os << "состояние=" << (sputnik.isOn ? "вкл" : "выкл");
    return os;
}