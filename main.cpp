#include "MainWindow.h"

#include "ZTranslatorManager.h"

#include <windows.h>
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include <QDir>
#include <QSplashScreen>
#include <QPixmap>
#include <iostream>
#include <QSet>


//======================================================
int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("windows-1251");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);

    // create qApp properties and set .pro defines into them
#ifdef APP_DISPLAY_NAME
    QApplication::setApplicationDisplayName(APP_DISPLAY_NAME);
#endif

#ifdef APP_PRODUCT
    QApplication::setApplicationName(APP_PRODUCT);
#endif

#ifdef APP_VERSION
    QApplication::setApplicationVersion(APP_VERSION);
#endif

#ifdef APP_COMPANY
    QApplication::setOrganizationName(APP_COMPANY);
#endif

#ifdef APP_COMPANY_URL
    QApplication::setOrganizationDomain(APP_COMPANY_URL);
#endif

#ifdef APP_COPYRIGHT
    qApp->setProperty("appCopyright", QString(APP_COPYRIGHT));
#endif

#ifdef APP_ICON
    qApp->setProperty("appIcon", QString(APP_ICON));
#endif

    ZTranslatorManager languageManager;
    languageManager.zp_installTranslatorsToApplication();


    MainWindow w;

    // pointer to main window for message handler

    w.show();
    return a.exec();
}
//===============================================
