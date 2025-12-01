#pragma once
#include <string>
#include <chrono>
#include <sstream>

class Transaction {
public:
    Transaction() = default;
    Transaction(std::string id, std::string dateStr, int productId, int quantity, double totalAmount);
    virtual ~Transaction() = default;

    const std::string& getTransactionId() const;
    const std::string& getDate() const;
    int getProductId() const;
    int getQuantity() const;
    double getTotalAmount() const;

    // Pure virtual: compute total (implemented in derived classes)
    virtual double computeTotal() = 0;

    // operator
    virtual std::string toString() const;

protected:
    std::string transactionId;
    std::string date;
    int productId{ 0 };
    int quantity{ 0 };
    double totalAmount{ 0.0 };
};
