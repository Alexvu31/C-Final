#include "InventoryManager.h"
#include "DataManager.h"
#include <iostream>

#ifdef USE_NANA
#include "GUI.h" 
#endif

int main() {
    InventoryManager manager;
    const std::string dataFile = "data/inventory.json";

    // try to load
    if (!DataManager::loadFromJson(manager, dataFile)) {
        std::cout << "No existing data loaded (file not found or invalid). Starting with empty inventory.\n";
    }
    else {
        std::cout << "Loaded inventory data from " << dataFile << "\n";
    }

#ifdef USE_NANA
    showMainWindow(manager);
#else
    // simple CLI fallback demo
    std::cout << "Nana GUI support not enabled. CLI demo:\n";
    auto p = std::make_shared<Product>(1, "Sample Product", "General", 9.99, 100);
    manager.addProduct(p);
    std::cout << "Products:\n";
    for (auto& prod : manager.listProducts()) std::cout << *prod << "\n";
#endif

    // save on exit
    if (!DataManager::saveAsJson(manager, dataFile)) {
        std::cerr << "Failed to save data to " << dataFile << "\n";
    }
    else {
        std::cout << "Saved data to " << dataFile << "\n";
    }
    return 0;
}
