#pragma once
#include <string>
#include <ostream>

class Product {
public:
    Product() = default;
    Product(int id, std::string name, std::string category, double unitPrice, int qty);

    // getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getCategory() const;
    double getUnitPrice() const;
    int getQuantity() const;

    // behaviors
    void updateQuantity(int delta); // can increase or decrease
    double inventoryValue() const;

    // operators
    bool operator==(const Product& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Product& p);

private:
    int id{ 0 };
    std::string name;
    std::string category;
    double unitPrice{ 0.0 };
    int quantity{ 0 };

    // friend function example (access to private)
    friend double getUnitPrice(const Product& p);
};

double getUnitPrice(const Product& p);
