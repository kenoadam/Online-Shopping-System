#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include <limits>

using namespace std;

// Used to ensure stock updates are thread-safe
mutex stockMutex;

// Represents an individual product
class Product {
private:
    string name;
    string description;
    double price;
    int stock;

public:
    Product(string n, string d, double p, int s)
        : name(n), description(d), price(p), stock(s) {}

    string getName() { return name; }
    double getPrice() { return price; }

    void describe() {
        cout << name << " - " << description
             << " ($" << price << "), In stock: " << stock << endl;
    }

    bool reduceStock(int qty) {
        lock_guard<mutex> lock(stockMutex);
        if (qty <= stock) {
            stock -= qty;
            return true;
        }
        return false;
    }

    int getStock() {
        lock_guard<mutex> lock(stockMutex);
        return stock;
    }
};

// Manages a user's cart and the items inside it
class ShoppingCart {
private:
    map<Product*, int> items;

public:
    void addProduct(Product* product, int qty) {
        if (product->getStock() >= qty) {
            items[product] += qty;
            cout << qty << " x " << product->getName()
                 << " added to cart.\n";
        } else {
            cout << "Not enough stock for "
                 << product->getName() << ".\n";
        }
    }

    double getTotal() {
        double total = 0;
        for (auto& item : items) {
            total += item.first->getPrice() * item.second;
        }
        return total;
    }

    void checkout(double discountRate) {
        cout << "\n--- Checkout Summary ---\n";
        for (auto& item : items) {
            cout << item.second << " x " << item.first->getName()
                 << " @ $" << item.first->getPrice() << " each\n";

            if (!item.first->reduceStock(item.second)) {
                cout << "Error: Could not update stock for "
                     << item.first->getName() << endl;
            }
        }
        double total = getTotal();
        double discount = total * discountRate;
        double finalTotal = total - discount;
        cout << "Subtotal: $" << total << endl;
        cout << "Discount: -$" << discount << endl;
        cout << "Total Due: $" << finalTotal << endl;
        cout << "Thank you for your purchase!\n";
    }
};

// Base class for all users
class User {
protected:
    string name;
    ShoppingCart cart;

public:
    User(string n) : name(n) {}

    virtual void applyDiscountAndCheckout() {
        cart.checkout(0.0);  // No discount
    }

    void addToCart(Product* product, int qty) {
        cart.addProduct(product, qty);
    }

    virtual ~User() {}
};

// Premium user gets 10% discount
class PremiumUser : public User {
public:
    PremiumUser(string n) : User(n) {}

    void applyDiscountAndCheckout() override {
        cart.checkout(0.10);
    }
};

// VIP user gets 20% discount
class VIPUser : public User {
public:
    VIPUser(string n) : User(n) {}

    void applyDiscountAndCheckout() override {
        cart.checkout(0.20);
    }
};

// Displays product list and handles user selections
void displayMenu(const vector<Product>& products) {
    cout << "\n--- Product Menu ---\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". ";
        products[i].describe();
    }
    cout << products.size() + 1 << ". Checkout\n";
}

// Simulates a full interactive session
void userSession(User* user, vector<Product>& products) {
    while (true) {
        displayMenu(products);
        cout << "\nEnter the number of the product to add to your cart: ";
        int choice;
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > products.size() + 1) {
            cout << "Invalid input. Please try again.\n";
            cin.clear(); // reset fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            continue;
        }

        if (choice == products.size() + 1) {
            string confirm;
            cout << "Would you like to proceed to checkout? (yes/no): ";
            cin >> confirm;
            if (confirm == "yes") {
                user->applyDiscountAndCheckout();
                break;
            } else {
                continue;
            }
        }

        int qty;
        cout << "Enter quantity: ";
        cin >> qty;

        if (qty > 0) {
            user->addToCart(&products[choice - 1], qty);
        } else {
            cout << "Quantity must be positive.\n";
        }
    }
}

int main() {
    // Create sample products
    vector<Product> catalog = {
        Product("Coffee Maker", "12-cup drip brewer", 79.99, 10),
        Product("Toaster", "4-slice with defrost", 49.99, 5),
        Product("Electric Kettle", "1.7L fast boil", 39.99, 8)
    };

    // Choose user type
    cout << "Welcome to the Online Shopping System!\n";
    cout << "Enter your name: ";
    string name;
    cin.ignore(); // clear newline from previous input
    getline(cin, name);

    cout << "Select user type:\n1. Regular\n2. Premium\n3. VIP\nChoice: ";
    int type;
    cin >> type;

    User* user;
    if (type == 2) {
        user = new PremiumUser(name);
    } else if (type == 3) {
        user = new VIPUser(name);
    } else {
        user = new User(name);
    }

    // Simulate shopping session
    userSession(user, catalog);

    delete user;
    return 0;
}
