#include <iostream>
#include <fstream>
#include <vector>

int main() {
    setlocale(LC_ALL, "russian");
    const std::string imageFilePath = "D:\\logo.png"; // Укажите путь к вашему изображению

    // Открываем файл в бинарном режиме
    std::ifstream imageFile(imageFilePath, std::ios::binary);
    if (!imageFile.is_open()) {
        std::cerr << "Ошибка при открытии файла: " << imageFilePath << std::endl;
        return 1;
    }

    // Читаем данные из файла в буфер
    std::vector<char> ImgBin;
    char ch;
    while (imageFile.get(ch)) {
        ImgBin.push_back(ch);
    }

    // Выводим бинарные данные изображения в консоль
    for (const char& ch : ImgBin) {
        std::cout << static_cast<int>(ch) << " "; // Выводим байты как целые числа
    }
    std::cout << std::endl;

    // Теперь у вас есть бинарные данные изображения в векторе 'buffer'
    // Можете обрабатывать их по своему усмотрению

    // Пример вывода размера изображения
    std::cout << "Размер изображения: " << ImgBin.size() << " байт" << std::endl;

    // Закрываем файл
    imageFile.close();

    return 0;
}