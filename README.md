# Banking Management System in C

A command-line based Banking Management System developed in C as a first-year college project. The system supports essential banking operations such as account creation, authentication, transactions, and history tracking using file handling.

## Features

### Core Functionalities

- User Authentication with custom memory-based password encryption
- Account Creation and Management
- Deposits, Withdrawals, and Transfers
- Transaction History Logging
- File-based Data Storage using `users.txt`, `accounts.txt`, and `transactions.txt`


### Security and Data Handling

- Simple custom encryption inspired by hashing and XOR methods
- Failed transactions are logged separately
- Backup system for important data files


## File Structure
Banking-Management-System/
├── main.c                   // Entry point and menu navigation
├── auth.c                   // User authentication and encryption
├── accounts.c               // Account-related functions
├── transactions.c           // Deposit, withdraw, transfer functions
├── history.c                // Transaction history viewing
├── utils.c                  // Utility functions
├── users.txt                // Stores user credentials
├── accounts.txt             // Stores account details
├── transactions.txt         // Logs all transactions
├── failed_transactions.txt  // Records failed transaction attempts
└── backups/                 // Backup copies of critical files



## Project Goals

- Practice file handling and modular programming in C
- Learn the basics of encryption
- Simulate real-world systems using data structures
- Build a menu-driven console application


## Developers

- Syed Ayaan Hasan 
- Syed Obaid Faraz
- Tushar Vibhakar Kulkarni


## Notes

- Encryption used in this project is for academic purposes and not suitable for real-world security.
- Console-based interface only; no GUI.
- Keep backup copies of data files to avoid accidental loss.


## Learnings

- File I/O operations in C
- Modular programming and use of header files
- Command-line menu systems
- Basic password security concepts


## License

This project is developed for educational use. You are free to modify and adapt it for learning purposes.


