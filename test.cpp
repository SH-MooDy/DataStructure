#include <iostream> 
#include <list> 
using namespace std; 
int main() { 
  list<int> first;                                
  list<int> second(4,100);                       
  list<int> third(second.begin(), second.end());  
  list<int> fourth(third);                       
  int myints[] = {16,2,77,29}; 
  list<int> fifth(myints, myints+sizeof(myints)/
sizeof(int)); 
  for (auto it=fifth.begin(); it!=fifth.end(); it++) 
    cout << *it << ' '; 
  cout << '\n'; 
  return 0; 
}