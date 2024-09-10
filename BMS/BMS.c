#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store account details
struct Account {
    int accountNumber;
    char name[100];
    float balance;
};

// Function prototypes
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void displayMenu();

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                printf("Exiting the program. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n=== Bank Management System ===\n");
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Exit\n");
}

// Function to create a new account
void createAccount() {
    struct Account acc;
    FILE *file;

    printf("Enter account number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter name: ");
    scanf(" %[^\n]", acc.name);
    acc.balance = 0.0;

    file = fopen("accounts.dat", "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, file);
    fclose(file);

    printf("Account created successfully!\n");
}

// Function to deposit money into an account
void deposit() {
    struct Account acc;
    FILE *file;
    int accNumber;
    float amount;
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accNumber);

    file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, file);
            printf("Amount deposited successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to withdraw money from an account
void withdraw() {
    struct Account acc;
    FILE *file;
    int accNumber;
    float amount;
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accNumber);

    file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (acc.balance < amount) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                fseek(file, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, file);
                printf("Amount withdrawn successfully!\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to check the balance of an account
void checkBalance() {
    struct Account acc;
    FILE *file;
    int accNumber;
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accNumber);

    file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNumber) {
            printf("Account Number: %d\n", acc.accountNumber);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}
