#include "Utils/LogManager.h"
#include <cassert>
int main(int argc, char* argv)
{
    int res = LM.startUp();
    assert(res == 0);

    LM.setLogTime();
    LM.setLogToScreen();

    LM.writeLog("Starting application..");

    LM.shutDown();
    return 0;
}