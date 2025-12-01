#pragma once
#include "Transaction.h"

class PurchaseTransaction : public Transaction {
public:
    PurchaseTransaction() = default;
    PurchaseTransaction(std::string id, std::string dateStr, int productId, int quantity, double unitCost);

    double computeTotal() override; // total cost = unitCost * quantity
    double getUnitCost() const;

private:
    double unitCost{ 0.0 };
};
