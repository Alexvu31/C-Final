#pragma once
#include <memory>
#include "Transaction.h"
#include "Product.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>


// Template analytics engine. T is the Transaction pointer type or Product pointer type usage.
template <typename T>
class Analytics {
public:
    // total sales across transactions (summing getTotalAmount)
    static double totalSales(const std::vector<std::shared_ptr<T>>& transactions) {
        double total = 0.0;
        for (auto const& t : transactions) total += t->getTotalAmount();
        return total;
    }

    // average transaction value
    static double averageTransactionValue(const std::vector<std::shared_ptr<T>>& transactions) {
        if (transactions.empty()) return 0.0;
        return totalSales(transactions) / static_cast<double>(transactions.size());
    }

    // highest and lowest-selling product (by quantity). Requires product id in transactions.
    // returns pair<productId_of_highest, productId_of_lowest>
    static std::pair<int, int> highestLowestSellingProduct(const std::vector<std::shared_ptr<T>>& transactions) {
        if (transactions.empty()) return { -1, -1 };
        std::unordered_map<int, int> qtyByProduct;
        for (auto const& t : transactions) {
            qtyByProduct[t->getProductId()] += t->getQuantity();
        }
        int highestId = -1, lowestId = -1;
        int highestQty = std::numeric_limits<int>::min();
        int lowestQty = std::numeric_limits<int>::max();
        for (auto const& kv : qtyByProduct) {
            if (kv.second > highestQty) { highestQty = kv.second; highestId = kv.first; }
            if (kv.second < lowestQty) { lowestQty = kv.second; lowestId = kv.first; }
        }
        return { highestId, lowestId };
    }
};
