#include <thread>
#include <sstream>
#include <cmath>

#include "Client.h"

int main() {

	Client client;

	client.write("clear\n");
	client.write("create obj1      sphere   material color 255 0   0   transform translation 0 0 0 \n");
	client.write("create obj2      cylinder material color 0   255 0   transform translation 5 0 0 \n");
	client.write("create obj3      cuboid   material color 0   0   255 transform translation 0 5 0 \n");
	client.write("create obj1.obj4 model    material color 255 0   255 transform translation 0 0 5 rotation -90 0 0 scale 0.1 0.1 0.1 path /home/emozdzen/Downloads/3DBenchy.stl\n");

	float t = 0;

	while(true) {
		t +=0.01;

		{
			std::stringstream ss;
			ss << "update obj1 ";
			ss << "transform translation " << 10*std::sin(t) << " " << " 0 " << 10*std::cos(t) << " ";
			ss << "\n";

			client.write(ss.str());
		}

		{
			std::stringstream ss;
			ss << "update obj1.obj4 ";
			ss << "transform rotation -90 " << t*180/3.1415 << " 0 ";
			ss << "\n";

			client.write(ss.str());
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
