//=========================================
#include "MainWindow.h"
#include "PlayfairCipher.h"

#include <QApplication>
#include <ControlPanel.h>
#include <QSettings>
//=========================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(qApp->applicationDisplayName());


    createComponents();
    createConnections();
    restoreSettings();
}
//=========================================
MainWindow::~MainWindow()
{
    saveSettings();
}
//=========================================
void MainWindow::createComponents()
{
    controlPanel = new ControlPanel(this);
    playfairCipher = new PlayfairCipher(this);

    setCentralWidget(controlPanel);
}
//=========================================
void MainWindow::createConnections()
{
    connect(controlPanel, &ControlPanel::encryptRequest,
            playfairCipher, &PlayfairCipher::encrypt);

    connect(controlPanel, &ControlPanel::decryptRequest,
            playfairCipher, &PlayfairCipher::decrypt);

    connect(playfairCipher, &PlayfairCipher::encrypted,
            controlPanel, &ControlPanel::showMsg);

    connect(playfairCipher, &PlayfairCipher::decrypted,
            controlPanel, &ControlPanel::showMsg);

    connect(playfairCipher, &PlayfairCipher::errorMessage, controlPanel, &ControlPanel::showError);
}
//=========================================
void MainWindow::saveSettings() const
{
    QSettings settings("/settings.ini", QSettings::IniFormat);
    settings.setValue("geometry", saveGeometry());

}
//=========================================
void MainWindow::restoreSettings()
{
    QSettings settings("/settings.ini", QSettings::IniFormat);
    restoreGeometry(settings.value("geometry").toByteArray());
}
//=========================================


