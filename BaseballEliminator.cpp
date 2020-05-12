#include <bits/stdc++.h>
#define l long long

using namespace std;

vector<vector<int>> rGraph;
vector<vector< int>> graph;
vector<vector<int>> g;
vector<int> w;
vector<int > losses;
vector<int> lefts;
vector<string> teams;
vector<int> againstGamesLeftForAll;
vector<int> nodesOfTeams;
class paired
{
    public:
    bool isVisited;
    int parent;
    paired(bool isVisited,int parent)
    {
        this->isVisited=isVisited;
        this->parent=parent;
    }
};
bool bfs(const int s,const int t,int n,int& maxFlow)
{
    vector<paired> visited;
    for(int i=0;i<n;i++)
    {
        paired p(false, -1);
        visited.push_back(p);
    }
    queue< int> q;
    q.push(s);
    (visited[s]).isVisited=true;
    while(q.size()>0)
    {
        int no=q.front();
        q.pop();
        for( int i=0;i<n;i++)
        {
            if(rGraph[no][i]!=0)
            {
                if(!visited[i].isVisited)
                {
                    q.push(i);
                    visited[i].isVisited=true;
                    visited[i].parent=no;
                }
            }
        }
    }
    if(visited[t].isVisited)
    {
         int child=t;
        while(visited[child].parent!=-1)
        {
            int p=visited[child].parent;
            if(rGraph[p][child]<maxFlow)
                maxFlow=rGraph[p][child];
            
            child=p;
            if(child==0)
                break;
        }
         int child1=t;
        while(visited[child1].parent!=-1 )
        {
             int p=visited[child1].parent;
            rGraph[p][child1]-=maxFlow;
            rGraph[child1][p]+=maxFlow;
            child1=p;
            
            if(child1==0)
                break;
        }
       
        return true;
    }

    return false;
}

string convert(string s)
{
    string firstWord="";
    string secondWord="";
    int ch=-1;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='_')
        {
            ch=1;
        }
        else
        {
            if(ch==-1)
            {
                firstWord+=s[i];
            }
            else 
                secondWord+=s[i];
        }
    }

    if(secondWord.length()!=0)
    {
        return (firstWord+" "+ secondWord);
    }
    else 
        return firstWord;
}

int convertInt(int x, int original)                 //return int after considering the removed team
{
    if(x<original)
        return x;
    else 
        return (x-1);

}

