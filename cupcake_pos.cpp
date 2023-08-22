//
// Created by Suswagatam Rong on 16/08/23.
// 

#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <random>

#define sysclear() printf("\033[H\033[J")

int returnRandomNumber();

class SaleItem {
public:
    SaleItem() :
        id(0), price(0.0), tax_rate(0.0), description(""), quantity(1) {
    }

    ~SaleItem() = default;

    bool create(std::string new_description) {
        // generate a random id between 1 - 100
        id = returnRandomNumber();
        description = std::move(new_description);
        return true;
    }

    // getters to access the private data members
    int getID() const {
        return id;
    }
    double getPrice() const {
        return price;
    }
    std::string getDescription() {
        return description;
    }
    int getQuantity() const {
        return quantity;
    }
    double getTaxRate() const {
        return tax_rate;
    }

    // setters to update/initialise the private data members
    void setPrice(double new_price) {
        this->price = new_price;
    }
    void setDescription(std::string new_description) {
        this->description = std::move(new_description);
    };
    void setQuantity(int new_quantity) {
        this->quantity = new_quantity;
    }
    void setTaxRate(double new_taxRate) {
        this->tax_rate = new_taxRate;
    }

    void purchaseItem (int purchase_quantity) {
        quantity = quantity - purchase_quantity;
    }

private:
    int id;
    double price;
    double tax_rate;
    std::string description;
    int quantity;
};

int main() {
    //srand(time(NULL));

    std::list<SaleItem> inventory;
    std::list<SaleItem>::iterator iter;
    inventory.clear();

    SaleItem test1;
    test1.create("Vanilla");
    test1.setPrice(4.95);
    test1.setQuantity(5);
    inventory.push_back(test1);

    std::string version = "v0.2.0";
    char user_choice;

    while (true) {
        sysclear();
        std::cout << "\nCupcake POS - " << version << std::endl;
        // std::cout << std::endl;

        // header
        std::cout << "ID | Description | Price | Quantity in stock" << std::endl;

        // printing value using iterator
        for (iter = inventory.begin(); iter != inventory.end(); iter++) {
            std::cout
                    << iter->getID() << " | "
                    << iter->getDescription() << " \t | "
                    << iter->getPrice() << "  | "
                    << iter->getQuantity() << std::endl;
        }

        // POS Menu
        std::cout << std::endl
                  << std::endl;
        std::cout << "[a]dd a new cupcake" << std::endl;
        std::cout << "[c]omplete a cupcake purchase" << std::endl;
        std::cout << "[u]pdate cupcake quantity" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "\nChoice: [acuq] - ";
        std::cin >> user_choice;

        if (user_choice == 'q') {
            std::cout << "\nHave a wonderful day!" << std::endl;
            break;
        }
        else if (user_choice == 'c') {
            int checkout_id;
            int checkout_quantity;
            double total_amount;
            double total_tax;

            std::cout << "Enter Cupcake ID to purchase: ";
            std::cin >> checkout_id;
            for (iter = inventory.begin(); iter != inventory.end(); iter++) {
                if (checkout_id == iter->getID()) {
                    std::cout << "Enter the quantity: ";
                    std::cin >> checkout_quantity;

                    if (checkout_quantity > iter->getQuantity()) {
                        std::cout << "Sorry, not enough in quantity." << std::endl;

                        // clears the buffer to the MAX
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get(); // waits for key press
                    }
                    else {
                        iter->purchaseItem(checkout_quantity);

                        total_amount = checkout_quantity * iter->getPrice();
                        total_tax = total_amount * (iter->getTaxRate() * 0.01);

                        std::cout << "Total amount: " << total_amount << std::endl;
                        std::cout << "Tax: " << total_tax << std::endl;

                        std::cout << "Total billing amount incl. tax: " << total_amount + total_tax << std::endl;

                        // clears the buffer to the MAX
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get(); // waits for key press
                    }
                    break;
                }
            }
        }
        else if (user_choice == 'u') {
            int stock_id;
            int stock_quantity;

            std::cout << "Enter Cupcake ID to update quantity: ";
            std::cin >> stock_id;
            for (iter = inventory.begin(); iter != inventory.end(); iter++) {
                if (stock_id == iter->getID()) {
                    std::cout << "Enter new quantity: ";
                    std::cin >> stock_quantity;

                    iter->setQuantity(stock_quantity);
                    break;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}

int returnRandomNumber() {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 100);

    // Use distrib to transform the random unsigned int
    // generated by gen into an int in [1, 100]
    return distrib(gen);
}