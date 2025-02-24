#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "beauty_salon_bookings.txt"
#define MAX_BOOKINGS 50
#define SERVICE_NAME_LENGTH 50
#define TIME_LENGTH 10
#define PRICE_LENGTH 10
#define NAME_LENGTH 50
#define PHONE_LENGTH 20

// Arrays to store booking information
char clientNames[MAX_BOOKINGS][NAME_LENGTH];
char clientPhones[MAX_BOOKINGS][PHONE_LENGTH];
char services[MAX_BOOKINGS][SERVICE_NAME_LENGTH];
char times[MAX_BOOKINGS][TIME_LENGTH];
char prices[MAX_BOOKINGS][PRICE_LENGTH];
int bookingCount = 0;  // Counter for the number of bookings

// Function declarations
bool addBooking();
void listAllBookings();
void loadBookingsFromFile();
void saveBookingsToFile();
bool searchBookingByPhone();
bool updateBooking();
bool deleteBooking();

int main() {
    int choice;

    loadBookingsFromFile(); // Load existing bookings from file

    while (1) {
        printf("\n===== Beauty Salon Booking System =====\n");
        printf("1. Add Booking\n");
        printf("2. List All Bookings\n");
        printf("3. Search Booking by Phone\n");
        printf("4. Update Booking\n");
        printf("5. Delete Booking\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (addBooking()) {
                    saveBookingsToFile(); // Save new booking to file
                }
                break;
            case 2:
                listAllBookings(); // Display all bookings
                break;
            case 3:
                searchBookingByPhone(); // Search booking by phone number
                break;
            case 4:
                if (updateBooking()) {
                    saveBookingsToFile(); // Save updated booking to file
                }
                break;
            case 5:
                if (deleteBooking()) {
                    saveBookingsToFile(); // Save changes after deleting a booking
                }
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0); // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


void listAllBookings() {
    if (bookingCount == 0) {// Check if there are any bookings
        printf("No bookings set.\n");
        return;
    }

    printf("Bookings:\n");
    printf("Name - Phone - Service - Time - Price\n");
    for (int i = 0; i < bookingCount; i++) {// Loop through all bookings and display them
        printf("%s - %s - %s - %s - %s\n", clientNames[i], clientPhones[i], services[i], times[i], prices[i]);
    }
}

bool addBooking() {
    if (bookingCount >= MAX_BOOKINGS) {// Check if maximum number of bookings has been reached
        printf("Maximum number of bookings reached.\n");
        return false;
    }

    int serviceType, specificService;// Variables to store user input
    printf("Select service type: 1. Hair, 2. Makeup, 3. Nails\n");
    scanf("%d", &serviceType);// Get user input for service type

    switch (serviceType) {
        case 1:// Get user input for specific service and store it in the services array
            printf("Hair services: 1. Consultation Long Hair (150), 2. Consultation Short Hair (75)\n");
            printf("3. Fair Long Hair (200), 4. Fair Short Hair (100)\n");
            scanf("%d", &specificService);// Get user input for specific service
            if (specificService == 1) {
                strcpy(services[bookingCount], "Consultation Long Hair");
                strcpy(prices[bookingCount], "150");
            } else if (specificService == 2) {
                strcpy(services[bookingCount], "Consultation Short Hair");
                strcpy(prices[bookingCount], "75");
            } else if (specificService == 3) {
                strcpy(services[bookingCount], "Fair Long Hair");
                strcpy(prices[bookingCount], "200");
            } else if (specificService == 4) {
                strcpy(services[bookingCount], "Fair Short Hair");
                strcpy(prices[bookingCount], "100");
            } else {
                printf("Invalid choice. Please try again.\n");
                return false;
            }
            break;
        case 2:// Get user input for specific service and store it in the services array
            printf("Makeup services: 1. Light Makeup (100), 2. Heavy Makeup (200)\n");
            scanf("%d", &specificService);
            if (specificService == 1) {// Get user input for specific service
                strcpy(services[bookingCount], "Light Makeup");
                strcpy(prices[bookingCount], "100");
            } else if (specificService == 2) {// Get user input for specific service
                strcpy(services[bookingCount], "Heavy Makeup");
                strcpy(prices[bookingCount], "200");
            } else {
                printf("Invalid choice. Please try again.\n");
                return false;
            }
            break;
        case 3:// Get user input for specific service and store it in the services array
            printf("Nail services: 1. Pedicure (50), 2. Manicure (50)\n");
            scanf("%d", &specificService);
            if (specificService == 1) {// Get user input for specific service and store it in the services array
                strcpy(services[bookingCount], "Pedicure");
                strcpy(prices[bookingCount], "50");
            } else if (specificService == 2) {
                strcpy(services[bookingCount], "Manicure");
                strcpy(prices[bookingCount], "50");
            } else {
                printf("Invalid choice. Please try again.\n");
                return false;
            }
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            return false;
    }

    printf("Enter client name: ");
    scanf("%s", clientNames[bookingCount]);

    printf("Enter client phone: ");
    scanf("%s", clientPhones[bookingCount]);

    printf("Enter booking time (HH:MM): ");
    scanf("%s", times[bookingCount]);

    bookingCount++;
    return true;
}
void saveBookingsToFile() {
    FILE *file = fopen(FILENAME, "w");// Open file for writing
    if (file == NULL) {// Check if file was opened successfully
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < bookingCount; i++) {// Loop through all bookings and write them to file
        fprintf(file, "%s,%s,%s,%s,%s\n", clientNames[i], clientPhones[i], services[i], times[i], prices[i]);
    }

    fclose(file);
}
bool searchBookingByPhone() {
    char phone[PHONE_LENGTH];
    printf("Enter phone number to search: ");
    scanf("%s", phone);

    bool found = false;// Variable to store whether a booking was found
    for (int i = 0; i < bookingCount; i++) {// Loop through all bookings and display the ones with the given phone number
        if (strcmp(clientPhones[i], phone) == 0) {// Check if the phone number matches
            printf("%s - %s - %s - %s - %s\n", clientNames[i], clientPhones[i], services[i], times[i], prices[i]);
            found = true;
        }
    }

    if (!found) {// Check if a booking was found
        printf("No booking found for this phone number.\n");
    }

    return found;
}
bool updateBooking() {
    char phone[PHONE_LENGTH];
    printf("Enter phone number to update: ");
    scanf("%s", phone);

    bool found = false;
    for (int i = 0; i < bookingCount; i++) {// Loop through all bookings and update the one with the given phone number
        if (strcmp(clientPhones[i], phone) == 0) {// Check if the phone number matches
            printf("Enter new booking time (HH:MM): ");
            scanf("%s", times[i]);// Get user input for new booking time
            found = true;
        }
    }

    if (!found) {
        printf("No booking found for this phone number.\n");
    }

    return found;
}

bool deleteBooking() {
    char phone[PHONE_LENGTH];
    printf("Enter phone number to delete: ");
    scanf("%s", phone);

    bool found = false;
    for (int i = 0; i < bookingCount; i++) {// Loop through all bookings and delete the one with the given phone number
        if (strcmp(clientPhones[i], phone) == 0) {// Check if the phone number matches
            for (int j = i; j < bookingCount - 1; j++) {// Loop through all bookings after the deleted one and move them one position back
                strcpy(clientNames[j], clientNames[j + 1]);// Move booking information one position back
                strcpy(clientPhones[j], clientPhones[j + 1]);// Move booking information one position back
                strcpy(services[j], services[j + 1]);// Move booking information one position back
                strcpy(times[j], times[j + 1]);       // Move booking information one position back
                strcpy(prices[j], prices[j + 1]);// Move booking information one position back
            }
            bookingCount--; // Decrease booking count
            found = true;
        }
    }

    if (!found) {
        printf("No booking found for this phone number.\n");
    }

    return found;
}

void loadBookingsFromFile() {
    FILE *file = fopen(FILENAME, "r");// Open file for reading
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");// Split line into tokens
        strcpy(clientNames[bookingCount], token);// Copy token to clientNames array

        token = strtok(NULL, ",");
        strcpy(clientPhones[bookingCount], token);

        token = strtok(NULL, ",");
        strcpy(services[bookingCount], token);

        token = strtok(NULL, ",");
        strcpy(times[bookingCount], token);

        token = strtok(NULL, ",");
        strcpy(prices[bookingCount], token);

        bookingCount++;
    }

    fclose(file);
}


