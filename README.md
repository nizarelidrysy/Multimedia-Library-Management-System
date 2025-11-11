📚 Project 5: Multimedia Library Management System
🌟 Overview
This is a console-based application developed in C++ using Object-Oriented Programming (OOP) principles to manage the inventory and operations of a multimedia library.



The project is designed for a team of 4-5 students and focuses on object design and code quality, not graphical interfaces.


✨ Key Functional Requirements
The application must include the following minimum functionalities:
Media Management (CRUD): Add, modify, delete, and view media records.
Search and Sort: Search the collection by title or media type, and implement sorting.
Loan Operations: Handle borrowing (Emprunts) and returning (Retours) of media, including availability checks.
Statistics: Calculate the total duration and average duration for audiovisual content.
Reporting: Export reports of the library status to a text file (.txt).
💻 Technical Implementation (C++ POO)
The following OOP concepts and C++ features must be mastered and implemented:
Inheritance: Use a base class Media with derived classes for specific types: Livre (Book), Audio, and Video. Optional: Implement LivreAudio using multiple inheritance.
Polymorphism: Implement polymorphism for display and statistical calculations.
Smart Pointers: Utilize smart pointers (unique_ptr / shared_ptr) for robust memory management.
Operator Overloading: Overload operators for comparison (<, ==).
Robustness: Implement exception handling to ensure application stability.
Data Persistence: Manage the state of the library through file reading/writing.