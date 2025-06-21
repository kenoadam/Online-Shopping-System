# Online Shopping System in C++

Video Demo: https://youtu.be/6g1uXgwqu54

Author: Adam Johnson  
GitHub: kenoadam  
Location: Kenosha, USA  
Date Recorded: 06/20/2025



## Description

This project is a console-based online shopping system written in C++. It simulates a simplified e-commerce platform with features such as:

- A product catalog with names, descriptions, prices, and stock quantities.
- A shopping cart that allows users to add items and check totals.
- Three types of users (Regular, Premium, VIP) with different discount levels.
- A thread-safe checkout system using mutexes to protect shared resources.

Users begin by entering their name and selecting a user type. They can then browse a product menu, add items to their cart, and confirm checkout. Discounts are applied based on user type.



## Files Included

- main.cpp – Contains all class definitions, the interactive menu system, and the main function. This is the complete application in one file.



## Project Features

- Encapsulation: All class attributes are private and accessed through public member functions.
- Inheritance and Polymorphism: User roles are implemented using class inheritance, with discounts handled through polymorphic methods.
- Multithreading Support: The system uses mutexes to safely update shared inventory in simulated concurrent scenarios.
- Input Validation: The system checks user input to prevent errors and ensure smooth interaction.



## How to Compile and Run

### Compile (using g++)
```bash
g++ -std=c++11 -pthread main.cpp -o shopping_app
