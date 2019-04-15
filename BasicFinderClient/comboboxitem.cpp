#include "comboboxitem.h"
#include <QDebug>
#include <QPainter>

ComboboxItem::ComboboxItem(QWidget *parent) : QWidget(parent)
{
        mouse_press=false;

        button=new QPushButton(this);
        button->setToolTip("删除账号信息");
        button->setStyleSheet("background:transparent;");

        m_label = new QLabel(this);

        m_layout = new QHBoxLayout(this);
        m_layout->addWidget(m_label);
        m_layout->addStretch();
        m_layout->addWidget(button);

        m_layout->setSpacing(3);
        m_layout->setContentsMargins(2, 2, 2, 2);

        setLayout(m_layout);
        connect(button,SIGNAL(clicked()),this,SLOT(potionclicked()));
}

void ComboboxItem::potionclicked()
{
    QString ls=this->m_label->text();
    qDebug()<<"ls="<<ls;
    emit chooseAccount(ls);
}
void ComboboxItem::mousePressEvent(QMouseEvent *event)
{

 if(event->button() == Qt::LeftButton)
 {

  mouse_press = true;
 }
}

void ComboboxItem::mouseReleaseEvent(QMouseEvent *event)
{
 if(mouse_press)
 {
  emit showAccount(this->m_label->text());
  mouse_press = false;
 }
}

