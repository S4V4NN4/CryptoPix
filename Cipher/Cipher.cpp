#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const char pngN[] = { -119, 80, 78, 71, 13, 10, 26, 10 };
const char pngK[] = {  };
const char jpgN[] = { -1, -40, -1, -32, 0, 16, 74, 70, 73, 70, 0 };
int key[4];


int randd()
{
    int random = std::rand() % 256 - 128; // Генерируем случайное число в диапазоне от -128 до 127
    return random;
}



void createKey(int k[])
{
    for (int i = 0; i < 4; i++)
    {
        k[i] = randd();
    }
}



char* rassh(string name)
{
    char* rassh = new char[5];
    int j = 0;
    for (int i = name.length() - 4; i < name.length(); i++)
    {
        rassh[j] = name[i];
        j = j + 1;
    }
    rassh[4] = '\0';
    return rassh;
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
    int razzm;
    char* rasssh = rassh(name);
    if (sravnStr(rasssh, ".png"))
    {
        razzm = 1;
    }
    else if (sravnStr(rasssh, ".jpg"))
    {
        razzm = 2;
    }
    else if (sravnStr(rasssh, "jpeg"))
    {
        razzm = 0;
    }
    else
    {
        cout << ":(";
        return;
    }


    char* buff = new char[name.length() + 9];
    char mod[] = "_modified";
    if (razzm)
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
            buff[name.length() - 4 + 9 + i] = rasssh[i];
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
            buff[name.length() - 5 + 10 + i] = rasssh[i];
        }
    }
    buff[name.length() + 9] = '\0';

    string saveFilePath = buff;


    // cout << '\n' << buff << '\n';


    ofstream saveFile(saveFilePath, ios::binary);
    if (!saveFile.is_open())
    {
        cout << "Ошибка при открытии файла: " << saveFilePath << "\n";
        delete[] buff;
        delete[] rasssh;
        return;
    }


    for (const char& ch : v)
    {
        saveFile.put(ch);
    }


    saveFile.close();
    delete[] buff;
    delete[] rasssh;
}

void decrypt(vector<char>& v)
{





}



void dec_encFunc(vector<char>& v, const int key[], string name)
{
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = int(v[i]) ^ key[i % 4];
    }
}






int main() 
{
    srand(time(nullptr));
    setlocale(LC_ALL, "russian");
    string imageFilePath = "D:\\logo.png";
    char* rasssh;
    rasssh = rassh(imageFilePath);
    cout << rasssh << '\n';

    // std::cin >> imageFilePath;
    // cout << imageFilePath << '\n';

    std::ifstream imageFile(imageFilePath, ios::binary);
    if (!imageFile.is_open()) 
    {
        cout << "Ошибка при открытии файла: " << imageFilePath << "\n";
        return 1;
    }


    vector<char> Img;
    char ch;
    while (imageFile.get(ch)) 
    {
        Img.push_back(ch);
    }


    /*
    // Выводим бинарные данные изображения в консоль
    for (const char& ch : Img) 
    {
        cout << static_cast<int>(ch) << " "; // Выводим байты как целые числа
    }
    cout << "\n";
    cout << "Размер изображения: " << Img.size() << " байт" << "\n";
    */





    createKey(key);
    vector<char> Img1 = { 123, 4, -5, 12, 90, -45, 1, 0, 4, 1, 9, 45, 32 };
    for (int i = 0; i < Img1.size(); ++i) { cout << Img1[i] << " "; }
    cout << '\n';
    dec_encFunc(Img1, key);
    for (int i = 0; i < Img1.size(); ++i) { cout << Img1[i] << " "; }

    cout << '\n';
    for (int i = 0; i < 8; ++i) { cout << pngN[i] << " "; }

    imageFile.close();

    delete[] rasssh;

    saveFile(Img, imageFilePath);
    
    return 0;
}