#include <stdio.h>

int signup();
int login();
void details();
void deposit();
void withdraw();
void transfer();
void transfer_history();

int storedId = 0;
int storedPin = 0;
int amount = 0;

int transferIds[1000];
int transferAmounts[1000];
int transferCount = 0;

int signup() {
    printf("\n=== Signup ===\n");
    printf("Enter your ID (number): ");
    if (scanf("%d", &storedId) != 1) {
        printf("Invalid input!\nID must be a number.\n");
        while (getchar() != '\n');
        return 1;
    }

    printf("Set your PIN (number): ");
    if (scanf("%d", &storedPin) != 1) {
        printf("Invalid input!\nPIN must be a number.\n");
        while (getchar() != '\n');
        return 1;
    }

    while (getchar() != '\n');
    printf("Signup successful!\n");
    return 0;
}

int login() {
    int inputId, inputPin;
    printf("\n=== Login ===\n");

    printf("Enter your ID: ");
    if (scanf("%d", &inputId) != 1) {
        printf("Invalid input!\nID must be a number.\n");
        while (getchar() != '\n');
        return 1;
    }

    printf("Enter your PIN: ");
    if (scanf("%d", &inputPin) != 1) {
        printf("Invalid input!\nPIN must be a number.\n");
        while (getchar() != '\n');
        return 1;
    }

    while (getchar() != '\n');

    if (inputId == storedId && inputPin == storedPin) {
        printf("Login successful!\n");
        details();
    } else {
        printf("Login failed!\n");
    }
    return 0;
}

void details() {
    int choice;
    while (1) {
        printf("\n====== Account Dashboard ======\n");
        printf("1) View Account Details\n");
        printf("2) View Account Balance\n");
        printf("3) Deposit\n");
        printf("4) Withdraw\n");
        printf("5) Transfer\n");
        printf("6) Transfer History\n");
        printf("7) Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\nPlease enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Stored ID: %d\n", storedId);
                printf("Stored PIN: %d\n", storedPin);
                break;
            case 2:
                printf("Account Balance: %d\n", amount);
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                transfer();
                break;
            case 6:
                transfer_history();
                break;
            case 7:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void deposit() {
    int depositAmount;
    printf("Enter amount to deposit: ");
    if (scanf("%d", &depositAmount) != 1 || depositAmount <= 0) {
        printf("Invalid amount!\n");
        while (getchar() != '\n');
        return;
    }
    amount += depositAmount;
    printf("Deposited %d successfully!\nNew Balance: %d\n", depositAmount, amount);
    while (getchar() != '\n');
}

void withdraw() {
    int withdrawAmount;
    printf("Enter amount to withdraw: ");
    if (scanf("%d", &withdrawAmount) != 1 || withdrawAmount <= 0) {
        printf("Invalid amount!\n");
        while (getchar() != '\n');
        return;
    }
    if (withdrawAmount > amount) {
        printf("Insufficient balance!\n");
        while (getchar() != '\n');
        return;
    }
    amount -= withdrawAmount;
    printf("Withdrawn %d successfully.\nNew Balance: %d\n", withdrawAmount, amount);
    while (getchar() != '\n');
}

void transfer() {
    int recipientId, transferAmount;
    printf("\n=== Transfer ===\n");

    printf("Enter recipient ID: ");
    if (scanf("%d", &recipientId) != 1) {
        printf("Invalid input!\nID must be a number.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter amount to transfer: ");
    if (scanf("%d", &transferAmount) != 1 || transferAmount <= 0) {
        printf("Invalid amount!\n");
        while (getchar() != '\n');
        return;
    }
    if (transferAmount > amount) {
        printf("Insufficient balance!\n");
        while (getchar() != '\n');
        return;
    }

    if (transferCount >= 1000) {
        printf("Transfer history full. Cannot store more.\n");
        return;
    }

    amount -= transferAmount;
    transferIds[transferCount] = recipientId;
    transferAmounts[transferCount] = transferAmount;
    transferCount++;

    printf("Transferred %d to ID %d. Remaining Balance: %d\n", transferAmount, recipientId, amount);
    while (getchar() != '\n');
}

void transfer_history() {
    printf("\n=== Transfer History ===\n");

    if (transferCount == 0) {
        printf("No transfers made yet.\n");
        return;
    }

    for (int i = 0; i < transferCount; i++) {
        printf("%d) Sent %d to ID %d\n", i + 1, transferAmounts[i], transferIds[i]);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n===== Main Menu =====\n");
        printf("1) Signup\n");
        printf("2) Login\n");
        printf("3) Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Thank you! Goodbye.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}