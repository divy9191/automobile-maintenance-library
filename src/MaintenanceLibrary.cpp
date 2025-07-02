#include "MaintenanceLibrary.h"
#include <algorithm>

MaintenanceLibrary::MaintenanceLibrary() {
    initializeDefaultTasks();
}

void MaintenanceLibrary::addVehicle(std::shared_ptr<Automobile> vehicle) {
    if (vehicle) {
        vehicles.push_back(vehicle);
    }
}

bool MaintenanceLibrary::removeVehicle(int vehicleId) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [vehicleId](const std::shared_ptr<Automobile>& vehicle) {
            return vehicle->getId() == vehicleId;
        });
    
    if (it != vehicles.end()) {
        vehicles.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<Automobile> MaintenanceLibrary::getVehicle(int vehicleId) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [vehicleId](const std::shared_ptr<Automobile>& vehicle) {
            return vehicle->getId() == vehicleId;
        });
    
    return (it != vehicles.end()) ? *it : nullptr;
}

const std::vector<std::shared_ptr<Automobile>>& MaintenanceLibrary::getAllVehicles() const {
    return vehicles;
}

void MaintenanceLibrary::addAvailableTask(std::shared_ptr<MaintenanceTask> task) {
    if (task) {
        availableTasks.push_back(task);
    }
}

const std::vector<std::shared_ptr<MaintenanceTask>>& MaintenanceLibrary::getAvailableTasks() const {
    return availableTasks;
}

std::shared_ptr<MaintenanceTask> MaintenanceLibrary::getAvailableTask(int taskId) {
    auto it = std::find_if(availableTasks.begin(), availableTasks.end(),
        [taskId](const std::shared_ptr<MaintenanceTask>& task) {
            return task->getId() == taskId;
        });
    
    return (it != availableTasks.end()) ? *it : nullptr;
}

bool MaintenanceLibrary::addMaintenanceTaskToVehicle(int vehicleId, int taskId) {
    auto vehicle = getVehicle(vehicleId);
    auto task = getAvailableTask(taskId);
    
    if (vehicle && task && task->isApplicableToVehicle(vehicle->getVehicleType())) {
        vehicle->addMaintenanceTask(task);
        return true;
    }
    return false;
}

bool MaintenanceLibrary::removeMaintenanceTaskFromVehicle(int vehicleId, int taskIndex) {
    auto vehicle = getVehicle(vehicleId);
    if (vehicle) {
        return vehicle->removeMaintenanceTask(taskIndex);
    }
    return false;
}

void MaintenanceLibrary::initializeDefaultTasks() {
    availableTasks.clear();
    
    // Add default maintenance tasks
    addAvailableTask(MaintenanceTask::createOilChange());
    addAvailableTask(MaintenanceTask::createTireRotation());
    addAvailableTask(MaintenanceTask::createBatteryInspection());
    addAvailableTask(MaintenanceTask::createBrakeInspection());
    addAvailableTask(MaintenanceTask::createAirFilterReplacement());
    addAvailableTask(MaintenanceTask::createTransmissionService());
}

std::vector<std::shared_ptr<MaintenanceTask>> MaintenanceLibrary::getApplicableTasksForVehicle(const std::string& vehicleType) const {
    std::vector<std::shared_ptr<MaintenanceTask>> applicableTasks;
    
    for (const auto& task : availableTasks) {
        if (task->isApplicableToVehicle(vehicleType)) {
            applicableTasks.push_back(task);
        }
    }
    
    return applicableTasks;
}

int MaintenanceLibrary::getVehicleCount() const {
    return static_cast<int>(vehicles.size());
}

int MaintenanceLibrary::getTotalMaintenanceTasksCount() const {
    int total = 0;
    for (const auto& vehicle : vehicles) {
        total += static_cast<int>(vehicle->getMaintenanceTasks().size());
    }
    return total;
}
