# Online Shopping System in C++

#### Video Demo: [Insert your YouTube video URL here]

#### Author: Adam Johnson 
#### GitHub: kenoadam 
#### Location: Kenosha USA  
#### Date Recorded: 06/16/2025

---

## 📦 Description

This is a **console-based online shopping system in C++** that simulates a basic e-commerce experience with the following core features:

- A catalog of products that users can browse.
- A shopping cart that tracks products and quantities.
- Multiple user types (Regular, Premium, VIP) with varying benefits.
- A secure, thread-safe checkout process using multithreading and mutexes to simulate multiple users interacting concurrently.

Users begin by selecting a role and entering their name. The system then presents a menu-driven interface that allows them to view available products, add them to their cart, and proceed to checkout. At checkout, product stock is updated accordingly, and the final bill reflects any applicable user discounts.

---

## 📁 Files

- **main.cpp**:  
  The core source file containing all class definitions, the main shopping loop, and multithreaded execution logic.

---

## ⚙️ Features

- **Product Management**  
  Each `Product` has a name, description, price, and stock quantity. Users can view product info and attempt purchases.

- **User Types via Inheritance**  
  - `User`: Base class with name and email.
  - `RegularUser`: No discount.
  - `PremiumUser`: 10% discount.
  - `VIPUser`: 20% discount.

- **Thread Safety**  
  Product stock is protected using `std::mutex` and `std::lock_guard`, simulating realistic concurrent shopping scenarios.

- **Interactive Menu System**  
  Text-based UI that walks users through browsing, adding to cart, and checking out.

- **Encapsulation and Clean OOP Design**  
  All attributes are private, with access controlled through public member functions.

---

## 💡 Design Justifications

- **Polymorphism** allows clean separation of behavior by user type.
- **Multithreading** adds realism and demonstrates concurrency control.
- **Encapsulation** protects internal state and enforces abstraction.
- **Menu-driven input** simplifies user experience and aligns with GeeksforGeeks best practices.

---

## 🖥️ How to Compile and Run

### Step 1: Clone or Download
Clone this repository or download the project files manually.

### Step 2: Compile
Using g++:
```bash
g++ -std=c++11 -pthread main.cpp -o shopping_app
