#include <thread>
#include <string>
#include <cmath>

#include "Client.h"

int main() {
	Client client;

	client.write("clear\n");
	client.write("create obj1      sphere   material color 255 0   0   geometry 0.25\n");
	client.write("create obj2      cylinder material color 0   255 0   geometry 0.25 0.25\n");
	client.write("create obj2.obj3 cuboid   material color 255 0   255 transform translation 1 0 0 geometry 0.25 0.25 0.25\n");

	double time = 0;

	while(true) {
		time +=0.01;

		client.write("update obj2      transform translation " + std::to_string(std::sin(time)) + " 0 0\n");
		client.write("update obj2.obj3 transform rpy 0 0 " + std::to_string(100*time) + "\n");

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
