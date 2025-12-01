#include "InventoryManager.h"
#include <algorithm>

bool InventoryManager::addProduct(std::shared_ptr<Product> product) {
    if (!product) return false;
    int id = product->getId();
    if (products.find(id) != products.end()) return false; // already exists
    products[id] = std::move(product);
    return true;
}

bool InventoryManager::editProduct(int productId, const Product& newData) {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    // replace values (maintain pointer)
    it->second->updateQuantity(newData.getQuantity() - it->second->getQuantity());
    // other fields need to be replaced (no setters provided, so recreate)
    it->second = std::make_shared<Product>(newData);
    return true;
}

bool InventoryManager::deleteProduct(int productId) {
    auto it = products.find(productId);
    if (it == products.end()) return false;
    products.erase(it);
    return true;
}

std::optional<std::shared_ptr<Product>> InventoryManager::getProduct(int id) const {
    auto it = products.find(id);
    if (it == products.end()) return std::nullopt;
    return it->second;
}

std::vector<std::shared_ptr<Product>> InventoryManager::listProducts() const {
    std::vector<std::shared_ptr<Product>> out;
    out.reserve(products.size());
    for (const auto& kv : products) out.push_back(kv.second);
    return out;
}

bool InventoryManager::recordPurchase(const std::shared_ptr<Transaction>& purchase) {
    if (!purchase) return false;
    // increase product quantity
    int pid = purchase->getProductId();
    auto it = products.find(pid);
    if (it == products.end()) return false;
    it->second->updateQuantity(purchase->getQuantity());
    transactions.push_back(purchase);
    return true;
}

bool InventoryManager::recordSale(const std::shared_ptr<Transaction>& sale) {
    if (!sale) return false;
    int pid = sale->getProductId();
    auto it = products.find(pid);
    if (it == products.end()) return false;
    if (it->second->getQuantity() < sale->getQuantity()) {
        // not enough stock
        return false;
    }
    it->second->updateQuantity(-sale->getQuantity());
    transactions.push_back(sale);
    return true;
}

const std::vector<std::shared_ptr<Transaction>>& InventoryManager::getTransactions() const {
    return transactions;
}

double InventoryManager::totalInventoryValue() const {
    double total = 0.0;
    for (auto const& kv : products) total += kv.second->inventoryValue();
    return total;
}

int InventoryManager::totalQuantityForProduct(int productId) const {
    auto it = products.find(productId);
    if (it == products.end()) return 0;
    return it->second->getQuantity();
}

void InventoryManager::clearAll() {
    products.clear();
    transactions.clear();
}
