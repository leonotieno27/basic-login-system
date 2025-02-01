//basic login system
//by leonotieno27

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct users {
    char username[50];
    char password[50];
};

FILE *fptr;

//Function prototypes
void signUp();
void login();

int main() {
    int choice;
    printf("\t\t\t***Basic Login System***\n\n");

    puts("Choose an option: (1/2)");
    puts("1.Sign up");
    puts("2.Login");
    scanf("%d", &choice);
    getchar();

    if (choice == 1){
        signUp();
    }else if(choice == 2){
        login();
    }else{
        puts("Wrong input");
    }
    return 0;
}

void signUp() {
    system("clear");
    puts("\tRegister in the system\n");
    struct users user;

    //open file for appending
    fptr = fopen("database.txt", "ab");
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter your name: ");
    fgets(user.username, 50, stdin);
    user.username[strcspn(user.username, "\n")] = '\0'; // Remove newline

    printf("Enter your password: ");
    fgets(user.password, 50, stdin);
    user.password[strcspn(user.password, "\n")] = '\0';

    fwrite(&user, sizeof(struct users), 1, fptr);
    fclose(fptr);  // Close file after writing

    printf("You have been added to the system.\n");
}

void login() {
    system("clear");
    puts("\tLogin into the system\n");

    char checkUsername[50];
    char checkPassword[50];
    struct users user;
    int found = 0;

    // Open file for reading
    fptr = fopen("database.txt", "rb");
    if (fptr == NULL) {
        puts("Error opening file");
        return;
    }

    printf("Enter username: ");
    fgets(checkUsername, sizeof(checkUsername), stdin);
    checkUsername[strcspn(checkUsername, "\n")] = '\0';

    printf("Enter password: ");
    fgets(checkPassword, sizeof(checkPassword), stdin);
    checkPassword[strcspn(checkPassword, "\n")] = '\0';

    // Loop to check all users in the database
    while (fread(&user, sizeof(struct users), 1, fptr)) {
        if (strcmp(checkUsername, user.username) == 0 && strcmp(checkPassword, user.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fptr); // Close the file

    if (found) {
        system("clear");
        printf("Logged In\nWelcome %s!\n", user.username);
    } else {
        puts("Wrong username or password");
    }
}
