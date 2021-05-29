#include<bits/stdc++.h>
using namespace std;

int main() {
    
	cout << "Enter the number of processes:\n";
	int n,i;
	cin >> n;
	vector<tuple<int, int, int, int, int>>times(n); // {at, bt, ct, tat, wt}
	
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
	
	int ti=0;   // current time
	
	for(i=0;i<n;i++){
	    
	    if(ti < get<0>(times[i]) ) ti = get<0>(times[i]);
	    
	    get<2>(times[i]) = ti + get<1>(times[i]);
	    ti+=get<1>(times[i]);
	    
	    get<3>(times[i]) = get<2>(times[i]) - get<0>(times[i]);
	    get<4>(times[i]) = get<3>(times[i]) - get<1>(times[i]);
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
