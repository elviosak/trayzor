#include "maintray.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication * app = new QApplication(argc, argv);

    //MainTray tray =
    new MainTray(app);

    return app->exec();
}
