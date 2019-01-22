#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void slotNew();
    ~MainWindow();

signals:
    void startText(QString &text);

private:
    void slotOpen();
    void slotSave();
    void updateTitle();
    bool askForFileSaveAndClose();
    void saveAs();
    void closeWindow();

private:
    Ui::MainWindow *ui;
    QString mFileName;
    QFile mFile;

};

#endif // MAINWINDOW_HPP
