#include "Client.h"

int main() {

	Client client;

	client.write("clear\n");
	client.write("create obj1 sphere   material color 255 0   0   transform translation 0 0 0 \n");
	client.write("create obj2 cylinder material color 0   255 0   transform translation 5 0 0 \n");
	client.write("create obj3 cuboid   material color 0   0   255 transform translation 0 5 0 \n");
	client.write("create obj4 model    material color 255 0   255 transform translation 0 0 5 rotation -90 0 0 scale 0.1 0.1 0.1 path /home/emozdzen/Downloads/3DBenchy.stl\n");

	//client.write("update obj1 transform translation 10 0 0\n");
}
