//=========================================
#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
//=========================================
#include <QWidget>
//=========================================
class QLineEdit;
class QPushButton;
class QTextEdit;
//=========================================
class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);

signals:

    void encryptRequest(const QString& key, const QString& msg) const;
    void decryptRequest(const QString& key, const QString& msg) const;

public slots:

    void showEncrypted(const QString &msg);
    void showDecrypted(const QString &msg);
    void showError(const QString& msg);

private slots:

    void swapIO();
    void initEncryption();
    void initDecryption();
    void buttonEnablingControl();

private:
    //VARS
    QLineEdit* keyLineEdit;
    QTextEdit *inputTextEdit;
    QTextEdit *encryptedTextEdit;
    QTextEdit *decryptedTextEdit;
    QPushButton* encryptBtn;
    QPushButton* decryptBtn;
    //FUNCS
    void createComponents();
    void createConnections();
    QString createCaption(const QString& caption);
};
//=========================================
#endif // CONTROLPANEL_H
