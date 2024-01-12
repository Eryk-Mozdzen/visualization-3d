#include <thread>
#include <sstream>
#include <cmath>

#include "Client.h"

int main() {

	Client client;

	client.write("clear\n");
	client.write("create obj1      sphere   material color 255 0   0   transform scale 0.1 0.1 0.1\n");
	client.write("create obj2      cylinder material color 0   255 0   transform scale 0.1 0.1 0.1\n");
	client.write("create obj1.obj3 cuboid   material color 255 0   255 transform translation 10 0 0\n");

	float t = 0;

	while(true) {
		t +=0.01;

		{
			std::stringstream ss;
			ss << "update obj1 ";
			ss << "transform translation " << std::cos(t) << " " << std::sin(t) << " 0";
			ss << "\n";

			client.write(ss.str());
		}

		{
			std::stringstream ss;
			ss << "update obj1.obj3 ";
			ss << "transform rotation 0 0 " << t*180/3.14;
			ss << "\n";

			client.write(ss.str());
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
