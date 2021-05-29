#include<bits/stdc++.h>

using namespace std;

//structure of a proceess
struct Process{
    int *alloc;    // amount of each resource allocated
    int *maxi;      // maximum resources needed
    int *rem;    
    int comp;      


};

//structure of a Resource
struct Resource{
        int ins;        // instances
        int sum;        // sum of each resource
        int avail;      // available resources
};

// array of structures
Process *p; 
Resource *r;


void bankers(int n,int res){
    int i, j, f, loop, seq[n], sq;

    for(int j=0;j<res;j++)             
        r[j].avail = r[j].ins - r[j].sum;

    for(i=0;i<n;i++)
        p[i].comp = 0;

    loop = 0; 
    sq = 0;     
    i = 0;        

    while(i<n){
        if(p[i].comp != 1){
            f = 1;      
            for(j=0;j<res;j++){                              
                if(r[j].avail < p[i].rem[j]){
                    f = 0;
                    break;
                }
            }

            if(f==1){
                for(j=0;j<res;j++){
                    r[j].avail += p[i].alloc[j];
                }

                loop = 1;
                
                seq[sq] = i+1;
                sq++;

                p[i].comp = 1;
                
            }
        }

        if(sq == n){
            break;
        }

        i++;
        if(i==n){
            if(loop == 0){
                break;
            }
            else{
                i = 0;
                loop = 0;
            }
        }
    }


    if(sq < n)
        cout<<"\nSystem goes in deadlock, safe sequence not possible."<<endl;
    else{
        cout<<"\nSystem won't go in deadlock and processes are executed in following sequence: "<<endl;
        for(i=0;i<n;i++){
            cout<<"Process "<<seq[i]<<endl;
        }
    }

    return;
}


int main(){
    int n, res, i, j, f;

    cout<<"Enter number of processes: "<<endl;
    cin>> n;
    cout<<"Enter number of resources: "<<endl;
    cin>> res;

    p = (Process*)malloc(n*sizeof(Process));
    r = (Resource*)malloc(res*sizeof(Resource));
    
    cout<<"Enter the number of instances of each resource: "<<endl;
    for(i=0;i<res;i++){
        cin >> r[i].ins;
        r[i].sum = 0;
    }

    f = 1;   
    
    cout<<"\nEnter the number of allocated instances of each resource to each process: "<<endl;
    for(i=0;i<n;i++){
        p[i].alloc = (int*)malloc(res*sizeof(int));
        cout<<"Enter number of each resources allocated to process "<<i+1<<" :"<<endl;
        for(int j=0;j<res;j++){
            cin>> p[i].alloc[j];
            r[j].sum += p[i].alloc[j];
            if(r[j].sum > r[j].ins)     
                f = 0;
        }
    }


    cout<<"\nEnter the maximum requirement of each process: "<<endl;
    for(i=0;i<n;i++){

        p[i].maxi = (int*)malloc(res*sizeof(int));
        p[i].rem = (int*)malloc(res*sizeof(int));

        cout<<"Enter maximum need of each resource for process "<<i+1<<" :"<<endl;
        for(int j=0;j<res;j++){
            cin>> p[i].maxi[j];

            if(p[i].maxi[j] > r[j].ins)
                f = 0;

            p[i].rem[j] = p[i].maxi[j] - p[i].alloc[j];  
            if(p[i].rem[j] < 0)
                p[i].rem[j] = 0;  
        }
    }


    if(f == 0)
        cout<<"\nSystem goes in deadlock, safe sequence not possible."<<endl;
    else
        bankers(n,res);

    return 0;
}