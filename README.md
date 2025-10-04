# 🏦 Client Management System (C++)

This is a simple, console-based application written in C++ for managing client bank records. It allows an administrator to view, add, delete, update, and find client information, with data persistently stored in a local text file.

## ✨ Features

* **View All Clients:** Display a formatted list of all active client records.
* **Add New Client:** Create a new client record with validation for unique account numbers.
* **Delete Client:** Find a client by account number and mark them for deletion after confirmation.
* **Update Client:** Find a client and modify their details (Pin Code, Name, Phone, and Account Balance).
* **Find Client:** Search and display a single client's details by account number.
* **File Persistence:** All data is loaded from and saved to a text file (`Clients.txt`).

---

## 🛠️ Technology Used

* **Language:** C++
* **Environment:** Console Application (Windows, Linux, or macOS)
* **File Format:** Plain Text (`Clients.txt`) with custom delimiter (`#//#`).

---

## 🚀 How to Run the Project

### Prerequisites

You need a C++ compiler installed on your system, such as:
* **GCC** (The GNU Compiler Collection)
* **Microsoft Visual Studio** (Recommended for Windows users)

### Compilation and Execution

1.  **Save the code:** Save the provided C++ code into a file named `ProjectName.cpp` (e.g., `ClientManager.cpp`).
2.  **Compile:** Open your terminal or command prompt, navigate to the directory where you saved the file, and compile it.

    ```bash
    g++ ClientManager.cpp -o ClientManager.exe
    ```

3.  **Run:** Execute the compiled program.

    ```bash
    ./ClientManager.exe
    ```

    The application will launch the **Main Menu**, allowing you to interact with the system.

---

## 📁 File Structure

The project relies on a single data file:

| File Name | Description |
| :--- | :--- |
| `ProjectName.cpp` | The main C++ source code containing all logic and the `main` function. |
| **`Clients.txt`** | The database file where client records are saved and loaded from. If this file doesn't exist, the program will create it when attempting to write data. |

---

## 📚 Future Improvements

* **Robust Input Validation:** Add checks for numeric/string types on all inputs (e.g., ensuring Pin Code and Phone are numeric).
* **Data Security:** Implement encryption for sensitive data like Pin Codes in the `Clients.txt` file.
* **User Interface:** Upgrade to a GUI (using frameworks like Qt or SFML) for a better user experience.
* **Search Optimization:** For very large datasets, optimize search and lookup using maps or database libraries instead of linear file reading.
