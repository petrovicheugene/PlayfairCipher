//=========================================
#ifndef PLAYFAIRENCRYPTOR_H
#define PLAYFAIRENCRYPTOR_H
//=========================================
#include <QObject>
//=========================================
struct Letter
{
    Letter(QString ch = QString()) { character = ch; };
    QString character;
    int row;
    int column;
};
//=========================================
class PlayfairCipher : public QObject
{
    Q_OBJECT
public:
    explicit PlayfairCipher(QObject *parent = nullptr);

signals:

    void encrypted(const QString &msg) const;
    void decrypted(const QString &msg) const;
    void errorMessage(const QString &msg) const;

public slots:

    void encrypt(const QString &keyword, const QString &message);
    void decrypt(const QString &keyword, const QString &message);

private:
    // VARS

    enum Language
    {
        L_NOT_DEFINED,
        L_RUS,
        L_ENG
    };
    QString workStr;
    QString substitutionChar;
    QStringList cipherMatrix;

    // FUNCS
    Language checkInputData(const QString &key, const QString &msg);
    void prepareMsg(const QString &msg);
    bool createCipherMatrix(const QString &key, Language lang);
    QString encryptNextPair();
    QString decryptNextPair();
    bool getNextPair(QPair<Letter, Letter> &charPair);
    Letter defineCharPosition(const QString &ch);
};
//=========================================
#endif // PLAYFAIRENCRYPTOR_H
