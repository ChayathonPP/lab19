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

void importDataFromFile(const string& filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            char name[100];
            int score,score1,score2,score3;
            sscanf(line.c_str(), "%[^:]:%d %d %d ", name, &score1 ,&score2 ,&score3);
            score=score1+score2+score3;
            names.push_back(name);
            scores.push_back(score);
            grades.push_back(score2grade(score));
        }
        file.close();
    }
}

void getCommand(string& command, string& key){
    cout << "Please input your command: ";
    cin >> command;

    
    if(toUpperStr(command)=="EXIT")
    return;
    else if(toUpperStr(command)=="GRADE" or toUpperStr(command)=="NAME")
    {
          cin.ignore();
          getline(cin, key);
    }
    else 
    return;
    

}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
    bool found = false;
    for(unsigned i = 0; i < names.size();i++){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size();i++){
        if(toUpperStr(string(1,grades[i])) == key){
            cout << names[i] << " (" << scores[i] << ") " << endl;
            found = true;
        }
    }
     if(!found)
     {
      cout << "Cannot found.\n";
      }
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