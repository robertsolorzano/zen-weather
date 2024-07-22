#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// Constructor for MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this)) // Initialize the network manager
{
    ui->setupUi(this); // Set up the UI components

    // Connect the fetchWeatherButton's clicked signal to the on_fetchWeatherButton_clicked slot
    connect(ui->fetchWeatherButton, &QPushButton::clicked, this, &MainWindow::on_fetchWeatherButton_clicked);

    // Connect the network manager's finished signal to the onWeatherDataReceived slot
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onWeatherDataReceived);
}

// Destructor for MainWindow
MainWindow::~MainWindow()
{
    delete ui; // Clean up the UI pointer
}

// Slot that gets called when fetchWeatherButton is clicked
void MainWindow::on_fetchWeatherButton_clicked()
{
    // Get the text from the cityLineEdit widget
    QString city = ui->cityLineEdit->text();

    // Fetch weather data for the entered city
    fetchWeatherData(city);
}

// Method to fetch weather data from the API
void MainWindow::fetchWeatherData(const QString &city)
{
    // Define the API key and the URL for the weather API
    QString apiKey = "a14e91e6cc4118d2abc0f1608eeff13d";
    QString url = QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric").arg(city, apiKey);

    // Make a GET request to the weather API
    networkManager->get(QNetworkRequest(QUrl(url)));
}

// Slot that gets called when weather data is received from the API
void MainWindow::onWeatherDataReceived(QNetworkReply* reply)
{
    // Check for network errors
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
        ui->temperatureLabel->setText(QString::number(temperature) + " °C");
    }

    if (jsonObj.contains("weather")) {
        QJsonArray weatherArray = jsonObj["weather"].toArray();
        if (!weatherArray.isEmpty()) {
            QJsonObject weather = weatherArray.first().toObject();
            QString description = weather["description"].toString();
            ui->descriptionLabel->setText(description);
        }
    }

    reply->deleteLater();
}
