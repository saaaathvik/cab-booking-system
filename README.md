# Cab Booking System - README

## Project Overview
This project is a Cab Booking System written in C, which uses Dijkstra's algorithm for calculating the shortest distance between points on a map. It handles customer and driver databases, calculates fares based on distance, vehicle type, and surcharges, and tracks cancellations.

## File Structure

### 1. **Customer_Creator.c**
- Used to create the Customer Database.  
- No need to run, attached for reference.

### 2. **Driver_DB_Creator.c**
- Used to create the Driver Database.  
- No need to run, attached for reference.

### 3. **Customer_Details.txt**
- Contains the Customer Database stored as a Binary File.  
- Place it in the same directory as Project.c during runtime for smooth operation.  
- Holds the Customer's Name and Number_Of_Cancellations.

### 4. **Driver_Details.txt**
- Contains the Driver Database stored as a Binary File.  
- Place it in the same directory as Project.c during runtime for smooth operation.  
- Holds the Driver_ID, Name, Phone_No, x_coordinate, y_coordinate, Rating, No_Of_Raters, and Type_Of_Vehicle for 24 different drivers.

### 5. **Driver_Details.pdf**
- Contains the Driver Database stored as a PDF File.  
- Not used in the program but provided for readability and verification.

### 6. **Map.jpg**
- Contains a picture of the map used for the Cab Booking System.  
- This file is for comprehension and verification of the system's functionality.

### 7. **Report.pdf**
- Documentation of the project, providing a detailed explanation of its functionality and design.

### 8. **Project.c**
- The main program implementing the Cab Booking System.

## Key Features
- **Shortest Distance Calculation:** Uses Dijkstra’s algorithm to calculate the shortest route between locations.
- **Driver Location Identification:** Identifies on which road a driver is located using the coordinates.
- **Fare Calculation:** Computes the fare based on pickup and drop locations, vehicle type, distance, and additional charges like surge fees and cancellations.

## How to Use
1. Make sure all required files are in the same directory as Project.c.
2. Run Project.c to initialize the cab booking system.
3. Use the Customer_Details.txt and Driver_Details.txt files for customer and driver data management.
4. Follow the prompts in the program to book a cab and calculate fares.

---

For any further questions or suggestions, feel free to contact the project author.