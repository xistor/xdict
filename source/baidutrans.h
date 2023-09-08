#ifndef BAIDUTRANS_H
#define BAIDUTRANS_H

#include "translator.h"

class BaiduTrans : public Translator
{
public:
    BaiduTrans();

    QString translate(const QString &from, const QString &to, const QString &word) override;

};

#endif // BAIDUTRANS_H
