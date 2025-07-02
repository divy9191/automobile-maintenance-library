#include "MaintenanceTask.h"
#include <memory>
#include <sstream>

// Initialize static member
int MaintenanceTask::nextId = 1;

MaintenanceTask::MaintenanceTask(const std::string& taskName, const std::string& description, 
                                const std::vector<std::string>& applicableVehicleTypes)
    : taskName(taskName), description(description), applicableVehicleTypes(applicableVehicleTypes), id(nextId++) {
}

bool MaintenanceTask::isApplicableToVehicle(const std::string& vehicleType) const {
    return std::find(applicableVehicleTypes.begin(), applicableVehicleTypes.end(), vehicleType) 
           != applicableVehicleTypes.end();
}

std::string MaintenanceTask::toString() const {
    std::stringstream ss;
    ss << taskName << " (ID: " << id << ") - " << description << " [Applicable to: ";
    for (size_t i = 0; i < applicableVehicleTypes.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << applicableVehicleTypes[i];
    }
    ss << "]";
    return ss.str();
}

// Factory methods
std::shared_ptr<MaintenanceTask> MaintenanceTask::createOilChange() {
    return std::make_shared<MaintenanceTask>(
        "Oil Change",
        "Change engine oil and oil filter",
        std::vector<std::string>{"gas", "diesel"}
    );
}

std::shared_ptr<MaintenanceTask> MaintenanceTask::createTireRotation() {
    return std::make_shared<MaintenanceTask>(
        "Tire Rotation",
        "Rotate tires to ensure even wear",
        std::vector<std::string>{"electric", "gas", "diesel"}
    );
}

std::shared_ptr<MaintenanceTask> MaintenanceTask::createBatteryInspection() {
    return std::make_shared<MaintenanceTask>(
        "Battery Inspection",
        "Inspect high-voltage battery system and connections",
        std::vector<std::string>{"electric"}
    );
}

std::shared_ptr<MaintenanceTask> MaintenanceTask::createBrakeInspection() {
    return std::make_shared<MaintenanceTask>(
        "Brake Inspection",
        "Inspect brake pads, rotors, and brake fluid",
        std::vector<std::string>{"electric", "gas", "diesel"}
    );
}

std::shared_ptr<MaintenanceTask> MaintenanceTask::createAirFilterReplacement() {
    return std::make_shared<MaintenanceTask>(
        "Air Filter Replacement",
        "Replace engine air filter",
        std::vector<std::string>{"gas", "diesel"}
    );
}

std::shared_ptr<MaintenanceTask> MaintenanceTask::createTransmissionService() {
    return std::make_shared<MaintenanceTask>(
        "Transmission Service",
        "Service transmission fluid and filter",
        std::vector<std::string>{"gas", "diesel"}
    );
}
