#include <iostream>
#include <string>
#include "VendingMachine/vending_machine.h"
#include "Snack/snack.h"

int main()
{
    unsigned int slotCount = 3;
    unsigned int slotCapacity = 4;

    Snack *bounty = new Snack("Bounty");
    Snack *snickers = new Snack("Snickers");
    SnackSlot *slot = new SnackSlot(slotCapacity/*количество батончиков, которые помещаются в слот*/);
    SnackSlot *slot2 = new SnackSlot(slotCapacity/*количество батончиков, которые помещаются в слот*/);
    slot->addSnack(bounty); //Добавляем батончик в слот
    slot->addSnack(snickers);
    VendingMachine* machine = new VendingMachine(slotCount /*Количество слотов для снеков*/);
    machine->addSlot(slot); // Помещаем слот обратно в аппарат

    Snack* get_snack = machine->byFromSlot(0);

    std::cout << machine->getEmptySlotsCount()<<std::endl; // Должно выводить количество пустых слотов для снеков
    delete machine;
    delete slot;
    delete snickers;
    delete bounty;
    if( get_snack != nullptr )
        delete get_snack;
    return 0;
}