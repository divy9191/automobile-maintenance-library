#ifndef MAINTENANCE_TASK_H
#define MAINTENANCE_TASK_H

#include <string>
#include <vector>
#include <algorithm>
#include <memory>

/**
 * Base class for maintenance tasks
 */
class MaintenanceTask {
private:
    std::string taskName;
    std::string description;
    std::vector<std::string> applicableVehicleTypes;
    static int nextId;
    int id;
    
public:
    // Constructor
    MaintenanceTask(const std::string& taskName, const std::string& description, 
                   const std::vector<std::string>& applicableVehicleTypes);
    
    // Virtual destructor
    virtual ~MaintenanceTask() = default;
    
    // Getters
    int getId() const { return id; }
    const std::string& getTaskName() const { return taskName; }
    const std::string& getDescription() const { return description; }
    const std::vector<std::string>& getApplicableVehicleTypes() const { return applicableVehicleTypes; }
    
    // Utility methods
    bool isApplicableToVehicle(const std::string& vehicleType) const;
    virtual std::string toString() const;
    
    // Factory methods for common maintenance tasks
    static std::shared_ptr<MaintenanceTask> createOilChange();
    static std::shared_ptr<MaintenanceTask> createTireRotation();
    static std::shared_ptr<MaintenanceTask> createBatteryInspection();
    static std::shared_ptr<MaintenanceTask> createBrakeInspection();
    static std::shared_ptr<MaintenanceTask> createAirFilterReplacement();
    static std::shared_ptr<MaintenanceTask> createTransmissionService();
};

#endif // MAINTENANCE_TASK_H
