#include <iostream>
#include "Listener/listener.h"
#include "Sender/sender.h"

static const int PORT = 7777;
static const int BUF_SIZE = 1024;


int main() {
    Listener li(PORT, BUF_SIZE);
    li.ThreadRun();

    Sender sender(PORT);
    sender.Run();

    li.Stop();
    return 0;
}
