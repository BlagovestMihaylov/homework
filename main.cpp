#include "test/Tests.h"
#include "inteface/Interface.h"

int main() {
    Tests::init();

    Interface interface;
    interface.Run();
}

