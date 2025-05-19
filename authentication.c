#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

const int caesarkey = 19;
const char substitution_key[] = "PGWHSXCTIRZQLJOAMUYVNDFEBK";

// --- Encryption logic ---
char substitute_char(char c, const char key[]) {
    c = toupper(c);
    return key[c - 'A'];
}

char* encrypt(char *passkey) {
    int length = strlen(passkey);
    char *encrypted_password = (char *)malloc(length + 1);
    if (!encrypted_password) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        if (islower(passkey[i])) {
            int x = (passkey[i] - 'a' + caesarkey) % 26;
            encrypted_password[i] = tolower(substitute_char('a' + x, substitution_key));
        } else if (isupper(passkey[i])) {
            int x = (passkey[i] - 'A' + caesarkey) % 26;
            encrypted_password[i] = substitute_char('A' + x, substitution_key);
        } else {
            encrypted_password[i] = passkey[i];
        }
    }
    encrypted_password[length] = '\0';
    return encrypted_password;
}

// --- Sign-up logic ---
void signup() {
    char username[100], password[100];

    printf("\nChoose a Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Choose a Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    // Check if username already exists
    FILE *file = fopen("users.txt", "r");
    if (file) {
        char line[200], file_user[100];
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%[^,]", file_user) == 1) {
                if (strcmp(username, file_user) == 0) {
                    printf("Username already exists. Try a different one.\n");
                    fclose(file);
                    return;
                }
            }
        }
        fclose(file);
    }

    char *encrypted_pass = encrypt(password);

    // Append to users.txt
    file = fopen("users.txt", "a");
    if (!file) {
        printf("Error: Cannot open users.txt for writing.\n");
        free(encrypted_pass);
        return;
    }

    fprintf(file, "%s,%s\n", username, encrypted_pass);
    fclose(file);
    free(encrypted_pass);
    printf("Sign-up successful! You can now log in.\n");
}

// --- Authentication logic ---
int authenticate() {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error: Cannot open users.txt\n");
        return 0;
    }

    char input_username[100], input_password[100];
    int attempts = 0;
    time_t lock_until = 0;

    while (1) {
        time_t now = time(NULL);
        if (now < lock_until) {
            printf("Account locked. Try again in %ld seconds.\n", lock_until - now);
            continue;
        }

        printf("\nUsername: ");
        fgets(input_username, sizeof(input_username), stdin);
        input_username[strcspn(input_username, "\n")] = 0;

        printf("Password: ");
        fgets(input_password, sizeof(input_password), stdin);
        input_password[strcspn(input_password, "\n")] = 0;

        char *encrypted_input = encrypt(input_password);

        rewind(file);
        char line[200], file_user[100], file_pass[100];
        int found = 0;

        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "%[^,],%s", file_user, file_pass) == 2) {
                if (strcmp(input_username, file_user) == 0 &&
                    strcmp(encrypted_input, file_pass) == 0) {
                    found = 1;
                    break;
                }
            }
        }

        free(encrypted_input);

        if (found) {
            printf("Login successful!\n");
            fclose(file);
            return 1;
        } else {
            printf("Invalid username or password.\n");
            attempts++;
            if (attempts >= 3) {
                printf("Too many failed attempts. Locking for 30 seconds.\n");
                lock_until = time(NULL) + 30;
                attempts = 0;
            }
        }
    }
}

int main() {
    printf("=== Welcome to the Login System ===\n");
    int choice;
    do {
        printf("\n1. Login\n2. Sign Up\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);
        getchar(); // clear newline after scanf

        switch (choice) {
            case 1:
                authenticate();
                break;
            case 2:
                signup();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
