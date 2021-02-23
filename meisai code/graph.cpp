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
    fout.open("2021_ICM_Problem_D_Data/artist_degree.csv");
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
    unordered_map<string, int> hash;
    vector<data> ret;
    int index = 0;
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
        if(hash.find(impacter) == hash.end()){
            hash.insert(make_pair(impacter, index));
            ret.push_back(data(impacter));
            index++;
        }
        if(hash.find(follower) == hash.end()){
            hash.insert(make_pair(follower, index));
            ret.push_back(data(follower));
            index++;
        }
        int temp_index = hash[impacter];
        ret[temp_index].out_degree++;
        temp_index = hash[follower];
        ret[temp_index].in_degree++;
    }
    string max_ID;
    int max = 0;
    for(int i = 0; i < ret.size(); i++) {
        if(ret[i].out_degree > max){
            max = ret[i].out_degree;
            max_ID = ret[i].ID;
        }
        fout << ret[i].ID << ',' << ret[i].in_degree << ',' << ret[i].out_degree << endl;
    }
    fin.close();
    fout.close();
    cout << max_ID << ' ' << max << endl;
    return 0;
}
