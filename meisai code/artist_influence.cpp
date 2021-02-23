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
    fin_1.open("2021_ICM_Problem_D_Data/artist_degree.csv");
    fin_2.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fout.open("2021_ICM_Problem_D_Data/artist_influence.csv");
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

    unordered_map< string, pair<int, int> > hash_1;
    unordered_map<string, int> hash_2;
    vector<data> ret;
    string context, sub_context, ID, in_degree_str;
    stringstream sin;
    int index = 0, in_degree_num;

    while(getline(fin_1, context)) {
        sin.clear();
        sin << context;
        getline(sin, ID, ',');
        getline(sin, in_degree_str, ',');
        // in_degree_str.pop_back();
        in_degree_num = my_stoi(in_degree_str);
        if(hash_1.find(ID) == hash_1.end()){
            ret.push_back(data(ID));
            hash_1.insert(make_pair(ID, make_pair(in_degree_num, index)));
            index++;
        }
        getline(sin, in_degree_str, ',');
    }

    string impacter, follower;
    while(getline(fin_2, context)) {
        sin.clear();
        sin << context;
        int i = 0;
        while(getline(sin, sub_context, ',')){
            if(i == 0){
                impacter = sub_context;
            }
            if(i == 4){
                follower = sub_context;
            }
            i++;
        }
        double temp = hash_1[follower].first;
        // cout << temp << endl;
        int index = hash_1[impacter].second;
        if(temp != 0)
            ret[index].val += 1/temp;
    }

    double max = 0.0;
    for(int i = 0; i < ret.size(); i++) {
        if(ret[i].val > max){
            max = ret[i].val;
            ID = ret[i].ID;
        }
        fout << ret[i].ID << ',' << ret[i].val << endl;
    }

    cout << ID << ' ' << max << endl;

    return 0;
}