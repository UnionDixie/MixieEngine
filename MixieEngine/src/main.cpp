#include "Engine/Utility/log.h"
#include "Engine/Engine.h"

int main(int argc,char** argv) {

    Utility::Timer timer;
    Utility::Logger logger;

    Engine engine;
    engine.run();

    std::cout << Utility::cnt << " " << Utility::usedMem << " Bytes!" << "\n";

    return 0;
}