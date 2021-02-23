#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fout.open("2021_ICM_Problem_D_Data/artist_genres.csv");
    if(!fin.is_open()){
        cout << "1 ERROR!!!" << endl;
        return 0;
    }
    if(!fout.is_open()){
        cout << "2 ERROR!!!" << endl;
        return 0; 
    }
    string context;
    string sub_context;
    stringstream sin;
    getline(fin, context);
    context.clear();
    while (getline(fin, context)) {
        int i = 0;
        sin.clear();
        sin << context;
        while(getline(sin, sub_context, ',')) {
            if(i == 0 || i == 4){
                fout << sub_context << ',';
            }
            if(i == 2 || i == 6){
                fout << sub_context << endl;
            }
            i++;
        }
    }
    fin.close();
    fout.close();
    return 0;
}