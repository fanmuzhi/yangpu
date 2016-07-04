#include "yangpu.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Yangpu w;
	w.show();
	w.showMaximized();
	return a.exec();
}
