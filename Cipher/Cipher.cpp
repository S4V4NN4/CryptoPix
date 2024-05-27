#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


const char pngN[] = { -119, 80, 78, 71, 13, 10, 26, 10 }; // начало PNG - 8 байт
const char pngK[] = { 0, 0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126 }; // конец PNG - 12 байт
const char jpgN[] = { -1, -40, -1, -32 }; // , 0, 16, 74, 70, 73, 70, 0 }; // начало JPEG/JPG
int key[4];


int randd()
{
    int random = std::rand() % 256 - 128; // Генерируем случайное число в диапазоне от -128 до 127
    return random;
}


void createKey()
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
    else if (sravnStr(ext, ".txt"))
    {
        delete[] ext;
        return -2;
    }
    else
    {
        delete[] ext;
        return -1;
    }
}



void plusRas(char*& buff, string name, const char* ch, int j)
{
    char mod[] = "_crypted";
    for (int i = 0; i < name.size() - 4; i++)
    {
        buff[i] = name[i];
    }
    for (int i = 0; i < 8; i++)
    {
        buff[name.length() - 4 + i] = mod[i];
    }
    for (int i = 0; i < 4 + j; i++)
    {
        buff[name.length() - 4 + 8 + i] = ch[i];
    }
}
string newName(string name)
{
    string saveFilePath;
    char* buff = new char[name.length() + 10];
    int ext = extFile(name);

    switch (ext)
    {
    case 1:
        plusRas(buff, name, ".png", 0);
        break;
    case 2:
        plusRas(buff, name, ".jpg", 0);
        break;
    case 3:
        plusRas(buff, name, ".jpeg", 1);
        break;
    }

    buff[name.length() + 8] = '\0';
    saveFilePath = buff;
    delete[] buff;
    return saveFilePath;
}


void keyInImg(vector<char>& img, int ext)
{
    if (ext == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            img.insert(img.begin() + img.size() - 12, key[i]);
        }
    }
    else if (ext == 2 || ext == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            img.push_back(key[i]);
        }
    }
}
void keyInFile()
{
    string keyFile;
    while (true)
    {
        cout << "Enter the path where to save the key. (with file name and extension)\n>>>";
        cin >> keyFile;
        if (extFile(keyFile) != -2)
        {
            cout << "\nInvalid input.\n\n";
            continue;
        }
        break;
    }
    ofstream saveKey(keyFile);
    if (!saveKey.is_open())
    {
        cout << "Key error.\n";
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        saveKey << key[i] << " ";
    }
}
void keyInConsole()
{
    for (int i = 0; i < 4; i++)
    {
        cout << key[i] << " ";
    }
    cout << "\n";
}

void keyFromImg(vector<char>& img, int ext)
{
    if (ext == 1)
    {
        int j = 0;
        for (int i = 3; i >= 0; i--)
        {
            key[j] = img[img.size() - 13 - i];
            j++;
            img.erase(img.begin() + img.size() - 13 - i);
        }
    }
    else if (ext == 2 || ext == 3)
    {
        int j = 3;
        for (int i = 0; i < 4; i++)
        {
            key[j] = img[img.size() - 1];
            img.pop_back();
            j--;
        }
    }
}
void keyFromFile()
{
    string keyFile;
    while (true)
    {
        cout << "Enter the path to the file with key. (with file name and extension)\n>>>";
        cin >> keyFile;
        if (extFile(keyFile) != -2)
        {
            cout << "\nInvalid input.\n\n";
            continue;
        }
        break;
    }
    ifstream file(keyFile);
    if (!file.is_open()) 
    {
        cout << "Error opening: " << keyFile << ", or the file does not exist.\n";
        return;
    }

    for (int i = 0; i < 4; i++) 
    {
        if (!(file >> key[i])) 
        {
            cout << "Error reading: " << keyFile << ".\n";
            return;
        }
    }
}
void keyFromConsole()
{
    cout << "Enter the key.\n>>>";
    for (int i = 0; i < 4; i++)
    {
        cin >> key[i];
    }
}


