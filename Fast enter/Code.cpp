#include <iostream>
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

const int& operator-(const set<string>::const_iterator& End, const set<string>::const_iterator& Start) {
    int counter = 0;
    set<string>::const_iterator LocalEnd = End;
    while (LocalEnd != Start) {
        counter++;
        LocalEnd--;
    }

    return counter;
}

bool Check_word_in_DB(const set<string>& DataBase, const string& word_for_search) {
    if (DataBase.size() == 0 || word_for_search == "")
        return false;
    set<string>::const_iterator Start = DataBase.cbegin();
    set<string>::const_iterator End = DataBase.cend();
    --End;

    while ((End - Start) > 1) {
        int Middle = (End - Start) / 2;
        set<string>::const_iterator ItMiddle = Start;
        advance(ItMiddle, Middle);
        if (word_for_search > *ItMiddle)
            Start = ItMiddle;
        else
            End = ItMiddle;
    }

    if (*Start == word_for_search || *End == word_for_search) return true;
    else return false;
}

string Find_word(const set<string>& DataBase, const string& word_for_search) {
    if (DataBase.size() == 0 || word_for_search == "")
        return "";

    set<string>::const_iterator Start = DataBase.cbegin();
    set<string>::const_iterator End = DataBase.cend();
    --End;

    while ((End - Start) > 1) {
        int Middle = (End - Start)/2;
        set<string>::const_iterator ItMiddle = Start;
        advance(ItMiddle, Middle);
        if (word_for_search > *ItMiddle)
            Start = ItMiddle;
        else
            End = ItMiddle;
    }

    if (*Start > word_for_search) return *Start;
    else return *End;
}

int main()
{
    {
        set<string> DataBase;
        ifstream* InputFile = new ifstream("file.txt");
        if (InputFile->is_open())
            FillDB(DataBase, InputFile);

        InputFile->close();
        delete InputFile;

        int number_words;
        cin >> number_words;

        string** Printed_words = new string * [number_words];
        for (int i = 0; i < number_words; ++i)
            Printed_words[i] = new string("");

        char Symbol;

        int Counter_words = 0;

        while (Counter_words < number_words) {
            system("cls");
            string Found_word = Find_word(DataBase, *Printed_words[Counter_words]);
            if (Found_word != "")
                printf("Maybe you want: %s (enter CTRL+p)\n", Found_word.c_str());
            printf("%d\n", number_words);
            for (int i = 0; i < Counter_words + 1; ++i)
                cout << *Printed_words[i] << ' ';
            Symbol = _getch();
            switch (Symbol) {
            case 16: // if Symbol == (CTRL + p)
                *Printed_words[Counter_words] = Found_word;
                ++Counter_words;
                break;
            case ' ':
                cout << ' ';
                if (!Check_word_in_DB(DataBase, *Printed_words[Counter_words]))
                    DataBase.insert(*Printed_words[Counter_words]);
                ++Counter_words;
                break;
            default:
                *Printed_words[Counter_words] += Symbol;
                system("cls");
            }
        }

        system("cls");
        printf("%d\n", number_words);
        for (int i = 0; i < number_words; ++i)
            cout << *Printed_words[i] << ' ';

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

        for (int i = 0; i < number_words; ++i)
            delete Printed_words[i];
        delete[] Printed_words;
    }
        _CrtDumpMemoryLeaks();
        system("pause");
        
    return 0;
}
