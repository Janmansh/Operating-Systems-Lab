#include<bits/stdc++.h>
using namespace std;

//stores size, accomodation status and number of occupied partition for a process
struct Partition{
    int acc;
    int size;
    int process_id;
    int process_size;
};

int main(){
  
  cout << "Enter total size (in KB): ";
  int size;   // size
  cin >> size;
  
  cout << "Enter total number of partitions: ";
  int partitions;   // number of partitions
  cin >> partitions;
  
  int i,j;
  Partition part[partitions];  // partitions
  int used = 0;       // used memory
  int parts = 0;      // number of partitions created
  
  for(i=0; i<partitions; i++){
    cout << "Size of partition " << i+1 <<"(in KB) : ";
    int p;
    cin >> p;
    used += p;
    if(used > size){
      part[i].acc = -1;
      part[i].size = 0;
      part[i].process_id = -1;
      part[i].process_size = 0;
      cout << "Part " << i+1 << " can't be given enough space as only " << size - used + p << "KB is remaining.\n";
      used -= p;
    }
    else{
      parts++;
      part[i].acc = 0;
      part[i].size = p;
      part[i].process_id = -1;
      part[i].process_size = 0;
    }
  }
  
  int space = size - used;     // Amount of space with no partition (wasted)
  int fragmentation = 0; 
  
  while (1){
    cout << "\nEnter--> 1 : Insert,  2 : Delete,  3 : Stop\n";
    
    int x, p_id, process_size;
    cin>>x;
    
    if( x == 1 ){
      cout << "Enter process id : " ;
      cin >> p_id;

      int flag = 0;
      for(i=0; i<partitions ;i++){
        if(part[i].process_id == p_id){
          flag = 1;
          cout << "Process " << p_id << " already exists at partition " << i+1 << "\n";
          break;
        }
      }
      if(flag == 1){
        continue;
      }

      cout << "Enter process size(in KB) : ";
      cin >> process_size;

      int internal_frag = 0;
      int external_frag = 0;
      int fit = -1;
      for(i=0; i<partitions ; i++){
        if(part[i].acc == -1) continue;
        
        if(part[i].acc == 1){
          internal_frag = max(internal_frag, (part[i].size-part[i].process_size));
          external_frag += part[i].size - part[i].process_size;
          continue;
        }

        if(fit==-1 && part[i].size >= process_size){
          fit = i;
        }
        
        else if(fit>=0 && part[fit].size < part[i].size){
          fit = i;
        }
        
        else{
          external_frag += part[i].size;
        }
        
      }

      if(fit == -1){
        if(internal_frag >= process_size && external_frag >= process_size)
          cout << "Process " << p_id <<  " cannot be accomodated in any partition due to both external fragmentation and internal fragmentation" << "\n";
        else if(internal_frag >= process_size)
          cout << "Process " << p_id << " cannot be accomodated in any partition due to internal fragmentation" << "\n";
        else if(external_frag >= process_size)
          cout << "Process " << p_id << " cannot be accomodated in any partition due to external fragmentation" << "\n";
        else
          cout << "Process " << p_id << " cannot be accomodates due to insufficient space" << "\n";
      }
      
      else{
        part[fit].acc = 1;
        part[fit].process_id = p_id;
        part[fit].process_size = process_size;
        cout << "Process " << p_id << " is accomodated in partition number " << fit+1 << "\n";
      }
      
    }
    else if( x == 2){
      cout << "Enter the process id of the process to be deleted: ";
      
      cin >> p_id;

      int flag = 0;

      for(i=0;i<partitions ; i++){
        if(part[i].process_id == p_id){
          flag = 1;
          break;
        }
      }

      if(flag == 1){
        cout << "Process removed from partiton " << i+1 << "\n";
        part[i].acc = 0;
        part[i].process_id = -1;
        part[i].process_size = 0;
      }
      
      else{
        cout << "Process does not exist in any partition " << "\n";
      }
    }
    
    else if( x == 3 ){
      break;
    }
    
    else{
      cout << "Wrong input. Try again.\n";
    }
  }
  
  
  fragmentation = 0;    // Total internal fragmentation
  
  for(i=0; i<partitions ; i++){
    if(part[i].acc == 0 || part[i].acc == -1) continue;
      fragmentation += (part[i].size - part[i].process_size);
  }
  
  cout << "\nPartition Table (according to worst fit) : \n";
  
  cout << "Partition No.   Partition status   Partition Size   Process ID   Process Size\n";
  
  for(i=0; i<partitions; i++){
    cout << "     " << i+1 << "       " << "         " << part[i].acc << "     " << "              " << part[i].size << "KB  " << "        " << part[i].process_id << "    " << "        " << part[i].process_size << "KB\n";
  }

  cout << "\nTotal wasted space: " << space << "KB" << "\n";
  cout << "\nTotal internal fragmentation: "<< fragmentation << "KB" << "\n";
  
  return 0;
}
