# Baseaball-Elimination-Max-Flow-Algorithm-
Implementation of the baseball elimination problem using Max Flow algorithm
                      **Baseball Elimination Problem**

Given the standings in a sports league at some point during the season,
determine which teams have been mathematically eliminated from winning
their division.

##The-baseball-elimination-problem:- In the baseball elimination problem,
there is a league consisting of N teams. At some point during the season,
team i has w[i] wins and g[i][j] games left to play against team j. A team is
eliminated if it cannot possibly finish the season in first place or tied for first
place. The goal is to determine exactly which teams are eliminated. The
problem is not as easy as many sports writers would have you believe, in part
because the answer depends not only on the number of games won and left
to play, but also on the schedule of remaining games. To see the
complication, consider the following scenario:

| Team          | Wins | Loss | Left | Atl | Phi | NY  | Mon |
| ------------- | ---- | ---- |----- | --- | --- | --- | --- |
| Atlanta       |  83  |  71  |   8  |  0  |  1  |  6  |  1  |
| Philadelphia  |  80  |  79  |   3  |  1  |  0  |  0  |  2  |
| New_York      |  78  |  78  |   6  |  6  |  0  |  0  |  0  |
| Montreal      |  77  |  82  |   3  |  1  |  2  |  0  |  0  |
 
Montreal is mathematically eliminated since it can finish with at most 80
wins and Atlanta already has 83 wins. This is the simplest reason for
elimination. However, there can be more complicated reasons. For example,
Philadelphia is also mathematically eliminated. It can finish the season with
as many as 83 wins, which appears to be enough to tie Atlanta. But this
would require Atlanta to lose all of its remaining games, including the 6
against New York, in which case New York would finish with 84 wins. We
note that New York is not yet mathematically eliminated despite the fact that
it has fewer wins than Philadelphia.

It is sometimes not so easy for a sports writer to explain why a particular
team is eliminated and newspapers occasionally get it wrong. Consider the
following scenario from the American League East at the end of play on
August 30, 1996. Note that a team's total number of remaining games does
not necessarily equal the number of remaining games against divisional
rivals since teams may play opponents outside of their own division.

|Team       |  Wins| Loss| Left | NY  |Bal |Bor| Tor| Det|
|----------|--------|---|-----|---|----|---|---|---|
|New_York   |   75  | 59  | 21 |   0  | 3 |  8  | 7 |  3|
|Baltimore |    71   |63  | 16  |  3  | 0  | 2  | 7  | 4|
|Boston   |     69   |66  | 10   | 8  | 2  | 0  | 0  | 0|
|Toronto |      63   |72  | 14   | 7  | 7  | 0  | 0  | 0|
|Detroit|       49   |86 |   7   | 3 |  4   |0 |  0  | 0|

At first (or second) glance it might appear that Detroit still has a remote
chance of catching New York and winning the division since Detroit can
finish with as many as 76 wins. Try to convince yourself that this is not the
case and that Detroit is already mathematically eliminated. Here's one
explanation. We provide a simpler explanation below.

##A maximum flow formulation: We now solve the baseball elimination
problem by reducing it to the maximum flow problem. To check whether or
not one particular team x is eliminated, we create a network and solve a
maximum flow problem in it. In the network, feasible integral flows
correspond to outcomes of the remaining schedule. There are vertices
corresponding to teams (other than team x ) and to remaining divisional
games not involving team x . Intuitively, each unit of flow in the network
corresponds to a remaining game. As it flows through the network, it passes
from a game node, say between teams i and j, then through one of the team
nodes i or j, classifying this game as being won by that team.

More precisely, our graph includes the following edges and capacities. We
connect an artificial source s to each game node i-j and sets its capacity to
g[i][j] . If a flow uses all g[i][j] units of capacity on this edge, then we think
of all these games as being played, and the wins are distributed between
team nodes i and j. We connect each game node i-j with the two opposing
teams to ensure that one of the two teams earns a win. We do not need to
restrict the amount of flow on such edges. Finally, we connect each team
node to an artificial sink t. Team x can win as many as w[x] + r[x] games, so to
prevent team i from winning more than that many games in total, we include
an edge from team node i to the sink with capacity w[x] + r[x] - w[i] .

If the max flow in the network below saturates all arcs leaving s then this
corresponds to assigning winners to all of the remaining games in such a way
that no team wins more games than x . If the max flow does not saturate all
arcs leaving s then there is no scenario in which team x wins the division.

