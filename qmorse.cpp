#include "qmorse.h"

QMorse::QMorse()
{
    alphabet = {
        {'A',".-"},
        {'B',"-..."},
        {'C',"-.-."},
        {'D',"-.."},
        {'E',"."},
        {'F',"..-."},
        {'G',"--."},
        {'H',"...."},
        {'I',".."},
        {'J',".---"},
        {'K',"-.-"},
        {'L',".-.."},
        {'M',"--"},
        {'N',"-."},
        {'O',"---"},
        {'P',".--."},
        {'Q',"--.-"},
        {'R',".-."},
        {'S',"..."},
        {'T',"-"},
        {'U',"..-"},
        {'V',"...-"},
        {'W',".--"},
        {'X',"-..-"},
        {'Y',"-.--"},
        {'Z',"--.."},
        {'0',"-----"},
        {'1',".----"},
        {'2',"..---"},
        {'3',"...--"},
        {'4',"....-"},
        {'5',"....."},
        {'6',"-...."},
        {'7',"--..."},
        {'8',"---.."},
        {'9',"----."},
        {'.',".-.-.-"},
        {',',"--..--"},
        {'?',"..--.."},
        {'=',"-...-"}
    };
}

QString QMorse::encode(const QString &s) {
    QString r = "";

    for (const QChar c : s) {
        if(alphabet.contains(c.toUpper())) {
            r += alphabet[c.toUpper()];
            r += " ";
        } else {
            if (c.isSpace()) r += "  ";
        }
    }

    return r;
}

QString QMorse::decode(const QString &s) {
    QString r; 
    QStringList words = s.split("  ");

    for(int index = 0; index < words.count(); ++index) {
        QString word = words[index].trimmed();
        for(auto &chars : word.split(" ")) {
            for (auto it = alphabet.begin(); it != alphabet.end(); it++) {
                if (chars == it.value()) {
                    r.append(it.key());
                }
            }

        }
        r.append(index == words.count()-1 ? "" : " ");
    }

    return r;
}