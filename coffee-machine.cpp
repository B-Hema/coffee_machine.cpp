#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Class representing a menu item with its properties
class MenuItem {
public:
    string name;     // Name of the menu item
    double price;    // Price of the menu item
    int water;       // Water required (in ml)
    int milk;        // Milk required (in ml)
    int coffee;      // Coffee required (in gm)

    // Constructor to initialize menu item properties
    MenuItem(string n, double p, int w, int m, int c) {
        name = n;
        price = p;
        water = w;
        milk = m;
        coffee = c;
    }
};

// Class representing the coffee menu
class Menu {
public:
    MenuItem espresso = MenuItem("Espresso", 25, 100, 150, 25);
    MenuItem latte = MenuItem("Latte", 15, 100, 150, 30);
    MenuItem cappuccino = MenuItem("Cappuccino", 30, 100, 150, 30);
};

// Class representing the coffee maker with resources
class CoffeeMaker {
public:
    int Water;    // Available water
    int Milk;     // Available milk
    int Coffee;   // Available coffee
    double money; // Total money received

    // Constructor to initialize resources
    CoffeeMaker(int W, int M, int C, double p) {
        Water = W;
        Milk = M;
        Coffee = C;
        money = p;
    }

    // Method to make coffee
    bool makeCoffee(MenuItem item, int quantity) {
        if ((Water >= item.water * quantity) && 
            (Milk >= item.milk * quantity) && 
            (Coffee >= item.coffee * quantity)) {
            cout << "Making " << quantity << " " << item.name << "(s)..." << endl;
            cout << "Here are your " << quantity << " " << item.name << "(s)... Enjoy!" << endl;
            return true; // Coffee made successfully
        }
        cout << "Insufficient resources to make " << item.name << endl;
        return false; // Coffee could not be made
    }
};

// Class representing the money handling machine
class MoneyMachine {
public:
    double total; // Total money collected

    // Constructor to initialize total money
    MoneyMachine(double p) {
        total = p;
    }

    // Method to process coins
    bool processCoins(MenuItem item, int quantity) {
        double totalMoney = 0.0;
        double requiredAmount = item.price * quantity; // Calculate the total price

        // Inform the customer about the required amount
        cout << "The price for " << quantity << " " << item.name << "(s) is ₹" << requiredAmount << endl;

        // Display coin options
        cout << "\nPlease choose which coins to insert:" << endl;
        cout << "1. ₹1" << endl;
        cout << "2. ₹2" << endl;
        cout << "3. ₹5" << endl;
        cout << "4. ₹10" << endl;

        // Loop to accept coins until the required amount is met
        while (totalMoney < requiredAmount) {
            cout << "\nYou currently have ₹" << totalMoney << ". You need ₹" << (requiredAmount - totalMoney) << " more." << endl;
            cout << "Select a coin to insert (1-4): ";
            int option;
            cin >> option;

            int quantity; // Variable to hold the number of coins
            switch (option) {
                case 1:
                    cout << "How many ₹1 coins? ";
                    cin >> quantity;
                    totalMoney += quantity * 1.0;
                    break;
                case 2:
                    cout << "How many ₹2 coins? ";
                    cin >> quantity;
                    totalMoney += quantity * 2.0;
                    break;
                case 3:
                    cout << "How many ₹5 coins? ";
                    cin >> quantity;
                    totalMoney += quantity * 5.0;
                    break;
                case 4:
                    cout << "How many ₹10 coins? ";
                    cin >> quantity;
                    totalMoney += quantity * 10.0;
                    break;
                default:
                    cout << "Invalid option. Please select a valid coin." << endl;
                    break;
            }
        }

        cout << "Total = ₹" << totalMoney << endl;

        // If overpayment occurs, calculate and provide change
        if (totalMoney > requiredAmount) {
            double change = totalMoney - requiredAmount;
            cout << "Here is ₹" << setprecision(2) << fixed << change << " in change." << endl;
        }

        total += requiredAmount;  // Add the price to total money collected
        return true; // Coins processed successfully
    }
};

// Class to manage and check available resources
class SufficientResources {
public:
    int Water;    // Available water
    int Milk;     // Available milk
    int Coffee;   // Available coffee
    double money; // Total money collected

    // Constructor to initialize resources
    SufficientResources(int W, int M, int C, double p) {
        Water = W;
        Milk = M;
        Coffee = C;
        money = p;
    }

