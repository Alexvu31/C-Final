#include "DataManager.h"
#include "Product.h"
#include "PurchaseTransaction.h"
#include "SalesTransaction.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>        // for time, localtime
#include <memory>       // for shared_ptr
#include <iostream>     // (optional, for debug)


using json = nlohmann::json;

static std::string currentDateString() {
    // minimal date string; production code might format properly
    std::time_t t = std::time(nullptr);
    char buf[64];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t))) return { buf };
    return {};
}

bool DataManager::saveAsJson(const InventoryManager& manager, const std::string& filepath) {
    json j;
    // products
    j["products"] = json::array();
    for (auto const& p : manager.listProducts()) {
        json pj;
        pj["id"] = p->getId();
        pj["name"] = p->getName();
        pj["category"] = p->getCategory();
        pj["unitPrice"] = p->getUnitPrice();
        pj["quantity"] = p->getQuantity();
        j["products"].push_back(pj);
    }

    j["transactions"] = json::array();
    for (auto const& t : manager.getTransactions()) {
        json tj;
        tj["transactionId"] = t->getTransactionId();
        tj["date"] = t->getDate();
        tj["productId"] = t->getProductId();
        tj["quantity"] = t->getQuantity();
        tj["totalAmount"] = t->getTotalAmount();
        // for type info, try dynamic cast
        if (dynamic_cast<PurchaseTransaction*>(t.get())) tj["type"] = "purchase";
        else if (dynamic_cast<SalesTransaction*>(t.get())) tj["type"] = "sale";
        else tj["type"] = "unknown";
        j["transactions"].push_back(tj);
    }

    std::ofstream ofs(filepath);
    if (!ofs) return false;
    ofs << j.dump(4);
    return true;
}

bool DataManager::loadFromJson(InventoryManager& manager, const std::string& filepath) {
    std::ifstream ifs(filepath);
    if (!ifs) return false;
    json j;
    ifs >> j;

    manager.clearAll();

    if (j.contains("products")) {
        for (auto& pj : j["products"]) {
            int id = pj.value("id", 0);
            std::string name = pj.value("name", "");
            std::string category = pj.value("category", "");
            double unitPrice = pj.value("unitPrice", 0.0);
            int qty = pj.value("quantity", 0);
            auto p = std::make_shared<Product>(id, name, category, unitPrice, qty);
            manager.addProduct(p);
        }
    }

    if (j.contains("transactions")) {
        for (auto& tj : j["transactions"]) {
            std::string type = tj.value("type", "sale");
            std::string tid = tj.value("transactionId", "");
            std::string date = tj.value("date", "");
            int pid = tj.value("productId", 0);
            int qty = tj.value("quantity", 0);
            double total = tj.value("totalAmount", 0.0);

            if (type == "purchase") {
                double unitCost = (qty != 0) ? (total / qty) : 0.0;
                auto pt = std::make_shared<PurchaseTransaction>(tid, date, pid, qty, unitCost);
                manager.recordPurchase(pt);
            }
            else {
                double unitPrice = (qty != 0) ? (total / qty) : 0.0;
                auto st = std::make_shared<SalesTransaction>(tid, date, pid, qty, unitPrice);
                manager.recordSale(st);
            }
        }
    }

    return true;
}
