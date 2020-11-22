#include "window.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "verticaloption.h"
#include "options.h"
#include <QSlider>
#include <QLabel>

void function(QLabel *x,QSlider *y,int *str)
{
     x->setText(QString::number(y->value())+"mv");
     *str = (y->value());
}

verticaloption::verticaloption(QString val, int *str, QWidget *parent)
{

       QSlider *v = new QSlider(Qt::Horizontal) ;
       v->setMinimum(-120);
       v->setMaximum(+120);
       v->setValue(0);

       QLabel *label = new QLabel(val);

       QLabel *num = new QLabel("0mv");


        connect(v, &QSlider::valueChanged, [num,v,str]() { function(num,v,str);});

        this->addWidget(label);
        this->addWidget(v);
        this->addWidget(num);

}


