#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
class ComboboxItem : public QWidget
{
    Q_OBJECT
public:
    explicit ComboboxItem(QWidget *parent = 0);

    QLabel *m_img;
    QLabel *m_label;
    QHBoxLayout *m_layout;
    QPushButton* button;
    bool mouse_press;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void chooseAccount(const QString&);
    void showAccount(const QString&);

public slots:
    void potionclicked();
};

#endif // COMBOBOXITEM_H
