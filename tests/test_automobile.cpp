#include <gtest/gtest.h>
#include "../src/Automobile.h"
#include "../src/MaintenanceTask.h"

class AutomobileTest : public ::testing::Test {
protected:
    void SetUp() override {
        electricCar = std::make_shared<ElectricCar>("Tesla", "Model S", 2022, 10000, 100);
        gasCar = std::make_shared<GasCar>("Toyota", "Camry", 2021, 25000, 15.0);
        dieselCar = std::make_shared<DieselCar>("Ford", "F-250", 2020, 45000, 20.0);
        
        oilChangeTask = MaintenanceTask::createOilChange();
        tireRotationTask = MaintenanceTask::createTireRotation();
        batteryInspectionTask = MaintenanceTask::createBatteryInspection();
    }

    std::shared_ptr<ElectricCar> electricCar;
    std::shared_ptr<GasCar> gasCar;
    std::shared_ptr<DieselCar> dieselCar;
    
    std::shared_ptr<MaintenanceTask> oilChangeTask;
    std::shared_ptr<MaintenanceTask> tireRotationTask;
    std::shared_ptr<MaintenanceTask> batteryInspectionTask;
};

TEST_F(AutomobileTest, VehicleCreation) {
    EXPECT_EQ(electricCar->getMake(), "Tesla");
    EXPECT_EQ(electricCar->getModel(), "Model S");
    EXPECT_EQ(electricCar->getYear(), 2022);
    EXPECT_EQ(electricCar->getOdometerReading(), 10000);
    EXPECT_EQ(electricCar->getVehicleType(), "electric");
    EXPECT_EQ(electricCar->getBatteryCapacity(), 100);
}

TEST_F(AutomobileTest, MaintenanceTaskApplicability) {
    // Oil change should not be applicable to electric cars
    electricCar->addMaintenanceTask(oilChangeTask);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 0);
    
    // Oil change should be applicable to gas cars
    gasCar->addMaintenanceTask(oilChangeTask);
    EXPECT_EQ(gasCar->getMaintenanceTasks().size(), 1);
    
    // Tire rotation should be applicable to all vehicle types
    electricCar->addMaintenanceTask(tireRotationTask);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 1);
    
    gasCar->addMaintenanceTask(tireRotationTask);
    EXPECT_EQ(gasCar->getMaintenanceTasks().size(), 2);
    
    dieselCar->addMaintenanceTask(tireRotationTask);
    EXPECT_EQ(dieselCar->getMaintenanceTasks().size(), 1);
}

TEST_F(AutomobileTest, BatteryInspectionElectricOnly) {
    // Battery inspection should only be applicable to electric cars
    electricCar->addMaintenanceTask(batteryInspectionTask);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 1);
    
    gasCar->addMaintenanceTask(batteryInspectionTask);
    EXPECT_EQ(gasCar->getMaintenanceTasks().size(), 0);
    
    dieselCar->addMaintenanceTask(batteryInspectionTask);
    EXPECT_EQ(dieselCar->getMaintenanceTasks().size(), 0);
}

TEST_F(AutomobileTest, RemoveMaintenanceTask) {
    electricCar->addMaintenanceTask(tireRotationTask);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 1);
    
    bool removed = electricCar->removeMaintenanceTask(0);
    EXPECT_TRUE(removed);
    EXPECT_EQ(electricCar->getMaintenanceTasks().size(), 0);
    
    // Try to remove from empty list
    bool removedAgain = electricCar->removeMaintenanceTask(0);
    EXPECT_FALSE(removedAgain);
}

TEST_F(AutomobileTest, UniqueIds) {
    auto car1 = std::make_shared<ElectricCar>("Tesla", "Model 3", 2022, 5000);
    auto car2 = std::make_shared<GasCar>("Honda", "Civic", 2021, 15000);
    
    EXPECT_NE(car1->getId(), car2->getId());
    EXPECT_NE(car1->getId(), electricCar->getId());
}
