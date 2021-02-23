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
    ifstream fin_1;
    ofstream fout;
    ofstream fout_1;
    fin.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fin_1.open("2021_ICM_Problem_D_Data/artist_year.csv");
    fout.open("2021_ICM_Problem_D_Data/sub_artist_year.csv");
    fout_1.open("2021_ICM_Problem_D_Data/sub_artist_degree.csv");
    if(!fin.is_open()){
        cout << "1 ERROR!!!" << endl;
        return 0;
    }
    if(!fin_1.is_open()){
        cout << "2 ERROR!!!" << endl;
        return 0;
    }
    if(!fout.is_open()){
        cout << "3 ERROR!!!" << endl;
        return 0; 
    }
    
    string context, sub_context, ID, geners;
    unordered_map<string, string> hash;
    stringstream sin;
    vector<string> ret;
    getline(fin, context);
    while(getline(fin, context)) {
        int i = 0;
        sin.clear();
        sin << context;
        while(getline(sin, sub_context, ',')) {
            if(i == 0){
                ID = sub_context;
            }
            if(i == 2){
                geners = sub_context;
            }
            i++;
        }
        // cout << geners << endl;
        // cout << ID << endl;
        if(hash.find(ID) == hash.end()){
            hash.insert(make_pair(ID, geners));
        }
    }

    while(getline(fin_1, context, '\n')) {
        sin.clear();
        sub_context.clear();
        sin << context;
        getline(sin, sub_context, ',');
        ID = sub_context;
        // cout << ID << endl;
        geners = hash[ID];
        //cout << geners << endl;
        getline(sin, sub_context, ',');
        if(geners == string("Pop/Rock")) {
            fout << ID << ',' << sub_context << endl;
        }
    }

    fin_1.close();
    fin_1.open("2021_ICM_Problem_D_Data/artist_degree.csv");
    if(!fin_1.is_open()){
        cout << "4 ERROR!!!" << endl;
        return 0;
    }

    int i = 0;
    while(getline(fin_1, context)){
        sin.clear();
        sin << context;
        getline(sin, ID, ',');
        //cout << ID << endl;
        geners = hash[ID];
        // cout << geners << endl;
        getline(sin, sub_context, ',');
        getline(sin, sub_context, ',');
        if(geners == string("Pop/Rock")){
            cout << i << endl;
            i++;
            // sub_context.pop_back();
            fout_1 << ID << ',' << sub_context << endl;
        }
    }
    fin.close();
    fin_1.close();
    fout.close();
    fout_1.close();
    return 0;
}