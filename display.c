#include <stdio.h>

int signup();
int login();
void details();
void deposit();
void withdraw();


int storedId = 0;
int storedPin = 0;
int amount = 0;


int signup() {
    printf("\nSignup:\n");
    printf("Enter your Account number: ");
    scanf("%d", &storedId);
    printf("Set your PIN (number): ");
    scanf("%d", &storedPin);
    printf("Signup successful!\n\n");
    return 0;
}


int login() {
    int inputId, inputPin;

    printf("\nLogin:\n");
    printf("Enter your Account number: ");
    scanf("%d", &inputId);
    printf("Enter your PIN: ");
    scanf("%d", &inputPin);

    if (inputId == storedId && inputPin == storedPin) {
        printf("Login successful!\n\n");
        details();  
    } else {
        printf("Login failed!\n\n");
    }
    return 0;
}


void details() {
    int choice;
    while (1) {
        printf("\n====== Account Dashboard ======\n");
        printf("1) View Account Details\n");
        printf("2) Deposit\n");
        printf("3) Withdraw\n");
        printf("4) Transfer (not implemented)\n");
        printf("5) Transfer History (not implemented)\n");
        printf("6) Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Stored ID: %d\n", storedId);
            printf("Stored PIN: %d\n", storedPin);
            printf("Account Balance: %d\n", amount);
        } else if (choice == 2) {
            deposit();
        } else if (choice == 3) {
            withdraw();
        } else if (choice == 4 || choice == 5) {
            printf("Feature not implemented yet.\n");
        } else if (choice == 6) {
            printf("Logging out...\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
}


void deposit() {
    int depositAmount;
    printf("Enter amount to deposit: ");
    scanf("%d", &depositAmount);
    if (depositAmount > 0) {
        amount += depositAmount;
        printf("Deposited %d successfully. New Balance: %d\n", depositAmount, amount);
    } else {
        printf("Invalid amount!\n");
    }
}


void withdraw() {
    int withdrawAmount;
    printf("Enter amount to withdraw: ");
    scanf("%d", &withdrawAmount);
    if (withdrawAmount > 0 && withdrawAmount <= amount) {
        amount -= withdrawAmount;
        printf("Withdrawn %d successfully. New Balance: %d\n", withdrawAmount, amount);
    } else {
        printf("Invalid amount or insufficient balance!\n");
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
        scanf("%d", &choice);

        if (choice == 1) {
            signup();
        } else if (choice == 2) {
            login();
        } else if (choice == 3) {
            printf("Thank you! Goodbye.\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}