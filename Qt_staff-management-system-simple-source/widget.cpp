#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1400,700);
    // set buttons' text and font
    QFont font("Arial", 12);

    //create horizontal layout (must be a pointer)
    QHBoxLayout* hlayout = new QHBoxLayout;

    this->showInfo.setText("Show table");
    this->showInfo.setFont(font);
    this->showInfo.setChecked(true);

    this->add.setText("Add new staff");
    this->add.setFont(font);

    this->sort.setText("Sort by ID");
    this->sort.setFont(font);

    this->find.setText("Find staff");
    this->find.setFont(font);

    this->save.setText("Save changes");
    this->save.setFont(font);

    this->del.setText("Delete staff");
    this->del.setFont(font);

    this->clean.setText("Clear all");
    this->clean.setFont(font);

    this->exitsys.setText("Exit");
    this->exitsys.setFont(font);

    // add buttons to Hlayout
    hlayout->addWidget(&showInfo);
    hlayout->addWidget(&add);
    hlayout->addWidget(&sort);
    hlayout->addWidget(&find);
    hlayout->addWidget(&save);
    hlayout->addWidget(&del);
    hlayout->addWidget(&clean);
    hlayout->addWidget(&exitsys);


    // create vertical layout (must be a pointer)
    QVBoxLayout* vlayout = new QVBoxLayout;
    // add H to V
    vlayout->addLayout(hlayout);
    hlayout->setAlignment(Qt::AlignTop);

    //init table
    this->excel = new QTableWidget;
    //set table header
    this->excel->setColumnCount(8);;
    this->excel->resize(1400,500);
    this->excel->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Name"<<"Gender"<<"Department"<<"Position"<<"Phone Nmber"<<"Email"<<"Birthday");
    this->excel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // self-adaptation
    QFont Hfont("Calibri", 12, QFont::Bold);
    this->excel->horizontalHeader()->setFont(Hfont); // set font

    //set contents
    init_Emp();

    //this->excel->verticalHeader()->setHidden(true);  // hide row index

    //add table to Vlayout
    vlayout->addWidget(excel);

    //add vlayout to widget
    this->setLayout(vlayout);

    //connect excel and checkpoint("show table)
    connect(&showInfo, &QCheckBox::stateChanged,[&](){
        if(showInfo.isChecked()){
           excel->show();
        }
        else{
           excel->hide();
        }
    });

    //connect button("add") with add_Emp()
    connect(&add, QPushButton::clicked, this, &Widget::add_Emp);

    //double click to write cells
    connect(excel, &QTableWidget::cellDoubleClicked, this, &Widget::editCell);

    //connect button("sort") with sort_Emp()
    connect(&sort, &QPushButton::clicked, this, &Widget::sort_Emp);

    //connect button("find") with find_Emp()
    connect(&find, &QPushButton::clicked, this, &Widget::find_Emp);

    //connect button("save") with save_Emp()
    connect(&save, QPushButton::clicked, this, &Widget::save_Emp);

    //connect button("del") with del_Emp()
    connect(&del, &QPushButton::clicked, this, &Widget::del_Emp);

    //connect button("clean") with clean_Emp()
    connect(&clean,&QPushButton::clicked, this, &Widget::clean_Emp);

    //connect button("existsys") with exit
    connect(&exitsys,&QPushButton::clicked,this,[](){exit(0);});
}

Widget::~Widget()
{

}

//initiate staff table
void Widget::init_Emp()
{
    //select file
    QFile f(FILE);

    //open file and tell whether successfully opened
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Failed to open this file !"<<"Init failed.";
        return;
    }
    qDebug()<<"Open successfully!";
    
    //set table rows
    //read String from file
    QTextStream in(&f);
    //output.setCodec("UTF-8");
    int num = 0;
    while(!in.atEnd()){
        QString LineStr = in.readLine();
        QStringList LineList = LineStr.split('\t');
        int rowCount = this->excel->rowCount();
        this->excel->insertRow(rowCount);
        int colCount = this->excel->columnCount();
        for(int col = 0; col < colCount; ++col){
            this->excel->setItem(rowCount, col, new QTableWidgetItem(LineList[col]));
        }
        ++num;
    }
    f.close();
    qDebug()<<"File opened, get "<<num<<" lines.";
}

