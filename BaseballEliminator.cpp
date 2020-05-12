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
    vector<int> nodesOfMatches;
    vector<int > firstTeam;
    vector<int > firstTeamOriginal;
    vector<int> secondTeam;
    vector<int> secondTeamOriginal;
    int noOfGamesNodes=0;
    int capacity=0;
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
// vector<int> minCutNodes;
bool bfs(const int s,const int t,int n,int& maxFlow)
{
    vector<paired> visited;
    for(int i=0;i<n;i++)
    {
        paired p(false, -1);
        visited.push_back(p);
    }
    
    // cout<<"size of vector is "<<visited.size()<<endl;
    queue< int> q;
    q.push(s);
    (visited[s]).isVisited=true;
    // if(s==t)
    // return true;
    // minCutNodes.push_back()
    
    while(q.size()>0)
    {
        // cout<<"size of q= "<<q.size()<<endl;
        int no=q.front();
        // cout<<"front element of q is "<<q.front()<<endl;
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
                    // cout<<i<<" pushed into the queue"<<endl;
                }
            //     if(rGraph[s][i]<maxFlow)
            //     maxFlow=rGraph[s][i];
                
            //     return bfs(i, t,n, *rGraph, &maxFlow);
                
            }
        }
    }
    // if(maxFlow==500)
    // {
    //     for(int j=0;j<visited.size();j++)
    //     {
    //         if(visited[j].isVisited){
              
    //             cout<<"visited["<<j<<"]= "<<visited[j].isVisited<<endl;
    //             cout<<"rGraph["<<j<<"]= "<<rGraph[j][n-1]<<endl<<endl;
    //         }
    //     }
    // }
    if(visited[t].isVisited)
    {
        // cout<<"value of t was "<<t<<endl;
        // cout<<"path found"<<endl;
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
         // cout<<"maxflow found to be "<<maxFlow<<endl;
        while(visited[child1].parent!=-1 )
        {
             int p=visited[child1].parent;
             // cout<<"rGraph["<<p<<"]["<<child1<<"] was "<<rGraph[p][child1]<<endl;
             // int x=rGraph[p][child1];
            rGraph[p][child1]-=maxFlow;
            rGraph[child1][p]+=maxFlow;
            // cout<<"rGraph["<<p<<"]["<<child1<<"] is "<<rGraph[p][child1]<<endl;
            child1=p;
            
            if(child1==0)
                break;
        }
       
        return true;
    }
    // else cout<<"last node not visited"<<endl;

    return false;
}

