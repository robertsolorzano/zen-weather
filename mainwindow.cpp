#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>
#include <QSvgWidget>
#include <QMap>
#include <cstdlib> // For getenv

// Icon mapping
QMap<QString, QString> iconMap = {
    {"01d", ":/icons/wi-day-sunny.svg"},
    {"01n", ":/icons/wi-night-clear.svg"},
    {"02d", ":/icons/wi-day-cloudy.svg"},
    {"02n", ":/icons/wi-night-alt-cloudy.svg"},
    {"03d", ":/icons/wi-cloud.svg"},
    {"03n", ":/icons/wi-cloud.svg"},
    {"04d", ":/icons/wi-cloudy.svg"},
    {"04n", ":/icons/wi-cloudy.svg"},
    {"09d", ":/icons/wi-showers.svg"},
    {"09n", ":/icons/wi-night-alt-showers.svg"},
    {"10d", ":/icons/wi-rain.svg"},
    {"10n", ":/icons/wi-night-alt-rain.svg"},
    {"11d", ":/icons/wi-thunderstorm.svg"},
    {"11n", ":/icons/wi-night-alt-thunderstorm.svg"},
    {"13d", ":/icons/wi-snow.svg"},
    {"13n", ":/icons/wi-night-alt-snow.svg"},
    {"50d", ":/icons/wi-fog.svg"},
    {"50n", ":/icons/wi-night-fog.svg"}
};

// Constructor for MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this)) // Initialize the network manager
    , backgroundPixmap(":/images/images/background.jpg") // Load the background image
{
    ui->setupUi(this); // Set up the UI components

    // Initialize the weather icon widget
    weatherIconWidget = new QSvgWidget(this);
    weatherIconWidget->setGeometry(350, 10, 100, 100); // Adjust the position and size as needed

    // Fetch the user's location and weather data
    fetchLocation();
}

// Destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui; // Clean up the UI pointer
}

// Custom paint event to draw the background image
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Draw the background image scaled to the window size
    painter.drawPixmap(rect(), backgroundPixmap);

    // Call the base class implementation
    QMainWindow::paintEvent(event);
}

// Custom resize event to ensure the background is repainted when the window is resized
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    update();
}

// Method to fetch the user's location
void MainWindow::fetchLocation()
{
    QNetworkRequest request(QUrl("http://ip-api.com/json"));
    disconnect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onWeatherDataReceived);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onLocationDataReceived);
    networkManager->get(request);
}

// Slot that gets called when location data is received
void MainWindow::onLocationDataReceived(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "Error", "Failed to fetch location data");
        return;
    }

    // Read the response data
    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonObject jsonObj = jsonDoc.object();

    // Parse the JSON data to get the city
    if (jsonObj.contains("city")) {
        QString city = jsonObj["city"].toString();
        fetchWeatherData(city);
    }

    reply->deleteLater();
}

// Method to fetch weather data from the API
void MainWindow::fetchWeatherData(const QString &city)
{
    // Fetch the API key from the environment variable
    const char* apiKey = std::getenv("WEATHER_API_KEY");
    if (!apiKey) {
        QMessageBox::critical(this, "Error", "API key not set in environment variables");
        return;
    }

    QString url = QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=imperial").arg(city, apiKey);

    // Make a GET request to the weather API
    QNetworkRequest request((QUrl(url)));
    disconnect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onLocationDataReceived);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onWeatherDataReceived);
    networkManager->get(request);
}

// Slot that gets called when weather data is received from the API
void MainWindow::onWeatherDataReceived(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::critical(this, "Error", "Failed to fetch weather data");
        return;
    }

    // Read the response data
    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonObject jsonObj = jsonDoc.object();

    // Parse the JSON data
    if (jsonObj.contains("main")) {
        QJsonObject main = jsonObj["main"].toObject();
        double temperature = main["temp"].toDouble();
        ui->temperatureLabel->setText(QString::number(temperature) + " °F");
    }

    if (jsonObj.contains("weather")) {
        QJsonArray weatherArray = jsonObj["weather"].toArray();
        if (!weatherArray.isEmpty()) {
            QJsonObject weather = weatherArray.first().toObject();
            QString description = weather["description"].toString();
            ui->descriptionLabel->setText(description);

            // Get the weather icon code and display the icon
            QString iconCode = weather["icon"].toString();
            displayWeatherIcon(iconCode);
        }
    }

    reply->deleteLater();
}

// Method to display weather icon
void MainWindow::displayWeatherIcon(const QString &iconCode)
{
    if (iconMap.contains(iconCode)) {
        QString iconPath = iconMap[iconCode];
        weatherIconWidget->load(iconPath);
    } else {
        QMessageBox::warning(this, "Warning", "Weather icon not found");
    }
}
