#include<bits/stdc++.h>
using namespace std;

int main(){
  
  int n,i,j,vm,pm,ps;
  cout << "Enter the size of virtual memory in KB: ";
  cin >> vm;
  cout << "Enter the size of physical memory in KB: ";
  cin >> pm;

  cout << "Enter the size of page in KB: ";
  cin >> ps;

  int pvm = vm/ps, ppm = pm/ps;

  cout << "Number of pages in virtual memory: " << pvm << "\n";
  cout << "Pages are from 0 - " << pvm-1 << "\n";
  cout << "Number of frames in physical memory: " << ppm << "\n";
  cout << "Frames are from 0 - " << ppm-1 << "\n";
  
  int a[ppm];         // Frame array
  int b[pvm];         // Virtual memory array
  
  int sm;
  
  cout << "Enter the number of tracks in Secondary Memory: ";
  cin >> sm;
  
  cout << "Secondary Memory is from 0 - " << sm-1 <<"\n";
  
  int sec_m[pvm];
  
  cout << "\nEnter the track location of pages\n";
  
  for(i=0;i<pvm;i++){
    cout << "Location of P" << i << ": ";
    int kk;
    cin >> kk;
    sec_m[i] = kk;
  }
  
  int head;
  
  cout << "\nInitial Location of R/W head: ";
  cin >> head;
  
  while(head >= sm){
    cout << "Wrong head value. Enter from 0 - " << sm-1 << " again\n";
    cin >> head;
  }
  
  for(i=0;i<ppm;i++)a[i]=-1;
  for(i=0;i<pvm;i++)b[i]=-1;

  int max_offset = ps*1024 - 1;
  
  int k, input = 0, fault=0;
  j = 0;
  
  set<int>r_seq;      // set to store the request sequence
  
  while(1){
    cout << "\nEnter 1 to virtual address in the format 'page_no word_offset', Enter 2 to stop adding: ";
    cin >> k;
    
    if(k == 2){
      break;
    }
    
    if(k!=1){
      cout << "Wrong input please try again\n";
      continue;
    }
    
    int p, flag=0, offset;    // page number and flag to check if page already present and word-offset
    cout << "Page No.: ";
    cin >> p;

    cout << "Offset: ";
    cin >> offset;

    if(offset > max_offset ){
      cout << "Offset exceeded maximum offset limit\n";
      continue;
    }
    
    input++;
    
    if(b[p] != -1){
      cout << "The physical address for the above virtual address is " << b[p] << " " << offset << "\n";
      continue;
    }

    cout << "P" << p << " is not present in the physical memory\n";
    
    if(r_seq.find(sec_m[p]) == r_seq.end()){
      cout << "Track request => Track " << sec_m[p] << "\n";
      r_seq.insert(sec_m[p]);
    }

    for(i=0;i<ppm;i++){
      if(a[i] == -1){
        cout << "P" << p << " is accomodated in frame F" << i << "\n";
        a[i] = p;
        b[p] = i;
        fault++;
        flag = 1;
        break;
      }
    }

    if(flag)continue;
    
    cout << "P"<< p << " is accomodated in frame F" << j << " after removing P" << a[j] << " according to FIFO\n";

    b[a[j]] = -1;
    b[p] = j;
    a[j] = p;

    j++;
    j%=ppm;
    fault++;
    
  }
  
  int seek_time = 0;
  auto it = r_seq.begin();
  
  int star = head;
  
  // adding all differences to the left of head (if any)
  if((*it) <= head ){
    seek_time += (head - (*it));
    star = (*it);
  }
  
  it = r_seq.end();
  
  it--;
  
  // adding all differences to the right of head (if any)
  if((*it) > head ){
    seek_time += ((*it) - star);
  }
  
  double ratio = (fault*1.0)/(input*1.0);
  
  cout << "\nNo. of page faults: "<<fault<<"\n";
  
  cout << "\nPage fault ratio = No. of page faults/total inputs\n";
  
  cout <<" = "<<fault<<"/"<<input<<" = "<<ratio<<"\n";
  
  cout << "\nSeek time (according to LOOK algorithm with initial direction left) = " << seek_time << "\n";

  cout << "\nFinal page table: \n";

  for(i=0;i<pvm;i++){
    if( b[i] == -1){
      cout << "P" << i << " Not in any frame\n";
      continue;
    }
    cout << "P" << i << " " << b[i] << "\n";
  }
  
  cout << "\nFinal physical memory alloted: \n";

  for(i=0;i<ppm;i++){
    if(a[i] == -1){
      cout << "F" << i << " Empty\n";
      continue;
    }
    cout << "F" << i << " P" << a[i] << "\n";
  }
  
  return 0;
}
