#include "Automobile.h"
#include "MaintenanceTask.h"
#include <sstream>
#include <algorithm>

// Initialize static member
int Automobile::nextId = 1;

Automobile::Automobile(const std::string& make, const std::string& model, int year, int odometerReading)
    : make(make), model(model), year(year), odometerReading(odometerReading), id(nextId++) {
}

void Automobile::addMaintenanceTask(std::shared_ptr<MaintenanceTask> task) {
    if (task && task->isApplicableToVehicle(getVehicleType())) {
        maintenanceTasks.push_back(task);
    }
}

bool Automobile::removeMaintenanceTask(int taskIndex) {
    if (taskIndex >= 0 && taskIndex < static_cast<int>(maintenanceTasks.size())) {
        maintenanceTasks.erase(maintenanceTasks.begin() + taskIndex);
        return true;
    }
    return false;
}

std::string Automobile::toString() const {
    std::stringstream ss;
    ss << year << " " << make << " " << model 
       << " (ID: " << id << ", Odometer: " << odometerReading << " miles)";
    return ss.str();
}

// ElectricCar implementation
ElectricCar::ElectricCar(const std::string& make, const std::string& model, int year, 
                         int odometerReading, int batteryCapacity)
    : Automobile(make, model, year, odometerReading), batteryCapacity(batteryCapacity) {
}

std::string ElectricCar::toString() const {
    std::stringstream ss;
    ss << Automobile::toString() << " [Electric, Battery: " << batteryCapacity << " kWh]";
    return ss.str();
}

// GasCar implementation
GasCar::GasCar(const std::string& make, const std::string& model, int year, 
               int odometerReading, double fuelCapacity)
    : Automobile(make, model, year, odometerReading), fuelCapacity(fuelCapacity) {
}

std::string GasCar::toString() const {
    std::stringstream ss;
    ss << Automobile::toString() << " [Gas, Tank: " << fuelCapacity << " gallons]";
    return ss.str();
}

// DieselCar implementation
DieselCar::DieselCar(const std::string& make, const std::string& model, int year, 
                     int odometerReading, double fuelCapacity)
    : Automobile(make, model, year, odometerReading), fuelCapacity(fuelCapacity) {
}

std::string DieselCar::toString() const {
    std::stringstream ss;
    ss << Automobile::toString() << " [Diesel, Tank: " << fuelCapacity << " gallons]";
    return ss.str();
}