![Screenshot from 2020-05-13 06-55-47](https://user-images.githubusercontent.com/53982432/81761484-ac761f00-94e7-11ea-84ac-8c5d92ca9f94.png)

##**What the min cut tells us** By solving a max flow problem, we can
determine which teams are mathematically eliminated. It would be nice if we
could also explain the reason for a team's elimination to a friend without
resorting to network flow theory. Here's a more convincing and succinct
argument for Detroit's elimination in the American League East example
above. With the best possible luck, Detroit could finish season with as many
as 49 + 27 = 76 wins. Consider the subset of teams R = { NY, Bal, Bos, Tor}.
Collectively, they have 278 wins among them. There are 3 + 8 + 7 + 2 + 7 =
27 remaining games among them, so collectively, these four teams must win
at least 27 more games. On average, the teams in R win at least 305 / 4 =
76.25 games. Regardless of the outcome, one team in R will win at least 77
games, thereby eliminating Detroit.

In fact, when a team is mathematically eliminated there always exists such a
convincing certificate of elimination, although the subset of teams R may not
be the rest of the division as it is above. However, you can always find such a
subset R by choosing the team vertices on the source side of a min s-t cut in
the baseball elimination network. Note that although we use max flows and
min cuts to find the subset R, once we have it, the argument for a team's
elimination does not involve any sophisticated mathematics.

##**Problem**: Write a program that reads in a sports league and prints
out a list of all of the teams that are mathematically eliminated. For each
team, give a convincing reason why of the form described above.

##**INPUT:**\
4\
Atlanta       83 71  8  0 1 6 1\
Philadelphia  80 79  3  1 0 0 2\
New_York      78 78  6  6 0 0 0\
Montreal      77 82  3  1 2 0 0

##**OUTPUT:** 
Philadelphia is eliminated.\
They can win at most 80 + 3 = 83 games.\
Atlanta and New York have won a total of 161 games.\
They play each other 6 times.\
So on average, each of the teams wins 167/2 = 83.5 games.

Montreal is eliminated.\
They can win at most 77 + 3 = 80 games.\
Atlanta has won a total of 83 games.\
They play each other 0 times.\
So on average, each of the teams in this group wins 83/1 = 83 games.

##**Simplifying assumptions** Assume that no games end in a tie (as is the
case in Major League Baseball). Also assume that there are no rainouts, i.e.,
every scheduled game is played. Ignore wildcard possibilities, i.e., when a
team can make the playoffs without finishing first in its division. Finally,
assume that there are no whitespace characters in the name of a team.

#**EXPLAINATION OF THE PROGRAM**

##**HOW TO COMPILE AND EXECUTE THE CODE?**

The program is written in c++. The zip folder contains two files only- BaseballEliminator.cpp and ReadMe.txt. The BaseballEliminator.cpp takes input from a file "input.txt" which should be changed accordingly. So, in order to execute the code on Linux(Ubuntu) type on the terminal. 

g++ BaseballEliminator.cpp
./a.out

Or the code can directly be compiled over any compiler. 


##**PURPOSE OF EACH SOURCE FILES:**
There is only one source file in the zip folder which can be summarised as below:

**vector<int> g:** It is the adjacency matrix which contains the information about matches left and who plays those matches exactly.

**vector<int> graph,rGraph:** contains the graph when we analyse the situation of a team. It should be noted that the team for which we are analysing isn't present in graph, rGraph. 'graph' represents the graph with the functionalities as described on the webpage of the assignment page. There is one source node which is connected to the nodes indicating left matches in the tournament. These match nodes are then connected to the team nodes whose match is indicating that particular match node. 'rGraph' is the residual graph of 'graph' which is used in the max flow algorithm.

**vector<int> w:** contains the number of matches won by each team.

**vector<int> losses:** contains the matches lost by each team.

**vector<int> lefts:** contains the matches left for each team to play.

**vector<string> teams:** contains the name of each team

**class paired:** This class has two fields isVisited, parent. The objects of this class is used in the bfs function.

**bool bfs:** This function is for doing breadth-first search in the residual graph , returns true if there is any bfs path from the source node to sink node else returns false. It also creates a negative edge in the residual graph after finding one bfs path (which is required in the max flow algorithm). A vector contains the nodes visited in the residual graph. There is a priority queue for performing breadth-first search. Then the topmost node in the queue is popped out. If there is an edge between the popped node and any other node and if the other node is not visited already then push that node in the priority queue. Finally, if the sink vertex is visited (i.e. there is a bfs path from source to the sink) then count the min weighted edge in the path and then subtract that weight from each edge involved in the path.

**string convert(string s):** Helper function to convert New_York to New York

**int convertInt():** Helper function which decreases the value of int by 1 if it is greater than some specific int

**int increaseInt():**  Helper function which increases value of int by 1 if its greater than some specific int.


**int main():**
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

##**OVERALL TOP VIEW OF THE PROGRAM:**
The program takes input from a file "input.txt" having the league table of a tournament and output which teams are eliminated from the league tournament which many newspapers often get wrong. Although, the program uses max flow algorithm still the output contains a convincing certificate of elimination which can be explained to anyone easily.

Thanks
