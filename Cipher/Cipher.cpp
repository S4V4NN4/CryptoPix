#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;



int randd()
{
    int random = std::rand() % 256 - 128; // Генерируем случайное число в диапазоне от -128 до 127
    return random;
}



int key[4];

void createKey(int k[])
{
    for (int i = 0; i < 4; i++)
    {
        k[i] = randd();
    }
}


void encrypt(vector<char>& v, string name)
{
    


}


bool sravnStr(char* ras, const char* ch)
{
    for (int i = 0; i < 4; i++)
    {
        if (ras[i] != ch[i]) { return 0; }
    }
    return 1;
}
void saveFile(vector<char>& v, string name)
{
    bool razm;
    char* rassh = new char [5];
    int j = 0;
    for (int i = name.length() - 4; i < name.length(); i++)
    {
        rassh[j] = name[i];
        j = j + 1;
    }
    rassh[4] = '\0';
    if (sravnStr(rassh, ".png"))
    {
        razm = 1;
    }
    else if (sravnStr(rassh, ".jpg"))
    {
        razm = 1;
    }
    else if (sravnStr(rassh, "jpeg"))
    {
        razm = 0;
    }
    else
    {
        return;
        cout << ":(";
    }


    // Путь к файлу для сохранения
    char* buff = new char[name.length() + 9];
    char mod[] = "_modified";
    if (razm)
    {
        for (int i = 0; i < name.length() - 4; i++)
        {
            buff[i] = name[i];
        }
        for (int i = 0; i < 9; i++)
        {
            buff[name.length() - 4 + i] = mod[i];
        }
        for (int i = 0; i < 4; i++)
        {
            buff[name.length() - 4 + 9 + i] = rassh[i];
        }
    }
    else
    {
        for (int i = 0; i < name.length() - 5; i++)
        {
            buff[i] = name[i];
        }
        for (int i = 0; i < 9; i++)
        {
            buff[name.length() - 5 + i] = mod[i];
        }
        buff[name.length() - 5 + 9] = '.';
        for (int i = 0; i < 4; i++)
        {
            buff[name.length() - 5 + 10 + i] = rassh[i];
        }
    }
    buff[name.length() + 9] = '\0';

    string saveFilePath = buff;

    // cout << '\n' << buff << '\n';


    // Открываем файл в бинарном режиме для записи
    std::ofstream saveFile(saveFilePath, ios::binary);
    if (!saveFile.is_open())
    {
        cout << "Ошибка при открытии файла: " << saveFilePath << "\n";
        return;
    }

    // Записываем данные из вектора в файл
    for (const char& ch : v)
    {
        saveFile.put(ch);
    }

    // Закрываем файл
    saveFile.close();
    delete[] rassh;
}

void decrypt(vector<char>& v)
{





}


int main() 
{
    srand(time(nullptr));
    setlocale(LC_ALL, "russian");
    string imageFilePath = "D:\\Download\\1234.jpeg"; //"D:\\logo.png"; // Путь к изображению
    //string imageFilePath = "D:\\logo.png";
    // std::cin >> imageFilePath;
    // cout << imageFilePath << '\n';
    // Открываем файл в бинарном режиме
    std::ifstream imageFile(imageFilePath, ios::binary);
    if (!imageFile.is_open()) 
    {
        cout << "Ошибка при открытии файла: " << imageFilePath << "\n";
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


    decrypt(Img);



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



    saveFile(Img, imageFilePath);
    /*
    // Путь к файлу для сохранения
    string saveFilePath = "D:\\Download\\1234_modified.jpeg";

    // Открываем файл в бинарном режиме для записи
    std::ofstream saveFile(saveFilePath, ios::binary);
    if (!saveFile.is_open())
    {
        cout << "Ошибка при открытии файла: " << saveFilePath << "\n";
        return 1;
    }

    // Записываем данные из вектора в файл
    for (const char& ch : Img)
    {
        saveFile.put(ch);
    }

    // Закрываем файл
    saveFile.close();
    */
    return 0;
}