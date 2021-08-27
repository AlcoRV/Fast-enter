#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <conio.h>

using namespace std;

void FillDB(set<string>& DataBase, ifstream* InputFile) {
    while (!InputFile->eof()) {
        string t;
        *InputFile >> t;
        DataBase.emplace(t);
    }
}

bool Check(const set<string>& DataBase, const string& word_for_search) {
    if (DataBase.size() == 0)
        return false;
    set<string>::const_iterator word_in_DB = DataBase.cbegin();
    int i = 0;
    while (i < word_for_search.size() && word_in_DB != DataBase.cend()) {
            if (word_for_search[i] != (*word_in_DB)[i])
                word_in_DB++;
            else
                i++;
    }
    if (word_in_DB == DataBase.cend()) return false;
    return true;
}

string Find(const set<string>& DataBase, const string& word_for_search) {
    if (DataBase.size() == 0)
        return "";
    set<string>::const_iterator word_in_DB = DataBase.cbegin();
    int i = 0;
    while (i < word_for_search.size() && word_in_DB != DataBase.cend()) {
        if (word_for_search[i] != (*word_in_DB)[i])
            word_in_DB++;
        else
            i++;
    }
    if (word_in_DB == DataBase.cend()) return "";
    return *word_in_DB;
}

int main()
{
    srand(time(0));
    {
        set<string> DataBase;
        ifstream* InputFile = new ifstream("file.txt");
        if (InputFile->is_open())
            FillDB(DataBase, InputFile);

        InputFile->close();
        delete InputFile;

        int num_words;
        cin >> num_words;

        string** str = new string * [num_words];
        for (int i = 0; i < num_words; ++i)
            str[i] = new string("");

        char ch;

        int j = 0;

        while (j < num_words) {
            system("cls");
            string t = Find(DataBase, *str[j]);
            if (t != "")
                printf("Maybe you want: %s (enter CTRL+p)\n", t.c_str());
            printf("%d\n", num_words);
            for (int i = 0; i < j + 1; ++i)
                cout << *str[i] << ' ';
            ch = _getch();
            switch (ch) {
            case 16:
                *str[j] = t;
                ++j;
                break;
            case ' ':
                cout << ' ';
                if (!Check(DataBase, *str[j]))
                    DataBase.insert(*str[j]);
                ++j;
                break;
            default:
                *str[j] += ch;
                system("cls");
            }
        }

        system("cls");
        printf("%d\n", num_words);
        for (int i = 0; i < num_words; ++i)
            cout << *str[i] << ' ';

        ofstream OutputFile("file.txt");
        if (OutputFile.is_open()) {
            set<string>::const_iterator It = DataBase.cbegin();
            set<string>::const_iterator End = DataBase.cend();
            --End;
            for (It; It != End; ++It)
                OutputFile << *It << ' ';
            OutputFile << *End;
        }
        OutputFile.close();

        for (int i = 0; i < num_words; ++i)
            delete str[i];
        delete[] str;
    }
        _CrtDumpMemoryLeaks();
        system("pause");
    return 0;
}
