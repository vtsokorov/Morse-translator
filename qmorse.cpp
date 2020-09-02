#include "qmorse.h"

QMorse::QMorse()
{
    alphabet = {
        {'A',".-"}, {'B',"-..."}, {'C',"-.-."}, {'D',"-.."}, {'E',"."},
        {'F',"..-."}, {'G',"--."}, {'H',"...."}, {'I',".."}, {'J',".---"},
        {'K',"-.-"}, {'L',".-.."}, {'M',"--"}, {'N',"-."}, {'O',"---"},
        {'P',".--."}, {'Q',"--.-"}, {'R',".-."}, {'S',"..."}, {'T',"-"},
        {'U',"..-"}, {'V',"...-"}, {'W',".--"}, {'X',"-..-"}, {'Y',"-.--"},
        {'Z',"--.."}, {'0',"-----"}, {'1',".----"}, {'2',"..---"}, {'3',"...--"},
        {'4',"....-"}, {'5',"....."}, {'6',"-...."}, {'7',"--..."}, {'8',"---.."},
        {'9',"----."}, {'.',".-.-.-"}, {',',"--..--"}, {'?',"..--.."}, {'=',"-...-"}
    };
}

QString QMorse::encode(const QString &s) {

    QString r;
    for (const auto &c : s) {
        if(alphabet.contains(c.toUpper())) {
            r.append(alphabet[c.toUpper()]).append(QChar::Space);
        } else {
            if (c.isSpace()) r.append(QChar::Space);
        }
    }

    return r;
}

QString QMorse::decode(const QString &s) {

    QString r; 
    QStringList words = s.split(QString().append(QChar::Space).append(QChar::Space));
    for(int index = 0; index < words.count(); ++index) {
        auto word = words[index].trimmed();
        for(const auto &chars : word.split(QChar::Space)) {
            for(const auto &value : alphabet) {
                if (chars == value)
                    r.append(alphabet.key(value));
            }
        }
        r.append(index == words.count()-1 ? QChar() : QChar::Space);
    }

    return r;
}
