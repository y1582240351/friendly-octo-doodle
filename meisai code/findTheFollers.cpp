#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct data{
    string ID;
    int in_degree;
    int out_degree;
    data() : in_degree(0), out_degree(0){}
    data(string &str) : ID(str), in_degree(0), out_degree(0){}
};

int main(){
    ifstream fin;
    ofstream fout;
    fin.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fout.open("2021_ICM_Problem_D_Data/influence_follower_of_theBeltals.csv");
    if(!fin.is_open()){
        cout << "1 ERROR!!!" << endl;
        return 0;
    }
    if(!fout.is_open()){
        cout << "2 ERROR!!!" << endl;
        return 0; 
    }
    
    string context, sub_context, impacter, follower;
    stringstream sin;
    vector<string> ret;
    getline(fin, context);
    while(getline(fin, context)) {
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
            ret.push_back(follower);
        }
    }
    for(int i = 0; i < ret.size(); i++) {
        fout << ret[i] << endl;
    }
    cout << ret.size() << endl;
    fin.close();
    fout.close();
    return 0;
}