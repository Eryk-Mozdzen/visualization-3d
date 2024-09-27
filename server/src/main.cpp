#include <QApplication>

#include "Server.h"
#include "Window.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	Server server;
	Window window;

	QObject::connect(&server, &Server::receive, &window, &Window::receive);

 	window.show();

	return app.exec();
}
