# MediCore Hospital Management System

Student-level C++ OOP project based on the provided assignment. The program uses file-based persistence and a simple SFML GUI.

## Features

- Patient, Doctor and Admin login
- Appointments, billing, prescriptions and medical records
- Immediate file updates after every change
- Manual sorting logic for appointments, bills and records
- Required operator overloading and custom exceptions
- Simple GUI built with SFML

## Sample Login Data

- Patient: `1` / `pass123`
- Patient: `2` / `patient2`
- Doctor: `1` / `doc456`
- Doctor: `2` / `doc789`
- Admin: `1` / `admin123`

## Build

1. Open a terminal in the project folder.
2. Run:

```bash
cmake -S . -B build
cmake --build build
```

3. Run the executable from the build folder:

```bash
build/MediCore.exe
```

The `data` folder is copied into the build folder automatically by CMake.

## Notes

- All source files are separated into `.h` and `.cpp` files.
- No `std::vector` is used.
- No `std::string` is used in the project code.
- File I/O is handled only through `FileHandler`.
- Input validation is handled only through `Validator`.
- Replace this line with your public GitHub repository link before final submission.

GitHub Repository Link: `ADD-YOUR-REPOSITORY-LINK-HERE`
