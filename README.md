# Calculator Application README

---

## Description

This is a simple calculator application implemented in C++ using the Win32 API for the Windows platform. The application provides a graphical user interface (GUI) for performing basic arithmetic operations such as addition, subtraction, multiplication, and division.

---

## Features

- GUI interface with buttons for digits (0-9), arithmetic operations (+, -, *, /), clear (C), and equal (=).
- Input field to display user input and calculation results.
- Error handling for division by zero and invalid operations.

---

## Usage

1. Run the compiled executable file (`Calculator.exe`).
2. Use the buttons to input numbers and select arithmetic operations.
3. Press the "C" button to clear the input.
4. Press the "=" button to perform the calculation and display the result.

---

## Compilation Instructions

To compile the source code, you need a C++ compiler and the Windows SDK installed on your system. Follow these steps:

1. Open Command Prompt or any suitable compiler environment.
2. Navigate to the directory containing the source code files (`calculator.cpp`).
3. Run the following command to compile the code:
g++ calculator.cpp -o Calculator.exe -mwindows
4. After successful compilation, you will find the `Calculator.exe` executable in the same directory.

---

## Dependencies

- Windows SDK
- C++ compiler (e.g., GCC)

---
