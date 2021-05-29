#include<bits/stdc++.h>
using namespace std;


int main(){
  
  cout << "Enter total size: ";
  int size;   // size
  cin >> size;
  
  cout << "Enter total number of processes: ";
  int n,i;
  cin >> n;     // number of processes
  
  int accomodated = 0;  // Total number of processes accomodated
  
  for(i=0; i<n; i++){
    
    cout << "Size of P" << i+1 <<": ";
    int process;  // process size
    cin >> process;
    size -= process;
    
    if(size < 0){
      size += process;
      cout << "P" << i+1 <<" can't be accomodated because only " << size <<"KB are remaining.\n";
    }
    else{
      accomodated++;
    }
  }
  
  cout << "Total unused space = " << size << "KB\n";
  cout << "Number of processes accomodated = " << accomodated << "\n";
}
