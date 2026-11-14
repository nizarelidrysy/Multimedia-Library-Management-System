## Multimedia Library Management System: A Retro CRUD Simulation

The **Multimedia Library Management System** is a C++ based console application designed to simulate a digital media ecosystem. It features a retro computer library interface that distinguishes between administrative control and user-end interactions, focusing on robust data management and object-oriented principles.

---

## Key Features

The project is structured to handle various media types (Books, Movies, Games) through two primary access levels:

### 1. Dual-Mode Interface

The system operates on a bifurcated logic to ensure secure data handling and a streamlined user experience:

#### Admin Mode:
* **Inventory Management:** Full CRUD (Create, Read, Update, Delete) capabilities for the library’s collection.
* **Data Persistence:** Tools to modify the underlying database of media items, ensuring the library remains up-to-date.
* **System Oversight:** Secure access to administrative functions for managing digital assets.

#### User Mode:
* **Media Discovery:** Browse the full catalog of available media with formatted console output.
* **Shopping Simulation:** A virtual marketplace where users can select and "purchase" media items.
* **Interactive Navigation:** Simple, prompt-based menus designed for ease of use within the terminal.

### 2. Technical Architecture

* **Object-Oriented Design:** Developed using **C++**, leveraging inheritance and polymorphism to manage different media types efficiently.
* **Memory Management:** Utilizes modern C++ standards, including **smart pointers**, to ensure efficient memory usage and prevent leaks during runtime.
* **Search & Filter:** Built-in logic to quickly locate specific items within the library’s collection based on various metadata.

### 3. File & Data Handling

* **Digital Infrastructure:** Simulates a structured database environment (utilizing SQLite or similar flat-file logic depending on the branch) to manage seat reservations or media stock.
* **Scalable Logic:** The codebase is designed to handle increasing amounts of media data without sacrificing performance.

---

## Usage

* **Initialization:** Upon launching the executable, choose between **Admin** and **User** modes.
* **Admin Controls:** Use the designated menu keys to add new media entries, update existing details, or remove outdated content.
* **User Experience:** Browse the catalog by selecting the "Display" option and follow the prompts to add items to your virtual cart.
* **Exiting:** Use the "Return" or "Exit" commands to safely close the session and ensure data consistency.

---

## Contribution

This project serves as a foundation for digital infrastructure simulations. Contributions that enhance the UI/UX of the console or add new media categories are welcome!

* Fork the repository.
* Create your feature branch (`git checkout -b feature/improved-logic`).
* Commit your changes.
* Open a Pull Request.

---

## 📄 License

This project is open-source and open for contribution.

---

<div align="center">
  <p>Built with ❤️ by Nizar EL IDRYSY.</p>
</div>
