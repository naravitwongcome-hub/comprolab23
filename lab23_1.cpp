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
    ifstream source(filename.c_str());
    string line;
    while(getline(source, line)){
        int loc = line.find(':');
        if(loc == -1) continue; 

        string name = line.substr(0, loc);
        int s1, s2, s3;
        string scorePart = line.substr(loc + 1);
        
        if(sscanf(scorePart.c_str(), "%d %d %d", &s1, &s2, &s3) == 3){
            int totalScore = s1 + s2 + s3;
            names.push_back(name);
            scores.push_back(totalScore);
            grades.push_back(score2grade(totalScore));
        }
    }
    source.close();
}

void getCommand(string &command, string &key){
cout << "Please input your command: " <<"\n";
    string input;
    getline(cin,input);

    int pos = input.find(' '); 

    if(pos != -1){
        command = input.substr(0, pos);
        key = input.substr(pos + 1);
    } else {
        command = input;
        key = "";
    }

}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(int i = 0; i < (int)names.size(); ++i){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
            break;
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){

bool found = false;
    cout << "---------------------------------\n";
    for(int i = 0; i < (int)names.size(); ++i){ 
        string currentGrade(1, grades[i]);
        if(currentGrade == key){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found) cout << "Cannot found.\n";
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