    // Method to check and update resources
    bool satisfyResources(MenuItem item, int quantity) {
        if ((Water >= item.water * quantity) && 
            (Milk >= item.milk * quantity) && 
            (Coffee >= item.coffee * quantity)) {
            // Deduct resources if available
            Water -= item.water * quantity;
            Milk -= item.milk * quantity;
            Coffee -= item.coffee * quantity;
            money += item.price * quantity; // Update total money
            cout << "There are sufficient resources for " << quantity << " " << item.name << "(s)" << endl;
            return true; // Resources are sufficient
        } else {
            cout << "Sorry, there are insufficient resources for " << item.name << endl;
            cout << "Can't make your " << item.name << endl;
            return false; // Resources are insufficient
        }
    }
};

// Main function to drive the coffee machine program
int main() {
    Menu menu; // Create a menu
    CoffeeMaker coffeeMaker(5000, 4000, 1000, 0.0); // Initialize coffee maker with resources
    MoneyMachine moneyMachine(0.0); // Initialize money machine
    SufficientResources sufficientResources(5000, 4000, 1000, 0.0); // Initialize resource manager

    string choice; // User's coffee choice
    char anotherOrder; // To check if user wants another coffee
    char quitChoice; // To check if user wants to quit

    cout << "Welcome to the coffee machine!" << endl;

    // Main loop for the coffee ordering process
    do {
        // Display the coffee menu
        cout << "\n      Coffee Menu   " << endl;
        cout << "Coffee Name  |  Price" << endl;
        cout << "-------------------------" << endl;
        cout << "Espresso     |  ₹25" << endl;
        cout << "Latte        |  ₹15" << endl;
        cout << "Cappuccino   |  ₹30" << endl;

        cout << "What would you like? (espresso/latte/cappuccino/off/report): ";
        cin >> choice;

        // Handle user commands
        if (choice == "off") {
            cout << "Shutting down..." << endl;
            break; // Exit the program
        } else if (choice == "report") {
            // Display available resources and total money collected
            cout << "Water: " << sufficientResources.Water << "ml" << endl;
            cout << "Milk: " << sufficientResources.Milk << "ml" << endl;
            cout << "Coffee: " << sufficientResources.Coffee << "gm" << endl;
            cout << "Money: ₹" << setprecision(2) << fixed << moneyMachine.total << endl;
        } else {
            // Handle coffee ordering
            int quantity;
            if (choice == "espresso") {
                cout << "How many would you like? (1-5): ";
                cin >> quantity;
            } else if (choice == "latte") {
                cout << "How many would you like? (1-5): ";
                cin >> quantity;
            } else if (choice == "cappuccino") {
                cout << "How many would you like? (1-5): ";
                cin >> quantity;
            } else {
                cout << "Invalid choice. Please try again." << endl;
                continue; // Restart the loop for valid input
            }

            // Validate quantity
            if (quantity < 1 || quantity > 5) {
                cout << "Invalid quantity. Please enter a number between 1 and 5." << endl;
                continue; // Restart the loop for valid input
            }

            // Check resources and process payment
            if (choice == "espresso") {
                if (sufficientResources.satisfyResources(menu.espresso, quantity)) {
                    if (moneyMachine.processCoins(menu.espresso, quantity)) {
                        coffeeMaker.makeCoffee(menu.espresso, quantity);
                    }
                }
            } else if (choice == "latte") {
                if (sufficientResources.satisfyResources(menu.latte, quantity)) {
                    if (moneyMachine.processCoins(menu.latte, quantity)) {
                        coffeeMaker.makeCoffee(menu.latte, quantity);
                    }
                }
            } else if (choice == "cappuccino") {
                if (sufficientResources.satisfyResources(menu.cappuccino, quantity)) {
                    if (moneyMachine.processCoins(menu.cappuccino, quantity)) {
                        coffeeMaker.makeCoffee(menu.cappuccino, quantity);
                    }
                }
            }
        }

        // Ask the customer if they want another coffee or to quit
        cout << "\nDo you want another coffee? (y/n): ";
        cin >> anotherOrder;

        if (anotherOrder == 'n' || anotherOrder == 'N') {
            cout << "Do you want to quit? (y/n): ";
            cin >> quitChoice;
        }

    } while (anotherOrder == 'y' || anotherOrder == 'Y' || (anotherOrder == 'n' && quitChoice == 'n'));

    cout << "Thank you for choosing the coffee machine. Bye!" << endl;
    cout << "See you again :)" << endl;

    return 0; // End of the program
}
                   



    
   
       
