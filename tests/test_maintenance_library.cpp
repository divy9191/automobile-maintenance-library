#include <gtest/gtest.h>
#include "../src/MaintenanceLibrary.h"

class MaintenanceLibraryTest : public ::testing::Test {
protected:
    void SetUp() override {
        library = std::make_unique<MaintenanceLibrary>();
        
        electricCar = std::make_shared<ElectricCar>("Tesla", "Model 3", 2022, 10000);
        gasCar = std::make_shared<GasCar>("Toyota", "Camry", 2021, 25000);
        dieselCar = std::make_shared<DieselCar>("Ford", "F-250", 2020, 45000);
    }

    std::unique_ptr<MaintenanceLibrary> library;
    std::shared_ptr<ElectricCar> electricCar;
    std::shared_ptr<GasCar> gasCar;
    std::shared_ptr<DieselCar> dieselCar;
};

TEST_F(MaintenanceLibraryTest, AddAndRemoveVehicles) {
    EXPECT_EQ(library->getVehicleCount(), 0);
    
    library->addVehicle(electricCar);
    EXPECT_EQ(library->getVehicleCount(), 1);
    
    library->addVehicle(gasCar);
    library->addVehicle(dieselCar);
    EXPECT_EQ(library->getVehicleCount(), 3);
    
    bool removed = library->removeVehicle(electricCar->getId());
    EXPECT_TRUE(removed);
    EXPECT_EQ(library->getVehicleCount(), 2);
    
    // Try to remove non-existent vehicle
    bool removedAgain = library->removeVehicle(999);
    EXPECT_FALSE(removedAgain);
    EXPECT_EQ(library->getVehicleCount(), 2);
}

TEST_F(MaintenanceLibraryTest, GetVehicle) {
    library->addVehicle(electricCar);
    
    auto retrieved = library->getVehicle(electricCar->getId());
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), electricCar->getId());
    
    auto nonExistent = library->getVehicle(999);
    EXPECT_EQ(nonExistent, nullptr);
}

TEST_F(MaintenanceLibraryTest, DefaultTasks) {
    const auto& tasks = library->getAvailableTasks();
    EXPECT_GT(tasks.size(), 0);
    
    // Should have basic maintenance tasks
    bool hasOilChange = false;
    bool hasTireRotation = false;
    bool hasBatteryInspection = false;
    
    for (const auto& task : tasks) {
        if (task->getTaskName() == "Oil Change") hasOilChange = true;
        if (task->getTaskName() == "Tire Rotation") hasTireRotation = true;
        if (task->getTaskName() == "Battery Inspection") hasBatteryInspection = true;
    }
    
    EXPECT_TRUE(hasOilChange);
    EXPECT_TRUE(hasTireRotation);
    EXPECT_TRUE(hasBatteryInspection);
}

TEST_F(MaintenanceLibraryTest, AddMaintenanceTaskToVehicle) {
    library->addVehicle(electricCar);
    library->addVehicle(gasCar);
    
    const auto& tasks = library->getAvailableTasks();
    int tireRotationTaskId = -1;
    int oilChangeTaskId = -1;
    int batteryInspectionTaskId = -1;
    
    for (const auto& task : tasks) {
        if (task->getTaskName() == "Tire Rotation") tireRotationTaskId = task->getId();
        if (task->getTaskName() == "Oil Change") oilChangeTaskId = task->getId();
        if (task->getTaskName() == "Battery Inspection") batteryInspectionTaskId = task->getId();
    }
    
    // Add tire rotation to electric car (should work)
    bool success = library->addMaintenanceTaskToVehicle(electricCar->getId(), tireRotationTaskId);
    EXPECT_TRUE(success);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 1);
    
    // Add oil change to electric car (should fail)
    success = library->addMaintenanceTaskToVehicle(electricCar->getId(), oilChangeTaskId);
    EXPECT_FALSE(success);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 1);
    
    // Add battery inspection to gas car (should fail)
    success = library->addMaintenanceTaskToVehicle(gasCar->getId(), batteryInspectionTaskId);
    EXPECT_FALSE(success);
    EXPECT_EQ(gasCar->getMaintenanceTasks().size(), 0);
    
    // Add oil change to gas car (should work)
    success = library->addMaintenanceTaskToVehicle(gasCar->getId(), oilChangeTaskId);
    EXPECT_TRUE(success);
    EXPECT_EQ(gasCar->getMaintenanceTasks().size(), 1);
}

TEST_F(MaintenanceLibraryTest, GetApplicableTasksForVehicle) {
    auto electricTasks = library->getApplicableTasksForVehicle("electric");
    auto gasTasks = library->getApplicableTasksForVehicle("gas");
    auto dieselTasks = library->getApplicableTasksForVehicle("diesel");
    
    // Electric cars should not have oil change tasks
    bool electricHasOilChange = false;
    for (const auto& task : electricTasks) {
        if (task->getTaskName() == "Oil Change") electricHasOilChange = true;
    }
    EXPECT_FALSE(electricHasOilChange);
    
    // Gas cars should have oil change tasks
    bool gasHasOilChange = false;
    for (const auto& task : gasTasks) {
        if (task->getTaskName() == "Oil Change") gasHasOilChange = true;
    }
    EXPECT_TRUE(gasHasOilChange);
    
    // All vehicle types should have tire rotation
    bool electricHasTireRotation = false;
    bool gasHasTireRotation = false;
    bool dieselHasTireRotation = false;
    
    for (const auto& task : electricTasks) {
        if (task->getTaskName() == "Tire Rotation") electricHasTireRotation = true;
    }
    for (const auto& task : gasTasks) {
        if (task->getTaskName() == "Tire Rotation") gasHasTireRotation = true;
    }
    for (const auto& task : dieselTasks) {
        if (task->getTaskName() == "Tire Rotation") dieselHasTireRotation = true;
    }
    
    EXPECT_TRUE(electricHasTireRotation);
    EXPECT_TRUE(gasHasTireRotation);
    EXPECT_TRUE(dieselHasTireRotation);
}
