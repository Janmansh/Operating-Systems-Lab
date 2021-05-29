#include<bits/stdc++.h>
using namespace std;

// sorting according to priority and arrival time
bool priority(tuple<int,int,int,int>a, tuple<int,int,int,int>b){
  
  if( (get<0>(a)) == (get<0>(b)) ){
    return( (get<1>(a)) < (get<1>(b)) );
  }
  
  return( (get<0>(a)) < (get<0>(b)) );
}


int main() {
	int n,i,j;
	cout << "Enter the number of processes: \n";
	cin >> n; // number of processes
	
	int at[n],bt[n],p[i];   // arrival time and burst time and priority
	vector<tuple<int,int,int,int>>v;   // arrival time and burst time and priority and process number respectively
	
	int least_at = 10000000, total_time=0;
	
	cout << "Enter the arrival, burst times and priority respectively: \n";
	
	for(i=0;i<n;i++){
	  cout << "Arrival, Burst, Priority: ";
	  cin >> at[i] >> bt[i] >> p[i];
	  
	  if(at[i] < least_at){
	    least_at = at[i];
	  }
	  total_time += bt[i];
	  
	  v.push_back(make_tuple(p[i], at[i], bt[i], i+1));
	}
	
	total_time+=least_at;
	sort(v.begin(), v.end(), priority);   // sorting according to priority and arrival time
	
	int res[n+1], cur_time = 0;  // result array
	vector<int>seq;  // answer sequence
	
	for(i = 0;i <= n;i++) res[i]=-1;
	
	int start[n+1], end[n+1];
	
	while(cur_time < total_time){
	  
	  for(i = 0; i < v.size(); i++){
	    if( get<1>(v[i]) <= cur_time && get<2>(v[i]) > 0 ){
	      
	      get<2>(v[i]) -= 1;
	      
	      if( get<2>(v[i]) == 0 ){
	        end[get<3>(v[i])] = cur_time + 1;
	        seq.push_back( get<3>(v[i]) );
	      }
	      
	      if(res[get<3>(v[i])] == -1){
	        start[get<3>(v[i])] = cur_time;
	        res[get<3>(v[i])] = cur_time - get<1>(v[i]);
	      }
	      
	      break;
	    }
	  }
	  
	  cur_time++;
	}
	
	double answer=0;   // average response time
	for(i=1;i<=n;i++){
	  answer += res[i];
	}
	
	answer/=n;
	cout << "The processes get processed in the following sequence: \n";
	
	for(i=0;i<seq.size();i++){
	  cout << "P" << seq[i] << " started at time: " << start[seq[i]] << " and got ended at time: " << end[seq[i]] <<"\n";
	}
	
	cout << "The average response time of the above sequence of processes is: " << answer << "\n";
	
	return 0;
}

