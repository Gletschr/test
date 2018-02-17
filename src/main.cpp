#include <QApplication>
#include "TestGLWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Create window.
	TestGLWindow testGLWindow;

	// Initialize resources (load points, calculate transforms).
	testGLWindow.loadAndPrepareRenderResources();

	// Show result.
	testGLWindow.show();

	return a.exec();
}
