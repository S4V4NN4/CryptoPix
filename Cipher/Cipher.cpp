#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const char pngN[] = { -119, 80, 78, 71, 13, 10, 26, 10 }; // начало PNG - 8 байт
const char pngK[] = { 0, 0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126 }; // конец PNG - 12 байт
const char jpgN[] = { -1, -40, -1, -32 };//, 0, 16, 74, 70, 73, 70, 0 }; // начало JPEG/JPG
int key[4];


int randd()
{
    int random = std::rand() % 256 - 128; // Генерируем случайное число в диапазоне от -128 до 127
    return random;
}



void createKey(int key[])
{
    for (int i = 0; i < 4; i++)
    {
        key[i] = randd();
    }
}

bool sravnStr(char* sr, const char* ch)
{
    for (int i = 0; i < 4; i++)
    {
        if (sr[i] != ch[i]) { return 0; }
    }
    return 1;
}


int extFile(string name)
{
    char* ext = new char[5];
    int j = 0;
    for (int i = name.length() - 4; i < name.length(); i++)
    {
        ext[j] = name[i];
        j = j + 1;
    }
    ext[4] = '\0';
    if (sravnStr(ext, ".png"))
    {
        delete[] ext;
        return 1;
    }
    else if (sravnStr(ext, ".jpg"))
    {
        delete[] ext;
        return 2;
    }
    else if (sravnStr(ext, "jpeg"))
    {
        delete[] ext;
        return 3;
    }
    else
    {
        cout << ":( 1";
        delete[] ext;
        return -1;
    }
}


void plusRas(char*& buff, string name, const char* ch, int j)
{
    char mod[] = "_modified";
    for (int i = 0; i < name.size() - 4; i++)
    {
        buff[i] = name[i];
    }
    for (int i = 0; i < 9; i++)
    {
        buff[name.length() - 4 + i] = mod[i];
    }
    for (int i = 0; i < 4 + j; i++)
    {
        buff[name.length() - 4 + 9 + i] = ch[i];
    }
}
void newName(string name, string& saveFilePath)
{
    char* buff = new char[name.length() + 10];
    int ext = extFile(name);
    if (ext == -1)
    {
        cout << ":( 2";
        return;
    }
    else if (ext == 1)
    {
        plusRas(buff, name, ".png", 0);
    }
    else if (ext == 2)
    {
        plusRas(buff, name, ".jpg", 0);
    }
    else if (ext == 3)
    {
        plusRas(buff, name, ".jpeg", 1);
    }
    else
    {
        cout << ":( 3";
        return;
    }
    buff[name.length() + 9] = '\0';
    saveFilePath = buff;
    delete[] buff;
}
void saveInFile(vector<char>& v, string name)
{
    string saveFilePath;
    newName(name, saveFilePath);

    ofstream saveFile(saveFilePath, ios::binary);
    if (!saveFile.is_open())
    {
        cout << "Ошибка при открытии файла: " << saveFilePath << "\n";
        return;
    }
    for (const char& ch : v)
    {
        saveFile.put(ch);
    }


    saveFile.close();
}



void Enc(vector<char>& v, string name)
{
    int ext = extFile(name);
    if (ext == -1)
    {
        cout << ":( 4";
        return;
    }
    else if (ext == 1)
    {
        int j = 0;
        for (int i = 3; i >= 0; i--)
        {
            key[j] = v[v.size() - 13 - i];
            j++;
            v.erase(v.begin() + v.size() - 13 - i);
        }
    }
    else if (ext == 2 || ext == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            v.push_back(key[i]);
        }
    }
    else
    {
        cout << ":( 5";
        return;
    }
}


void Dec(vector<char>& v, string name)
{
    int ext = extFile(name);
    if (ext == -1)
    {
        cout << ":( 4";
        return;
    }
    else if (ext == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            v.insert(v.begin() + v.size() - 12, key[i]);
        }
    }
    else if (ext == 2 || ext == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            v.push_back(key[i]);
        }
    }
    else
    {
        cout << ":( 5";
        return;
    }
}


void returnExt(vector<char>& v, string name)
{
    int ext = extFile(name);
    if (ext == -1)
    {
        cout << ":( 4";
        return;
    }
    else if (ext == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            v[i] = pngN[i];
        }
        int j = 0;
        for (int i = 12; i > 0; i--)
        {
            v[v.size() - i] = pngK[j];
            j++;
        }
    }
    else if (ext == 2 || ext == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            v[i] = jpgN[i];
        }
    }
    else
    {
        cout << ":( 5";
        return;
    }
}
void DecEnc(vector<char>& v, int key[], string name, bool enc)
{
    if (enc)
    {
        Enc(v, name);
        for (int i = 0; i < v.size(); ++i)
        {
            v[i] = int(v[i]) ^ key[i % 4];
        }
    }
    else
    {
        createKey(key);
        for (int i = 0; i < v.size(); ++i)
        {
            v[i] = int(v[i]) ^ key[i % 4];
        }
        Dec(v, name);
    }
    returnExt(v, name);
}






int main() 
{
    srand(time(nullptr));
    setlocale(LC_ALL, "russian");
    string imageFilePath = "D:/logo_modified.png"; // "D:/logo_modified.png"

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


    DecEnc(Img, key, imageFilePath, 1);




    // Выводим бинарные данные изображения в консоль
    //for (const char& ch : Img) 
    //{
    //    cout << static_cast<int>(ch) << " "; // Выводим байты как целые числа
    //}
    //cout << "\n";
    //cout << "Размер изображения: " << Img.size() << " байт" << "\n";
    for (int i = 0; i < 4; i++)
    {
        cout << key[i] << " ";
    }


    imageFile.close();

    saveInFile(Img, imageFilePath);
    return 0;
}