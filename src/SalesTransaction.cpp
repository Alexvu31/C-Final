#include "SalesTransaction.h"

SalesTransaction::SalesTransaction(std::string id, std::string dateStr, int productId, int quantity, double unitPrice)
    : Transaction(std::move(id), std::move(dateStr), productId, quantity, unitPrice* quantity), unitPrice(unitPrice) {
}

double SalesTransaction::computeTotal() {
    totalAmount = unitPrice * static_cast<double>(quantity);
    return totalAmount;
}

double SalesTransaction::getUnitPrice() const {
    return unitPrice;
}
