#include <algorithm> 
#include <iostream> 
#include <vector> 
using namespace std; 
int main() { 
    vector<int> my_vec = { 1, 3, 1, 4, 4, 6, 5, 6, 6 }; 
    sort(my_vec.begin(), my_vec.end()); 
    for (int item : my_vec) 
        cout << item << " "; 
    cout << endl; 
    auto it = unique(my_vec.begin(), my_vec.end()); 
    for (int item : my_vec) 
        cout << item << " "; 
    cout << endl; 
    my_vec.erase(it, my_vec.end()); 
    for (int item : my_vec) 
        cout << item << " "; 
    cout << endl; 
    return 0; 
}
