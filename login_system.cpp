
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

const string FILE_NAME = "users.txt";

bool validUsername(const string& username)
{
    if (username.length() < 3 || username.length() > 20)
        return false;

    for (char c : username)
    {
        if (!((c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') || c == '_'))
            return false;
    }

    return true;
}

bool usernameExists(const string& username)
{
    ifstream file(FILE_NAME);
    string savedUser, savedPassword;

    while (file >> savedUser >> savedPassword)
    {
        if (savedUser == username)
            return true;
    }

    return false;
}

void registerUser()
{
    string username, password;

    cout << "\n--- Registration ---\n";
    cout << "Enter username: ";
    getline(cin, username);

    if (!validUsername(username))
    {
        cout << "Username must be 3-20 characters "
             << "using letters, digits or underscore.\n";
        return;
    }

    if (usernameExists(username))
    {
        cout << "Username already exists!\n";
        return;
    }

    cout << "Enter password (minimum 8 characters): ";
    getline(cin, password);

    if (password.length() < 8 || password.length() > 128)
    {
        cout << "Password must be 8-128 characters long.\n";
        return;
    }

    ofstream file(FILE_NAME, ios::app);

    if (!file)
    {
        cout << "Error: Could not save registration.\n";
        return;
    }

    // Demonstration only: do not use real passwords.
    file << username << ' ' << password << '\n';
    file.close();

    if (!file)
    {
        cout << "Error while saving user details.\n";
        return;
    }

    cout << "Registration successful!\n";
}

void loginUser()
{
    string username, password;
    string savedUser, savedPassword;

    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    ifstream file(FILE_NAME);

    if (!file)
    {
        cout << "No registered users found. Register first.\n";
        return;
    }

    while (file >> savedUser >> savedPassword)
    {
        if (savedUser == username && savedPassword == password)
        {
            cout << "Login successful! Welcome, "
                 << username << "!\n";
            return;
        }
    }

    cout << "Invalid username or password.\n";
}

int main()
{
    string choice;

    do
    {
        cout << "\n==============================\n";
        cout << " LOGIN & REGISTRATION SYSTEM\n";
        cout << "==============================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        getline(cin, choice);

        if (choice == "1")
            registerUser();
        else if (choice == "2")
            loginUser();
        else if (choice == "3")
            cout << "Thank you for using the system!\n";
        else
            cout << "Invalid choice. Enter 1, 2 or 3.\n";

    } while (choice != "3");

    return 0;
}
