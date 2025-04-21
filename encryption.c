#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int caesarkey = 19;
const char substitution_key[] = "PGWHSXCTIRZQLJOAMUYVNDFEBK";
const int alphabets[26] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
                      13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
                    };

char* encrypt(char *passkey);
char* decrypt(char *encrypted);
char substitute_char(char c, const char key[]);
char reverse_substitute(char c, const char key[]);


int main()
{
    char *password = "abcd";
    char *x = encrypt(password);
    printf("Encrypted: %s\n", x);
    char *y = decrypt(x);
    printf("Decrypted: %s\n", y);
    free(x);
}

char* encrypt(char *passkey)
{
    int length = strlen(passkey);
    char *encrypted_password = (char*)(malloc)(length + 1);

    for(int i = 0; i < length; i++)
    {
        if (passkey[i] >= 'a' && passkey[i] <= 'z')
            {
                int x = (alphabets[passkey[i] - 'a'] + caesarkey) % 26;
                encrypted_password[i] = 'a' + x;
                encrypted_password[i] = tolower(substitute_char(encrypted_password[i], substitution_key));
            }
            else if (passkey[i] >= 'A' && passkey[i] <= 'Z')
            {
                int x = (alphabets[passkey[i] - 'A'] + caesarkey) % 26;
                encrypted_password[i] = 'A' + x;
                encrypted_password[i] = substitute_char(encrypted_password[i], substitution_key);
            }
            else
                encrypted_password[i] = passkey[i];
    }
    encrypted_password[length] = '\0';
    return encrypted_password ;
}

char* decrypt(char *encrypted)
{
    int length = strlen(encrypted);
    char* decrypted = (char*)malloc(length + 1);

    for (int i = 0; i < length; i++) 
    {
        char is_lower = islower(encrypted[i]);  
        char substituted = reverse_substitute(encrypted[i], substitution_key);

        if (isalpha(substituted)) 
        {
            int idx = (toupper(substituted) - 'A' - caesarkey + 26) % 26;
            decrypted[i] = is_lower ? ('a' + idx) : ('A' + idx);
        } 
        else 
        {
            decrypted[i] = substituted;
        }
    } 

    decrypted[length] = '\0';
    return decrypted;
}


char substitute_char(char c, const char key[])
{
    c = toupper(c);
    int ascci_value = c;

    char out = key[ascci_value - 65];
    return out;
}

char reverse_substitute(char c, const char key[]) 
{
    c = toupper(c); 
    for (int i = 0; i < 26; i++) {
        if (key[i] == c) {
            return 'A' + i;
        }
    }
    return c;
}