string convert(string s)
{
    string firstWord="";
    string secondWord="";
    int ch=-1;
    for(int i=0;i<s.length();i++)
    {
        // cout<<"s[i]= "<<s[i]<<endl;
        if(s[i]=='_')
        {
            // cout<<"found"<<endl;
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
bool makeGraph(int checkTeam,int n)
{
    cout<<"For checkTeam= "<<teams[checkTeam]<<endl;

    graph.clear();
    rGraph.clear();
    nodesOfTeams.clear();
    nodesOfMatches.clear();
    firstTeam.clear();
    firstTeamOriginal.clear();
    secondTeam.clear();
    secondTeamOriginal.clear();
    noOfGamesNodes=0;
    capacity=0;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(j!=checkTeam && i!=checkTeam)
            {
                if(g[i][j]!=0 && j>=i)
                {
                    nodesOfMatches.push_back(g[i][j]);
                    firstTeamOriginal.push_back(i);
                    secondTeamOriginal.push_back(j);
                    firstTeam.push_back(convertInt(i,checkTeam));

                    secondTeam.push_back(convertInt(j,checkTeam));
                    noOfGamesNodes++;
                }
            }
        }
    }
///////////////////////////////    
    //Source 
    vector<int> gamesLeftForSource;
    gamesLeftForSource.push_back(0);
    for(int i=0;i<nodesOfMatches.size();i++)
    {
        gamesLeftForSource.push_back(nodesOfMatches[i]);
        capacity+=nodesOfMatches[i];
    }
    
    for(int i=0;i<n-1;i++)
    {
        gamesLeftForSource.push_back(0);
    }
    gamesLeftForSource.push_back(0);
    graph.push_back(gamesLeftForSource);
    rGraph.push_back(gamesLeftForSource);

    for(int i=0;i<gamesLeftForSource.size();i++)
    {
        cout<<"gamesLeftForSource[i]= "<<gamesLeftForSource[i]<<endl;
    }
////////////////////////////////////////////////////////////////////////
    //Match Nodes
    for(int i=0;i<noOfGamesNodes;i++)
    {
        vector<int> weightOfMatchNodes;
        weightOfMatchNodes.push_back(0);
        for(int j=0;j<noOfGamesNodes;j++)
        {
            weightOfMatchNodes.push_back(0);
        }

        for(int j=0;j<n-1;j++)
        {
            if(j==firstTeam[i] || j==secondTeam[i])
                weightOfMatchNodes.push_back(1000);
            else 
                weightOfMatchNodes.push_back(0);
        }
        weightOfMatchNodes.push_back(0);
        graph.push_back(weightOfMatchNodes);
        rGraph.push_back(weightOfMatchNodes);
    }

///////////////////////////////////////////////////////////////////////////
    //team nodes
    for(int i=0;i<n-1;i++)
    {
        vector<int> weightOfTeamNodes;
        for(int j=0;j<=noOfGamesNodes+n-1;j++)
        {
            weightOfTeamNodes.push_back(0);
        }

        if(w[checkTeam]+lefts[checkTeam]-w[increaseInt(i,checkTeam)]>=0)
            weightOfTeamNodes.push_back(w[checkTeam]+lefts[checkTeam]-w[increaseInt(i,checkTeam)]);

        else 
        {
            cout<<"found"<<endl;
            cout<<teams[checkTeam]<<" is eliminated."<<endl;
            cout<<"They can win at most "<<w[checkTeam]<<" + "<<lefts[checkTeam]<<" = "<<w[checkTeam]+lefts[checkTeam]<<" games ."<<endl;
            cout<<teams[increaseInt(i,checkTeam)]<<" has won a total of "<<w[increaseInt(i,checkTeam)]<<" games ."<<endl;
            cout<<"They play each other 0 times."<<endl;
            cout<<"So on average, each of the teams in this group wins "<<w[increaseInt(i,checkTeam)]<<"/1 = "<<w[increaseInt(i,checkTeam)]<<" games ."<<endl;
            return false;
        }
        graph.push_back(weightOfTeamNodes);

        rGraph.push_back(weightOfTeamNodes);
    }
//////////////////////////////////////////////////////////////////////////////
    //sink node
    vector<int> sinkWeight;
    for(int i=0;i<=noOfGamesNodes+n;i++)
    {
        sinkWeight.push_back(0);
    }
    graph.push_back(sinkWeight);
    rGraph.push_back(sinkWeight);
///////////////////////////////////////////////////////////////////////////////

    cout<<"GRAPH WAS "<<endl;
    for(int i=0;i<graph.size();i++)
    {
        for(int j=0;j<graph[i].size();j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }

    return true;
}

int main()
 {
    ifstream infile;        //taking input of all parent-child nodes    
    string filename = "/home/ash/Desktop/MaxFlow/testCases/baseball/teams54.txt";
    infile.open(filename);                          //use of .c_str()???????????????????????????
   
    string line;
    getline(infile, line);
    istringstream check(line); 

    int n; 
    check >> n;
// cout<<"value of n= "<<n<<endl;
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
        // vector<int> againstGamesLeft;
        
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
            // againstGamesLeft.push_back(games);
            g[t][t1]=games;
            t1++;
        }

        // againstGamesLeftForAll.push_back(againstGamesLeft);
        t++;
    }
for(int i=0;i<n;i++)
    {
        int checking=-1;
        // for(int j=0;j<n;j++)
        // {
        //     if(j!=i)
        //     {
        //         if(w[j]>w[i]+lefts[i])
        //         {
        //             checking=0;
        //             cout<<convert(teams[i])<<" is eliminated."<<endl;
        //             cout<<"They can win at most "<<w[i]<<" + "<<lefts[i]<<" = "<<w[i]+lefts[i]<<" games."<<endl;
        //             cout<<convert(teams[j])<<" has won a total of "<<w[j]<<" games."<<endl;
        //             cout<<"They play each other 0 times."<<endl;
        //             cout<<"So on average, each of the teams in this group wins "<<w[j]<<"/1 = "<<w[j]<<" games."<<endl<<endl;
        //             break;
        //         }
        //     }
        // }

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
                                // cout<<"non zero weight of g["<<j<<"]["<<k<<"]"<<endl;
                                nodes.push_back(g[j][k]);
                                capacityFromSource+=g[j][k];
                                if(j<i){
                                // cout<<"j<i"<<endl;
                                firstTeam.push_back(j);
                                }
                                else 
                                    firstTeam.push_back(j-1);
                                
                                if(k<i){
                                secondTeam.push_back(k);
                                // cout<<"k<i"<<endl;
                                }
                                else
                                    secondTeam.push_back(k-1);
                                noOfGamesNodes++;
                                // cout<<"found a match betwween "<<j<<" and "<<k<<endl;
                            }
                        }
                    }
                }
            }
            // for(int j=0;j<firstTeam.size();j++)
            // {
            //     cout<<"firstTeam["<<j<<"]= "<<firstTeam[j]<<endl;

            //     cout<<"secondTeam["<<j<<"]= "<<secondTeam[j]<<endl;
            // }
            for(int j=0;j<n-1;j++)
            {
                nodes.push_back(10000);
                // cout<<"node added"<<endl;
            }
            nodes.push_back(0);
            // for(int j=0;j<nodes.size();j++)
            // {
            //     cout<<"nodes["<<j<<"] = "<<nodes[j]<<endl;
            // }
            // cout<<"size of nodes ="<<nodes.size()<<endl;
            // cout<<"noOfGamesNodes= "<<noOfGamesNodes<<endl;
            vector<int> gamesLeftForSource;
            gamesLeftForSource.push_back(0); 
            // int capacityFromSource=0;
            for(int j=1;j<=noOfGamesNodes;j++)
            {
                gamesLeftForSource.push_back(nodes[j]);
                // capacityFromSource+=nodes[j];
                // cout<<"loop executed "<<j+1<<"times"<<endl;
            }

            for(int j=0;j<n-1;j++)
            {
                gamesLeftForSource.push_back(0);
            }

            gamesLeftForSource.push_back(0);
            // for(int j=0;j<gamesLeftForSource.size();j++)
            // {
            //     cout<<"gamesLeftForSource["<<j<<"]="<<gamesLeftForSource[j]<<endl;
            // }
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

            // for(int j=0;j<nodes.size();j++)

            // {
            //     cout<<"nodes[j]= "<<nodes[j]<<endl;
            // }
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
                            // if(k<i){
                                if(w[i]+ lefts[i]- w[k]>=0){
                                    gamesLeftforTeam.push_back(w[i]+ lefts[i]- w[k]);
                                }
                                else
                                {
                                    // cout<<"FOUND"<<endl;
                                    cout<<convert(teams[i])<<" is eliminated."<<endl;
                                    cout<<"They can win at most "<<w[i]<<" + "<<lefts[i]<<" = "<<w[i]+lefts[i]<<" games."<<endl;
                                    cout<<convert(teams[k])<<" has won a total of "<<w[k]<<" games."<<endl;
                                    cout<<"They play each other 0 times."<<endl;
                                    cout<<"So on average, each of the teams in this group wins "<<w[k]<<"/1 = "<<w[k]<<" games."<<endl;
                                    checkin2=1;
                                    break;
                                }
                            // }
                            
                            // else 
                            // {
                            //     if(w[i]+ lefts[i]- w[k+1]>=0){
                            //         gamesLeftforTeam.push_back(w[i]+ lefts[i]- w[k+1]);
                            //     }
                            // }
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
            // if(checkin2>0)
            //     continue();

                vector<int > ga;
                for(int j=0;j<nodes.size();j++)
                {
                    ga.push_back(0);
                }

                graph.push_back(ga);
                rGraph.push_back(ga);
                // cout<<"graph size= "<<graph.size()<<endl;
                // cout<<"rGraph size= "<<rGraph.size()<<endl;

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
                // if(i==4){
                // cout<<"GRAPH FORMED was :"<<endl;

                // for(int j=0;j<nodes.size();j++)
                // {
                //     cout<<j<<"  ";    
                //     for(int k=0;k<nodes.size();k++)
                //     {
                //         cout<<graph[j][k]<<" ";
                //     }
                //     cout<<endl;
                // }
                // cout<<"Residual GRAPH FORMED was :"<<endl;

                // for(int j=0;j<nodes.size();j++)
                // {
                //     cout<<j<<"  ";    
                //     for(int k=0;k<nodes.size();k++)
                //     {
                //         cout<<rGraph[j][k]<<" ";
                //     }
                //     cout<<endl;
                // }
                // }
                while(bfs(0,nodes.size()-1,nodes.size(), maxFlow))
                {
                    max+=maxFlow;
                    if(i==4){
                    // cout<<"maxFlow= "<<maxFlow<<" and max= "<<max<<endl;
                    }
                    maxFlow=1000;
                }

                int teamsForAverage[n];
                for(int j=0;j<n;j++)
                {
                    teamsForAverage[j]=-1;
                }

                

                for(int j=1;j<=noOfGamesNodes;j++)
                {
                    // for(int k=0;k<nodes.size();k++)
                    // {
                    // if(j>noOfGamesNodes)
                    // {
                    // cout<<"value of team redn checked is "<<rGraph[0][j]<<" for which "<<endl;
                    // cout<<"firstTeam = "<<firstTeam[j-1]<<endl;
                    // cout<<"secondTeam= "<<secondTeam[j-1]<<endl;
                    // cout<<"graph[0][j]= "<<graph[0][j]<<endl;

                    // cout<<"rGraph[0][j]= "<<rGraph[0][j]<<endl;
                    if(rGraph[0][j]!=0)
                    {
                        // cout<<"reduced"<<endl;
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

            

                // cout<<"For team[i] = "<<teams[i]<<endl;
                // cout<<"max= "<<max<<endl;
                // cout<<"capacityFromSource= "<<capacityFromSource<<endl;
                // if(i==4)
                // {
                // cout<<"GRAPH FORMED IS :"<<endl;

                // for(int j=0;j<nodes.size();j++)
                // {
                //     cout<<j<<"  ";    
                //     for(int k=0;k<nodes.size();k++)
                //     {
                //         cout<<rGraph[j][k]<<" ";
                //     }
                //     cout<<endl;
                // }
                // }

//                 if(i==4)
//                 {
//                     for(int j=0;j<nodes.size();j++)
//                     {
//                         if(rGraph[0][j]!=0)
//                         {

//                             cout<<"graph[0][j]= "<<graph[0][j]<<endl;
//                             cout<<"non zero value for "<<j<<" having firstTeam= "<<firstTeam[j-1]<<" and secondTeam= "<<secondTeam[j-1]<<endl;
//                             cout<<"graph["<<firstTeam[j-1]<<"][last]= "<<graph[firstTeam[j-1]+noOfGamesNodes][nodes.size()-1]<<endl;
//                             cout<<"rGraph["<<firstTeam[j-1]<<"][last]= "<<rGraph[firstTeam[j-1]+noOfGamesNodes][nodes.size()-1]<<endl;
//                             cout<<"rGraph["<<secondTeam[j-1]<<"][last]= "<<rGraph[secondTeam[j-1]+noOfGamesNodes][nodes.size()-1]<<endl;
//                             // maxFlow=500;
// // bool t=bfs(0,nodes.size()-1,nodes.size(), maxFlow);
// //                             cout<<t<<endl;
//                         }
//                     }
//                 }
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
                // cout<<"reached end"<<endl;

            }
            // cout<<endl;
        }
    }
    
    return 0;
}
