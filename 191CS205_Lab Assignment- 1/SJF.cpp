#include<bits/stdc++.h>
using namespace std;

int main() {
    
	cout << "Enter the number of processes:\n";
	int n,i,j;
	cin >> n;
	vector<tuple<int, int, int, int, int>>times(n);   // {at, bt, ct, tat, wt}
	
	cout << "Enter the Arrival time and Burst time respectively of "<<n<<" programs:\n";
	for(i=0;i<n;i++){
	    int t;
	    cin>>t;
	    get<0>(times[i])=t;  // Arrival time
	    cin>>t;
	    get<1>(times[i])=t;  // Burst time
	    get<2>(times[i])=0;  // Completion time
	    get<3>(times[i])=0;  // Turn around time
	    get<4>(times[i])=0;  // Waiting time
	}
	
	sort(times.begin(),times.end()); // sorting according to Arrival time
	
	int ti=get<0>(times[0]);   // current time
	int visited[n]={0};        // programs visited
	
	for(i=0;i<n;i++){
	    
	    int min=1000000,tak=-1,min1=1000000; // tak is the index of the chosen element
	    
	    for(j=0;j<n;j++){
	        
	        if(visited[j])continue;
	        
	        if(get<0>(times[j])<=ti){
	            if(get<1>(times[j])<min){
	                min=get<1>(times[j]);
	                tak=j;
	            }
	        }
	        
	        else{
	            if(get<0>(times[j])<min1){
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
	        ti += get<1>(times[tak]);
	        get<2>(times[tak]) = ti;
	        get<3>(times[tak]) = get<2>(times[tak]) - get<0>(times[tak]);
	        get<4>(times[tak]) = get<3>(times[tak]) - get<1>(times[tak]);
	    }
	    
	}
	
	double TAT=0,TWT=0;
	
	for(i=0;i<n;i++){
	    TAT += get<3>(times[i]);
	    TWT += get<4>(times[i]);
	}
	
	TAT = TAT/(1.0*n);    // Average TAT
	TWT = TWT/(1.0*n);    // Average WT
	
	cout << "Average Turn around time is: " << TAT <<"\n";
	cout << "Average Waiting time is: " << TWT <<"\n";
	
	return 0;
}
