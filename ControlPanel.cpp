//=========================================
#include "ControlPanel.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

//=========================================
ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent)
{
    createComponents();
    createConnections();
    buttonEnablingControl();
}
//=========================================
void ControlPanel::showEncrypted(const QString &msg)
{
    encryptedTextEdit->setText(msg);
}
//=========================================
void ControlPanel::showDecrypted(const QString &msg)
{
    decryptedTextEdit->setText(msg);
}
//=========================================
void ControlPanel::showError(const QString& msg)
{
    QMessageBox::critical(this, tr("Error"), msg, QMessageBox::Ok);
}
//=========================================
void ControlPanel::createComponents()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QLabel* label = new QLabel(this);
    label->setText(createCaption(tr("Key word:")));
    mainLayout->addWidget(label);

    keyLineEdit = new QLineEdit(this);
    mainLayout->addWidget(keyLineEdit);

    label = new QLabel(this);
    label->setText(createCaption(tr("Original message:")));
    mainLayout->addWidget(label);

    inputTextEdit = new QTextEdit(this);
    mainLayout->addWidget(inputTextEdit);

    label = new QLabel(this);
    label->setText(createCaption(tr("Encrypted message:")));
    mainLayout->addWidget(label);

    encryptedTextEdit = new QTextEdit(this);
    mainLayout->addWidget(encryptedTextEdit);

    label = new QLabel(this);
    label->setText(createCaption(tr("Decrypted message:")));
    mainLayout->addWidget(label);

    decryptedTextEdit = new QTextEdit(this);
    mainLayout->addWidget(decryptedTextEdit);

    QDialogButtonBox *btnBox = new QDialogButtonBox(this);
    mainLayout->addWidget(btnBox);

    encryptBtn = new QPushButton(this);
    encryptBtn->setText(tr("Encrypt"));
    btnBox->addButton(encryptBtn, QDialogButtonBox::ActionRole);

    decryptBtn = new QPushButton(this);
    decryptBtn->setText(tr("Decrypt"));
    btnBox->addButton(decryptBtn, QDialogButtonBox::ActionRole);

}
//=========================================
void ControlPanel::createConnections()
{
    connect(encryptBtn, &QPushButton::clicked, this, &ControlPanel::initEncryption);
    connect(decryptBtn, &QPushButton::clicked, this, &ControlPanel::initDecryption);

    connect(keyLineEdit, &QLineEdit::textChanged, this, &ControlPanel::buttonEnablingControl);
    connect(inputTextEdit, &QTextEdit::textChanged, this, &ControlPanel::buttonEnablingControl);
    connect(encryptedTextEdit, &QTextEdit::textChanged, this, &ControlPanel::buttonEnablingControl);
}
//=========================================
QString ControlPanel::createCaption(const QString& caption)
{
    return QString("<b><font color=darkBlue>%1</font></b>").arg(caption);
}
//=========================================
void ControlPanel::swapIO()
{
    inputTextEdit->setText(encryptedTextEdit->toPlainText());
}
//=========================================
void ControlPanel::initEncryption()
{
    emit encryptRequest(keyLineEdit->text(), inputTextEdit->toPlainText());
}
//=========================================
void ControlPanel::initDecryption()
{
    emit decryptRequest(keyLineEdit->text(), encryptedTextEdit->toPlainText());
}
//=========================================
void ControlPanel::buttonEnablingControl()
{
    encryptBtn->setEnabled(!keyLineEdit->text().isEmpty()
                           && !inputTextEdit->toPlainText().isEmpty());
    decryptBtn->setEnabled(!keyLineEdit->text().isEmpty()
                           && !encryptedTextEdit->toPlainText().isEmpty());
}
//=========================================
