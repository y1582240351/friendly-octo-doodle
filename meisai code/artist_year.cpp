#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unordered_map>

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
    ifstream fin;
    ofstream fout;
    fin.open("2021_ICM_Problem_D_Data/influence_data.csv");
    fout.open("2021_ICM_Problem_D_Data/artist_year.csv");
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
    unordered_map<string, bool> hash;
    getline(fin, context);
    context.clear();
    int max = 0, min = 0x7fffffff;
    int count = 0;
    bool flag = false;
    while (getline(fin, context)) {
        int i = 0;
        sin.clear();
        sin << context;
        while(getline(sin, sub_context, ',')) {
            if(i == 0 || i == 4){
                if(hash.find(sub_context) == hash.end()) {
                    hash.insert(make_pair(sub_context, true));
                }else {
                    flag = true;
                    i++;
                    continue;
                }
                fout << sub_context << ',';
            }
            if(i == 3 || i == 7){
                if(flag){
                    flag = false;
                    i++;
                    continue;
                }
                if(i == 7)
                    sub_context.pop_back();
                int temp = my_stoi(sub_context);
                if(temp == 0){
                    count++;
                }
                if(temp > max)
                    max = temp;
                if(temp < min)
                    min = temp;
                fout << sub_context << '\n';
            }
            i++;
        }
    }
    cout << count << endl << max << endl << min << endl;
    fin.close();
    fout.close();
    return 0;
}