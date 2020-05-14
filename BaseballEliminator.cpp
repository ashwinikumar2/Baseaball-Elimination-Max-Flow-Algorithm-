//BASEBALL ELIMINATION PROBLEM USING MAX FLOW ALGORITHM
#include <bits/stdc++.h>
#define l long long

using namespace std;

vector<vector<int>> rGraph;			//graph,rGraph: contains the graph when we analyse the situation of a team.
vector<vector< int>> graph;			//It should be noted that the team for which we are analysing isn't present in graph, rGraph. 
vector<vector<int>> g;				//contains the information about matches left and who plays those matches exactly.
vector<int> w;						//contains the number of matches won by each team.
vector<int > losses;				//contains the matches lost by each team.
vector<int> lefts;					//contains the matches left for each team to play.
vector<string> teams;				//contains the name of each team

//Helper Class of whose objects contains information about 
//their parent and whether this node is visited already or not
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

//function for doing breadth first search in the residual graph 
//returns true if there is any bfs path from source node to sink node else returns false
bool bfs(const int s,const int t,int n,int& maxFlow)
{
    vector<paired> visited;					//contains the nodes visited in the residual graph
    for(int i=0;i<n;i++)
    {
        paired p(false, -1);
        visited.push_back(p);
    }
    queue< int> q;							//priority queue for performing breadth first search 
    q.push(s);				
    (visited[s]).isVisited=true;
    while(q.size()>0)
    {
        int no=q.front();					//the topmost node in the queue is popped out
        q.pop();
        for( int i=0;i<n;i++)
        {
            if(rGraph[no][i]!=0)			//if there is an edge between the popped node and any other node 
            {
                if(!visited[i].isVisited)	//if the other node is not visited already
                {	
                    q.push(i);
                    visited[i].isVisited=true;
                    visited[i].parent=no;
                }
            }
        }
    }
    //To check whether last node is visited or not
    if(visited[t].isVisited)
    {
         int child=t;
        while(visited[child].parent!=-1)		//loop for counting the min weighted edge in the whole path
        {
            int p=visited[child].parent;
            if(rGraph[p][child]<maxFlow)
                maxFlow=rGraph[p][child];
            
            child=p;
            if(child==0)
                break;
        }
         int child1=t;
        while(visited[child1].parent!=-1 )			//loop for deducting the weight of min edge and creating the negative edge in the residual graph
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

//Helper function to convert New_York to New York
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
//Helper function which just decreases value of an int by 1 if its greater than some specific int
int convertInt(int x, int original)                 //return int after considering the removed team
{
    if(x<original)
        return x;
    else 
        return (x-1);

}
//helper function which just increases value of an int by 1 if its greater than some specific int
int increaseInt(int x, int original)
{
    if(x<original)
        return x;
    else
        return (x+1);
}

int main()
 {
    //Reading from file and storing it in vector<string> teams
    ifstream infile;        //taking input of all parent-child nodes    
    string filename = "input.txt";
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
        
        w.push_back(win);						//w is constructed
        losses.push_back(loss);					//losses is constructed
        lefts.push_back(left);					//lefts is constructed
        int games;
        
        while(check1>>games)
        {
            g[t][t1]=games;
            t1++;
        }
        t++;
    }

    //Now for every team we will analyse whether it is eliminated from the tournament or not
    for(int i=0;i<n;i++)
    {
        int checking=-1;        			//no significance only for debugging purposes
        if(checking<0)
        {
            graph.clear();
            rGraph.clear();
            vector<int> nodes;				//vector having all the nodes in order for the 'graph'
            nodes.push_back(0);						//source node added to the 'nodes' vector
            vector<int> firstTeam;			//vector having the information about the first team of a 'match node'
            vector<int> secondTeam;			//vector having the information about the second team of a 'match node'
            int noOfGamesNodes=0;			//indicates number of 'match nodes' in the graph
            int checkin2=-1;                //indicates that team is eliminated trivially (as described on web page) if its value gets positive after the next for loop else team is not trivially eliminated
            int capacityFromSource=0;		//indicates the total weight of the edges originating from the source node
            for(int j=0;j<n;j++)            //to construct the graph nodes
            {                               //this for loop will construct the required match nodes and also the artificial source node
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
            for(int j=0;j<n-1;j++)                  //nodes of n-1 team nodes
            {
                nodes.push_back(10000);
            }
            
            nodes.push_back(0);                     //artificial sink node
            vector<int> gamesLeftForSource;         //vector for assigning weights for the edges from source to other nodes of the graph
            gamesLeftForSource.push_back(0);        //no self loop on the source node
            
            for(int j=1;j<=noOfGamesNodes;j++)      //putting weight of the edges from source node to match nodes
            {
                gamesLeftForSource.push_back(nodes[j]);
            }

            for(int j=0;j<n-1;j++)					//there is no edge from source node to the team nodes
            {
                gamesLeftForSource.push_back(0);
            }

            gamesLeftForSource.push_back(0);		//there is no edge between source and the sink node
            graph.push_back(gamesLeftForSource);
            rGraph.push_back(gamesLeftForSource);


            //set the weight to be infinity for edges from match nodes to the team nodes
            for(int j=0;j<noOfGamesNodes;j++)
            {
                vector<int> gaemesLeft;				//vector for assigning weights for the edges from 'match nodes' to other nodes of the graph
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
            //set the weight of edges from team nodes to the artificial sink node
            for(int k=0;k<n;k++)
            {
                if(k!=i)
                {
                    vector<int > gamesLeftforTeam;			//vector for assigning weights for the edges from 'team nodes' to other nodes of the graph

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
            if(checkin2<0)      //if checkin2 is less than zero then the team is surely not trivially eliminated               
            {					//the team can either eliminate non-trivially or do not eliminate from the tournament
                vector<int > ga;                    //assigning weights for edges from artificial sink to other nodes of the graph (which is zero for all edges)
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

                int max=0;                          //indicates the total max flow of network
                int maxFlow=10000;                   //indicates the max flow of a network in each bfs path
                while(bfs(0,nodes.size()-1,nodes.size(), maxFlow))		//if bfs is true then add the max flow of the bfs path to the total max flo
                {
                    max+=maxFlow;
                    
                    maxFlow=10000;
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
                vector<int> forAverage;                 //helper vector for taking teams in min cut(i.e. there average provides the certificate of elimination)
                for(int j=0;j<n;j++)
                {
                    if(j!=i)
                    if(teamsForAverage[j]>0)
                        forAverage.push_back(j);
                }


                if(max!=capacityFromSource)             //if maxFlow does not saturate all the arcs leaving source then that team is eliminated from the tournament
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
                    //printing the required output
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
