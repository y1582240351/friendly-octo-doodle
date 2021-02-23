#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

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

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fout.open("2021_ICM_Problem_D_Data/sub_follower_year.csv");
    if(!fin.is_open()){
        cout << "1 ERROR!!!" << endl;
        return 0;
    }
    if(!fout.is_open()){
        cout << "2 ERROR!!!" << endl;
        return 0; 
    }
    
    string context, sub_context, year, i_geners;
    stringstream sin;
    vector<int> ret(9, 0);
    getline(fin, context);
    while(getline(fin, context)) {
        int i = 0;
        sin.clear();
        sin << context;
        while(getline(sin, sub_context, ',')) {
            if(i == 7){
                year = sub_context;
            }
            if(i == 2){
                i_geners = sub_context;
            }
            i++;
        }
        //cout << i_geners << endl;
        if(i_geners == string("Pop/Rock")){
            year.pop_back();
            int index = (my_stoi(year) - 1930) / 10;
            ret[index]++;
        }
    }
    for(int i = 0; i < ret.size(); i++) {
        fout << ret[i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}