#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream input("name_score.txt");
    string msg;
    char tname[50];
    int score1,score2,score3;
    while(getline(input,msg)){
        char format[] = "%[^:]: %d %d %d";
        sscanf(msg.c_str(),format,tname,&score1,&score2,&score3);
        names.push_back(tname);
        int allscore = score1+score2+score3;
        scores.push_back(allscore);
        grades.push_back(score2grade(allscore));
    }
    input.close();
}

void getCommand(string &command, string &key){
    string text;
    char a[100];
    char b[100];
    char format[] = "%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin,text);
    sscanf(text.c_str(),format,a,b);
    command = a;
    key = b;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool flag = false;
    cout << "---------------------------------\n";
    for(unsigned int i=0; i<names.size(); i++){
        if(key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << '\n';
            cout << names[i] << "'s grade = " << grades[i] << '\n';
            flag = true;
            break;
        }
    }
    if(!flag) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool flag = false;
    cout << "---------------------------------\n";
    for(unsigned int i=0; i<names.size(); i++){
        if(key[0] == grades[i]){
            cout << names[i] << " (" << scores[i] << ")"<< '\n';
            flag = true;
        }
    }
    if(!flag) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
