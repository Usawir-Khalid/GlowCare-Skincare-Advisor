#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Login System
class LoginSystem {
protected:
    string username, password;

public:
    bool registerUser() {
        cout << "Choose a username: ";
        getline(cin, username);
        cout << "Choose a password: ";
        getline(cin, password);

        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();
            cout << "? Registration successful!\n";
            return true;
        }
        cout << "? Registration failed.\n";
        return false;
    }

    bool loginUser() {
        cout << "Enter your username: ";
        getline(cin, username);
        cout << "Enter your password: ";
        getline(cin, password);

        ifstream file("users.txt");
        string line;
        bool found = false;

        while (getline(file, line)) {
            size_t spacePos = line.find(' ');
            if (spacePos != string::npos) {
                string u = line.substr(0, spacePos);
                string p = line.substr(spacePos + 1);
                if (u == username && p == password) {
                    found = true;
                    break;
                }
            }
        }
        file.close();

        if (found) {
            cout << "? Login successful! Welcome " << username << "!\n";
            return true;
        } else {
            cout << "? Invalid username or password.\n";
            return false;
        }
    }
};

// Skincare Advisor Class
class User {
protected:
    string name;
    int age;
    string skinType;
    bool usesSunscreen;
    string diet;
    string activityLevel;

public:
    void getUserInfo() {
        cout << "\nEnter your full name: ";
        getline(cin, name);
        cout << "Enter your age: ";
        cin >> age;
        cin.ignore(); // clear newline
    }

    virtual void askQuestions() = 0;
    virtual void giveRecommendations() = 0;
};

class SkinCareAdvisor : public User {
public:
    void askQuestions() override {
        cout << "\nWhat is your skin type (oily/dry/combination/sensitive)? ";
        getline(cin, skinType);

        cout << "Do you use sunscreen daily? (yes/no): ";
        string input;
        getline(cin, input);
        usesSunscreen = (input == "yes");

        cout << "Describe your diet (balanced/junk/vegetarian): ";
        getline(cin, diet);

        cout << "How active are you daily? (low/medium/high): ";
        getline(cin, activityLevel);
    }

    void giveRecommendations() override {
        cout << "\n===== Skincare & Health Recommendations for " << name << " =====\n\n";

        cout << "[ Diet Tips ]\n";
        if (diet == "junk") {
            cout << "• Reduce fast food and sugary drinks. Add greens, berries, and omega-3-rich foods like fish and walnuts.\n";
        } else if (diet == "vegetarian") {
            cout << "• Include vitamin B12, protein (lentils, tofu), and healthy fats (avocados, seeds).\n";
        } else {
            cout << "• Keep your balanced diet! Include antioxidants (e.g., green tea) for glowing skin.\n";
        }

        cout << "\n[ Lifestyle Tips ]\n";
        if (activityLevel == "low") {
            cout << "• Try light workouts, yoga, or walking daily. It boosts circulation and skin glow.\n";
        } else {
            cout << "• Great! Staying active keeps your skin and body fresh.\n";
        }

        cout << "\n[ Sunscreen Use ]\n";
        if (!usesSunscreen) {
            cout << "• Start using SPF 30+ sunscreen daily. It prevents dark spots, wrinkles, and skin cancer.\n";
        } else {
            cout << "• Continue using sunscreen. Reapply every 2-3 hours when outdoors.\n";
        }

        cout << "\n[ Skincare Routine ]\n";
        if (skinType == "oily") {
            cout << "• Use gel-based cleanser (with salicylic acid).\n• Water-based moisturizer.\n• Clay mask twice a week.\n";
        } else if (skinType == "dry") {
            cout << "• Hydrating cleanser (with glycerin).\n• Thick cream moisturizers.\n• Use facial oils at night.\n";
        } else if (skinType == "combination") {
            cout << "• Gentle foaming cleanser.\n• Gel for oily areas, cream for dry parts.\n• Exfoliate 1-2 times a week.\n";
        } else if (skinType == "sensitive") {
            cout << "• Fragrance-free products.\n• Avoid alcohol-based toners.\n• Use aloe vera or chamomile.\n";
        } else {
            cout << "• Unknown skin type. Please try again.\n";
        }

        cout << "\n[ Extra Tips for Glowing Skin ]\n";
        cout << "• Drink 8-10 glasses of water.\n• Sleep 7-8 hours.\n• Reduce stress.\n• Clean pillowcases.\n• Be consistent.\n";
        cout << "=============================================\n";
    }
};

// Main Program
int main() {
    LoginSystem login;
    int choice;

    cout << "=== Welcome to GlowCare Skincare Advisor ===\n";
    cout << "1. Register\n2. Login\nEnter your choice: ";
    cin >> choice;
    cin.ignore();

    bool proceed = false;
    if (choice == 1) {
        proceed = login.registerUser();
    } else if (choice == 2) {
        proceed = login.loginUser();
    } else {
        cout << "? Invalid choice.\n";
        return 0;
    }

    if (proceed) {
        SkinCareAdvisor advisor;
        advisor.getUserInfo();
        advisor.askQuestions();
        advisor.giveRecommendations();
    }

    return 0;
}
