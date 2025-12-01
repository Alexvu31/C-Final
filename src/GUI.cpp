
#include "PurchaseTransaction.h"
#include "InventoryManager.h"
#include "DataManager.h"
#include "GUI.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/menu.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/place.hpp>

using namespace nana;

void showMainWindow(InventoryManager& manager) {
    form fm{ API::make_center(800, 600) };
    fm.caption("Inventory Management System");

    // Menubar
    menubar menubar_{ fm };
    menubar_.push_back("Products");
    menubar_.at(0).append("Add Product");
    menubar_.at(0).append("Edit Product");

    menubar_.push_back("Transactions");
    menubar_.at(1).append("Record Purchase");
    menubar_.at(1).append("Record Sale");

    menubar_.push_back("Analytics");
    menubar_.at(2).append("Show Summary");

    // Listboxes
    listbox lbProducts(fm, rectangle{ 10, 30, 380, 500 });
    lbProducts.append_header("ID", 50);
    lbProducts.append_header("Name", 150);
    lbProducts.append_header("Category", 100);
    lbProducts.append_header("Unit Price", 80);
    lbProducts.append_header("Qty", 50);

    listbox lbTransactions(fm, rectangle{ 400, 30, 380, 500 });
    lbTransactions.append_header("TID", 80);
    lbTransactions.append_header("Date", 140);
    lbTransactions.append_header("PID", 50);
    lbTransactions.append_header("Qty", 50);
    lbTransactions.append_header("Total", 80);

    // Populate function
    auto populate = [&]() {
        lbProducts.clear();
        auto cat_prod = lbProducts.append("Products");
        for (auto const& p : manager.listProducts()) {
            cat_prod.append({
                std::to_string(p->getId()),
                p->getName(),
                p->getCategory(),
                std::to_string(p->getUnitPrice()),
                std::to_string(p->getQuantity())
                });
        }

        lbTransactions.clear();
        auto cat_trx = lbTransactions.append("Transactions");
        for (auto const& t : manager.getTransactions()) {
            cat_trx.append({
                t->getTransactionId(),
                t->getDate(),
                std::to_string(t->getProductId()),
                std::to_string(t->getQuantity()),
                std::to_string(t->getTotalAmount())
                });
        }
        };

    // Menubar click handler
    menubar_.events().click([&](menu::item_proxy& item) {
        if (item.text() == "Add Product") {
            form dialog{ fm, API::make_center(350, 250) };
            dialog.caption("Add Product");

            // ID
            label l1{ dialog, "ID:" };
            l1.move(point{ 10, 10 });
            textbox tbId{ dialog };
            tbId.move(point{ 120, 10 });
            tbId.size(nana::size{ 200, 25 });

            // Name
            label l2{ dialog, "Name:" };
            l2.move(point{ 10, 45 });
            textbox tbName{ dialog };
            tbName.move(point{ 120, 45 });
            tbName.size(nana::size{ 200, 25 });

            // Category
            label l3{ dialog, "Category:" };
            l3.move(point{ 10, 80 });
            textbox tbCat{ dialog };
            tbCat.move(point{ 120, 80 });
            tbCat.size(nana::size{ 200, 25 });

            // Unit Price
            label l4{ dialog, "Unit Price:" };
            l4.move(point{ 10, 115 });
            textbox tbUnit{ dialog };
            tbUnit.move(point{ 120, 115 });
            tbUnit.size(nana::size{ 200, 25 });

            // Quantity
            label l5{ dialog, "Quantity:" };
            l5.move(point{ 10, 150 });
            textbox tbQty{ dialog };
            tbQty.move(point{ 120, 150 });
            tbQty.size(nana::size{ 200, 25 });

            // OK button
            button ok{ dialog, "OK" };
            ok.move(point{ 120, 190 });
            ok.events().click([&]() {
                try {
                    int id = std::stoi(tbId.text());
                    std::string name = tbName.text();
                    std::string cat = tbCat.text();
                    double unit = std::stod(tbUnit.text());
                    int qty = std::stoi(tbQty.text());
                    auto p = std::make_shared<Product>(id, name, cat, unit, qty);
                    manager.addProduct(p);
                }
                catch (...) {}
                dialog.close();
                populate();
                });

            dialog.show();
            exec();
        }
        else if (item.text() == "Record Purchase") {
            form dialog{ fm, API::make_center(350, 200) };
            dialog.caption("Record Purchase");

            label l1{ dialog, "TID:" };
            l1.move(point{ 10, 10 });
            textbox tbTid{ dialog };
            tbTid.move(point{ 120, 10 });
            tbTid.size(nana::size{ 200, 25 });

            label l2{ dialog, "Product ID:" };
            l2.move(point{ 10, 45 });
            textbox tbPid{ dialog };
            tbPid.move(point{ 120, 45 });
            tbPid.size(nana::size{ 200, 25 });

            label l3{ dialog, "Quantity:" };
            l3.move(point{ 10, 80 });
            textbox tbQty{ dialog };
            tbQty.move(point{ 120, 80 });
            tbQty.size(nana::size{ 200, 25 });

            label l4{ dialog, "Unit Cost:" };
            l4.move(point{ 10, 115 });
            textbox tbUnit{ dialog };
            tbUnit.move(point{ 120, 115 });
            tbUnit.size(nana::size{ 200, 25 });

            button ok{ dialog, "OK" };
            ok.move(point{ 120, 150 });
            ok.events().click([&]() {
                try {
                    std::string tid = tbTid.text();
                    int pid = std::stoi(tbPid.text());
                    int qty = std::stoi(tbQty.text());
                    double unit = std::stod(tbUnit.text());
                    std::string date = ""; // add a date picker if needed
                    auto tptr = std::make_shared<PurchaseTransaction>(tid, date, pid, qty, unit);
                    manager.recordPurchase(tptr);
                }
                catch (...) {}
                dialog.close();
                populate();
                });

            }
        
        }); // closes menubar click lambda

    fm.show();
    exec();
} // closes showMainWindow
