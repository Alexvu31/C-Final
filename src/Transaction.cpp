#include "Transaction.h"

Transaction::Transaction(std::string id, std::string dateStr, int productId, int quantity, double totalAmount)
    : transactionId(std::move(id)), date(std::move(dateStr)), productId(productId), quantity(quantity), totalAmount(totalAmount) {
}

const std::string& Transaction::getTransactionId() const { return transactionId; }
const std::string& Transaction::getDate() const { return date; }
int Transaction::getProductId() const { return productId; }
int Transaction::getQuantity() const { return quantity; }
double Transaction::getTotalAmount() const { return totalAmount; }

std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "Transaction[ID=" << transactionId << ", Date=" << date << ", ProductID=" << productId
        << ", Quantity=" << quantity << ", Total=" << totalAmount << "]";
    return oss.str();
}
