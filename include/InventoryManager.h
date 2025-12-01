#pragma once
#include "Product.h"
#include "Transaction.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <optional>

class InventoryManager {
public:
    InventoryManager() = default;
    ~InventoryManager() = default;

    // product operations
    bool addProduct(std::shared_ptr<Product> product);
    bool editProduct(int productId, const Product& newData);
    bool deleteProduct(int productId);
    std::optional<std::shared_ptr<Product>> getProduct(int id) const;
    std::vector<std::shared_ptr<Product>> listProducts() const;

    // transaction operations
    bool recordPurchase(const std::shared_ptr<Transaction>& purchase); // adds stock
    bool recordSale(const std::shared_ptr<Transaction>& sale); // reduces stock
    const std::vector<std::shared_ptr<Transaction>>& getTransactions() const;

    // analytics helpers
    double totalInventoryValue() const;
    int totalQuantityForProduct(int productId) const;

    // persistence helpers (DataManager will call)
    void clearAll();

private:
    std::unordered_map<int, std::shared_ptr<Product>> products;
    std::vector<std::shared_ptr<Transaction>> transactions;
};
