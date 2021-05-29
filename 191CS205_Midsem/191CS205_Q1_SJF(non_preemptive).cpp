#include<bits/stdc++.h>
using namespace std;

int main() {
    
	cout << "Enter the number of processes:\n";
	int n,i,j;
	cin >> n;   //number of processes
	
	vector<tuple<int, int, int>>times(n);   // {Arrival time, Burst time. process number}
	
	cout << "Enter the Arrival time and Burst time respectively of "<<n<<" programs:\n";
	for(i=0;i<n;i++){
	    int t;
	    
	    cout << "Arrival, Burst: ";
	    
	    cin >> t;
	    get<0>(times[i]) = t;  // Arrival time
	    
	    cin >> t;
	    get<1>(times[i]) = t;  // Burst time
	    
	    get<2>(times[i]) = i+1;
	}
	
	sort(times.begin(),times.end()); // sorting according to Arrival time
	
	int ti=get<0>(times[0]);   // current time
	int visited[n]={0};        // programs visited
	
	vector<int>seq;  // sequence of processes processed
	
	int start[n+1],end[n+1], res[n+1];
	
	for(i=0;i<n;i++){
	    
	    int min=1000000,tak=-1,min1=1000000; // tak is the index of the chosen element
	    
	    for(j=0;j<n;j++){
	        
	        if(visited[j])continue;
	        
	        if(get<0>(times[j]) <= ti){
	            if( get<1>(times[j]) < min ){
	                min=get<1>(times[j]);
	                tak=j;
	            }
	        }
	        
	        else{
	            if( get<0>(times[j]) < min1 ){
	                min1=get<0>(times[j]);
	            }
	        }
	        
	    }
	    
	    // no element chosen (Arrival time of each greater than current time)
	    if(tak==-1){
	        ti=min1;
	        i--;
	    }
	    
	    else{
	        visited[tak]=1;
	        start[get<2>(times[tak])] = ti;
	        
	        res[get<2>(times[tak])] = start[get<2>(times[tak])] - get<0>(times[tak]);
	        ti += get<1>(times[tak]);
	        
	        end[get<2>(times[tak])] = ti;
	        seq.push_back(get<2>(times[tak]));
	    }
	    
	}
	
	double answer=0; // Average response time
	
	for( i = 1;i <= n; i++){
	  answer += res[i];
	}
	answer /= n;
	
	cout << "The processes get processed in the following sequence: \n";
	
	for(i=0;i<seq.size();i++){
	  cout << "P" << seq[i] << " started at time: " << start[seq[i]] << " and got ended at time: " << end[seq[i]] <<"\n";
	}
	
	cout << "The average response time of the above sequence of processes is: " << answer << "\n";
	
	return 0;
}
