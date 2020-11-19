#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnShowBooks_clicked();

    void on_btnAddBook_clicked();

    void on_btnDeleteBook_clicked();

    void on_btnUpdateBook_clicked();


    void on_btnLogin_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
