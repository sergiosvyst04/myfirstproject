#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->action_New, &QAction::triggered, this, &MainWindow::slotNew, Qt::UniqueConnection);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::slotOpen, Qt::UniqueConnection);
    connect(ui->action_Save, &QAction::triggered, this, &MainWindow::slotSave, Qt::UniqueConnection);
    connect(ui->action_Save_as, &QAction::triggered, this, &MainWindow::saveAs, Qt::UniqueConnection);
    connect(ui->action_Exit_3, &QAction::triggered, this, &MainWindow::closeWindow, Qt::UniqueConnection);
//    connect(this, &MainWindow::startText, ui->plainTextEdit, &QPlainTextEdit::setPlainText, Qt::UniqueConnection );

    QList<QAction*> ls = {ui->action_New, ui->action_Open, ui->action_Save, ui->action_Save_as, ui->action_Exit_3};
    ui->mainToolBar->addActions(ls);
    slotNew();
}

void MainWindow::slotNew()
{
    mFileName = "UntitledFile";

    if(!askForFileSaveAndClose())
    {
        return;
    }

    ui->plainTextEdit->clear();
    setWindowModified(false);

    updateTitle();
}

bool MainWindow::askForFileSaveAndClose()
{
    if(isWindowModified())
    {
        int lResult = QMessageBox::question(this, tr("Save changes"),
                                            QString(tr("File %1 is modified. Do you want to save your changes?")).arg(mFile.fileName()),
                                            QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
        if(QMessageBox::Yes == lResult)
        {
            slotSave();
        }
        else{
            if(QMessageBox::Cancel == lResult)
            {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::slotOpen()
{
    QString lFileName = QFileDialog::getOpenFileName(this, tr("open file"), QDir::homePath(),
                                                     tr("Text files(*.txt);; all files (*.*)"));
    if(lFileName.isEmpty())
        return;
    if(!askForFileSaveAndClose())
    {
        return;
    }

    QFile lFile(lFileName);

    if(lFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        mFileName = lFileName;
        ui->plainTextEdit->setPlainText(lFile.readAll());
        lFile.close();

        setWindowModified(false);
        updateTitle();
    }
    else{
        QMessageBox::warning(this, tr("Error"),
                             QString(tr("Could not open file %1 for reading")).arg(lFile.fileName()), QMessageBox::Ok);
    }
}


void MainWindow::saveAs()
{
    QString lFileName = QFileDialog::getSaveFileName(this, tr("Save file as..."),
                                                     QDir::homePath(),
                                                     tr("Text files (*.txt);;all files (*.*)"));


    if (lFileName.isEmpty())
    {
        return;
    }

    QFile lFile(lFileName);

    if (lFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        mFileName = lFileName;

        QByteArray lData;

        lData.append(ui->plainTextEdit->toPlainText());
        lFile.write(lData);
        lFile.close();

        setWindowModified(false);
    }
    else
    {

        QMessageBox::warning(this, tr("Error"), QString(tr("Could not open file %1 for writing")).arg(lFile.fileName()), QMessageBox::Ok);
    }
}

void MainWindow::slotSave()
{

    QString lFileName = QFileDialog::getSaveFileName(this, tr("Save file..."),
                                                     QDir::homePath(),
                                                     tr("Text files (*.txt);;all files (*.*)"));


    if (lFileName.isEmpty())
    {
        return;
    }

    QFile lFile(lFileName);

    if (lFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        mFileName = lFileName;

        QByteArray lData;

        lData.append(ui->plainTextEdit->toPlainText());
        lFile.write(lData);
        lFile.close();

        setWindowModified(false);
    }
    else
    {

        QMessageBox::warning(this, tr("Error"), QString(tr("Could not open file %1 for writing")).arg(lFile.fileName()), QMessageBox::Ok);
    }

}

void MainWindow::closeWindow()
{
    this->close();
    QString str = ui->plainTextEdit->toPlainText();

    emit startText(str);
}

void MainWindow::updateTitle()
{
    QString lTitle = QString("Text editor - %1[*]").arg(mFileName);

    setWindowTitle(lTitle);
}

MainWindow::~MainWindow()
{
    delete ui;
}
