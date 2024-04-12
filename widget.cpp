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

    /*
    connect(mpListWidget,&QListWidget::itemClicked,[](QListWidgetItem *item){
        if(item->checkState() == Qt::Checked)
            item->setCheckState(Qt::Unchecked);
        else
            item->setCheckState(Qt::Checked);
    });
    */
 }

Widget::~Widget()
{
    delete mpListWidget;
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();

    QListWidgetItem *item = new QListWidgetItem("",mpListWidget);
    Qt::ItemFlags flags = item->flags();
    //item->setFlags(flags | Qt::ItemIsUserCheckable);
    //item->setData(Qt::CheckStateRole,Qt::Checked);
    QCheckBox *chkBox = new QCheckBox(mpListWidget);
    item->setTextAlignment(Qt::AlignCenter);
    chkBox->setText(text);

    qDebug()<<chkBox->size();

    mpListWidget->addItem(item);
    mpListWidget->setItemWidget(item,chkBox);
}


void Widget::on_comboBox_currentIndexChanged(int index)
{
    QListWidgetItem *item = mpListWidget->item(index);
    if(!item)
        return;


    QWidget *widget = mpListWidget->itemWidget(item);
    QCheckBox *chkBox = dynamic_cast<QCheckBox *>(widget);


    if(!chkBox)
    {
        ui->textEdit->append("null");
        return;
    }

    Qt::CheckState chkStat = chkBox->checkState();
    QString chkStr = (chkStat==Qt::Checked)?"Checked":"UnChecked";
    QString text = chkBox->text();

    QString sumText = QString("index: %1  text: %2  checkstate: %3")\
                          .arg(index).arg(text).arg(chkStr);
    ui->textEdit->append(sumText);
}

