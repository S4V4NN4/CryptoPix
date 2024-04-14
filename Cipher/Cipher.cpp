#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int randd()
{
    std::srand(std::time(nullptr));
    int random = std::rand() % 256 - 128; // Генерируем случайное число в диапазоне от -128 до 127
    return random;
}


void encrypt(vector<char>& v)
{
    for (int i = 0; i < 8; i++)
    {
        v[i] = randd();
    }


}

void decrypt(vector<char>& v, string name)
{
    char* rassh = new char [4];
    for (int i = name.length() - 4; i < name.length(); i++)
    {
        rassh[i - name.length() - 4] = name[i];
        cout << rassh[i - name.length() - 4];
    }
    if (rassh == ".png")
    {
        cout << "png";
    }
    else if (rassh == ".jpg")
    {
        cout << "jpg";
    }
    else if (rassh == "jpeg")
    {
        cout << "jpeg";
    }
    else
    {
        cout << ":(";
    }
    delete[] rassh;
}


int main() {
    //setlocale(LC_ALL, "russian");
    string imageFilePath = "D:\\Download\\1234.jpeg"; //"D:\\logo.png"; // Путь к изображению
    // std::cin >> imageFilePath;

    // Открываем файл в бинарном режиме
    std::ifstream imageFile(imageFilePath, ios::binary);
    if (!imageFile.is_open()) 
    {
        cerr << "Ошибка при открытии файла: " << imageFilePath << "\n";
        return 1;
    }

    // Читаем данные из файла в буфер
    vector<char> Img;
    char ch;
    while (imageFile.get(ch)) 
    {
        Img.push_back(ch);
    }


    // Img[Img.size() - 1]

    decrypt(Img, imageFilePath);
    /*
    // Выводим бинарные данные изображения в консоль
    for (const char& ch : Img) 
    {
        cout << static_cast<int>(ch) << " "; // Выводим байты как целые числа
    }
    cout << "\n";

    // Теперь у нас есть бинарные данные изображения в векторе 'buffer'

    cout << "Размер изображения: " << Img.size() << " байт" << "\n";
    */
    /*
    for (int i = 0; i < 8; i++)
    {
        cout << Img[i] << " ";
    }
    cout << "\n";
    encrypt(Img);
    for (int i = 0; i < 8; i++)
    {
        cout << Img[i] << " ";
    }
    cout << "\n";
    Img[0] = -1; Img[1] = -40; Img[2] = -1; Img[3] = -32; Img[4] = 0; Img[5] = 16; Img[6] = 74; Img[7] = 70;
    for (int i = 0; i < 8; i++)
    {
        cout << Img[i] << " ";
    }
    cout << "\n";
    */

    // Закрываем файл
    imageFile.close();

    return 0;
}