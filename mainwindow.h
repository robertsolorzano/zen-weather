#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QResizeEvent>
#include <QSvgWidget>
#include <QLabel>
#include <QBuffer>

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

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager; // Manager to handle network requests
    void fetchWeatherData(const QString &city); // Method to fetch weather data
    void fetchLocation(); // Method to fetch the user's location
    void displayWeatherIcon(const QString &iconCode); // Method to display weather icon
    QPixmap backgroundPixmap;
    QSvgWidget *weatherIconWidget; // Widget to display SVG icons

    QString modifySvgColor(const QString &filePath, const QString &color); // Method to modify SVG color
};

#endif // MAINWINDOW_H
