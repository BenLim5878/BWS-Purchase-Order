#include "StockInventoryReportView.h"
#include <Windows.h>
#include <iostream>
#include "Time.h"
#include "Header.h"
#include "DataAccess.h"

using namespace std;

void View::StockInventoryReportView::show()
{
    system("CLS");
    ViewHeader::Header head;
    head.display();
    displayTime::Time dtime;
    dtime.show();

    float totalInventoryCost = 0;
    int  totalStockAmount = 0;
    int totalStockCategory = 0;

    auto productRepos = DataAccess::getInstance()->productRepository;
    for (int i = 0; i < productRepos->getTotalCategory(); i++) {
        auto productCategory = productRepos->getProductCategory(i);
        totalStockCategory++;
        cout <<
            productCategory->categoryTitle
            << endl;
        for (int j = 0; j < productRepos->getTotalItemByCategory(i); j++) {
            auto product = productRepos->getProduct(i, j);
            int stockAmount = productRepos->getProductStockAmount(product->getProductID());
            totalStockAmount += stockAmount;
            totalInventoryCost += (stockAmount * product->productPricePerUnit);
            cout
                << product->getProductID()
                << endl
                << product->productName
                << endl
                << product->productBrand
                << endl
                << product->productPricePerUnit
                << endl
                << Product::productStatusToString(product->productStatus)
                << endl
                << product->productQuantityPerUnit
                << endl
                << product->productStockUnit
                << endl
                << product->productVendor->vendorName
                << endl;
        }
    }
    cout << "Current Inventory Cost : RM " << totalInventoryCost << endl;
    cout << "Total Stock Amount: " << totalStockAmount << endl;
    cout << "Total Product Category: " << totalStockCategory << endl;
}
