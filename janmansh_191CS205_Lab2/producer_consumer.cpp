#include<bits/stdc++.h>
using namespace std;

int S=1, E, F=0, curtime=0;

struct Business{
    int at;
    int bt;
    int pc;
};

bool compareTwoBusinesses(Business a, Business b){
    return (a.at < b.at);
}

void wait(){
    while(S<=0);
    S = S-1;
}

void signal(){
    S = S+1;
}

void producer(int x,int t){
    E--;
    F++;
    cout<<"Producer "<<x+1<<" started producing at time"<<curtime<<"\n";
    curtime+=t;
    wait();
    return;
}

void consumer(int x,int t){
    E++;
    F--;
    cout<<"Consumer "<<x+1<<" started consuming at time"<<curtime<<"\n";
    curtime+=t;
    wait();
    return;
}

int main(){
    int n,m,buf,i,j;
    
    cout<<"Enter the buffer size: ";
    cin>>buf;

    cout<<"Enter number of producers and consumers respectively: "<<endl;
    cin>>n>>m;

    Business p[n], c[m];


    cout<<"Enter arrival time and burst time of Producers: "<<endl;
    for(int i=0;i<n;i++){
        cin>>p[i].at>>p[i].bt;
        p[i].pc = 1;
    }

    cout<<"Enter arrival time and burst time of Consumers: "<<endl;
    for(int i=0;i<m;i++){
        cin>>c[i].at>>c[i].bt;
        c[i].pc = 2;
    }

    sort(p,p+n, compareTwoBusinesses);
    sort(c,c+m, compareTwoBusinesses);

    E = buf;

    for(i=0,j=0;i<n&&j<m;){
        if(p[i].at <= c[j].at){
            if(S!=0 && E!=0){
                producer(i,p[i].bt);
                i++;
                int pr=i,cr=j,temp=p[i].bt;
                while((temp--)&&(p[pr].at)<=curtime&&pr<n){
                    cout<<"Producer P"<<pr+1<<" has to wait as P"<<i<<" is running\n";
                    pr++;
                }
                temp=p[i].bt;
                while((temp--)&&((p[cr].at)<=curtime)&&cr<m){
                    cout<<"Consumer C"<<cr+1<<" has to wait as P"<<i<<" is running\n";
                    cr++;
                }
                signal();
            }
            else{
                cout<<"Overflow occurred when Producer"<<i+1<<" arrived"<<endl;
            }
        }    
        else{
            if(S!=0 && F!=0){
                consumer(j,c[j].bt);
                j++;
                int pr=i,cr=j,temp=c[j].bt;
                while((temp--)&&(p[pr].at)<=curtime&&pr<n){
                    cout<<"Producer P"<<pr+1<<" has to wait as C"<<j<<" is running\n";
                    pr++;
                }
                temp=c[j].bt;
                while((temp--)&&(p[cr].at)<=curtime&&cr<m){
                    cout<<"Consumer C"<<cr+1<<" has to wait as C"<<j<<" is running\n";
                    cr++;
                }
                signal();
            }
            else{
                cout<<"Underflow occurred when Consumer "<<j+1<<" arrived."<<endl;
            } 
        }
    }

    while(i<n){
        if(S!=0 && E!=0){
            producer(i,p[i].bt);
            i++;
            int pr=i,cr=j,temp=p[i].bt;
            while((temp--)&&(p[pr].at)<=curtime&&pr<n){
                cout<<"Producer P"<<pr+1<<" has to wait as P"<<i<<" is running\n";
                pr++;
            }
            temp=p[i].bt;
            while((temp--)&&(p[cr].at)<=curtime&&cr<m){
                cout<<"Consumer C"<<cr+1<<" has to wait as P"<<i<<" is running\n";
                cr++;
            }
            signal();
        }
        else{
            cout<<"Overflow occurred when Producer"<<i+1<<" arrived"<<endl;
            cout<<"No consumers left to consume the products"<<endl;
            break;
        }
    }
    while(j<m){
        if(S!=0 && F!=0){
            consumer(j,c[j].bt);
            j++;
            int pr=i,cr=j,temp=c[j].bt;
            while((temp--)&&p[pr].at<=curtime&&pr<n){
                cout<<"Producer P"<<pr+1<<" has to wait as C"<<j<<" is running\n";
                pr++;
            }
            temp=c[j].bt;
            while((temp--)&&p[cr].at<=curtime&&cr<m){
                cout<<"Consumer C"<<cr+1<<" has to wait as C"<<j<<" is running\n";
                cr++;
            }
            signal();
        }
        elses{
            cout<<"Underflow occurred when Consumer "<<j+1<<" arrived."<<endl;
            cout<<"No producers left to consume the products"<<endl;
        } 
    }
    return 0;
}