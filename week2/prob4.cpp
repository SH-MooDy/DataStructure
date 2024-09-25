#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cctype>
#include<cassert>
#include<vector>
using namespace std;

struct Person {
    string name, address;
    string phone, email, web;
};

vector<Person> directory;


string trim(string str) {
    int s = 0, t = str.length() - 1;
    while (s < str.length() && isspace(str[s]))
        s++;
    while (t >= 0 && isspace(str[t]))
        t--;
    if (s <= t)
        return str.substr(s, t - s + 1);
    else
        return "";
}

vector<string> split_line(string& line, char delimiter) {
    vector<string> tokens;
    stringstream sstream(line);
    string str;
    while (getline(sstream, str, delimiter)) {
        tokens.push_back(trim(str));
    }
    return tokens;
}

void load_data(string file_name) {
    string line;

    ifstream infile(file_name);

    while (getline(infile, line)) {
        vector<string> tokens = split_line(line, '\t');

        assert(tokens.size() >= 4 && tokens.size() <= 5);

        Person p;
        p.name = tokens.at(0);
        p.address = tokens.at(1);
        p.phone = tokens.at(2);
        p.email = tokens.at(3);
        if (tokens.size() == 5) 
            p.web = tokens.at(4);

        directory.push_back(p);
    }
    infile.close();
}

void print_person(Person& p) {
    cout << p.name << ":" << endl;
    cout << "   Address: " << p.address << endl;
    cout << "   Phone: " << p.phone << endl;
    cout << "   Email: " << p.email << endl;
    cout << "   Web: " << p.web << endl;
}

void list_directory() {
    for (auto& person : directory) {
        print_person(person);
    }
}

void search_directory(string& prefix) {
    for (auto& p : directory) {
        if (p.name.compare(0, prefix.size(), prefix) == 0)
            print_person(p);
        else if (p.name.compare(0, prefix.size(), prefix) > 0)
            break;
    }
}

Person get_person_info(string name) {
    Person p;
    string line;
    p.name = name;
    cout << "   Address: ";
    getline(cin, line);
    p.address = trim(line);
    cout << "   Phone: ";
    getline(cin, line);
    p.phone = trim(line);
    cout << "   Email: ";
    getline(cin, line);
    p.email = trim(line);
    cout << "   Web: ";
    getline(cin, line);
    p.web = trim(line);
    return p;
}

void add_person(string name) {
    Person p = get_person_info(name);
    auto it = directory.begin();
    while (it != directory.end() && it->name <= name)
        it++;
    it = directory.insert(it, p);
}

void delete_person(string name) {
    string answer;
    for (auto it = directory.begin(); it != directory.end();) {
        if (it->name.compare(0, name.size(), name) == 0) {
            cout << "Want to delete '" << it->name << "'? ";
            cin >> answer;
            if (answer == "yes" || answer == "y")
                it = directory.erase(it);
            else
                it++;
        }
        else if (it->name.compare(0, name.size(), name) > 0)
            break;
        else
            it++;
    }
}

void save_directory() {
    ofstream outfile("address.tsv");
    for (auto& p : directory)
        outfile << p.name << '\t' << p.address << '\t' << p.phone << '\t' << p.email << '\t' << p.web << endl;
    outfile.close();
}

void search_directory_with_and(const vector<string>& keywords) {
    for (auto& person : directory) {
        bool match = true;
        for (const auto& keyword : keywords) {
            // 각 키워드가 이름, 주소, 이메일, 웹사이트, 전화번호에 포함되어 있는지 확인
            if (person.name.find(keyword) == string::npos &&
                person.address.find(keyword) == string::npos &&
                person.email.find(keyword) == string::npos &&
                person.web.find(keyword) == string::npos &&
                person.phone.find(keyword) == string::npos) {
                match = false;
                break;
            }
        }
        if (match) {
            print_person(person);
        }
    }
}

int main() {
    load_data("address.tsv");
    string command, arguments;
    
    while (1) {
        cout << "$ ";
        cin >> command;
        
        if (command == "exit")
            break;
        
        if (command == "list") {
            list_directory();
        } else if (command == "find") {
            getline(cin, arguments);
            string name = trim(arguments);
            if (name.length() > 0) {
                search_directory(name);
            }
        } else if (command == "add") {
            getline(cin, arguments);
            string name = trim(arguments);
            if (name.length() > 0) {
                add_person(name);
            }
        } else if (command == "delete") {
            getline(cin, arguments);
            string name = trim(arguments);
            if (name.length() > 0) {
                delete_person(name);
            }
        } else if (command == "save") {
            save_directory();
        } else if (command == "search") {
            getline(cin, arguments);
            string search_query = trim(arguments);
            if (search_query.length() > 0) {
                vector<string> keywords = split_line(search_query, '&');
                search_directory_with_and(keywords);
            }
        }
    }
    
    return 0;
}
