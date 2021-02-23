#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>
#include<vector>
#include<list>

using namespace std;

struct data{
    string d_1, d_2, d_3;
};

int main() {
    ifstream fin_1;
    ifstream fin_2;
    ofstream fout;
    fin_1.open("2021_ICM_Problem_D_Data/artist_genres.csv");
    fin_2.open("2021_ICM_Problem_D_Data/jiangweihou.csv");
    fout.open("2021_ICM_Problem_D_Data/geners_data.csv");
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
    string context;
    string sub_context_1, sub_context_2;
    stringstream sin;
    getline(fin_1, context);
    context.clear();

    unordered_map<string, string> hash;
    unordered_map<string, int> hash_2;
    while (getline(fin_1, context)) {
        sin.clear();
        sin << context;
        getline(sin, sub_context_1, ',');
        getline(sin, sub_context_2, ',');
        if(hash.find(sub_context_1) == hash.end())
            hash.insert(make_pair(sub_context_1, sub_context_2));
    }
    fin_1.close();

    vector< list<data> > final;
    data temp;
    int genres_index = 0;

    while (getline(fin_2, context)){
        sin.clear();
        sin << context;
        getline(sin, sub_context_1, ',');
        sub_context_1 = hash[sub_context_1];
        auto iter = hash_2.find(sub_context_1);
        if(iter == hash_2.end()){
            final.push_back(list<data>());
            genres_index = final.size()-1;
            hash_2.insert(make_pair(sub_context_1, genres_index));
        }else{
            genres_index = iter->second;
        }
        getline(sin, sub_context_2, ',');
        temp.d_1 = sub_context_2;
        getline(sin, sub_context_2, ',');
        temp.d_2 = sub_context_2;
        getline(sin, sub_context_2, ',');
        sub_context_2.pop_back();
        temp.d_3 = sub_context_2;
        final[genres_index].push_back(temp);
    }
    
    for(int i = 0; i < final.size(); ++i) {
        for(auto iter = final[i].begin(); iter != final[i].end();){
            fout << iter->d_1;
            iter++;
            if(iter != final[i].end()){
                fout << ',';
            }else{
                fout << endl;
            }
        }
        for(auto iter = final[i].begin(); iter != final[i].end();){
            fout << iter->d_2;
            ++iter;
            if(iter != final[i].end()){
                fout << ',';
            }else{
                fout << endl;
            }
        }
        for(auto iter = final[i].begin(); iter != final[i].end();){
            fout << iter->d_3;
            ++iter;
            if(iter != final[i].end()){
                fout << ',';
            }else{
                fout << endl;
            }
        }
    }
    

    fout.close();
    return 0;
}