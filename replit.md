# Automobile Maintenance Library

## Overview

This is a C++ based automobile maintenance tracking system with a web frontend. The system manages different types of vehicles (electric, gas, and diesel) and their associated maintenance tasks. It follows object-oriented design principles with a clear separation between the C++ backend library and a modern web interface built with Bootstrap and vanilla JavaScript.

## System Architecture

### Backend Architecture
- **Core Language**: C++ with C++17 standard
- **Build System**: CMake for cross-platform compilation
- **Design Pattern**: Object-oriented inheritance hierarchy
- **Threading**: Pthread support for concurrent operations
- **Compilation**: GCC with optimization flags (-O2) and strict warnings

### Frontend Architecture
- **Framework**: Vanilla JavaScript with Bootstrap 5.3.0
- **UI Library**: Bootstrap components for responsive design
- **Icons**: Font Awesome 6.4.0 for visual elements
- **Architecture Pattern**: Class-based JavaScript with modular design
- **Communication**: RESTful API calls to backend server

## Key Components

### C++ Backend Components

1. **Automobile Base Class**
   - Attributes: make, model, year, odometerReading
   - Serves as foundation for vehicle inheritance hierarchy

2. **Vehicle Derived Classes**
   - ElectricCar, GasCar, DieselCar
   - Each inherits from Automobile base class
   - Type-specific maintenance task compatibility

3. **MaintenanceTask Class**
   - Attributes: taskName, description, applicableVehicleTypes
   - Defines maintenance operations with vehicle type restrictions

4. **MaintenanceLibrary Class**
   - Central management system for vehicles and tasks
   - Methods for CRUD operations on vehicles and maintenance tasks
   - Validation logic for task-vehicle compatibility

### Frontend Components

1. **AutomobileMaintenanceApp Class**
   - Main application controller
   - Manages vehicle and task data
   - Handles user interactions and API communication

2. **Dashboard Interface**
   - Real-time statistics display
   - Vehicle type breakdown (total, electric, gas, diesel)
   - Interactive vehicle management interface

3. **Modal System**
   - Bootstrap-based task addition modal
   - Form validation and user feedback
   - Toast notifications for user actions

## Data Flow

1. **Vehicle Management**
   - User adds vehicle through web form
   - Frontend validates input and sends API request
   - C++ backend creates appropriate vehicle object
   - Vehicle stored in MaintenanceLibrary collection

2. **Task Assignment**
   - User selects vehicle for task addition
   - Available tasks filtered by vehicle type compatibility
   - Task association validated in backend
   - Updated vehicle data returned to frontend

3. **Data Persistence**
   - In-memory storage in C++ objects
   - API endpoints provide CRUD operations
   - Frontend maintains synchronized state

## External Dependencies

### C++ Backend
- **CMake**: Build system (minimum version 3.16)
- **PkgConfig**: Package configuration management
- **Pthread**: POSIX threading library
- **GCC/Clang**: C++17 compatible compiler

### Frontend
- **Bootstrap 5.3.0**: UI framework via CDN
- **Font Awesome 6.4.0**: Icon library via CDN
- **Modern Browser**: ES6+ JavaScript support required

### Optional Dependencies
- **Google Test**: Unit testing framework (commented out in CMakeLists.txt)
- **Web Server**: For serving static files and API endpoints

## Deployment Strategy

### Build Process
1. CMake configuration and build system generation
2. C++ compilation with optimization flags
3. Static file serving for web interface
4. Executable generation for maintenance server

### Development Environment
- Cross-platform support via CMake
- Hot-reload capability for web development
- Modular testing setup (currently commented)

### Production Considerations
- Optimized C++ build (-O2 flag)
- Static asset serving
- API server deployment
- Memory management for vehicle collections

## User Preferences

Preferred communication style: Simple, everyday language.

## Changelog

Changelog:
- July 02, 2025. Initial setup