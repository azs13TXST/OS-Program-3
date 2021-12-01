#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <ctime>
#include <cstdlib>

using namespace std;

void FIFO(int frames, int numProcesses, int processes, int x, int y, int hit, vector<int> p, vector<int> hi);
void LRU(int frames, int numProcesses, int processes, int x, int y, int hit, vector<int> p, vector<int> hi);
void Optimal(int frames, int numProcesses, int processes, int x, int y, int hit, vector<int> p, vector<int> hi);


int main() {
  int frames;
  int numProcesses;
  int x;
  int y;
  int hit = 0;
  int processes = 0; 

  cout << "Enter number of frames\n";
  cin >> frames;
  cout << "Enter number of processes\n";
  cin >> numProcesses;
  vector<int> p(numProcesses);
  vector<int> hi(numProcesses);
  cout << '\n';

  srand(time(0));
  for(int processes=0; processes<numProcesses; processes++)
    p[processes] = (rand() % 50) + 1;
    //10

  FIFO(frames, numProcesses, processes, x, y, hit, p, hi);
  LRU(frames, numProcesses, processes, x, y, hit, p, hi);
  Optimal(frames, numProcesses, processes, x, y, hit, p, hi);
    
  return 0;
} 

void FIFO(int frames, int numProcesses, int processes, int x, int y, int hit, vector<int> p, vector<int> hi)  {
  cout << "FIFO" << '\n';
  vector<vector<int>> a(frames);
  for(processes=0; processes<frames; processes++)  {
    a[processes]=vector<int>(numProcesses,-1);
  }

  map <int, int> mp;    
  for(processes=0; processes<numProcesses; processes++)  {
    vector<pair<int,int>> c;
    for(auto q: mp)  {
      c.push_back({q.second,q.first});
    }

    sort(c.begin(),c.end());
    bool hasrun=false;
    for(x=0; x<frames; x++)  {
      if(a[x][processes]==p[processes])  {
        hit++;
        hi[processes] = 1;
        mp[p[processes]]++;
        hasrun = true;
        break;
      }

      if(a[x][processes]==-1)  {
        for(y=processes; y<numProcesses; y++)
          a[x][y]=p[processes];
        mp[p[processes]]++;
        hasrun = true;
        break;
      }
    }

    if(x==frames||hasrun==false)  {
      for(x=0; x<frames; x++)  {
        if(a[x][processes]==c[c.size()-1].second)  {
          mp.erase(a[x][processes]);
          for(y=processes; y<numProcesses; y++)
            a[x][y]=p[processes];
          mp[p[processes]]++;
          break;
        }
      }
    }

    for(auto q:mp)  {
      if(q.first!=p[processes])  {
        mp[q.first]++;
      }
    }
  }

  cout<<"Process ";
  for(processes=0; processes<numProcesses; processes++)  {
    cout << p[processes] << " ";
  }

  cout<<'\n';
  for(processes=0; processes<frames; processes++)  {
    cout << "Frame " << processes << " ";
    for(x=0; x<numProcesses; x++)  {
      if(a[processes][x]==-1)
        cout << "E ";
      else 
        cout << a[processes][x] << " ";
    }
    cout << '\n';
  }

  for(processes=0; processes<numProcesses; processes++)  {
    if(hi[processes]==0)
      cout << "  ";
    else
      cout << hi[processes] << " ";
  }

  cout << "\n";
  cout << "Hit " << hit << '\n' << "Page Fault " << numProcesses-hit << '\n';
  cout << '\n';
}

