//Sputnic.h   -  объявление класса


#ifndef SPUTNIC_H
#define SPUTNIC_H

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
    double lastTelemetryTime;


    RecordTelemetry* telemetryHistory;
    int telemetryCapacity;
    int telemetryCount;

    void expandTelemetryArray();  // Вспомогательный метод для расширения массива

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
    std::string getName() const { return name; }
    double getOrbit() const { return orbit; }
    double getSpeed() const { return speed; }
    double getBatteryCharge() const { return batteryCharge; }
    double getEnergyDemandInSeconds() const { return energyDemandInSeconds; }
    bool getIsOn() const { return isOn; }

    // Сеттеры
    void setName(const std::string& n) { name = n; }
    void setPowerState(bool state);

    // Основные методы
    void operate(double seconds);
    double getOrbitalPeriod() const;
    void recharge(double efficiency, double sunlightSeconds);
    void printInfo() const;

    // Методы для работы с динамическими данными
    void addTelemetryRecord(double timestamp, double battery, double temp);
    void recordCurrentState();  // Автоматическая запись текущего состояния
    RecordTelemetry getTelemetryRecord(int index) const;
    int getTelemetryCount() const { return telemetryCount; }
    void clearTelemetryData();
    void printTelemetryHistory() const;
    double getAverageTemperature() const;

    // Перегруженные операторы
    Sputnik& operator+=(double additionalEnergy);        // Добавление энергии
    Sputnik operator+(double additionalEnergy) const;    // Создание копии с энергией
    RecordTelemetry& operator[](int index);              // Доступ к телеметрии
    const RecordTelemetry& operator[](int index) const;  // Константный доступ

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Sputnik& sputnik);
};

#endif