//add new staff
void Widget::add_Emp()
{
    int rowCount = this->excel->rowCount();
    qDebug()<<rowCount;
    this->excel->insertRow(rowCount);
    qDebug()<<this->excel->rowCount();

    QString new_id = QInputDialog::getText(nullptr, "Add New Staff","ID:");
    if(new_id == "") new_id = "NULL";
    for(int i = 0; i < rowCount; ++i){
        QTableWidgetItem* item = this->excel->item(i,0);
        if(item && item->text() == new_id){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Prompt");
            QString msg = QString("ID %1 already exists! Please retry.").arg(new_id);
            msgBox.setText(msg);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Ok){
                this->excel->removeRow(rowCount);
                return;
            }
        }
    }
    QString new_name = QInputDialog::getText(nullptr, "Add New Staff","Name:");
    if(new_name == "") new_name = "NULL";
    QString new_gender = QInputDialog::getText(nullptr, "Add New Staff","Gender:");
    if(new_gender == "") new_gender = "NULL";
    QString new_dep = QInputDialog::getText(nullptr, "Add New Staff","Department:");
    if(new_dep == "") new_dep = "NULL";
    QString new_pos = QInputDialog::getText(nullptr, "Add New Staff","Postiton:");
    if(new_pos == "") new_pos = "NULL";
    QString new_phone = QInputDialog::getText(nullptr, "Add New Staff","Phone:");
    if(new_phone == "") new_phone = "NULL";
    QString new_email = QInputDialog::getText(nullptr, "Add New Staff","Email:");
    if(new_email == "") new_email = "NULL";
    QString new_birth = QInputDialog::getText(nullptr, "Add New Staff","Birthday:");
    if(new_birth == "") new_birth = "NULL";

    this->excel->setItem(rowCount, 0, new QTableWidgetItem(new_id));
    this->excel->setItem(rowCount, 1, new QTableWidgetItem(new_name));
    this->excel->setItem(rowCount, 2, new QTableWidgetItem(new_gender));
    this->excel->setItem(rowCount, 3, new QTableWidgetItem(new_dep));
    this->excel->setItem(rowCount, 4, new QTableWidgetItem(new_pos));
    this->excel->setItem(rowCount, 5, new QTableWidgetItem(new_phone));
    this->excel->setItem(rowCount, 6, new QTableWidgetItem(new_email));
    this->excel->setItem(rowCount, 7, new QTableWidgetItem(new_birth));
}

//double click cells to write
void Widget::editCell(int row, int column)
{
    excel->editItem(excel->item(row, column));
}
void Widget::keyPressEvent(QKeyEvent *event) // press Enter to close edit mode
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        this->excel->closePersistentEditor(excel->currentItem());
    }
}

//find info , find by id/name
int Widget::find_Emp()
{
    int rowCount = this->excel->rowCount();
    int columnCount = this->excel->columnCount();

    //if no data, print "No staff!"
    if(rowCount == 0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Promt");
        msgBox.setText("No staff!");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok) return -1;
        return -1;
    }
    //data exists, input ID or name to index
    else{
        QString keyword = QInputDialog::getText(nullptr, "Search for staff","Input staff's ID or NAME here:");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Prompt");
        for (int row = 0; row < rowCount; ++row) {
            for (int col = 0; col < columnCount; ++col) {
                QTableWidgetItem* item = this->excel->item(row, col);
                if (item && item->text() == keyword) {
                    // match
                    this->excel->setCurrentCell(row, col);
                    msgBox.setText("Find staff!");
                    msgBox.addButton(QMessageBox::Ok);
                    int ret = msgBox.exec();
                    if(ret == QMessageBox::Ok) return row;
                }
            }
        }
        msgBox.setText("Staff doesn't exist!");
        msgBox.addButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok) return -1;
        return -1;
    }
}

//delete single staff
void Widget::del_Emp()
{
    int row = this->find_Emp();
    QMessageBox msgBox;
    if(row == -1) return;
    else{
        msgBox.setWindowTitle("Prompt");
        msgBox.setText("Sure to delete?");
        msgBox.addButton("Yes", QMessageBox::AcceptRole);
        QPushButton* noButton = msgBox.addButton("No", QMessageBox::RejectRole);
        msgBox.setDefaultButton(noButton);
        int ret = msgBox.exec();
        if(ret == QMessageBox::AcceptRole) this->excel->removeRow(row);

        return;
    }
}

//save to file
void Widget::save_Emp()
{
    QFile f(FILE);
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&f);
    for(int row = 0; row < excel->rowCount(); ++row){
        for(int col = 0; col < excel->columnCount(); ++col){
            QString cellData = excel->item(row,col)->text();
            out << cellData <<"\t";
        }
        out << endl;
    }
    f.close();

    //set prompt for button("save")
    QMessageBox msgBox;
    msgBox.setWindowTitle("Promt");
    msgBox.setText("Changes saved!");
    //add button and set default option
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    //show box, waiting for response
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        qDebug()<<"Confirmed.";
    }
}

//clean file
void Widget::clean_Emp()
{
    //set prompt for button("clean")
    QMessageBox msgBox;
    msgBox.setWindowTitle("Warning!");
    msgBox.setText("Sure to delete all data?");
    msgBox.addButton("Yes", QMessageBox::AcceptRole);
    QPushButton* noButton = msgBox.addButton("No", QMessageBox::RejectRole);
    msgBox.setDefaultButton(noButton);

    int ret = msgBox.exec();
    if(ret == QMessageBox::AcceptRole){
        //clean
        this->excel->clearContents();
        this->excel->setRowCount(0); //clearContents() only cleans content of cells, but leaves rows and columns
        save_Emp();
        qDebug()<<"file cleaned!";
        return;
    }
    else{
        //not clean
        qDebug()<<"clean file cancelled.";
        return;
    }
}

//sort employee by ID
void Widget::sort_Emp()
{
    this->excel->sortItems(0,Qt::AscendingOrder);
    qDebug()<<"Staff sorted!";
}