int increaseInt(int x, int original)
{
    if(x<original)
        return x;
    else
        return (x+1);
}
int main()
 {
    ifstream infile;        //taking input of all parent-child nodes    
    string filename = "/home/ash/Desktop/MaxFlow/testCases/baseball/teams54.txt";
    infile.open(filename);                         
   
    string line;
    getline(infile, line);
    istringstream check(line); 

    int n; 
    check >> n;
    for(int i=0;i<n;i++)
    {
        vector<int> v;
        for(int j=0;j<n;j++)
        {
            v.push_back(0);
            
        }
        g.push_back(v);
    }
    int t=0;
    while(getline(infile, line))    
    { 
        int t1=0;
        
        string team;

        istringstream check1(line); 
        check1>>team;
        
        teams.push_back(team);
        
        int win,loss,left;
        
        check1>>win;
        check1>>loss;
        check1>>left;
        
        w.push_back(win);
        losses.push_back(loss);
        lefts.push_back(left);
        int games;
        
        while(check1>>games)
        {
            g[t][t1]=games;
            t1++;
        }
        t++;
    }
    for(int i=0;i<n;i++)
    {
        int checking=-1;
        if(checking<0)
        {
            graph.clear();
            rGraph.clear();
            vector<int> nodes;
            nodes.push_back(0);
            vector<int> firstTeam;
            vector<int> secondTeam;
            int noOfGamesNodes=0;
            int checkin2=-1;
            int capacityFromSource=0;
            for(int j=0;j<n;j++)
            {
                if(j!=i)
                {
                    for(int k=0;k<n;k++)
                    {
                        if(k!=i)
                        {
                            if(g[j][k]!=0 && j>=k)
                            {
                                nodes.push_back(g[j][k]);
                                capacityFromSource+=g[j][k];
                                if(j<i){
                                firstTeam.push_back(j);
                                }
                                else 
                                    firstTeam.push_back(j-1);
                                
                                if(k<i){
                                secondTeam.push_back(k);
                                }
                                else
                                    secondTeam.push_back(k-1);
                                noOfGamesNodes++;
                            }
                        }
                    }
                }
            }
            for(int j=0;j<n-1;j++)
            {
                nodes.push_back(10000);
            }
            
            nodes.push_back(0);
            vector<int> gamesLeftForSource;
            gamesLeftForSource.push_back(0); 
            for(int j=1;j<=noOfGamesNodes;j++)
            {
                gamesLeftForSource.push_back(nodes[j]);
            }

            for(int j=0;j<n-1;j++)
            {
                gamesLeftForSource.push_back(0);
            }

            gamesLeftForSource.push_back(0);
            graph.push_back(gamesLeftForSource);
            rGraph.push_back(gamesLeftForSource);


            //set the weight to be infinity for remaining nodes
            for(int j=0;j<noOfGamesNodes;j++)
            {
                vector<int> gaemesLeft;
                for(int k=0;k<nodes.size();k++)
                {
                    if(k>noOfGamesNodes && ((firstTeam[j]==(k-noOfGamesNodes-1) )||(secondTeam[j]==(k-noOfGamesNodes-1)))  )
                        gaemesLeft.push_back(10000);
                    else 
                        gaemesLeft.push_back(0);
                }
                graph.push_back(gaemesLeft);
                rGraph.push_back(gaemesLeft);
            }
            //set the weight of team nodes with artificial sink
            for(int k=0;k<n;k++)
            {
                if(k!=i)
                {
                    vector<int > gamesLeftforTeam;

                    for(int j=0;j<nodes.size();j++)
                    {
                        if(j==nodes.size()-1)
                        {
                                if(w[i]+ lefts[i]- w[k]>=0){
                                    gamesLeftforTeam.push_back(w[i]+ lefts[i]- w[k]);
                                }
                                else
                                {
                                    cout<<convert(teams[i])<<" is eliminated."<<endl;
                                    cout<<"They can win at most "<<w[i]<<" + "<<lefts[i]<<" = "<<w[i]+lefts[i]<<" games."<<endl;
                                    cout<<convert(teams[k])<<" has won a total of "<<w[k]<<" games."<<endl;
                                    cout<<"They play each other 0 times."<<endl;
                                    cout<<"So on average, each of the teams in this group wins "<<w[k]<<"/1 = "<<w[k]<<" games."<<endl;
                                    checkin2=1;
                                    break;
                                }
                        }
                        else 
                        gamesLeftforTeam.push_back(0); 
                    }
                    if(checkin2>0)
                        break;
                    graph.push_back(gamesLeftforTeam);
                    rGraph.push_back(gamesLeftforTeam);


                }
            }
            if(checkin2<0)   
            {
                vector<int > ga;
                for(int j=0;j<nodes.size();j++)
                {
                    ga.push_back(0);
                }

                graph.push_back(ga);
                rGraph.push_back(ga);
                for(int j=0;j<nodes.size();j++)
                {
                    for(int k=0;k<nodes.size();k++)
                    {
                        if(graph[j][k]<0)
                        {
                            graph[j][k]=0;
                            rGraph[j][k]=0;
                        }
                    }
                }

                int max=0;
                int maxFlow=1000;
                while(bfs(0,nodes.size()-1,nodes.size(), maxFlow))
                {
                    max+=maxFlow;
                    
                    maxFlow=1000;
                }

                int teamsForAverage[n];
                for(int j=0;j<n;j++)
                {
                    teamsForAverage[j]=-1;
                }

                

                for(int j=1;j<=noOfGamesNodes;j++)
                {
                    if(rGraph[0][j]!=0)
                    {
                        int v=firstTeam[j-1];
                        int v1=secondTeam[j-1];
                        if(v<i )
                        teamsForAverage[v]=1;
                        else 
                            teamsForAverage[v+1]=1;

                        if(v1<i)
                        teamsForAverage[v1]=1;
                        else 
                            teamsForAverage[v1+1]=1;
                    }
                }
                vector<int> forAverage;
                for(int j=0;j<n;j++)
                {
                    if(j!=i)
                    if(teamsForAverage[j]>0)
                        forAverage.push_back(j);
                }


                if(max!=capacityFromSource)
                {

                    int winsTotal=0;
                    float winsAverage=0;
                    float noOfTeams=0;
                    vector<string> teamsWithMoreAverageWins;
                    int maxNoTeam=-1;
                    int gamesLeft1=0;


                    for(int j=0;j<forAverage.size();j++)
                    {
                    winsTotal+=w[forAverage[j]];
                    }
                
                    noOfTeams=forAverage.size();
                    for(int j=0;j<forAverage.size();j++)
                    {
                        for(int k=0;k<forAverage.size();k++)
                        {
                            if(j!=k && j>=k)
                            {
                                    gamesLeft1+=g[forAverage[j]][forAverage[k]];

                            }

                        }  

                    }

                    cout<<convert(teams[i])<<" is eliminated."<<endl;
                    cout<<"They can win at most "<<w[i]<<" + "<<lefts[i]<<" = "<<w[i]+lefts[i]<<" games."<<endl;

                    for(int j=0;j<forAverage.size();j++)
                    {
                       
                        if(j==forAverage.size()-1)
                        {
                                cout<<convert(teams[forAverage[j]])<<" have won a total of "<<winsTotal<<" games."<<endl;
                        }
                        else if(j==forAverage.size()-2)
                            cout<<convert(teams[forAverage[j]])<<" and ";
                        else
                        cout<<convert(teams[forAverage[j]])<<", ";
                    }

                    cout<<"They play each other "<<gamesLeft1<<" times."<<endl;
                    cout<<"So on average, each of the teams wins "<<winsTotal+gamesLeft1<<"/"<<noOfTeams<<" = "<<(winsTotal+gamesLeft1)/noOfTeams<<" games."<<endl;
                   
                }
                graph.clear();
                rGraph.clear();
            }
        }
    }
    
    return 0;
}
