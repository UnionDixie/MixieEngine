#include "Engine/Utility/utility.h"
#include "Engine/Engine.h"

int main(int argc,char** argv) {

    Utility::Watcher watcher;
    Utility::Timer timer;
    Utility::Logger logger;

    Engine engine;
    engine.run();

    

    return 0;
}