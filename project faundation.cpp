#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class SignUpSystem {
private:
    std::unordered_map<std::string, std::string> users;

    void loadUsers() {
        std::ifstream infile("users.txt");
        if (!infile.is_open()) {
            return;
        }
        std::string username, password;
        while (infile >> username >> password) {
            users[username] = password;
        }
        infile.close();
    }

    void saveUsers() {
        std::ofstream outfile("users.txt");
        if (!outfile.is_open()) {
            std::cerr << "Error: could not open file for writing." << std::endl;
            return;
        }
        for (const auto& user : users) {
            outfile << user.first << " " << user.second << std::endl;
        }
        outfile.close();
    }

public:
    SignUpSystem() {
        loadUsers();
    }

    ~SignUpSystem() {
        saveUsers();
    }

    void signUp() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        if (users.find(username) != users.end()) {
            std::cout << "Username already taken. Please choose another one." << std::endl;
            return;
        }
        std::cout << "Enter password: ";
        std::cin >> password;

        users[username] = password;
        std::cout << "Registration successful!" << std::endl;
    }

    void signIn() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (users.find(username) != users.end() && users[username] == password) {
            std::cout << "Sign-in successful!" << std::endl;
        } else {
            std::cout << "Invalid username or password." << std::endl;
        }
    }
};

int main() {
    SignUpSystem system;
    int choice;

    while (true) {
        std::cout << "1. Sign Up\n2. Sign In\n3. Exit\nChoose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.signUp();
                break;
            case 2:
                system.signIn();
                break;
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}