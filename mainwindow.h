#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
    void on_fetchWeatherButton_clicked();
    void onWeatherDataReceived(QNetworkReply* reply); // Slot to handle API response

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager; // Manager to handle network requests
    void fetchWeatherData(const QString &city); // Method to fetch weather data
};

#endif // MAINWINDOW_H
