#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QResizeEvent>
#include <QLabel>

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

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onWeatherDataReceived(QNetworkReply* reply); // Slot to handle API response
    void onLocationDataReceived(QNetworkReply* reply); // Slot to handle location API response
    void onIconDataReceived(QNetworkReply* reply); // Slot to handle icon image response

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager; // Manager to handle network requests
    void fetchWeatherData(const QString &city); // Method to fetch weather data
    void fetchLocation(); // Method to fetch the user's location
    void fetchWeatherIcon(const QString &iconCode); // Method to fetch weather icon
    QPixmap backgroundPixmap;
    QLabel *weatherIconLabel;
};

#endif // MAINWINDOW_H
