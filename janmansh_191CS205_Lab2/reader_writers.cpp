#include<bits/stdc++.h>
using namespace std;

int S=0, curtime, R;

struct Document{
    int at;
    int bt;
    int index;
    int wr;
    int w;
    int s;
    int wt;
};
Document *w, *r, *b;

bool compareDocuments(Document a, Document b){
    return (a.at < b.at);
}


void wait(){
    while(S<=0);
    S = S-1;
}

void signal(){
    S = S+1;
}

void writer(int x,int i){
    R = 0;
    cout<<"Writer "<<x+1<<" started writing at time "<<curtime<<endl;
    curtime += b[i].bt;
    signal();
    b[i].s = 1;
    return;
}

void reader(int x,int i){
    int t;
    if(R==1 && b[i].wt>0){
        if(b[i].wt + b[i].bt <= curtime)
            t = 0;
        else{
            t = b[i].wt + b[i].bt - curtime;
        }
    }
    else if(R==1){
        if(b[i].at + b[i].bt > curtime){
            t = b[i].at + b[i].bt - curtime;
        }
        else{
            t=0;
        }
    }
    else
        t = b[i].bt;
    R = 1;
    curtime += t;
    if(b[i].wt == 0)
        cout<<"Reader "<< x+1 <<" started reading at time "<< b[i].at <<endl;
    else
        cout<<"Reader "<< x+1 <<" started reading at time "<< b[i].wt <<endl;
    signal();
    b[i].s = 1;
    return;
}

int main(){
    int n,m,i,j;


    cout<<"Enter number of writers and readers respectively: "<<endl;
    cin>>n>>m;

    w = (Document*)malloc(n*sizeof(Document));
    r = (Document*)malloc(m*sizeof(Document));
    b = (Document*)malloc((m+n)*sizeof(Document));

    if(n>0) cout<<"Enter arrival time and burst time of Writers: "<<endl;
    for(i=0;i<n;i++){
        cin>>w[i].at>>w[i].bt;
        w[i].wr = 1;
        w[i].s = w[i].w = 0;
        w[i].index = i;
    }

    if(m>0) cout<<"Enter arrival time and burst time of Readers: "<<endl;
    for(i=0;i<m;i++){
        cin>>r[i].at>>r[i].bt;
        r[i].wr = 0;
        r[i].s = r[i].w = 0;
        r[i].index = i;
    }
    for(i=0;i<n;i++){
        b[i]=w[i];
    }
    for(i=n;i<n+m;i++){
        b[i]=r[i-n];
    }
    sort(b, b+n+m, compareDocuments);
    S = 1;
    R = 0;

    for(i=0;i<n+m;i++){
        cout<<b[i].wr<<" "<<b[i].index<<"\n";
    }

    for(i=0;i<n+m;i++){
        if(b[i].s==1)
            continue;

        if(b[i].wr==1){
            writer(b[i].index,i);
            signal();
        }   
        else{
            reader(b[i].index,i);
            signal();
        }

        for(j=i+1;b[j].at<curtime && j<n+m;j++){
    
            if(b[j].s == 1 )
                continue;
            if(b[j].wr == 0 && R==1){
                reader(b[j].index,j);
                signal();
            }
            else if(b[j].w == 1)
                continue;
            else if(b[j].wr == 0){
                cout << "Reader "<< b[j].index + 1 << " has to wait"<<endl;
                b[j].w = 1;
            }
            else{
                cout << "Writer "<< b[j].index + 1 << " has to wait"<<endl;
                b[j].w = 1;
            }
            b[j].wt = curtime;
        }
    }

    return 0;
}
