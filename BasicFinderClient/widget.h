#ifndef WIDGET_H
#define WIDGET_H
#include "comboboxitem.h"
#include <QWidget>
#include <QPoint>
#include <QListWidget>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QPoint z;
private slots:
    void on_btnMin_clicked();

    void on_btnClose_clicked();
    void onChooseAccount(const QString&);
    void showAccount(const QString&);
    void on_LoginBtn_clicked();
    void handleTimeout();
private:
    Ui::Widget *ui;
    QListWidget* m_listWidget;

    //QHash<ComboboxItem*,QListWidgetItem*> itemhash;
};

#endif // WIDGET_H
