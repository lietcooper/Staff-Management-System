#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringlist>
#include <QString>
#include <QFont>
#include <QPushButton>
#include <QCheckBox>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView> // 指针类型
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QKeyEvent>
#define FILE "Staff_Table.txt"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    //set buttons and checkboxes
    QCheckBox showInfo;
    QPushButton add;
    QPushButton sort;
    QPushButton find;
    QPushButton del;
    QPushButton save;
    QPushButton clean;
    QPushButton exitsys;

    //staff list table
    QTableWidget* excel;

    //double click to write
    void editCell(int row, int column);
    void keyPressEvent(QKeyEvent *event);

    //initiate excel
    void init_Emp();

    //add new staff
    void add_Emp();

    //delete staff
    void del_Emp();

    //find staff
    int find_Emp();

    //sort staff by ID
    void sort_Emp();


    //save to file
    void save_Emp();

    //clean file
    void clean_Emp();

};

#endif // WIDGET_H
