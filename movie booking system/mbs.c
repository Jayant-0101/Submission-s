#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_MOVIES 3
#define MAX_SEATS 50

// Structure to hold movie details
struct Movie {
    int movieID;
    char title[50];
    int availableSeats;
};

// Structure to hold booking details
struct Booking {
    int bookingID;
    int movieID;
    char customerName[50];
    int seatsBooked;
};

// Function prototypes
void displayMovies(struct Movie movies[], int count);
void bookTickets(struct Movie movies[], int count, struct Booking bookings[], int *bookingCount);
void viewBookings(struct Booking bookings[], int count);
void displayMenu();

int main() {
    struct Movie movies[MAX_MOVIES] = {
        {1, "Born to shine tour", 50},
        {2, "Dil-iluminati tour", 50},
        {3, "Animal", 50}
    };
    struct Booking bookings[MAX_SEATS];
    int bookingCount = 0;
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMovies(movies, MAX_MOVIES);
                break;
            case 2:
                bookTickets(movies, MAX_MOVIES, bookings, &bookingCount);
                break;
            case 3:
                viewBookings(bookings, bookingCount);
                break;
            case 4:
                printf("Exiting the program. Thank you for using the Movie Ticket Booking System!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\n=== Movie Ticket Booking System ===\n");
    printf("1. View Available Movies\n");
    printf("2. Book Tickets\n");
    printf("3. View Bookings\n");
    printf("4. Exit\n");
}

// Function to display available movies
void displayMovies(struct Movie movies[], int count) {
    printf("\nAvailable Movies:\n");
    printf("ID\tTitle\t\tAvailable Seats\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%d\n", movies[i].movieID, movies[i].title, movies[i].availableSeats);
    }
}

// Function to book tickets
void bookTickets(struct Movie movies[], int count, struct Booking bookings[], int *bookingCount) {
    int movieID, seats;
    char name[50];
    int found = 0;

    printf("\nEnter the Movie ID to book: ");
    scanf("%d", &movieID);
    getchar(); // To clear the newline character from the buffer

    // Find the movie by ID
    for (int i = 0; i < count; i++) {
        if (movies[i].movieID == movieID) {
            found = 1;
            printf("Enter your name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0; // Remove the newline character

            printf("Enter number of seats to book: ");
            scanf("%d", &seats);

            if (seats > movies[i].availableSeats) {
                printf("Not enough seats available! Please try again.\n");
                return;
            }

            // Update the movie's available seats
            movies[i].availableSeats -= seats;

            // Add booking details
            bookings[*bookingCount].bookingID = *bookingCount + 1;
            bookings[*bookingCount].movieID = movieID;
            strcpy(bookings[*bookingCount].customerName, name);
            bookings[*bookingCount].seatsBooked = seats;
            (*bookingCount)++;

            printf("Tickets booked successfully! Booking ID: %d\n", *bookingCount);
            return;
        }
    }

    if (!found) {
        printf("Movie not found! Please try again.\n");
    }
}

// Function to view bookings
void viewBookings(struct Booking bookings[], int count) {
    if (count == 0) {
        printf("\nNo bookings found!\n");
        return;
    }

    printf("\nBookings:\n");
    printf("ID\tMovie ID\tCustomer Name\tSeats Booked\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t\t%s\t\t%d\n", bookings[i].bookingID, bookings[i].movieID, bookings[i].customerName, bookings[i].seatsBooked);
    }
}
