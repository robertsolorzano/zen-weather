# zen-weather

![preview](/assets/preview.png)

## Introduction

Zen Weather App is a minimalistic and aesthetically pleasing desktop application that displays the current weather for your location

## Features

- Automatically fetches weather data based on your current location
- Displays temperature and weather conditions
- Customizable background and icon colors

## Installation

### Prerequisites

- Qt Creator
- Qt framework
- C++ compiler

### Steps

1. **Clone the repository:**

    ```bash
    git clone https://github.com/yourusername/zen-weather-app.git
    cd zen-weather-app
    ```

2. **Set up the environment variables:**

    Add your OpenWeatherMap API key to your shell configuration file (`~/.zshrc` or `~/.bashrc`).

    ```bash
    echo 'export WEATHER_API_KEY=your_api_key_here' >> ~/.zshrc
    source ~/.zshrc
    ```

3. **Open the project in Qt Creator:**
    - Open Qt Creator.
    - Click on `File > Open File or Project...`.
    - Select the `zen-weather.pro` file from the cloned repository.

4. **Build the project:**
    - Click on the `Build` button or go to `Build > Build Project`.
    - Wait for the build to complete.

5. **Locate the build directory:**
    - After the build completes, exit Qt Creator.
    - Open your terminal and navigate to the build directory inside your project folder `zen-weather-app/build/`.

6. **Run the application:**

    ```bash
    ./zen-weather
    ```

## Usage

1. **Launch the application:**

    The app will automatically detect your location and display the current weather.

## Configuration

### Changing Background and Icon Colors

You can change the background and icon colors by modifying the CSS styles in the `mainwindow.ui` file.

### Adding Custom Icons

To add custom icons, place your SVG files in the `resources/icons` directory and update the `iconMap` in `mainwindow.cpp`.

## Technologies Used

- C++
- Qt Framework
- OpenWeatherMap API

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- [OpenWeatherMap API](https://openweathermap.org/api)
- [Qt Framework](https://www.qt.io/)
