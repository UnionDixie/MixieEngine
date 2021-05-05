#include <iostream>
#include <memory>
#include <core/core.h>

class MyCore : public Engine::Core
{
public:
	virtual void update() override {
		//std::cout << "Frame:" << frame++ << "\n";
	}
private:
	int frame = 0;
};


int main() {

	std::cout << "\tEditor\n";

	auto myApp = std::make_unique<MyCore>();
	int exitCode = myApp->init(640, 480, "OpenGl >_<");

	std::cin.get();

	return exitCode;
}