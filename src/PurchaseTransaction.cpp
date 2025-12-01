#include "PurchaseTransaction.h"

PurchaseTransaction::PurchaseTransaction(std::string id, std::string dateStr, int productId, int quantity, double unitCost)
    : Transaction(std::move(id), std::move(dateStr), productId, quantity, unitCost* quantity), unitCost(unitCost) {
}

double PurchaseTransaction::computeTotal() {
    totalAmount = unitCost * static_cast<double>(quantity);
    return totalAmount;
}

double PurchaseTransaction::getUnitCost() const {
    return unitCost;
}
