#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

struct data{
    string ID;
    double val;
    data(string &str) : ID(str), val(0.0){}
    data(){}
};

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
    ifstream fin_1;
    ifstream fin_2;
    ofstream fout;
    fin_1.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fin_2.open("2021_ICM_Problem_D_Data/artist_degree.csv");
    fout.open("2021_ICM_Problem_D_Data/influence_follower_of_theBeltals.csv");
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

    string context, sub_context, impacter, follower;
    unordered_map<string, pair<int, double> > hash;
    int index = 0;
    stringstream sin;
    vector<data> ret;
    getline(fin_1, context);
    while(getline(fin_1, context)) {
        int i = 0;
        sin.clear();
        sin << context;
        while(getline(sin, sub_context, ',')) {
            if(i == 0){
                impacter = sub_context;
            }
            if(i == 4){
                follower = sub_context;
            }
            i++;
        }
        if(impacter == string("754032")){
            if(hash.find(follower) == hash.end()) {
                hash.insert(make_pair(follower, make_pair(index, 0.0)));
                ret.push_back(data(follower));
                index++;
            }
        }
    }

    while(getline(fin_2, context)) {
        sin.clear();
        sin << context;
        getline(sin, follower, ',');
        getline(sin, sub_context, ',');
        auto iter = hash.find(follower);
        if(iter != hash.end()){
            double temp = my_stoi(sub_context);
            if(temp != 0){
                iter->second.second = 1 / temp;
            }else{
                iter->second.second = 0;
            }
        }
        getline(sin, sub_context, ',');
    }

    for(int i = 0; i < ret.size(); i++) {
        ret[i].val = hash[ret[i].ID].second;
        fout << ret[i].ID << ',' << ret[i].val << endl;
    }

    return 0;
}