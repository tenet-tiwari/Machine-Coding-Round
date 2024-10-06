#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User {
protected:
    string userId;
    string username;
    string password;
public:
    User(string id, string uname, string pwd) : userId(id), username(uname), password(pwd) {}
    virtual void displayProfile() {
        cout << "User ID: " << userId << "\nUsername: " << username << endl;
    }
};

class Admin : public User {
public:
    Admin(string id, string uname, string pwd) : User(id, uname, pwd) {}
    
    void addMovie() {
        cout << "Movie added by Admin." << endl;
    }

    void removeMovie() {
        cout << "Movie removed by Admin." << endl;
    }
};

class Movie {
public:
    string movieId;
    string title;
    string genre;
    double rating;

    Movie(string id, string t, string g, double r) : movieId(id), title(t), genre(g), rating(r) {}

    void displayMovie() {
        cout << "Movie ID: " << movieId << "\nTitle: " << title << "\nGenre: " << genre << "\nRating: " << rating << endl;
    }
};

class Showtime {
public:
    string showtimeId;
    string movieId;
    string startTime;
    int availableSeats;

    Showtime(string sId, string mId, string sTime, int seats)
        : showtimeId(sId), movieId(mId), startTime(sTime), availableSeats(seats) {}

    void displayShowtime() {
        cout << "Showtime ID: " << showtimeId << "\nMovie ID: " << movieId << "\nStart Time: " << startTime << "\nAvailable Seats: " << availableSeats << endl;
    }
};

class Booking {
public:
    string bookingId;
    string userId;
    string showtimeId;
    vector<int> seatNumbers;
    double totalPrice;
    string status;

    Booking(string bId, string uId, string sId, vector<int> seats, double price)
        : bookingId(bId), userId(uId), showtimeId(sId), seatNumbers(seats), totalPrice(price), status("Booked") {}

    void displayBooking() {
        cout << "Booking ID: " << bookingId << "\nUser ID: " << userId << "\nShowtime ID: " << showtimeId << "\nTotal Price: " << totalPrice << "\nStatus: " << status << endl;
    }
};

class Ticket {
public:
    string ticketId;
    string bookingId;
    int seatNumber;

    Ticket(string tId, string bId, int seat) : ticketId(tId), bookingId(bId), seatNumber(seat) {}

    void displayTicket() {
        cout << "Ticket ID: " << ticketId << "\nBooking ID: " << bookingId << "\nSeat Number: " << seatNumber << endl;
    }
};

class Payment {
public:
    string paymentId;
    string userId;
    double amount;
    string status;

    Payment(string pId, string uId, double amt) : paymentId(pId), userId(uId), amount(amt), status("Success") {}

    void processPayment() {
        cout << "Payment of " << amount << " processed for user " << userId << endl;
    }

    void displayPayment() {
        cout << "Payment ID: " << paymentId << "\nUser ID: " << userId << "\nAmount: " << amount << "\nStatus: " << status << endl;
    }
};

class Seat {
public:
    int seatNumber;
    bool isAvailable;

    Seat(int num) : seatNumber(num), isAvailable(true) {}

    void markAsBooked() {
        isAvailable = false;
    }

    void markAsAvailable() {
        isAvailable = true;
    }

    void displaySeat() {
        cout << "Seat Number: " << seatNumber << "\nAvailable: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class CinemaHall {
public:
    string hallId;
    string name;
    vector<Seat> seats;

    CinemaHall(string id, string n, int totalSeats) : hallId(id), name(n) {
        for (int i = 1; i <= totalSeats; i++) {
            seats.push_back(Seat(i));
        }
    }

    void displayHall() {
        cout << "Cinema Hall ID: " << hallId << "\nName: " << name << "\nTotal Seats: " << seats.size() << endl;
    }
};

int main() {
    User customer("U001", "JohnDoe", "password123");
    Admin admin("A001", "AdminUser", "adminpass");

    Movie movie1("M001", "Inception", "Sci-Fi", 8.8);
    Showtime showtime1("S001", "M001", "10:00 AM", 50);

    vector<int> seats = {1, 2, 3};
    Booking booking1("B001", "U001", "S001", seats, 150.0);
    Payment payment1("P001", "U001", 150.0);

    customer.displayProfile();
    movie1.displayMovie();
    showtime1.displayShowtime();
    booking1.displayBooking();
    payment1.displayPayment();

    admin.addMovie();

    CinemaHall hall("H001", "Cinema 1", 100);
    hall.displayHall();

    return 0;
}
