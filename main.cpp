#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <assert.h>

using namespace std;

void wordStatistics(ifstream& fin, ofstream& fout, int histogramWords[], int histogramLetters[]);

int main()
{
    ifstream fin;
    ofstream fout;

    fin.open("words.txt");
    fout.open("words_statistics.txt");

    if (fin.fail()){
        cout << "Input file failed to open." <<endl;
        exit(1);
    }else{
        cout << "Input file opened successfully!" <<endl;
    }

    int histogramWords[14]= {0};
    int histogramLetters[26] = {0};

    wordStatistics(fin, fout, histogramWords, histogramLetters);

    fin.close();
    fout.close();

    return 0;
}

void wordStatistics(ifstream& fin, ofstream& fout, int histogramWords[], int histogramLetters[]){
    string word;

    int numberWords = 0;
    int numberLetters = 0;

    while (!fin.eof()){
        fin >> word;
        numberWords++;
        int wordLength = word.size();
        if (wordLength <= 13) {
            histogramWords[wordLength]++;
        }
        numberLetters += wordLength;
        for (int i = 0; i < wordLength; i++){
            histogramLetters[word[i]-'a']++;
        }
    }

    fout << "Number of words: " << numberWords << endl;
    fout << "Number of letters: " << numberLetters <<endl;
    fout << "Average length of words: " << static_cast<double>(numberLetters)/numberWords << endl << endl;

    int wordSum = 0;
    for (int i = 1; i<14; i++){
        fout << "Number of " << i << "-letter words: " << histogramWords[i] << endl;
        wordSum += histogramWords[i];
    }
    int greaterthirteen = numberWords - wordSum;
    fout << "Number of words of any other number of letters: " << greaterthirteen << endl;
    assert((greaterthirteen + wordSum) == numberWords);

    fout << endl;

    int letterSum = 0;
    for (int i = 0; i<26; i++){
        fout << "Frequency of letter '" << char(int('a')+i) << "': " << histogramLetters[i] << endl;
        letterSum += histogramLetters[i];
    }
    assert(letterSum == numberLetters);
}
