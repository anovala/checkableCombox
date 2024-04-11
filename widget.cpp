#include "widget.h"
#include "./ui_widget.h"
#include <QCheckBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("comboBox with CheckBox");
    mpListWidget = new QListWidget();
    ui->comboBox->setModel(mpListWidget->model());
    ui->comboBox->setView(mpListWidget);

    QListWidgetItem *item = new QListWidgetItem(mpListWidget);
    mpListWidget->addItem(item);
}

Widget::~Widget()
{
    delete mpListWidget;
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();

    QListWidgetItem *item = new QListWidgetItem(text,mpListWidget);
    Qt::ItemFlags flags = item->flags();
    item->setFlags(flags | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    item->setData(Qt::CheckStateRole,Qt::Unchecked);
    //QCheckBox *chkBox = new QCheckBox(mpListWidget);
    item->setTextAlignment(Qt::AlignCenter);

    mpListWidget->addItem(item);
    //mpListWidget->setItemWidget(item,chkBox);
    //mpListWidget->addItem(text);
}


void Widget::on_comboBox_currentIndexChanged(int index)
{
    QListWidgetItem *item = mpListWidget->item(index);
    if(!item)
        return;

    QString text = item->text();

    QWidget *widget = mpListWidget->itemWidget(item);
    //QCheckBox *chkBox = dynamic_cast<QCheckBox *>(widget);
    Qt::CheckState chkStat = item->checkState();

    /*
    if(!chkBox)
    {
        ui->textEdit->append("null");
        return;
    }
        */
    QString chkStr = (chkStat==Qt::Checked)?"Checked":"UnChecked";

    QString sumText = QString("index: %1  text: %2  checkstate: %3")\
                          .arg(index).arg(text).arg(chkStr);
    ui->textEdit->append(sumText);
}

