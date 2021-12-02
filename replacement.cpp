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
