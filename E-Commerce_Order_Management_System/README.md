# E-Commerce Order Management System

## Project Description

The **E-Commerce Order Management System** is a console-based C++ application designed to simulate the basic operations of an online shopping platform. The system manages **products, customers, orders, and payments** while applying important object-oriented programming concepts.

The application allows users to maintain product information such as product ID, name, price, stock, and category. It also manages customer details, including customer ID, name, email, phone number, and address. Orders can be created, updated, confirmed, cancelled, and displayed while tracking both order status and payment status.

Product categories, order statuses, payment statuses, and payment methods are implemented using **enums** to provide clear and controlled values throughout the system. A **union** is used to store payment-specific information efficiently. Depending on the selected payment method, the system can store credit card details, a UPI ID, or no additional information for cash payments.

The system also includes validation mechanisms to handle common invalid scenarios, such as:

* Product being out of stock
* Invalid product ID
* Invalid customer ID
* Attempting to cancel a delivered order
* Attempting payment for a cancelled order
* Confirming an order when the payment has failed

This project demonstrates the practical implementation of fundamental C++ programming and object-oriented concepts, including **classes, structures, unions, enums, constructors, member functions, and access specifiers**.

## Key Features

* Product management with stock availability checking
* Customer information management and updates
* Order creation and status management
* Order confirmation and cancellation
* Multiple payment methods: Credit Card, UPI, and Cash
* Payment-specific data handling using unions
* Validation and error handling for invalid operations
* Console-based user interaction

## Concepts Used

* **Class**
* **Struct**
* **Union**
* **Enum**
* **Constructor**
* **Member Functions**
* **Access Specifiers**
* **Conditional Statements**
* **Input Validation**
* **Object-Oriented Programming**

## Objective

The main objective of this project is to develop a structured understanding of how different C++ programming concepts can work together to build a simplified real-world **E-Commerce Order Management System**. It provides practical experience in designing classes and data structures, managing application states, validating user actions, and implementing object-oriented programming principles.
