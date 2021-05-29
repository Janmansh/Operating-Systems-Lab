#include<bits/stdc++.h>
using namespace std;

int main(){
  
  int n,i,j;
  cout << "Enter the No. of frames: ";
  
  cin >> n;     // No. of frames
  int a[n]={0};         // Frame array
  
  int k, input = 0, fault=0;
  j = 0;
  
  while(1){
    cout << "Enter 1 to add pages to frame, Enter 2 to stop adding: ";
    cin >> k;
    
    if(k == 2){
      break;
    }
    
    int p, flag=0;    // page number and flag to check if page already present
    cout << "Page No.: ";
    cin >> p;
    
    input++;
    
    for(i=0;i<n;i++){
      if(a[i] == p){
        cout << "P" << p << " is already present at frame F" << i << "\n";
        flag=1;
        break;
      }
    }
    
    if(flag)continue;
    
    if(a[j]==0){
      cout << "P" << p << " is accomodated in frame F" << j <<"\n";
      a[j] = p;
      fault++;
      j++;
      j%=n;
      continue;
    }
    
    cout << "P"<< p << " is accomodated in frame F" << j << " after removing P" << a[j] << "\n";
    
    a[j] = p;
    j++;
    j%=n;
    fault++;
    
  }
  
  double ratio = (fault*1.0)/(input*1.0);
  
  cout << "No. of page faults: "<<fault<<"\n";
  
  cout << "Page fault ratio = No. of page faults/total inputs\n";
  
  cout <<" = "<<fault<<"/"<<input<<" = "<<ratio<<"\n";
  
  return 0;
}
