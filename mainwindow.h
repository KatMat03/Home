#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <MyTCPServer.h>
#include <QStyle>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnStartSerwer_clicked();
    void newClientConnected();
    void on_btnSendToAll_clicked();
    void clientDisconnected();
    void clientDataReceived(QString message);

private:
    Ui::MainWindow *ui;
    MyTCPServer *_server;
};
#endif // MAINWINDOW_H