void LRU(int frames, int numProcesses, int processes, int x, int y, int hit, vector<int> p, vector<int> hi)  {
  cout << "LRU" << '\n';
  vector<vector<int>> a(frames);
  for(processes=0; processes<frames; processes++)  {
    a[processes]=vector<int>(numProcesses,-1);
  }

  map <int, int> mp;    
  for(processes=0; processes<numProcesses; processes++)  {
    vector<pair<int,int>> c;
    for(auto q: mp)  {
      c.push_back({q.second,q.first});
    }

    sort(c.begin(),c.end());
    bool hasrun=false;
    for(x=0; x<frames; x++)  {
      if(a[x][processes]==p[processes])  {
        hit++;
        hi[processes] = 1;
        mp[p[processes]] = 1;
        hasrun = true;
        break;
      }

      if(a[x][processes]==-1)  {
        for(y=processes; y<numProcesses; y++)
          a[x][y]=p[processes];
        mp[p[processes]]++;
        hasrun = true;
        break;
      }
    }

    if(x==frames||hasrun==false)  {
      for(x=0; x<frames; x++)  {
        if(a[x][processes]==c[c.size()-1].second)  {
          mp.erase(a[x][processes]);
          for(y=processes; y<numProcesses; y++)
            a[x][y]=p[processes];
          mp[p[processes]]++;
          break;
        }
      }
    }

    for(auto q:mp)  {
      if(q.first!=p[processes])  {
        mp[q.first]++;
      }
    }
  }

  cout << "Process ";
  for(processes=0; processes<numProcesses; processes++)  {
    cout << p[processes] << " ";
  }

  cout << '\n';
  for(processes=0; processes<frames; processes++)  {
    cout << "Frame " << processes << " ";
    for(x=0; x<numProcesses; x++)  {
      if(a[processes][x]==-1)
        cout << "E ";
      else 
      cout << a[processes][x] << " ";
    }
    cout << '\n';
  }

  for(processes=0; processes<numProcesses; processes++)  {
    if(hi[processes]==0)
      cout << "  ";
    else
      cout << hi[processes] << " ";
  }

  cout << "\n";
  cout << "Hit " << hit << '\n' << "Page Fault " << numProcesses-hit << '\n';
  cout << '\n';
}

void Optimal(int frames, int numProcesses, int processes, int x, int y, int hit, vector<int> p, vector<int> hi)  {
  cout << "Optimal" << '\n';
  vector<vector<int>> a(frames,vector<int>(numProcesses,-1));
  map <int, int> mp;    
  for(processes=0; processes<numProcesses; processes++)  {
    vector<int> op;
    vector<pair<int,int>> c;
    for(auto q: mp)  {
      c.push_back({q.second,q.first});
    }

    for(int q=processes+1; q<numProcesses; q++)  {
      for(x=0; x<frames; x++)  {
        if(a[x][processes]==p[q])  {
          op.push_back(p[q]);
        }            
      }
    }

    sort(op.begin(),op.end());
    op.erase(unique(op.begin(),op.end()),op.end());
    bool dontCall = true;        
    if(op.size()==frames)  {
      dontCall = false;
    }

    sort(c.begin(),c.end());
    bool hasrun = false;
    for(x=0; x<frames; x++)  {
      if(a[x][processes]==p[processes])  {
        mp[p[processes]]++;
        hasrun = true;
        break;
      }

      if(a[x][processes]==-1)  {
        for(y=processes; y<numProcesses; y++)
          a[x][y]=p[processes];
        mp[p[processes]]++;
        hasrun = true;
        break;
      }
    }

    if(x==frames||hasrun==false)  {
      for(x=0; x<frames; x++)  {
        if(dontCall==true)  {
          if(a[x][processes]==c[c.size()-1].second)  {
            mp.erase(a[x][processes]);
            for(y=processes; y<numProcesses; y++)
              a[x][y]=p[processes];
            mp[p[processes]]++;
            break;
          }
        }

        else if(dontCall==false)  {
          if(a[x][processes]==op[op.size()-1])  {
            mp.erase(a[x][processes]);
            for(y=processes; y<numProcesses; y++)
              a[x][y]=p[processes];
            mp[p[processes]]++;
            break;
          }
        }
      }
    }

    for(auto q:mp)  {
      if(q.first!=p[processes])  {
        mp[q.first]++;
      }
    }
  }

  vector<int> hitv(numProcesses);
  for(processes=1; processes<numProcesses; processes++)  {
    for(x=0; x<frames; x++)  {
      if(p[processes]==a[x][processes-1])  {
        hit++;
        hitv[processes] = 1;
        break;            
      }
    }
  }

  cout<<"Process ";
  for(processes=0; processes<numProcesses; processes++)  {
    cout << p[processes] << " ";
  }

  cout << '\n';
  for(processes=0; processes<frames; processes++)  {
    cout << "Frame " << processes << " ";
    for(x=0; x<numProcesses; x++)  {
      if(a[processes][x]==-1)
        cout << "E ";
      else 
        cout << a[processes][x] << " ";
    }
    cout << '\n';
  }

  cout << "HIT     ";
  for(processes=0; processes<hitv.size(); processes++)  {
    if(hitv[processes]==0)
      cout << "  ";
    else
      cout << hitv[processes] << " ";
  }

  cout << "\n";
  cout << "Hit " << hit << '\n' << "Page Fault " << numProcesses-hit << '\n';
  cout << '\n';
}


