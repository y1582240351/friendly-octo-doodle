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
    if(str.size() != 4){
        // cout << "ERROR!!!!! ,,,,,," << endl;
        cout << str << endl;
        return 0;
    }
    int ret = 0;
    for(int i = 0; i < 4; i++){
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
    fin_1.open("2021_ICM_Problem_D_Data/artist_genres.csv");
    fin_2.open("2021_ICM_Problem_D_Data/artist_year.csv");
    fout.open("2021_ICM_Problem_D_Data/year_genres.csv");
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
    unordered_map<string, int> hash_3;
    int genres_index = 0;
    while (getline(fin_1, context)) {
        sin.clear();
        sin << context;
        getline(sin, sub_context_1, ',');
        getline(sin, sub_context_2, ',');
        if(hash.find(sub_context_1) == hash.end())
            hash.insert(make_pair(sub_context_1, sub_context_2));
        
        if(hash_2.find(sub_context_2) == hash_2.end()) {
            cout << sub_context_2 << ' ' << genres_index+1 << endl;
            hash_2.insert(make_pair(sub_context_2, genres_index));
            genres_index++;
        }
    }
    fin_1.close();

    vector< vector<int> > year_genres(9, vector<int>(genres_index+1, 0));

    while(getline(fin_2, context)){
        sin.clear();
        sin << context;
        getline(sin, sub_context_1, ',');
        getline(sin, sub_context_2, ',');
        //sub_context_2.pop_back();
        string temp_genres = hash[sub_context_1];
        int i_g = hash_2[temp_genres];
        int i_y = my_stoi(sub_context_2) - 1930;
        i_y = i_y / 10;
        // cout << i_y << ' ' << i_g << endl;

        year_genres[i_y][i_g]++;
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < genres_index+1; j++){
            fout << year_genres[i][j];
            if(j != genres_index)
                fout << ',';
            else
                fout << endl;
        }
    }
    cout << "**********************" << endl << genres_index+1 << endl << "******************************" << endl;
    fin_2.close();
    fout.close();
    return 0;
}