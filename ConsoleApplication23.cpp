#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

class ExistLoginException : public exception {
public:
    const char* what() const noexcept override {
        return "This login already exists!";
    }
};

class WrongPasswordLengthException : public exception {
public:
    const char* what() const noexcept override {
        return "Password length must be greater than 7 characters!";
    }
};

class FormatPasswordException : public exception {
public:
    const char* what() const noexcept override {
        return "Password must contain at least one digit, one uppercase letter, and one lowercase letter!";
    }
};

class InvalidLoginException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid login entered!";
    }
};

class InvalidPasswordException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid password entered!";
    }
};

class User_Account {
public:
    string password, login;

    User_Account(string login, string password) : login(login), password(password) {}

    string getLogin() const {
        return login;
    }

    string getPassword() const {
        return password;
    }
};

class SocialNetwork {
private:
    vector<User_Account> accounts;

public:
    void registerUser(string login, string pass) {
        try {
            for (auto& u : accounts) {
                if (u.getLogin() == login) {
                    throw ExistLoginException();
                }
            }

            if (pass.length() < 7) {
                throw WrongPasswordLengthException();
            }

            bool hasDigit = false, hasLower = false, hasUpper = false;
            for (char c : pass) {
                if (isdigit(c)) hasDigit = true;
                if (islower(c)) hasLower = true;
                if (isupper(c)) hasUpper = true;
            }

            if (!(hasDigit && hasLower && hasUpper)) {
                throw FormatPasswordException();
            }

            User_Account newUser(login, pass);
            accounts.push_back(newUser);
            cout << "User registered successfully!" << endl;

        }
        catch (const ExistLoginException& e) {
            cout << e.what() << endl;
        }
        catch (const WrongPasswordLengthException& e) {
            cout << e.what() << endl;
        }
        catch (const FormatPasswordException& e) {
            cout << e.what() << endl;
        }
    }

    void loginUser(string login, string pass) {
        try {
            bool userFound = false;
            for (auto& u : accounts) {
                if (u.getLogin() == login) {
                    userFound = true;
                    if (u.getPassword() == pass) {
                        cout << "Login successful!" << endl;
                        return;
                    }
                    else {
                        throw InvalidPasswordException();
                    }
                }
            }
            if (!userFound) {
                throw InvalidLoginException();
            }
        }
        catch (const InvalidLoginException& e) {
            cout << e.what() << endl;
        }
        catch (const InvalidPasswordException& e) {
            cout << e.what() << endl;
        }
    }
};

int main() {
    SocialNetwork sn;

    sn.registerUser("user1", "Password123");
    sn.registerUser("user2", "1234abcD");
    sn.registerUser("user1", "newPassword");

    sn.loginUser("user1", "Password123");
    sn.loginUser("user1", "wrongPassword");
    sn.loginUser("user3", "Password123");

    return 0;
}
