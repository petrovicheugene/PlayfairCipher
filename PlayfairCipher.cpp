//=========================================
#include "PlayfairCipher.h"

#include <QDebug>
#include <QRegExp>
#include <QSet>
//=========================================
PlayfairCipher::PlayfairCipher(QObject *parent) : QObject(parent) {}
//=========================================
void PlayfairCipher::encrypt(const QString &keyword, const QString &message)
{
    QString key = keyword.toLower();
    QString msg = message.toLower();
    Language lang = checkInputData(key, msg);
    if (lang == L_NOT_DEFINED)
    {
        return;
    }

    prepareMsg(msg);
    createCipherMatrix(key, lang);

    QString encryptedStr;

    while (workStr.length() > 0)
    {
        encryptedStr.append(encryptNextPair());
    }

    emit encrypted(encryptedStr);
}
//=========================================
void PlayfairCipher::decrypt(const QString &keyword, const QString &message)
{
    QString key = keyword.simplified().toLower();
    QString msg = message.simplified().toLower();
    Language lang = checkInputData(key, msg);
    if (lang == L_NOT_DEFINED)
    {
        return;
    }

    prepareMsg(msg);
    createCipherMatrix(key, lang);

    QString decryptedStr;

    while (workStr.length() > 0)
    {
        decryptedStr.append(decryptNextPair());
    }

    emit decrypted(decryptedStr);
}
//=========================================
PlayfairCipher::Language PlayfairCipher::checkInputData(const QString &key, const QString &msg)
{
    if (key.isEmpty() || msg.isEmpty())
    {
        emit errorMessage(tr("The keyword and input message must be filled!"));
        return L_NOT_DEFINED;
    }

    QRegExp space("\\s");
    if (key.contains(space))
    {
        emit errorMessage(tr("The keyword must not contain spaces!"));
        return L_NOT_DEFINED;
    }

    QRegExp latRegexp("^[a-zA-Z\\s]{1,}$");
    QRegExp cyrRegexp("^[а-яА-Я\\s]{1,}$");

    if (latRegexp.exactMatch(key) && latRegexp.exactMatch(msg))
    {
        substitutionChar = "x";
        return L_ENG;
    }
    else if (cyrRegexp.exactMatch(key) && cyrRegexp.exactMatch(msg))
    {
        substitutionChar = "ъ";
        return L_RUS;
    }

    QString errorMsg = tr("The keyword and input message must be in the same language!");
    emit errorMessage(errorMsg);
    return L_NOT_DEFINED;
}
//=========================================
void PlayfairCipher::prepareMsg(const QString &msg)
{
    workStr = msg.simplified();
    QRegExp space("\\s");
    workStr.remove(space);
}
//=========================================
bool PlayfairCipher::createCipherMatrix(const QString &key, Language lang)
{
    if (key.isEmpty())
    {
        return false;
    }

    cipherMatrix.clear();
    QSet<QChar> insertedCharSet;

    // remove doplicates from key
    QString workKey = key;
    for (int i = 0; i < workKey.length(); ++i)
    {
        if (!insertedCharSet.contains(workKey.at(i)))
        {
            insertedCharSet.insert(workKey.at(i));
        }
        else
        {
            workKey.remove(i--, 1);
        }
    }

    QString alphabet;
    int columnCount = 0;
    if (lang == L_ENG)
    {
        workKey.remove("j");
        insertedCharSet.remove(QChar('j'));
        alphabet = "abcdefghiklmnopqrstuvwxyz";
        columnCount = 5;
    }
    else if (lang == L_RUS)
    {
        alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
        columnCount = 8;
    }

    for (int a = 0; a < alphabet.length(); ++a)
    {
        if (insertedCharSet.contains(alphabet.at(a)))
        {
            continue;
        }

        workKey.append(alphabet.at(a));
    }

    while (workKey.length() > 0)
    {
        QString row = workKey.left(columnCount);
        cipherMatrix.append(row);
        workKey.remove(0, columnCount);
    }
    return true;
}
//=========================================
QString PlayfairCipher::encryptNextPair()
{
    QString encryptedStr;
    QPair<Letter, Letter> charPair;
    if (!getNextPair(charPair))
    {
        return QString();
    }

    if (charPair.first.row == charPair.second.row) // rows match
    {
        // first letter
        if (charPair.first.column == cipherMatrix.at(charPair.first.row).size() - 1)
        {
            encryptedStr.append(cipherMatrix.at(charPair.first.row).at(0));
        }
        else
        {
            encryptedStr.append(cipherMatrix.at(charPair.first.row).at(charPair.first.column + 1));
        }
        // second letter
        if (charPair.second.column == cipherMatrix.at(charPair.second.row).size() - 1)
        {
            encryptedStr.append(cipherMatrix.at(charPair.second.row).at(0));
        }
        else
        {
            encryptedStr.append(cipherMatrix.at(charPair.second.row).at(charPair.second.column + 1));
        }
    }

    else if (charPair.first.column == charPair.second.column) // columns match
    {
        // first letter
        if (charPair.first.row == cipherMatrix.size() - 1)
        {
            encryptedStr.append(cipherMatrix.at(0).at(charPair.first.column));
        }
        else
        {
            encryptedStr.append(cipherMatrix.at(charPair.first.row + 1).at(charPair.first.column));
        }
        // second letter
        if (charPair.second.row == cipherMatrix.size() - 1)
        {
            encryptedStr.append(cipherMatrix.at(0).at(charPair.second.column));
        }
        else
        {
            encryptedStr.append(cipherMatrix.at(charPair.second.row + 1).at(charPair.second.column));
        }
    }
    else
    {
        encryptedStr.append(cipherMatrix.at(charPair.first.row).at(charPair.second.column));
        encryptedStr.append(cipherMatrix.at(charPair.second.row).at(charPair.first.column));
    }

    return encryptedStr;
}
//=========================================
QString PlayfairCipher::decryptNextPair()
{
    QString decryptedStr;
    QPair<Letter, Letter> charPair;
    if (!getNextPair(charPair))
    {
        return QString();
    }
    // rows match
    if (charPair.first.row == charPair.second.row)
    {
        // first letter
        if (charPair.first.column == 0)
        {
            decryptedStr.append(cipherMatrix.at(charPair.first.row)
                                    .at(cipherMatrix.at(charPair.first.row).size() - 1));
        }
        else
        {
            decryptedStr.append(cipherMatrix.at(charPair.first.row).at(charPair.first.column - 1));
        }
        // second letter
        if (charPair.second.column == 0)
        {
            decryptedStr.append(cipherMatrix.at(charPair.second.row)
                                    .at(cipherMatrix.at(charPair.second.row).size() - 1));
        }
        else
        {
            decryptedStr.append(cipherMatrix.at(charPair.second.row).at(charPair.second.column - 1));
        }
    }
    // columns match
    else if (charPair.first.column == charPair.second.column)
    {
        // first letter
        if (charPair.first.row == 0)
        {
            decryptedStr.append(cipherMatrix.at(cipherMatrix.size() - 1).at(charPair.first.column));
        }
        else
        {
            decryptedStr.append(cipherMatrix.at(charPair.first.row - 1).at(charPair.first.column));
        }
        // second letter
        if (charPair.second.row == 0)
        {
            decryptedStr.append(cipherMatrix.at(cipherMatrix.size() - 1).at(charPair.second.column));
        }
        else
        {
            decryptedStr.append(cipherMatrix.at(charPair.second.row - 1).at(charPair.second.column));
        }
    }
    else
    {
        decryptedStr.append(cipherMatrix.at(charPair.first.row).at(charPair.second.column));
        decryptedStr.append(cipherMatrix.at(charPair.second.row).at(charPair.first.column));
    }

    return decryptedStr;
}
//=========================================
bool PlayfairCipher::getNextPair(QPair<Letter, Letter> &charPair)
{
    if (workStr.length() == 1)
    {
        if (workStr.at(0) != substitutionChar)
        {
            charPair.first = defineCharPosition(workStr.at(0));
            workStr.remove(0, 1);
            charPair.second = defineCharPosition(substitutionChar);
        }
        else
        {
            return false;
        }
    }
    else if (workStr.at(0) == workStr.at(1))
    {
        charPair.first = defineCharPosition(workStr.at(0));
        workStr.remove(0, 1);
        charPair.second = defineCharPosition(substitutionChar);
    }
    else
    {
        charPair.first = defineCharPosition(workStr.at(0));
        charPair.second = defineCharPosition(workStr.at(1));
        workStr.remove(0, 2);
    }

    return true;
}
//=========================================
Letter PlayfairCipher::defineCharPosition(const QString &ch)
{
    Letter letter;
    letter.character = ch;
    bool breakFlag = false;
    for (int r = 0; r < cipherMatrix.size(); ++r)
    {
        for (int c = 0; c < cipherMatrix.at(r).length(); ++c)
        {
            if (cipherMatrix[r][c] == ch)
            {
                letter.row = r;
                letter.column = c;
                breakFlag = true;
                break;
            }
        }

        if (breakFlag)
        {
            break;
        }
    }

    return letter;
}
//=========================================
