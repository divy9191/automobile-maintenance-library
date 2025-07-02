#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class MaintenanceTask;

/**
 * Base class for all automobiles
 */
class Automobile {
protected:
    std::string make;
    std::string model;
    int year;
    int odometerReading;
    std::vector<std::shared_ptr<MaintenanceTask>> maintenanceTasks;
    static int nextId;
    int id;

public:
    // Constructor
    Automobile(const std::string& make, const std::string& model, int year, int odometerReading);
    
    // Virtual destructor for proper inheritance
    virtual ~Automobile() = default;
    
    // Getters
    int getId() const { return id; }
    const std::string& getMake() const { return make; }
    const std::string& getModel() const { return model; }
    int getYear() const { return year; }
    int getOdometerReading() const { return odometerReading; }
    const std::vector<std::shared_ptr<MaintenanceTask>>& getMaintenanceTasks() const { return maintenanceTasks; }
    
    // Setters
    void setOdometerReading(int reading) { odometerReading = reading; }
    
    // Pure virtual method to get vehicle type
    virtual std::string getVehicleType() const = 0;
    
    // Maintenance task management
    void addMaintenanceTask(std::shared_ptr<MaintenanceTask> task);
    bool removeMaintenanceTask(int taskIndex);
    
    // Utility methods
    virtual std::string toString() const;
};

/**
 * Electric car implementation
 */
class ElectricCar : public Automobile {
private:
    int batteryCapacity; // kWh
    
public:
    ElectricCar(const std::string& make, const std::string& model, int year, 
                int odometerReading, int batteryCapacity = 100);
    
    std::string getVehicleType() const override { return "electric"; }
    int getBatteryCapacity() const { return batteryCapacity; }
    void setBatteryCapacity(int capacity) { batteryCapacity = capacity; }
    
    std::string toString() const override;
};

/**
 * Gas car implementation
 */
class GasCar : public Automobile {
private:
    double fuelCapacity; // gallons
    
public:
    GasCar(const std::string& make, const std::string& model, int year, 
           int odometerReading, double fuelCapacity = 15.0);
    
    std::string getVehicleType() const override { return "gas"; }
    double getFuelCapacity() const { return fuelCapacity; }
    void setFuelCapacity(double capacity) { fuelCapacity = capacity; }
    
    std::string toString() const override;
};

/**
 * Diesel car implementation
 */
class DieselCar : public Automobile {
private:
    double fuelCapacity; // gallons
    
public:
    DieselCar(const std::string& make, const std::string& model, int year, 
              int odometerReading, double fuelCapacity = 20.0);
    
    std::string getVehicleType() const override { return "diesel"; }
    double getFuelCapacity() const { return fuelCapacity; }
    void setFuelCapacity(double capacity) { fuelCapacity = capacity; }
    
    std::string toString() const override;
};

#endif // AUTOMOBILE_H
