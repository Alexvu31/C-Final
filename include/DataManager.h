#pragma once
#include "InventoryManager.h"
#include <string>

class DataManager {
public:
    // save/load as JSON file
    static bool saveAsJson(const InventoryManager& manager, const std::string& filepath);
    static bool loadFromJson(InventoryManager& manager, const std::string& filepath);
};
