#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

ofstream out;

string inputText(const string& pot) {
    ifstream input(pot);
    stringstream sstream;

    if (!input.is_open()) {
        return string();
    }

    sstream << input.rdbuf();
    return sstream.str();
}

void izpis_KMPnext(vector<int>& polje, int len) {
    for (int i = 0; i < len; i++) {
        cout << polje[i] << ' ';
    }
    cout << endl;
}

vector<int> buildKMPTable(const string& vzorec) {
    int m = vzorec.size();
    vector<int> kmpNext(m, 0);
    kmpNext[0] = -1;
    int j = -1;

    for (int i = 1; i < m; i++) {
        while (j >= 0 && vzorec[j] != vzorec[i - 1]) {
            j = kmpNext[j];
        }
        j++;
        kmpNext[i] = j;
    }
    return kmpNext;
}

void KMP(const string& text, const string& vzorec) {
    int n = text.size();
    int m = vzorec.size();
    vector<int> kmpNext = buildKMPTable(vzorec);
    izpis_KMPnext(kmpNext, m);

    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && text[i] != vzorec[j]) {
            j = kmpNext[j];
        }
        j++;
        if (j == m) {
            out << (i - m + 1) << ' ';
            j = kmpNext[j - 1];
        }
    }
}

vector<int> buildSundayTable(const string& vzorec) {
    int m = vzorec.size();
    vector<int> BCH(256, m + 1); //če znak ni v vzorcu preskoči celo dolžina vzorca + 1
    for (int i = 0; i < m; i++) {
        BCH[vzorec[i]] = m - i;
    }
    return BCH;
}

void Sunday(const string& text, const string& vzorec) {
    int n = text.size();
    int m = vzorec.size();
    vector<int> BCH = buildSundayTable(vzorec);

    int j = 0;
    while (j + m <= n) {
        if (text.substr(j, m) == vzorec) {
            out << j << ' ';
            j += m;
        }
        else {
            j += BCH[text[j + m]];
        }
    }
}

int main(int argc, const char* const argv[]) {

    if (argc != 4) {
        return -1;
    }

    string text = inputText(argv[3]);
    string vzorec = argv[2];
    out.open("out.txt");

    if (!out) {
        return -2;
    }

    if (argv[1][0] == '0') {
        KMP(text, vzorec);
    }
    else {
        Sunday(text, vzorec);
    }

    return 0;
}
