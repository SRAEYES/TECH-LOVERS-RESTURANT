#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 100
#define MAX_ITEMS 50
#define MAX_USERS 10 
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20

// Structure to represent a user
struct User {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
};

// Structure to represent an item
struct Item {
    char name[20];
    float price;
    int quantity;
};

// Structure to represent an order
struct Order {
    char customerName[50];
    int itemCount;
    struct Item items[MAX_ITEMS];
};
// Function to authenticate users
int authenticateUser(const char *username, const char *password, struct User *users, int userCount) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

// Function to print the header of the bill
void Billhead(const char *customerName) {
    printf("\n\n");
    printf("\t    TECH LOVER'S Restaurant");
    printf("\n\t   -------------------------");
    printf("\nInvoice To: %s", customerName);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\tQty\t\tTotal\t\t\t\n");
    printf("---------------------------------------\n\n");
}

// Function to print the body of the bill
void Billbody(const struct Item *item) {
    printf("%s\t\t%d\t\t%.2f\t\t\n", item->name, item->quantity, item->quantity * item->price);
}

// Function to print the footer of the bill
void Billfooter(float total) {
    printf("\n");
    float discount = 0.03 * total;
    float netTotal = total - discount;
    float cgst = 0.025 * netTotal;
    float sgst = 0.025 * netTotal;
    float grandTotal = netTotal + cgst + sgst;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f\n", total);
    printf("Discount @3%%\t\t%.2f\n", discount);
    printf("\t\t\t\t\t-------\n");
    printf("Net Total\t\t\t%.2f\n", netTotal);
    printf("CGST @2.5%%\t\t\t%.2f\n", cgst);
    printf("SGST @2.5%%\t\t\t%.2f\n", sgst);
    printf("---------------------------------------\n");
    printf("Grand Total\t\t%.2f\n", grandTotal);
    printf("---------------------------------------\n");
}

int main() {
  struct User users[MAX_USERS] = {{"Abhijith", "abhi1"}, {"sraeyes", "sreaeyes1"}}; // Predefined users
  int userCount = 2;
    // Array to store multiple orders
    struct Order orders[MAX_CUSTOMERS];
    int orderCount = 0;
    char continueFlag = 'y';

    while (continueFlag == 'y' && orderCount < MAX_CUSTOMERS) {
        system("clear");
        float total = 0;
        int invoiceFound = 0;
      char username[USERNAME_LENGTH];
      char password[PASSWORD_LENGTH];
      int authenticated = 0;

     


        // Display the main menu
        printf("\t============TECH LOVER'S RESTAURANT============");
        printf("\n             _ _ __ _");
        printf("\n  Welcome To  | |_ |  ||   Lover's Resturant ");
        printf("\n              | |_ |_ |  |");
        printf("\n\n Specially Built For Tech Lovers Like You :)\n\n");
      printf("\n1. login\n");
        printf("2. Generate Invoice\n");
        printf("3. Show all Invoices\n");
        printf("4. Search Invoice\n");
        printf("5. Exit\n\n");
        printf("Your choice: ");

        int option;
        scanf("%d", &option);

        switch (option) {
          case 1:
                printf("Enter your username: ");
                scanf("%s", username);
                printf("Enter your password: ");
                scanf("%s", password);

                authenticated = authenticateUser(username, password, users, userCount);

                if (authenticated) {
                    printf("Login Successful!\n");
                  } else {
                      printf("Login Failed. Invalid username or password.\n");
                      return 1; // Exit the program if authentication fails
                  }
            case 2:
                // Generate a new invoice
                system("clear");
                struct Order *currentOrder = &orders[orderCount];
                printf("Please enter the name of the customer: ");
                scanf(" %[^\n]", currentOrder->customerName);
                printf("Please enter the number of items: ");
                scanf("%d", &currentOrder->itemCount);

                // Get details for each item in the order
                for (int i = 0; i < currentOrder->itemCount; i++) {
                    struct Item *item = &currentOrder->items[i];
                    printf("\nPlease Enter What You Want %d: ", i + 1);
                    scanf(" %[^\n]", item->name);
                    printf("How Many Units : \t");
                    scanf("%d", &item->quantity);
                    printf("Enter the unit price: ");
                    scanf("%f", &item->price);
                    total += item->quantity * item->price;
                }

                // Print the generated invoice
                Billhead(currentOrder->customerName);
                for (int i = 0; i < currentOrder->itemCount; i++) {
                    Billbody(&currentOrder->items[i]);
                }
                Billfooter(total);

                // Ask if the user wants to save the invoice
                printf("Do you want to save the invoice [y/n]: ");
                scanf(" %c", &continueFlag);

                if (continueFlag == 'y') {
                    orderCount++;
                }
                break;

            case 3:
                // Show all previous invoices
                system("clear");
                printf("* Your Previous Invoices *\n");
                for (int i = 0; i < orderCount; i++) {
                    struct Order *order = &orders[i];
                    float tot = 0;
                    Billhead(order->customerName);
                    for (int j = 0; j < order->itemCount; j++) {
                        Billbody(&order->items[j]);
                        tot += order->items[j].quantity * order->items[j].price;
                    }
                    Billfooter(tot);
                }
                break;

            case 4:
                // Search for a specific invoice
                printf("Enter the name of the customer: ");
                scanf(" %[^\n]", currentOrder->customerName);
                system("clear");
                printf("* Invoice of %s *", currentOrder->customerName);
                for (int i = 0; i < orderCount; i++) {
                    struct Order *order = &orders[i];
                    float tot = 0;
                    if (strcmp(order->customerName, currentOrder->customerName) == 0) {
                        Billhead(order->customerName);
                        for (int j = 0; j < order->itemCount; j++) {
                            Billbody(&order->items[j]);
                            tot += order->items[j].quantity * order->items[j].price;
                        }
                        Billfooter(tot);
                        invoiceFound = 1;
                    }
                }
                if (!invoiceFound) {
                    printf("Sorry, the invoice for %s does not exist", currentOrder->customerName);
                }
                break;

            case 5:
                // Exit the program
                printf("\n\t\t\t Thanks for Visiting :)\n\n");
                return 0;
            default:
                printf("Oops, Can't Find Your Option :(\n");
                break;
        }

        // Ask if the user wants to perform another operation
        printf("Do you want to perform another operation? [y/n]: ");
        scanf(" %c", &continueFlag);
    }

    printf("\n\t\t\t Thanks for Visiting :)\n\n");
    return 0;
}