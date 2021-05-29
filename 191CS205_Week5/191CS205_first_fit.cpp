#include<bits/stdc++.h>
using namespace std;

int insert_p(vector<pair<int,int>> &partition, int p_no, int p_size, int size, int remaining){
  int i, rem_part;
  if(p_size > remaining){
    cout << "Process " << p_no << " cannot be accomodated due to insufficient space\n";
    return remaining;
  }

  if(partition.size() == 1 && partition[0].first == -1){
    remaining -= p_size;
    partition.insert(partition.begin(),make_pair(p_no,p_size));
    partition.pop_back();
    if(remaining > 0)
      partition.push_back(make_pair(-1, remaining));
  }
  else{
    for(i=0; i<partition.size(); i++){
      if(partition[i].first > 0) continue;
      if(partition[i].second >= p_size){
        break;
      }
    }

    if(i==partition.size()){
      cout << "Process " << p_no << " cannot be accomodated due to external fragmentation"<< endl;
      return remaining;
    }

    remaining -= p_size;
    rem_part = partition[i].second - p_size;    
    partition[i].second = p_size;
    partition[i].first = p_no;

    if(rem_part > 0){
      if(i < partition.size()-1)
        partition.insert(partition.begin()+i+1, make_pair(-1, rem_part));
      else
        partition.push_back(make_pair(-1,rem_part));
    }
  
  }
  return remaining;
}


int delete_p(vector<pair<int,int>> &partition, int p_no, int size, int remaining){
  int i=0;
  while(i<partition.size()){
    if(partition[i].first == p_no){
      partition[i].first = -1;
      remaining += partition[i].second;
      break;
    }
    i++;
  }
  if(i == partition.size()){
    cout << "Process not in memory\n";
    return remaining;
  }
  if(i < partition.size() - 1 && partition[i+1].first == -1){
    partition[i].second += partition[i+1].second;
    partition.erase(partition.begin()+i+1);
  }
  if(i > 0 && partition[i-1].first == -1){
    partition[i].second += partition[i-1].second;
    partition.erase(partition.begin()+i-1);
  }
  return remaining;
}


int main(){
  int i, j, size, p_size, p_no, remaining;
  cout << "Enter the total size: ";
  cin >> size;
  vector<pair<int,int>> partition;
  partition.push_back(make_pair(-1, size));
  remaining = size;
  while(1){
    cout << "Enter-->\n1 : Insert,  2 : Delete,  3 : Stop\n";
    int x;
    cin>>x;
    if(x==1){
      cout << "Enter process no. and process size respectively: \n";
      cout << "Process no.: "; cin >> p_no;
      cout << "Process size: "; cin >> p_size;
      remaining = insert_p(partition, p_no, p_size, size, remaining);
    }
    else if(x==2){
      cout << "Enter process no.: ";
      cin >> p_no;
      remaining = delete_p(partition, p_no, size, remaining);
    }
    else if(x==3){
      break;
    }
    else{
      cout<<"wrong input, try again\n";
    }
  }
  cout << "\nMemory partitions: \n";
  for(i=0; i<partition.size(); i++){
    if(partition[i].first == -1){
      cout << "Partition " << i+1 << " is empty with size " << partition[i].second << "\n";
    }
    else{
      cout << "Partition " << i+1 << " is occupied by process " << partition[i].first <<" with size " << partition[i].second << "\n";
    }
  }
  cout << "\n----End----\n";
  
  
  return 0;
}
