#include <iostream>
#include "laptop/laptop.h"
#include "tablet/tablet.h"
#include "transformer/transformer.h"
#include "sold_electronics/sold_electronics.h"
#include <iostream>

using std::cout, std::endl, std::string, std::to_string, std::cin;

int main() {

    SoldElectronics * assortment[5];

    assortment[0] = new Laptop(100, "AMD");
    assortment[1] = new Tablet(90, 10);
    assortment[2] = new Transformer(110, "Nvidia", 10, 3);
    assortment[3] = new Laptop(105, "Nvidia");

    bool open = true;
    while (open)
    {
        cout << "Выберите продукт : 1 - ноутбук с AMD, 2 - планшет, 3 - трансформер, 4 - ноутбук с nvidia, 0 чтобы выйти" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                assortment[0] -> Show();
                break;

            case 2:
                assortment[1] -> Show();
                break;

            case 3:
                assortment[2] -> Show();
                break;

            case 4:
                assortment[3] -> Show();
                break;

            case 5:
                assortment[4] -> Show();
                break;

            case 0:
                open = false;
                break;

            default:
                cout << "Выберите продукт от 1 до 4 или 0, чтобы выйти" << endl;
                break;
        }
    }
    delete assortment[0];
    delete assortment[1];
    delete assortment[2];
    delete assortment[3];
    return 0;
}
