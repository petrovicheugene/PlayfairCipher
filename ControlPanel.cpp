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
}
//=========================================
void ControlPanel::showMsg(const QString& msg)
{
    outputTextEdit->setText(msg);
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
    label->setText(createCaption(tr("Input:")));
    mainLayout->addWidget(label);

    inputTextEdit = new QTextEdit(this);
    mainLayout->addWidget(inputTextEdit);

    label = new QLabel(this);
    label->setText(createCaption(tr("Output:")));
    mainLayout->addWidget(label);

    outputTextEdit = new QTextEdit(this);
    mainLayout->addWidget(outputTextEdit);

    QDialogButtonBox* btnBox = new QDialogButtonBox(this);
    mainLayout->addWidget(btnBox);

    swapBtn = new QPushButton(this);
    swapBtn->setText(tr("Swap"));
    btnBox->addButton(swapBtn, QDialogButtonBox::ActionRole);

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
    connect(swapBtn, &QPushButton::clicked,
            this, &ControlPanel::swapIO);
    connect(encryptBtn, &QPushButton::clicked,
            this, &ControlPanel::initEncryption);
    connect(decryptBtn, &QPushButton::clicked,
            this, &ControlPanel::initDecryption);

}
//=========================================
QString ControlPanel::createCaption(const QString& caption)
{
    return QString("<b><font color=darkBlue>%1</font></b>").arg(caption);
}
//=========================================
void ControlPanel::swapIO()
{
    inputTextEdit->setText(outputTextEdit->toPlainText());
}
//=========================================
void ControlPanel::initEncryption()
{
    emit encryptRequest(keyLineEdit->text(), inputTextEdit->toPlainText());
}
//=========================================
void ControlPanel::initDecryption()
{
    emit decryptRequest(keyLineEdit->text(), inputTextEdit->toPlainText());
}
//=========================================
