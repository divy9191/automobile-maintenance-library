# Automobile Maintenance Library Demo Script
**Duration:** 5 minutes

## Introduction (30 seconds)
"Welcome to the Automobile Maintenance Library - a C++ powered system for tracking vehicle maintenance across electric, gas, and diesel vehicles. This system demonstrates object-oriented programming principles with a modern web interface."

## Demo Flow

### 1. Show the Dashboard (30 seconds)
- Point out the three main statistics cards:
  - Total Vehicles (currently showing sample data)
  - Electric Vehicles count
  - Total Maintenance Tasks
- "The dashboard gives us a quick overview of our vehicle fleet"

### 2. Available Maintenance Tasks Overview (45 seconds)
- Scroll to the "Available Maintenance Tasks" section
- Highlight the different task types:
  - **Oil Change** - Gas and Diesel only
  - **Tire Rotation** - All vehicle types
  - **Battery Inspection** - Electric vehicles only
  - **Brake Inspection** - All vehicle types
  - **Air Filter Replacement** - Gas and Diesel only
  - **Transmission Service** - Gas and Diesel only
- "Notice how each task shows which vehicle types it applies to - this is the smart restriction system"

### 3. Add Electric Vehicle (45 seconds)
Fill out the form:
- **Type:** Electric
- **Make:** Tesla
- **Model:** Model Y
- **Year:** 2023
- **Odometer:** 12000
- Click "Add Vehicle"
- "Watch how the dashboard updates automatically"

### 4. Add Gas Vehicle (30 seconds)
Fill out the form:
- **Type:** Gas
- **Make:** Honda
- **Model:** Civic
- **Year:** 2022
- **Odometer:** 35000
- Click "Add Vehicle"

### 5. Add Diesel Vehicle (30 seconds)
Fill out the form:
- **Type:** Diesel
- **Make:** Ford
- **Model:** F-250
- **Year:** 2021
- **Odometer:** 67000
- Click "Add Vehicle"

### 6. Demonstrate Task Restrictions (90 seconds)

#### Electric Vehicle Tasks:
- Click "Add Task" on the Tesla Model Y
- Show available tasks in dropdown (should only show applicable ones)
- Select "Battery Inspection" - explain this is electric-only
- Add the task
- Try to show that "Oil Change" is NOT available for electric

#### Gas Vehicle Tasks:
- Click "Add Task" on Honda Civic
- Select "Oil Change" - explain this works for gas engines
- Add the task
- Select "Tire Rotation" - explain this works for all vehicles
- Add the task

#### Diesel Vehicle Tasks:
- Click "Add Task" on Ford F-250
- Select "Transmission Service" - explain heavy-duty maintenance
- Add the task

### 7. Show the Complete Vehicle Library (45 seconds)
- Scroll through the vehicle list
- Point out:
  - Color-coded vehicle type badges
  - Individual maintenance task lists for each vehicle
  - Vehicle-specific information (odometer, year, etc.)
  - Different applicable maintenance tasks per vehicle type

### 8. Demonstrate Remove Functionality (30 seconds)
- Remove one vehicle to show the delete functionality
- Watch dashboard update automatically
- "The system maintains data integrity throughout all operations"

### 9. Technical Architecture Highlight (30 seconds)
"Behind the scenes, this runs on:
- **C++ Backend:** Object-oriented design with inheritance (Automobile base class, Electric/Gas/Diesel derived classes)
- **Smart Task System:** Maintenance tasks automatically filter based on vehicle compatibility
- **Modern Web Interface:** Bootstrap-powered responsive design
- **Real-time Updates:** Dashboard statistics update automatically
- **RESTful API:** Clean separation between backend logic and frontend presentation"

### 10. Closing (15 seconds)
"This demonstrates how C++ object-oriented programming can power real-world applications with modern web interfaces. The system enforces business rules (like electric cars don't need oil changes) while providing an intuitive user experience."

## Key Talking Points Throughout Demo:

### Object-Oriented Design:
- "The inheritance hierarchy ensures each vehicle type has appropriate maintenance options"
- "Polymorphism allows the system to handle different vehicle types uniformly"

### Business Logic:
- "Smart restrictions prevent inappropriate maintenance assignments"
- "Each maintenance task knows which vehicle types it applies to"

### User Experience:
- "Real-time dashboard updates provide immediate feedback"
- "Color-coded interfaces make vehicle types immediately recognizable"
- "Form validation ensures data integrity"

### Technical Implementation:
- "C++ backend handles all business logic and data management"
- "Web frontend provides modern, responsive user interface"
- "RESTful API design enables future mobile app development"

## Backup Demo Points (if time allows):

### Error Handling:
- Try to add invalid data to show form validation
- Demonstrate graceful error messages

### Scalability:
- "System designed to handle large vehicle fleets"
- "Maintenance task library easily extensible"

### Future Enhancements:
- "Could add maintenance scheduling"
- "Integration with parts inventory systems"
- "Mobile app development using existing API"

## Demo Tips:
1. Keep the browser at a comfortable zoom level for audience visibility
2. Prepare the demo by clearing any existing data first
3. Have backup data ready if network issues occur
4. Practice the timing to stay within 5 minutes
5. Emphasize the smart restrictions - this is the key differentiator