#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <synchapi.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //去掉系统边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //阴影边框效果类
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(0);
    shadow->setColor(Qt::black);
    shadow->setOffset(0);
    ui->shadowWidget->setGraphicsEffect(shadow);

    //设置父窗口为透明
    this->setAttribute(Qt::WA_TranslucentBackground);


    m_listWidget = new QListWidget(this);


    //ui->LogincomboBox->itemText(1);
    QPixmap pixmap(":/White/closePressed");

    for (int i = 0; i < 4; ++i)
    {
        ComboboxItem* item = new ComboboxItem(this);

        item->m_label->setText(QString("Account") + QString::number(i, 10));

        item->button->setIcon(pixmap);
        item->button->setIconSize(pixmap.size());
        connect(item, SIGNAL(chooseAccount(const QString&)), this, SLOT(onChooseAccount(const QString&)));
        connect(item, SIGNAL(showAccount(QString)), this, SLOT(showAccount(QString)));
        QListWidgetItem* widgetItem = new QListWidgetItem(m_listWidget);
        m_listWidget->setItemWidget(widgetItem, item);

    }
    ui->LoginlineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);//输入时显示数字，失去焦点时显示圆点
    ui->LogincomboBox->setEditable(true);
    ui->LogincomboBox->setModel(m_listWidget->model());
    ui->LogincomboBox->setView(m_listWidget);
    ui->LogincomboBox->lineEdit()->setPlaceholderText("请输入用户名");//默认提示语
    ui->LoginlineEdit->setPlaceholderText("请输入密码：");
    Sleep(1000);
}
Widget::~Widget()
{
    delete m_listWidget;
    delete ui;
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if (this->z == QPoint())
        return;
    QPoint y = event->globalPos(); //鼠标相对于桌面左上角的位置，鼠标全局位置。

    QPoint x = y - this->z;

    this->move(x);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    QPoint y = event->globalPos(); //鼠标相对于桌面左上角的位置，鼠标全局位置。
    QPoint x = this->geometry().topLeft(); //窗口左上角相对于桌面左上角的位置，窗口位置
    this->z = y - x; //定值，不变的。
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    this->z = QPoint();
}

void Widget::on_btnMin_clicked()
{
    this->showMinimized();
}

void Widget::on_btnClose_clicked()
{
    this->close();
}

void Widget::onChooseAccount(const QString &ls)
{

    int list_count = m_listWidget->count();
    for(int i=0;i<list_count;i++)
    {
        QListWidgetItem *item = m_listWidget->item(i);
        ComboboxItem* account_item = (ComboboxItem*)(m_listWidget->itemWidget(item));
        QString account_number = account_item->m_label->text();
        if(ls == account_number)
        {
            m_listWidget->takeItem(i);
            delete item;

            break;
        }

    }
}

void Widget::showAccount(const QString &text)
{
    ui->LogincomboBox->setEditText(text);
    ui->LogincomboBox->hidePopup();
    ui->LoginlineEdit->clear();
    //ui->LoginlineEdit->setText("请输入密码：");
    ui->LoginlineEdit->setFocus();

}

void Widget::on_LoginBtn_clicked()
{
    QTimer *myt =new QTimer(this);

    connect(myt, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    myt->start(2000);
    this->setCursor(Qt::WaitCursor);

    QLineEdit *edit=ui->LogincomboBox->lineEdit();
    if(!edit->text().isEmpty())
    {
    int list_count = m_listWidget->count();
    for(int i=0;i<list_count;i++)
    {
        QListWidgetItem *item = m_listWidget->item(i);
        ComboboxItem* account_item = (ComboboxItem*)(m_listWidget->itemWidget(item));
        QString account_number = account_item->m_label->text();
        if(edit->text() == account_number)
        {

            return;
        }
    }

    ComboboxItem* item = new ComboboxItem(this);
    QPixmap pixmap(":/White/closePressed");
    item->m_label->setText(edit->text());
    item->button->setIcon(pixmap);
    item->button->setIconSize(pixmap.size());
    connect(item, SIGNAL(chooseAccount(const QString&)), this, SLOT(onChooseAccount(const QString&)));
    connect(item, SIGNAL(showAccount(QString)), this, SLOT(showAccount(QString)));
    QListWidgetItem* widgetItem = new QListWidgetItem(m_listWidget);
    m_listWidget->setItemWidget(widgetItem, item);
    }
    if(ui->LoginlineEdit->text().isEmpty()||(ui->LogincomboBox->lineEdit()->text().isEmpty())){
        QMessageBox message(QMessageBox::NoIcon, "提示?", "用户名或密码不能为空", QMessageBox::Yes | QMessageBox::No, NULL);

        if(message.exec() == QMessageBox::Yes)
        {
              message.reject();
        }
    }
}

void Widget::handleTimeout()
{
    this->setCursor(Qt::ArrowCursor);

}
