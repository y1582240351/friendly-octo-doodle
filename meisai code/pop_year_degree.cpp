#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include<list>

using namespace std;


bool is_num(char ch){
    if(ch >= '0' && ch <= '9')
        return true;
    return false;
}

int my_stoi(string& str){
    // if(str.size() != 4){
    //     // cout << "ERROR!!!!! ,,,,,," << endl;
    //     cout << str << endl;
    //     return 0;
    // }
    int ret = 0;
    for(int i = 0; i < str.size(); i++){
        if(!is_num(str[i])){
            cout << str << endl;
            return 0;
        }
        int a = str[i] - '0';
        ret *= 10;
        ret += a;
    }
    return ret;
}


int main() {
    ifstream fin_1;
    ifstream fin_2;
    ofstream fout;
    fin_1.open("2021_ICM_Problem_D_Data/sub_artist_year.csv");
    fin_2.open("2021_ICM_Problem_D_Data/sub_artist_degree.csv");
    fout.open("2021_ICM_Problem_D_Data/sub_year_degree.csv");
    if(!fin_1.is_open()){
        cout << "1 ERROR!!!" << endl;
        return 0;
    }
    if(!fin_2.is_open()){
        cout << "2 ERROR!!!" << endl;
    }
    if(!fout.is_open()){
        cout << "3 ERROR!!!" << endl;
        return 0; 
    }
    
    string context, sub_context;
    string ID, year;
    unordered_map<string, string> hash;
    stringstream sin;
    vector<int> sub_year_degree(9, 0);

    while(getline(fin_1, context)) {
        sin.clear();
        sin << context;
        getline(sin, ID, ',');
        getline(sin, year, ',');
        if(hash.find(ID) == hash.end()) {
            hash.insert(make_pair(ID, year));
        }
    }

    while(getline(fin_2, context)) {
        sin.clear();
        sin << context;
        getline(sin, ID, ',');
        getline(sin, sub_context, ',');
        year = hash[ID];
        int index = (my_stoi(year) - 1930) / 10;
        sub_year_degree[index] += my_stoi(sub_context);
    }

    for(int i = 0; i < sub_year_degree.size(); i++){
        fout << 1930 + i*10 << ',' << sub_year_degree[i] << endl;
    }
    fin_1.close();
    fin_2.close();
    fout.close();
    return 0;
}