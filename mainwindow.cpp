#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <qjsondocument.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnShowBooks_clicked()
{
    QNetworkRequest request(QUrl("http://localhost/io_exc/book"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        //Authenticate
        QString username="admin";
        QString password="1234";
        QString concatenatedCredentials = username + ":" + password;
           QByteArray data = concatenatedCredentials.toLocal8Bit().toBase64();
           QString headerData = "Basic " + data;
           request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

        QNetworkAccessManager nam;
        QNetworkReply *reply = nam.get(request);
        while (!reply->isFinished())
        {
            qApp->processEvents();
        }
        QByteArray response_data = reply->readAll();

        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject jsobj = json_doc.object();
        QJsonArray jsarr = json_doc.array();

        QString book;
        foreach (const QJsonValue &value, jsarr) {
          QJsonObject jsob = value.toObject();
          book+=jsob["id_book"].toString()+", "+jsob["name"].toString()+", "+jsob["author"].toString()+"\r";
          ui->txtBooks->setText(book);
        }

        reply->deleteLater();
}

void MainWindow::on_btnAddBook_clicked()
{
    QString name, author, isbn;
    name=ui->addName->text();
    author=ui->addAuthor->text();
    isbn=ui->addIsbn->text();

    QNetworkRequest request(QUrl("http://localhost/io_exc/book"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        //Authenticate
        QString username="admin";
        QString password="1234";
        QString concatenatedCredentials = username + ":" + password;
           QByteArray data = concatenatedCredentials.toLocal8Bit().toBase64();
           QString headerData = "Basic " + data;
           request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

        QJsonObject json;
        json.insert("name",name);
        json.insert("author",author);
        json.insert("isbn",isbn);
        QNetworkAccessManager nam;
        QNetworkReply *reply = nam.post(request, QJsonDocument(json).toJson());
        while (!reply->isFinished())
        {
            qApp->processEvents();
        }
        QByteArray response_data = reply->readAll();
        qDebug()<<response_data;
        ui->labelInfo->setText("Added : "+response_data);
        this->on_btnShowBooks_clicked();
        reply->deleteLater();

}

void MainWindow::on_btnDeleteBook_clicked()
{
    QString id=ui->deleteId->text();
    QNetworkRequest request(QUrl("http://localhost/io_exc/book"+id));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        //Authenticate
        QString username="admin";
        QString password="1234";
        QString concatenatedCredentials = username + ":" + password;
           QByteArray data = concatenatedCredentials.toLocal8Bit().toBase64();
           QString headerData = "Basic " + data;
           request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

        QNetworkAccessManager nam;
        QNetworkReply *reply = nam.deleteResource(request);
        while (!reply->isFinished())
        {
            qApp->processEvents();
        }
        QByteArray response_data = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(response_data);
        ui->labelInfo->setText("Deleted book id="+id);
        ui->deleteId->setText("");
        this->on_btnShowBooks_clicked();
        reply->deleteLater();
}

void MainWindow::on_btnUpdateBook_clicked()
{
    QString id, name, author,isbn;
    id=ui->updateId->text();
    name=ui->updateName->text();
    author=ui->updateAuthor->text();
    isbn=ui->updateIsbn->text();

    QNetworkRequest request(QUrl("http://localhost/io_exc/book/"+id));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        //Authenticate
        QString username="admin";
        QString password="1234";
        QString concatenatedCredentials = username + ":" + password;
           QByteArray data = concatenatedCredentials.toLocal8Bit().toBase64();
           QString headerData = "Basic " + data;
           request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

        QJsonObject json;
        json.insert("name",name);
        json.insert("author",author);
        json.insert("isbn",isbn);
        QNetworkAccessManager nam;
        QNetworkReply *reply = nam.put(request, QJsonDocument(json).toJson());
        while (!reply->isFinished())
        {
            qApp->processEvents();
        }
        QByteArray response_data = reply->readAll();
        qDebug()<<response_data;
        ui->labelInfo->setText("Added : "+response_data);
        this->on_btnShowBooks_clicked();
        reply->deleteLater();

}




void MainWindow::on_btnLogin_clicked()
{
    QString loginUsername,loginPassword;
    loginUsername=ui->lineEditUsername->text();
    loginPassword=ui->lineEditPassword->text();

    QNetworkRequest request(QUrl("http://localhost/io_exc/login"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        //Authenticate
        QString username="admin";
        QString password="1234";
        QString concatenatedCredentials = username + ":" + password;
           QByteArray data = concatenatedCredentials.toLocal8Bit().toBase64();
           QString headerData = "Basic " + data;
           request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

           QJsonObject json;
           json.insert("username",loginUsername);
           json.insert("password",loginPassword);
           QNetworkAccessManager nam;
           QNetworkReply *reply = nam.post(request, QJsonDocument(json).toJson());
        while (!reply->isFinished())
        {
            qApp->processEvents();
        }
        QByteArray response_data = reply->readAll();

        qDebug()<<"DATA:"+response_data;

        reply->deleteLater();

        if(response_data.compare("true")==0){
            ui->labelLoginTest->setText("Right");
        }
        else {
            ui->labelLoginTest->setText("Wrong");
        }
}
