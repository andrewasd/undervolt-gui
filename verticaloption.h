#ifndef VERTICALOPTION_H
#define VERTICALOPTION_H

#include <QHBoxLayout>
#include <qstring.h>

class verticaloption : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit verticaloption(QString val, int *x, QWidget *parent = nullptr);

signals:

};

#endif // VERTICALOPTION_H
