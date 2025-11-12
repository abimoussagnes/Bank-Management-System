# Bank Management System (C++)

A simple console-based Bank Management System written in C++. It demonstrates basic file-backed account management including creating accounts, depositing/withdrawing funds, balance inquiries, and listing/removing accounts. Data is stored locally in a binary file (data.bin).


## Features
- Create new bank accounts
- Deposit and withdraw money
- Check balance and account details
- List all accounts
- Close/delete an account
- Persistent storage using a binary data file (data.bin)


## Requirements
- C++11 or newer
- A C++ compiler for Windows (one of):
  - MinGW-w64 g++ (recommended for quick setup)
  - Microsoft Visual C++ (MSVC) via Visual Studio or Build Tools


## Project Structure
```
Bank-Management-System/
├─ main.cpp        // Application entry and logic
├─ data.bin        // Binary data store (created at runtime; may already exist)
└─ README.md       // This file
```


## Build Instructions (Windows)

### Using MinGW-w64 (g++)
1. Ensure g++ is available in PATH. If not installed, install MinGW-w64 and add its bin directory to PATH.
2. Open a terminal in the project root (Bank-Management-System).
3. Compile:
   ```bash
   g++ -std=c++11 -O2 -Wall -Wextra -o bank.exe main.cpp
   ```
4. Run:
   ```bash
   .\bank.exe
   ```

### Using Microsoft Visual C++ (MSVC)
1. Open "x64 Native Tools Command Prompt for VS" (or x86, matching your target).
2. Navigate to the project directory.
3. Compile:
   ```bat
   cl /EHsc /W4 /O2 main.cpp /Fe:bank.exe
   ```
4. Run:
   ```bat
   bank.exe
   ```


## Usage
- After launching the program, follow the on-screen menu to:
  - Create an account (you will be prompted for details like account number, holder name, and initial deposit)
  - Deposit funds (enter account number and amount)
  - Withdraw funds (enter account number and amount; basic validation is performed)
  - Display account details/balance
  - List all accounts
  - Close/delete an account
- Input is via standard console prompts.


## Data Persistence
- The application reads/writes records to a binary file named `data.bin` in the project directory.
- If `data.bin` does not exist, it will be created at runtime.
- Deleting `data.bin` will remove all stored accounts. Keep backups if needed.


## Notes
- This project is intended for learning and demonstration. It does not implement encryption, authentication, concurrency controls, or ACID guarantees.
- Error handling and validation are basic; adapt for production-grade requirements.
- If you modify the record structure in `main.cpp`, older `data.bin` files may become incompatible.


## Extending the Project
Suggested improvements:
- Replace binary file with a portable text (CSV/JSON) or embedded database (SQLite)
- Add unit tests (e.g., using GoogleTest) and CI workflows
- Implement transaction history per account
- Add interest calculation and account types (savings/current)
- Introduce PIN/password per account with hashed storage
- Build a simple GUI (Qt/ImGui) or a REST API backend


## License
This project is provided as-is for educational purposes. Choose and add a license (e.g., MIT) if you plan to distribute.