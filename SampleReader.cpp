#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream is("beginner.txt");
    string line;

    while (getline(is, line)) {
        cout << line << endl;
    }
    return 0;
}

//text in string spreichern 
//substring nur für die erste Zeile