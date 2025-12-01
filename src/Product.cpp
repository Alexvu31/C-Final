#include "Product.h"

Product::Product(int id, std::string name, std::string category, double unitPrice, int qty)
    : id(id), name(std::move(name)), category(std::move(category)), unitPrice(unitPrice), quantity(qty) {
}

int Product::getId() const { return id; }
const std::string& Product::getName() const { return name; }
const std::string& Product::getCategory() const { return category; }
double Product::getUnitPrice() const { return unitPrice; }
int Product::getQuantity() const { return quantity; }

void Product::updateQuantity(int delta) {
    quantity += delta;
    if (quantity < 0) quantity = 0; // guard - no negative stock
}

double Product::inventoryValue() const {
    return unitPrice * static_cast<double>(quantity);
}

bool Product::operator==(const Product& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << "Product[ID=" << p.id << ", Name=\"" << p.name
        << "\", Category=\"" << p.category
        << "\", UnitPrice=" << p.unitPrice
        << ", Quantity=" << p.quantity << "]";
    return os;
}

double getUnitPrice(const Product& p) {
    return p.unitPrice;
}
