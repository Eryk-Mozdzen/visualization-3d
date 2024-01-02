#include "Client.h"

int main() {

	Client client;

	client.write("clear\n");
	client.write("create name obj1 type cuboid material color 255 0 0\n");
	client.write("update name obj2 type model material color 255 0 255 path /home/emozdzen/Downloads/3DBenchy.stl\n");

	client.write("update name obj1 transform translation 10 0 0\n");
}