void saveKey(vector<char>& img, int ext)
{
    cout << "Save key in Image, in txt-file, or print to console? (1 - Img, 2 - txt, 3 - console)\n";

    int save;
    do
    {
        cout << ">>>"; cin >> save;
        switch (save)
        {
        case 1:
            keyInImg(img, ext);
            break;
        case 2:
            keyInFile();
            break;
        case 3:
            keyInConsole();
            break;
        default:
            cout << "Input Error.\n";
            break;
        }
    } while (save >= 3 && save <= 1);
}
void getKey(vector<char>& img, int ext)
{
    cout << "Get key from Image, from txt-file, or from console? (1 - Img, 2 - txt, 3 - console)\n";
    int save;
    do
    {
        cout << ">>>"; cin >> save;
        switch (save)
        {
        case 1:
            keyFromImg(img, ext);
            break;
        case 2:
            keyFromFile();
            break;
        case 3:
            keyFromConsole();
            break;
        default:
            cout << "Input Error.\n";
            break;
        }
    } while (save >= 3 && save <= 1);
}


void returnExt(vector<char>& img, int ext)
{
    if (ext == 1)
    {
        for (int i = 0; i < 8; i++)
        {
            img[i] = pngN[i];
        }
        int j = 0;
        for (int i = 12; i > 0; i--)
        {
            img[img.size() - i] = pngK[j];
            j++;
        }
    }
    else if (ext == 2 || ext == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            img[i] = jpgN[i];
        }
    }
}


void Crypt(vector<char>& img)
{
    for (int i = 0; i < img.size(); ++i)
    {
        img[i] = int(img[i]) ^ key[i % 4];
    }
}


void Decrypt(vector<char>& img, int ext)
{
    getKey(img, ext);
    Crypt(img);
}
void Encrypt(vector<char>& img, int ext)
{
    srand(time(nullptr));
    createKey();
    Crypt(img);
    saveKey(img, ext);
}


void DecEnc(vector<char>& img, string name)
{
    int ext = extFile(name);

    cout << "Decrypt or Encrypt the image? (Decrypt - 1, Encrypt - 2)\n>>>";
    int dec;
    do
    {
        cin >> dec;
    } while (dec != 1 && dec != 2);

    if (dec == 1)
    {
        Decrypt(img, ext);
    }
    else
    {
        Encrypt(img, ext);
    }

    returnExt(img, ext);
}


void saveInFile(vector<char>& img, string name)
{
    string saveFilePath = newName(name);

    ofstream saveFile(saveFilePath, ios::binary);
    if (!saveFile.is_open())
    {
        cout << "Error opening file: " << saveFilePath << ".\n";
        return;
    }
    for (const char& ch : img)
    {
        saveFile.put(ch);
    }

    saveFile.close();
}
int mainFunc()
{
    cout << "Welcome to CryptoPix!\n";
    string imageFilePath;
    
    while(true)
    {
        cout << "Enter the path to the Image: (with file name and extension)\nPossible extensions at the moment: PNG, JPG, JPEG.\n>>>";
        cin >> imageFilePath;
        if (extFile(imageFilePath) < 0)
        {
            cout << "\nInvalid input.\n\n";
            continue;
        }
        break;
    }

    ifstream imageFile(imageFilePath, ios::binary);
    if (!imageFile.is_open())
    {
        cout << "Error opening file: " << imageFilePath << ", or the file does not exist.\n";
        return 1;
    }

    vector<char> img;
    char ch;
    while (imageFile.get(ch))
    {
        img.push_back(ch);
    }

    
    DecEnc(img, imageFilePath);

    imageFile.close();

    saveInFile(img, imageFilePath);
    cout << "Thanks for using CryptoPix!";
    return 0;
}



int main() 
{
    if (mainFunc())
    {
        return 1;
    }

    return 0;
}