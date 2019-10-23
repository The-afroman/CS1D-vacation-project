#include "finalpage.h"
#include "ui_finalpage.h"

finalpage::finalpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finalpage)
{
    ui->setupUi(this);
    ui->tripTree->setColumnCount(5);
}


void finalpage::initUI(){

}

/*! Used to display the tree widget. The function adds the
 * data collected throught the trip and displays it in the tree widget*/
void finalpage::addTreeItem(const tripPage & page){
    qDebug() << "made it into add tree item function for " << page.getTitle() <<  endl;
    QTreeWidgetItem * item = new QTreeWidgetItem(ui->tripTree);
    item->setText(0, QString::fromStdString(page.getTitle().toStdString().substr(5)));
    item->setText(1, " ");
    //ui->tripTree->addTopLevelItem(item);
    string temp;
    double tempD;

    for(int i =0; i < page.getFoodListSize(); i++){
         QTreeWidgetItem * childItem = new QTreeWidgetItem();
         temp = page.getFoodLabels()[i]->text().toStdString();
         temp = temp.substr(0, temp.find("\n"));
         childItem->setText(1, QString::fromStdString("food " + temp));

         temp = page.getFoodLabels()[i]->text().toStdString();
         temp = temp.substr(temp.find("$"), 5);

         childItem->setText(2, QString::fromStdString(temp));

         tempD = stod(temp.substr(1));

         int x = page.getFoodQtyBox()[i]->value();

         childItem->setText(3, QString::fromStdString(std::to_string(x)));


         item->addChild(childItem);
    }

    QTreeWidgetItem *child = new QTreeWidgetItem();
    child->setText(3, "Subtotal: ");
    QString pageTotal = QString::number(page.getTotal(),'f', 2);
    child->setText(4, "$" + pageTotal);
    item->addChild(child);

}

/*! Sets the total cost then displays it using a label*/
void finalpage::setNetTotal(double value){
    net = value;
    QString netTotal = QString::number(net, 'f', 2);
    ui->totalLabel->setText(ui->totalLabel->text() + netTotal);
}

/*! Sets the distance then displays it using a label*/
void finalpage::setDistance(double distance)
{
    this->distance = distance;
    QString sDistance = QString::number(this->distance, 'f', 2);
    ui->distanceLabel->setText(ui->distanceLabel->text() + " " + sDistance + "km");
}

finalpage::~finalpage()
{
    delete ui;
}

/*! Returns to the main menu */
void finalpage::on_pushButton_clicked()
{
    emit backToMenu();
}
