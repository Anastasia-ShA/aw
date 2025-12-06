//sputnic.h

#ifndef SPUTNIK_H
#define SPUTNIK_H

#include <iostream>
#include <string>

class Sputnik {
public:
    struct RecordTelemetry {
        double timestamp;      // Время измерения (секунды)
        double batteryLevel;   // Уровень заряда батареи (%)
        double temperature;    // Температура спутника (°C)

        RecordTelemetry() : timestamp(0), batteryLevel(0), temperature(0) {}
        RecordTelemetry(double ts, double bat, double temp)
            : timestamp(ts), batteryLevel(bat), temperature(temp) {}
    };

private:
    std::string name;
    double orbit;
    double speed;
    double batteryCharge;
    double energyDemandInSeconds;
    bool isOn;

    RecordTelemetry* telemetryHistory;
    int telemetryCapacity;
    int telemetryCount;

    void expandTelemetryArray();

public:
    // Конструкторы
    Sputnik();
    Sputnik(std::string n, double o, double s, double bat, double energy, bool on);
    Sputnik(const Sputnik& other);  // Конструктор копирования

    // Деструктор
    ~Sputnik();

    // Оператор присваивания
    Sputnik& operator=(const Sputnik& other);

    // Геттеры
    bool getIsOn() const { return isOn; }

    // Сеттеры
    void setPowerState(bool state);


    void operate(double seconds);
    double getOrbitalPeriod() const;
    void recharge(double efficiency, double sunlightSeconds);
    void printInfo() const;

    // Методы для работы с динамическими данными
    void addTelemetryRecord(double timestamp, double battery, double temp);
    RecordTelemetry getTelemetryRecord(int index) const;
    int getTelemetryCount() const { return telemetryCount; }
    void printTelemetryHistory() const;

    // Перегруженные операторы
    Sputnik& operator+=(double additionalEnergy);        // Добавление энергии
    //RecordTelemetry& operator[](int index);              // Доступ к телеметрии
    //const RecordTelemetry& operator[](int index) const;  // Константный доступ
    RecordTelemetry operator[](int index) const;


    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Sputnik& sputnik);
};

#endif