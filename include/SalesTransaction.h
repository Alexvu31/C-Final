#pragma once
#include "Transaction.h"

class SalesTransaction : public Transaction {
public:
    SalesTransaction() = default;
    SalesTransaction(std::string id, std::string dateStr, int productId, int quantity, double unitPrice);

    double computeTotal() override; // total sales = unitPrice * quantity
    double getUnitPrice() const;

private:
    double unitPrice{ 0.0 };
};
