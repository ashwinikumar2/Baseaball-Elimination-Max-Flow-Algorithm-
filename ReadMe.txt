Licensed to Ashwini Kumar
Github: ashwinikumar2

HOW TO COMPILE AND EXECUTE THE CODE?

The program is written in c++. The zip folder contains two files only- BaseballEliminator.cpp and ReadMe.txt. The BaseballEliminator.cpp takes input from a file "input.txt" which should be changed accordingly. So, in order to execute the code on Linux(Ubuntu) type on the terminal. 

g++ BaseballEliminator.cpp
./a.out

Or the code can directly be compiled over any compiler. 


PURPOSE OF EACH SOURCE FILES:
There is only one source file in the zip folder which can be summarised as below:

vector<int> g: It is the adjacency matrix which contains the information about matches left and who plays those matches exactly.

vector<int> graph,rGraph: contains the graph when we analyse the situation of a team. It should be noted that the team for which we are analysing isn't present in graph, rGraph. 'graph' represents the graph with the functionalities as described on the webpage of the assignment page. There is one source node which is connected to the nodes indicating left matches in the tournament. These match nodes are then connected to the team nodes whose match is indicating that particular match node. 'rGraph' is the residual graph of 'graph' which is used in the max flow algorithm.

vector<int> w: contains the number of matches won by each team.

vector<int> losses: contains the matches lost by each team.

vector<int> lefts: contains the matches left for each team to play.

vector<string> teams: contains the name of each team

class paired: This class has two fields isVisited, parent. The objects of this class is used in the bfs function.

bool bfs: This function is for doing breadth-first search in the residual graph , returns true if there is any bfs path from the source node to sink node else returns false. It also creates a negative edge in the residual graph after finding one bfs path (which is required in the max flow algorithm). A vector contains the nodes visited in the residual graph. There is a priority queue for performing breadth-first search. Then the topmost node in the queue is popped out. If there is an edge between the popped node and any other node and if the other node is not visited already then push that node in the priority queue. Finally, if the sink vertex is visited (i.e. there is a bfs path from source to the sink) then count the min weighted edge in the path and then subtract that weight from each edge involved in the path.

string convert(string s): Helper function to convert New_York to New York

int convertInt(): Helper function which decreases the value of int by 1 if it is greater than some specific int

int increaseInt():  Helper function which increases value of int by 1 if its greater than some specific int.


int main():
The file (input.txt) is read using stringstream. As a result, 'g','teams', 'w', 'losses' and 'lefts' are constructed. 
Now, for every team (let that team be 'x') we analyse whether it is eliminated from the tournament or not. This is done using the MAX FLOW ALGORITHM.

We construct the adjacency matrix 'graph' and 'rGraph' which has the following properties:
(1) An artificial source 
(2) Nodes corresponding to matches left in the tournament not involving team 'x'. These nodes are referred to as 'Match Nodes'.
(3) Nodes corresponding to every team present in the tournament other than 'x'.

Edge weights of 'graph':
(1) The 'source' is connected to only match nodes with the weight of the edges equal to the number of matches left for the matches involving the same teams.
(2) The 'match nodes' are connected to the two 'team nodes' between whom the match was being played.
(3) The 'team nodes' are connected to the artificial sink node with weight equal to w[x]+ lefts[x]-w[i] where i= node of team 'i'.

Now, vector<int> nodes have all the nodes in order for the 'graph'. 
vector<int> firstTeam have the information about the first team of a 'match node'.
vector<int> secondTeam have the information about the second team of a 'match node'.
int noOfGamesNodes indicates the number of 'match nodes' in the graph.
int capacityFromSource indicates the total weight of the edges originating from the source node.

Now, for 'x' the vector 'nodes' is constructed as below:
(1) push_back(0) in 'nodes' vector for source node.
(2) for all non zero edges in 'g' and are in the lower triangular half of the matrix 'g', push_back in the 'nodes' vector.Simultaneously, push_back the first and second team numbers in firstTeam and secondTeam vectors. These are the 'match' nodes.
(3) for (n-1) times push_back(10000) in the 'nodes' vector. These are the 'team' nodes.
(4) for each 'team' nodes if w[x]+lefts[x]-w[i]>=0 then push_back(w[x]+lefts[x]-w[i]) into the 'nodes' vector else the team 'x' is eliminated trivially by team i.

Now, for 'x' the adjacency matrix 'graph' and 'rGraph' are constructed as below:
(1) construct vector gamesLeftForSource for assigning weights for the edges from source to other nodes of the graph. The edges are only between the source node and the match nodes with edge weights equal to the element of 'nodes' from index 1 to noOfGamesNodes. Then push_back gamesLeftForSource in 'graph' and 'rGraph'.
(2) for each 'match' node construct gaemesLeft for assigning weights for the edges from 'match nodes' to other nodes of the graph. There is an edge between 'match nodes' and 'team' nodes only with weight equal to the elements of nodes from the index (noOfGamesNodes+1) to ((size of nodes)-2). Then push_back gaemesLeft in 'graph' and 'rGraph'.
(3) for each 'team' node construct gamesLeftforTeam for assigning weights for the edges from 'team nodes' to other nodes of the graph. There is an edge between 'team' nodes and artificial sink only with weight equal assigned as:
if w[x]+lefts[x]-w[i]>=0 then push_back(w[x]+lefts[x]-w[i]) into the 'nodes' vector else the team 'x' is eliminated trivially by team i. 
Then push_back gamesLeftforTeam in 'graph' and 'rGraph'.
If maxFlow does not saturate all the arcs leaving source, then that team is eliminated from the tournament.
Else it is still in the tournament.
(4) further if checkin2<0 then the team is surely not trivially eliminated. Then construct vector 'ga' and push_back(0) for nodes.size() times. Then push_back 'ga' in 'graph' and 'rGraph'.

Now, using max flow algorithm call bfs function until there is an augmenting path in the residual graph and create negative edges in the residual graph. Add the min weight of the edge in the bfs path to the total max flow (i.e. int max ).

Now, if total max flow is equal to capacityFromSource then the team is still in the tournament else do the following:

After this, to calculate 'team' nodes in the 'min-cut' check which edges from the source still have non zero weight, then check ahead of the two team nodes check that which edges from the 'team' nodes to the artificial sink have zero weight. This corresponds to the teams ahead of which we cannot find a bfs path to the artificial sink. These nodes are thus in the S cut of S-T cut of a graph. 

Since it isn't easy to explain the concept of min-cut to everyone so we can provide a certificate of elimination by calculating the average wins of the teams in the min-cut. This average is found to be greater than w[x]+lefts[x].

TIME COMPLEXITY OF THE PROGRAM: O(V*max_flow*E) where V is the number of teams in the tournament & E is the number of edges
SPACE COMPLEXITY OF THE PROGRAM: O(V^4) where V is the number of teams in the tournament used up in 'graph' and 'rGraph'

OVERALL TOP VIEW OF THE PROGRAM:
The program takes input from a file "input.txt" having the league table of a tournament and output which teams are eliminated from the league tournament which many newspapers often get wrong. Although, the program uses max flow algorithm still the output contains a convincing certificate of elimination which can be explained to anyone easily.

Thanks
