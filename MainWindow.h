//=========================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//=========================================
#include <QMainWindow>
#include <QSettings>
//=========================================
class ControlPanel;
class PlayfairCipher;
//=========================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //VARS
    ControlPanel* controlPanel;
    PlayfairCipher* playfairCipher;

    //FUNCS
    void createComponents();
    void createConnections();

    void saveSettings() const;
    void restoreSettings();

};
//=========================================
#endif // MAINWINDOW_H
