#include<bits/stdc++.h>
using namespace std;


int main(){
  
  cout << "Enter total size: ";
  int size;   // size
  cin >> size;
  
  cout << "Enter total number of partitions: ";
  int partitions;   // number of partitions
  cin >> partitions;
  
  int i,j;
  int part[partitions];  // partitions
  int used = 0;       // used memory
  int parts = 0;      // number of partitions created
  
  for(i=0; i<partitions; i++){
    cout << "Size of partition " << i+1 <<": ";
    int p;
    cin >> p;
    used += p;
    if(used > size){
      part[i] = -1;
      cout << "Part " << i+1 << " can't be given enough space as only " << size - used + p << "KB is remaining.\n";
      used -= p;
    }
    else{
      parts++;
      part[i] = p;
    }
  }
  int space = size - used;     // Amount of space with no partition
  
  cout << "Enter total number of processes: ";
  int n;
  cin >> n;     // number of processes
  
  int process[n];     // processes
  for(i=0; i<n; i++){
    cout << "Size of P" << i+1 <<": ";
    cin >> process[i];
  }
  
  int fragmentation = 0;    // Total internal fragmentation
  
  for(i=0; i<n; i++){
    
    if(parts == 0){
      cout << "P" << i+1 << " can't be given because all partitions are used.\n";
      continue;
    }
    int f = 1;      // flag
    
    for(j=0; j<partitions; j++){
      if(part[j] >= process[i]){
        cout << "P" << i+1 << " is at Part" << j+1 << ".\n";
        fragmentation += part[j] - process[i];
        part[j] = -1;
        parts--;
        f = 0;
        break;
      }
    }
    
    if(f){
      cout << "P" << i+1 << " can't be given because no partition is of required size.\n";
    }
  }
  
  cout << "Space with no partition = " << space << "\n";
  cout << "Total internal fragmentation = " << fragmentation << "\n";
}