/*
FIFO

#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,i,x,y,hit=0;
    cout<<"Enter number of frames\n";
    cin>>n;
    cout<<"Enter number of processes\n";
    cin>>m;
    vector<int> p(m);
    vector<int> hi(m);
    cout<<"Enter processes\n";
    for(i=0;i<m;i++){
        cin>>p[i];
    }
    vector<vector<int>> a(n);
    for(i=0;i<n;i++){
        a[i]=vector<int>(m,-1);
    }
    map <int, int> mp;    
    for(i=0;i<m;i++){
        vector<pair<int,int>> c;
        for(auto q: mp){
            c.push_bacy({q.second,q.first});
        }
        sort(c.begin(),c.end());
        bool hasrun=false;
        for(x=0;x<n;x++){
            if(a[x][i]==p[i]){
                hit++;
                hi[i]=1;
                mp[p[i]]++;
                hasrun=true;
                breay;
            }
            if(a[x][i]==-1){
                for(y=i;y<m;y++)
                    a[x][y]=p[i];
                mp[p[i]]++;
                hasrun=true;
                breay;
            }
        }
        if(x==n||hasrun==false){
            for(x=0;x<n;x++){
                if(a[x][i]==c[c.size()-1].second){
                    mp.erase(a[x][i]);
                    for(y=i;y<m;y++)
                        a[x][y]=p[i];
                    mp[p[i]]++;
                    breay;
                }
            }
        }
        for(auto q:mp){
            if(q.first!=p[i]){
                mp[q.first]++;
            }
        }
    }
    cout<<"Process ";
    for(i=0;i<m;i++){
        cout<<p[i]<<" ";
    }
    cout<<'\n';
    for(i=0;i<n;i++){
        cout<<"Frame "<<i<<" ";
        for(x=0;x<m;x++){
            if(a[i][x]==-1)
                cout<<"E ";
                else 
            cout<<a[i][x]<<" ";
        }
        cout<<'\n';
    }
    for(i=0;i<m;i++){
        if(hi[i]==0)
        cout<<"  ";
        else
        cout<<hi[i]<<" ";
    }
    cout<<"\n";
    cout<<"Hit "<<hit<<'\n'<<"Page Fault "<<m-hit<<'\n';
    return 0;
}

LRU

#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,i,x,y,hit=0;
    cout<<"Enter number of frames\n";
    cin>>n;
    cout<<"Enter number of processes\n";
    cin>>m;
    vector<int> p(m);
    vector<int> hi(m);
    cout<<"Enter processes\n";
    for(i=0;i<m;i++){
        cin>>p[i];
    }    
    vector<vector<int>> a(n);
    for(i=0;i<n;i++){
        a[i]=vector<int>(m,-1);
    }
    map <int, int> mp;    
    for(i=0;i<m;i++){
        vector<pair<int,int>> c;
        for(auto q: mp){
            c.push_bacy({q.second,q.first});
        }
        sort(c.begin(),c.end());
        bool hasrun=false;
        for(x=0;x<n;x++){
            if(a[x][i]==p[i]){
                hit++;
                hi[i]=1;
                mp[p[i]]=1;
                hasrun=true;
                breay;
            }
            if(a[x][i]==-1){
                for(y=i;y<m;y++)
                    a[x][y]=p[i];
                mp[p[i]]++;
                hasrun=true;
                breay;
            }
        }
        if(x==n||hasrun==false){
            for(x=0;x<n;x++){
                if(a[x][i]==c[c.size()-1].second){
                    mp.erase(a[x][i]);
                    for(y=i;y<m;y++)
                        a[x][y]=p[i];
                    mp[p[i]]++;
                    breay;
                }
            }
        }
        for(auto q:mp){
            if(q.first!=p[i]){
                mp[q.first]++;
            }
        }
    }
    cout<<"Process ";
    for(i=0;i<m;i++){
        cout<<p[i]<<" ";
    }
    cout<<'\n';
    for(i=0;i<n;i++){
        cout<<"Frame "<<i<<" ";
        for(x=0;x<m;x++){
            if(a[i][x]==-1)
                cout<<"E ";
                else 
            cout<<a[i][x]<<" ";
        }
        cout<<'\n';
    }
    for(i=0;i<m;i++){
        if(hi[i]==0)
        cout<<"  ";
        else
        cout<<hi[i]<<" ";
    }
    cout<<"\n";
    cout<<"Hit "<<hit<<'\n'<<"Page Fault "<<m-hit<<'\n';
    return 0;
}

Optimal

#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,i,x,y;
    cout<<"Enter number of frames\n";
    cin>>n;
    cout<<"Enter number of processes\n";
    cin>>m;
    vector<int> p(m);
    cout<<"Enter processes\n";
    for(i=0;i<m;i++){
        cin>>p[i];
    }
    vector<vector<int>> a(n,vector<int>(m,-1));
    map <int, int> mp;    
    for(i=0;i<m;i++){
        vector<int> op;
        vector<pair<int,int>> c;
        for(auto q: mp){
            c.push_bacy({q.second,q.first});
        }
        for(int q=i+1;q<m;q++){
            for(x=0;x<n;x++){
                if(a[x][i]==p[q]){
                    op.push_bacy(p[q]);
                }            
            }
            }
        sort(op.begin(),op.end());
        op.erase(unique(op.begin(),op.end()),op.end());
        bool dontCall=true;        
        if(op.size()==n){
            dontCall=false;
        }
        sort(c.begin(),c.end());
        bool hasrun=false;
        for(x=0;x<n;x++){
            if(a[x][i]==p[i]){
                mp[p[i]]++;
                hasrun=true;
                breay;
            }
            if(a[x][i]==-1){
                for(y=i;y<m;y++)
                    a[x][y]=p[i];
                mp[p[i]]++;
                hasrun=true;
                breay;
            }
        }
        if(x==n||hasrun==false){
            for(x=0;x<n;x++){
                if(dontCall==true){
                    if(a[x][i]==c[c.size()-1].second){
                        mp.erase(a[x][i]);
                        for(y=i;y<m;y++)
                            a[x][y]=p[i];
                            mp[p[i]]++;
                        breay;
                    }
                }
                else if(dontCall==false){
                    if(a[x][i]==op[op.size()-1]){
                        mp.erase(a[x][i]);
                        for(y=i;y<m;y++)
                            a[x][y]=p[i];
                        mp[p[i]]++;
                        breay;
                    }
                }
            }
        }
        for(auto q:mp){
            if(q.first!=p[i]){
                mp[q.first]++;
            }
        }
    }
    int hit=0;
    vector<int> hitv(m);
    for(i=1;i<m;i++){
        for(x=0;x<n;x++){
            if(p[i]==a[x][i-1]){
                hit++;
                hitv[i]=1;
                breay;            
            }
        }
    }
    cout<<"Process ";
    for(i=0;i<m;i++){
        cout<<p[i]<<" ";
    }
    cout<<'\n';
    for(i=0;i<n;i++){
        cout<<"Frame "<<i<<" ";
        for(x=0;x<m;x++){
            if(a[i][x]==-1)
                cout<<"E ";
                else 
            cout<<a[i][x]<<" ";
        }
        cout<<'\n';
    }
    cout<<"HIT     ";
    for(i=0;i<hitv.size();i++){
        if(hitv[i]==0)
            cout<<"  ";
        else
        cout<<hitv[i]<<" ";
    }
    cout<<"\n";
    cout<<"Hit "<<hit<<'\n'<<"Page Fault "<<m-hit<<'\n';
    return 0;
    }
    */



/*
int main() 
{   
  srand(time(0));  // Initialize random number generator.
 
  for(int i=0;i<10;i++)
      cout << (rand() % 10) + 1<<" ";  
  return 0; 
}*/