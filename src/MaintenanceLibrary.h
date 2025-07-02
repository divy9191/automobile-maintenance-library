#ifndef MAINTENANCE_LIBRARY_H
#define MAINTENANCE_LIBRARY_H

#include "Automobile.h"
#include "MaintenanceTask.h"
#include <vector>
#include <memory>
#include <string>

/**
 * Main library class for managing vehicles and maintenance tasks
 */
class MaintenanceLibrary {
private:
    std::vector<std::shared_ptr<Automobile>> vehicles;
    std::vector<std::shared_ptr<MaintenanceTask>> availableTasks;
    
public:
    // Constructor
    MaintenanceLibrary();
    
    // Destructor
    ~MaintenanceLibrary() = default;
    
    // Vehicle management
    void addVehicle(std::shared_ptr<Automobile> vehicle);
    bool removeVehicle(int vehicleId);
    std::shared_ptr<Automobile> getVehicle(int vehicleId);
    const std::vector<std::shared_ptr<Automobile>>& getAllVehicles() const;
    
    // Maintenance task management
    void addAvailableTask(std::shared_ptr<MaintenanceTask> task);
    const std::vector<std::shared_ptr<MaintenanceTask>>& getAvailableTasks() const;
    std::shared_ptr<MaintenanceTask> getAvailableTask(int taskId);
    
    // Vehicle-specific maintenance task operations
    bool addMaintenanceTaskToVehicle(int vehicleId, int taskId);
    bool removeMaintenanceTaskFromVehicle(int vehicleId, int taskIndex);
    
    // Utility methods
    void initializeDefaultTasks();
    std::vector<std::shared_ptr<MaintenanceTask>> getApplicableTasksForVehicle(const std::string& vehicleType) const;
    
    // Statistics
    int getVehicleCount() const;
    int getTotalMaintenanceTasksCount() const;
};

#endif // MAINTENANCE_LIBRARY_H
