//Contributions Handled : Graph Theory : Maahir Sharma
//Functionalities as of now:
//1) Setting up Router Networks with Edges
//2) Calculation of Routing Tables via Bellmann Ford Algorithm in O(N^2);
//3) Finding the Maximal Strongly Connected Sub Network via KosaRaju Algorithm.
//4) Handling Link Failiure of between any two network routers with a direct edge.
//5) Added Link State Packet and Flooding Feature so that when flood occurs each router has access to LSP of the flood initiator.
/*6) Added Optimal Cell Tower Placement Map is likened to a color,(channel–colors are limited to four), and found where to economically position broadcast towers 
     for maximum coverage via Four Color Map Problem || Vizing's theorem (Referenced) */
/*___________________________________________________________________________________________________________________________________________________*/
/* Ravi Gusain : LinkedList Functionalities added */
/* Kushagra Sharma : Trees and Tries Functionalities to be added soon */
/* Rahul Das : Strings and Algorithms Functionalities to be added soon */
#include <bits/stdc++.h>
using namespace std;

struct Edges
{
  int a; //Source
  int b; //Destination
  int w; //Cost(Favourability)

  Edges(int s, int d, int c)
  {
    a = s;
    b = d;
    w = c;
  }
};
struct LSP
{
  int nodeid = -1;
  vector<int> neighbours;
  int sequence = 1;
  LSP(int nodeid, vector<int> chk, int tt)
  {
    this->nodeid = nodeid;
    neighbours = chk;
    sequence = tt;
  }
  LSP() {}
};
struct RFGraph
{
  LSP packet;
  RFGraph(LSP obj)
  {
    packet = obj;
  }
  RFGraph() {}
};
vector<Edges> ngraph;
vector<bool> vis(10000, false);
stack<int> st;
int tc = 0;
string ans = "";
void dfs(int src, vector<int> graph[], bool isecond = false)
{
  if (isecond)
  {
    tc++;
  }
  ans += to_string(src) + " ";
  vis[src] = true;
  for (int i = 0; i < graph[src].size(); i++)
  {
    if (!vis[graph[src][i]])
      dfs(graph[src][i], graph, isecond);
  }
  if (!isecond)
  {
    st.push(src);
  }
}
void removeEdge(int u, int v)
{
  for (int j = 0; j < ngraph.size(); j++)
  {
    if (ngraph[j].a == u && ngraph[j].b == v)
    {
      ngraph.erase(ngraph.begin() + j);
    }
    if (ngraph[j].a == v && ngraph[j].b == v)
    {
      ngraph.erase(ngraph.begin() + j);
    }
  }
}

void belford(int src, int n, vector<int> &dis)
{
  dis[src] = 0;
  for (int i = 0; i < n; i++)
  {
    for (auto e : ngraph)
    {
      int src, dest, cost;
      src = e.a;
      dest = e.b;
      cost = e.w;
      dis[dest] = min(dis[dest], dis[src] + cost);
    }
  }
}
vector<bool> cvis(10000, false);
void lspdfs(int src, vector<int> lg[])
{
  cvis[src] = true;
  for (int i = 0; i < lg[src].size(); i++)
  {
    if (!cvis[lg[src][i]])
    {
      lspdfs(lg[src][i], lg);
    }
  }
}
void EdgeColor(int ed[][3], int e)
{
  int i, c, j;
  for (i = 0; i < e; i++)
  {
    c = 1; //Assign color to current edge 1 initially.
  // If the same color is occupied by any of the adjacent edges,
  // then discard this color and go to flag again and try next color.
  flag:
    ed[i][2] = c;
    for (j = 0; j < e; j++)
    {
      if (j == i)
        continue;
      if (ed[j][0] == ed[i][0] || ed[j][0] == ed[i][1] || ed[j][1] == ed[i][0] || ed[j][1] == ed[i][1])
      {
        if (ed[j][2] == ed[i][2])
        {
          c++;
          goto flag;
        }
      }
    }
  }
}

/*Using doubly linked lists to represent computer processes via linear as well as cyclic links*/

struct Node
{
  struct Node *next;
  struct Node *prev;
  int value;
};

Node *head = NULL;
Node *tail = NULL;

void add_lin_prog(Node **ref, int data)
{
  Node *new_node = new Node;

  new_node->next = (*ref);
  new_node->prev = NULL;
  new_node->value = data;

  if ((*ref) != NULL)
    (*ref)->prev = new_node;
  else
  {
    head = new_node;
    tail = new_node;
  }

  (*ref) = new_node;
}

void add_cir_prog(Node **ref, int data)
{
  if ((*ref) == NULL)
  {
    add_lin_prog(ref, data);
    return;
  }

  if ((*ref)->next == NULL)
  {
    Node *new_node = new Node;
    new_node->next = (*ref);
    new_node->prev = (*ref);
    new_node->value = data;
    (*ref)->next = new_node;
    return;
  }

  Node *temp = (*ref)->next;

  Node *new_node = new Node;

  new_node->value = data;

  new_node->next = temp;

  temp->prev = new_node;

  new_node->prev = *ref;

  (*ref)->next = new_node;
}

int detectLoop(Node *ref)
{
  Node *tort = ref, *heir = ref;

  int cir_pr = 1;
  while (tort && heir && heir->next)
  {
    tort = tort->next;
    heir = heir->next->next;
    if (tort == heir)
    {
      tort = head;
      while (tort != heir)
      {
        tort = tort->next;
        heir = heir->next;
      }
      cout << "\nStarting process of cycle: " << tort->value;
      tort = tort->next;
      while (tort != heir)
      {
        tort = tort->next;
        cir_pr++;
      }
      cout << "\nNumber of processes in cycle: " << cir_pr;
      return tort->value;
    }
  }
  cout << "\nCyclic linked processes NOT found";
  return -1;
}

void display()
{
  Node *temp = head;

  cout << temp->value << " <-> ";
  temp = temp->next;

  while (temp != tail)
  {
    cout << temp->value << " <-> ";
    temp = temp->next;
  }

  cout << temp->value << " <-> ";
  temp = temp->next;
  while (temp != tail)
  {
    cout << temp->value << " <-> ";
    temp = temp->next;
  }
  cout << temp->value << endl;
}

/*____________________________________________________________________________________________________________________________________________*/
// Rahul Das
// C++ program to encode and decode a string using Huffman coding.
map<char, string> codes; // assigning characters with there huffman value
map<char, int> freq;     // stores frequency of characters

// A Huffman tree node
struct MinHeapNode
{
  char data;                 // One of the input characters
  int freq;                  // Frequency of the character
  MinHeapNode *left, *right; // Left and right child

  MinHeapNode(char data, int freq)
  {
    left = right = NULL;
    this->data = data;
    this->freq = freq;
  }
};

// utility function for the priority queue.
struct compare
{
  bool operator()(MinHeapNode *l, MinHeapNode *r)
  {
    return (l->freq > r->freq);
  }
};

// utility function to print characters along with there Huffman value.
void printCodes(struct MinHeapNode *root, string str)
{
  if (!root)
    return;
  if (root->data != '$')
    cout << root->data << ": " << str << "\n";
  printCodes(root->left, str + "0");
  printCodes(root->right, str + "1");
}

// utility function to store characters along with there huffman value in a hash table, here we have C++ STL map.
void storeCodes(struct MinHeapNode *root, string str)
{
  if (root == NULL)
    return;
  if (root->data != '$')
    codes[root->data] = str;
  storeCodes(root->left, str + "0");
  storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect to their heap root node value.
priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

// function to build the Huffman tree and store it in minHeap.
void HuffmanCodes(int size)
{
  struct MinHeapNode *left, *right, *top;
  for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
    minHeap.push(new MinHeapNode(v->first, v->second));
  while (minHeap.size() != 1)
  {
    left = minHeap.top();
    minHeap.pop();
    right = minHeap.top();
    minHeap.pop();
    top = new MinHeapNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    minHeap.push(top);
  }
  storeCodes(minHeap.top(), "");
}

// utility function to store characters with there frequencies in a map.
void calcFreq(string str, int n)
{
  for (int i = 0; i < str.size(); i++)
    freq[str[i]]++;

  // Traverse through map and print frequencies
  cout << "Input characters with there frequencies:\n";
  for (auto x : freq)
    cout << x.first << " " << x.second << endl;

  cout << "____________________________________________________\n";
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode *root, string s)
{
  string ans = "";
  struct MinHeapNode *curr = root;
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] == '0')
      curr = curr->left;
    else
      curr = curr->right;

    // reached leaf node
    if (curr->left == NULL and curr->right == NULL)
    {
      ans += curr->data;
      curr = root;
    }
  }
  return ans + '\0';
}

int main()
{
  int routers, connections;
  cout << "Enter number of Routers" << endl;
  cin >> routers;
  cout << "Enter number of Connections" << endl;
  cin >> connections;
  vector<int> graph[routers + 1];
  vector<int> lg[routers + 1];
  vector<RFGraph> ls(routers + 1);
  //For the first task of making Routing Tables for each node, we assume that the given graph is undirected.
  //For the second task of finding the Maximal Strongly Connected Sub-Network we have to assume that the graph is directed.
  for (int i = 0; i < connections; i++)
  {
    int origin;
    int destination;
    int cost;
    cin >> origin >> destination >> cost;
    ngraph.push_back({origin, destination, cost});
    graph[origin].push_back(destination);
    lg[origin].push_back(destination);
    lg[destination].push_back(origin);
    ngraph.push_back({destination, origin, cost});
  }
  //Cost or Link is assigned on the basis of desirability of Network Route for sending traffic.
  //We will now use Bellman Ford Algorithm in order to calculate the routing table for each node.
  int n = routers;
  vector<vector<int>> global(n + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; i++)
  {
    vector<int> dis(n + 1, 10000);
    belford(i, connections * 2, dis);
    cout << " Routing Table for " << i << " router : " << endl;
    for (int j = 1; j <= n; j++)
    {
      cout << i << " -> " << j << " With HOP Distance " << dis[j] << " " << endl;
      global[i][j] = dis[j];
    }
    cout << "____________________________________________________" << endl;
  }
  //Compulsorily we had to run the loops O(N^2) times in order to accomodate shortest possible distance from one node
  //to every other node. A LAN System behaves in a similar manner, what we printed above is known as Routing Table.
  // There are some obvious shortcomings, firstly this method doesn't account for Network Link Failiures, hence, finding optimal route
  //for traffic isn't always guranteed.

  //Printing Global View of Each Node:
  cout << " Final Distances Stored at Each Node (Global View) " << endl;
  for (int i = 1; i <= n; i++)
  {
    cout << i << " -> ";
    for (int j = 1; j <= n; j++)
    {
      cout << global[i][j] << " ";
    }
    cout << endl;
  }
  cout << "____________________________________________________" << endl;

  //Now we go on and find the maximal strongly connected sub-network.
  //A strongly connected component of a graph is defined as a component in which every node can visit every other node.
  //To do so we are going to implement KosaRaju Algorithm.
  for (int i = 0; i < n; i++)
  {
    if (!vis[i])
    {
      dfs(i, graph); //First make a normal dfs call to maintain the order of visiting elements in a stack.
    }
  }
  vector<int> revg[n + 1]; //Now reverse the given graph and maintain it in another list.
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < graph[i].size(); j++)
    {
      revg[graph[i][j]].push_back(i);
    }
  }
  int max_ele = -1e9;
  string fans = "";
  ans = "";
  for (int i = 0; i < n; i++)
    vis[i] = false;
  while (st.size() != 0)
  { //Call DFS on each member of the elements still maintaing the given order of stack.
    int rvtx = st.top();
    st.pop();
    if (!vis[rvtx])
    {
      ::tc = 0;
      dfs(rvtx, revg, true);
      if (tc > max_ele)
      {
        max_ele = tc;
        fans = ans;
      }
      ans = "";
    }
  }
  cout << "Maximal Strongly Connected Sub-Network has " << max_ele << " members and the members are : " << fans << endl;
  //Typically a network failiures occurs when the link between two nodes is broken. This coerces the whole system to reset the rerouting tables.
  //Link Failiure is usually prevented by setting a node that continuously sends validation packets to it's neighbours and awaits acknowledgement.
  //If acknowledgement isn't received then, in terms of graph theory, the edge between the two "routers"/"nodes" is removed and the shortest distance is
  //recalculated via Bellmann Ford Algorithm.
  cout << "Enter link between two nodes to be killed" << endl;
  int node1, node2;
  cin >> node1 >> node2;
  removeEdge(node1, node2);
  for (int i = 1; i <= n; i++)
  {
    vector<int> dis(n + 1, 10000);
    belford(i, connections * 2, dis);
    for (int j = 1; j <= n; j++)
    {
      global[i][j] = dis[j];
    }
  }
  cout << "Global view after killing the link : " << endl;
  for (int i = 1; i <= n; i++)
  {
    cout << i << " -> ";
    for (int j = 1; j <= n; j++)
    {
      cout << global[i][j] << " ";
    }
    cout << endl;
  }
  cout << "____________________________________________________" << endl;
  //Creating LSP of a given node
  //More precisely, each node creates an update packet, also called a link-state packet (LSP), which contains the following information:

  /* The ID of the node that created the LSP
      A list of directly connected neighbors of that node, with the cost of the link to each one
      A sequence number
      A time to live for this packet */
  /* Consider a node X that receives a copy of an LSP that originated at some other node Y. 
  If not, it stores the LSP. If it already has a copy, it compares the sequence numbers; 
  if the new LSP has a larger sequence number, it is assumed to be the more recent, and that LSP is stored, replacing the old one.
  A smaller (or equal) sequence number would imply an LSP older (or not newer) than the one stored, so it would be discarded and no further action would be needed. 
  If the received LSP was the newer one, X then sends a copy of that LSP to all of its neighbors except the neighbor from which the LSP was just received.
  The fact that the LSP is not sent back to the node from which it was received helps to bring an end to the flooding of an LSP. 
  Since X passes the LSP on to all its neighbors, who then turn around and do the same thing, the most recent copy of the LSP eventually reaches all nodes.*/
  int lspnode;
  cout << "Enter a node whose Link State packet is to be created" << endl; //In real life this process is automated when update is done.
  cin >> lspnode;
  vector<int> neighbours(0);
  for (int j = 0; j < lg[lspnode].size(); j++)
    neighbours.push_back(lg[lspnode][j]);
  LSP obj = {lspnode, neighbours, 1};
  cout << "Node Id : " << obj.nodeid << endl;
  cout << "Sequence Number (Default) : " << obj.sequence << endl;
  cout << "Neighbours : ";
  for (int i = 0; i < obj.neighbours.size(); i++)
  {
    cout << obj.neighbours[i] << " ";
  }
  cout << endl;
  lspdfs(lspnode, lg);
  //Giving Node 2 a Node ID which is greater than 3, this will imply that Node 2 has received a more recent flood from node 3 with greater sequence.
  //Hence , it will not update it's LSP to the flood recieved from Node 1.
  ls[2].packet.nodeid = 3;
  ls[2].packet.sequence = 4;
  for (int i = 1; i <= n; i++)
  {
    if (cvis[i])
    {
      if (ls[i].packet.nodeid == -1 || ls[i].packet.sequence < obj.sequence) //To replace the second condition of NodeId with Sequence Number.
        ls[i].packet = obj;
    }
  }
  cout << "Flooding successful displaying details" << endl;
  for (int i = 1; i <= n; i++)
  {
    if (ls[i].packet.nodeid != obj.nodeid)
    {
      continue;
    }
    cout << " Flood received from " << ls[i].packet.nodeid << " @ Node : " << i << endl; //Details of which Node has received the packet from initiator.
  }
  /*____________________________________________________________________________________________________________________________________________*/
  /*The next section deals with Cell Tower Placement Plan*/
  //We need to handle the following section carefully :
  /*Allocation of a different channel in the spots where
    channel overlap occurs (marked in color). In analogy,
    colors must be different, so that cell phone signals are
    handed off to a different channel.*/
  int i, ni, e, j, max = -1;
  cout << "Enter the number of towers to be placed on the map: ";
  cin >> ni;
  cout << "Enter the number of links between these towers: ";
  cin >> e;
  int ed[e][3], deg[ni + 1] = {0};
  for (i = 0; i < e; i++)
  {
    cout << "\nEnter the vertex pair for tower " << i + 1;
    cout << "\nN(1): ";
    cin >> ed[i][0];
    cout << "N(2): ";
    cin >> ed[i][1];
    //calculate the degree of each vertex
    ed[i][2] = -1;
    deg[ed[i][0]]++;
    deg[ed[i][1]]++;
  }
  //find out the maximum degree.
  for (i = 1; i <= ni; i++)
  {
    if (max < deg[i])
      max = deg[i];
  }
  EdgeColor(ed, e);
  cout << "\nAccording to Vizing's theorem this tower graph can use maximum of " << max + 1 << " colors to generate a valid edge coloring.\n";
  for (i = 0; i < e; i++)
    cout << "\nThe color of the edge between Tower N(1):" << ed[i][0] << " and Tower N(2):" << ed[i][1] << " is: color" << ed[i][2] << ".";
  /*Each cell region therefore uses one control tower with a
    specific channel and the region or control tower adjacent to it
    will use another tower and another channel. It is not hard to see
    how by using 4 channels, a node coloring algorithm can be
    used to efficiently plan towers and channels in a mobile
    network*/

  add_cir_prog(&tail, 1);
  add_lin_prog(&head, 2);
  add_lin_prog(&head, 3);
  add_lin_prog(&head, 4);
  add_cir_prog(&tail, 5);
  add_lin_prog(&head, 6);
  add_cir_prog(&tail, 7);
  add_cir_prog(&tail, 8);
  add_cir_prog(&tail, 9);

  cout << "*******************************************************\n";

  display();

  int cp = detectLoop(head);
  int pr;

  cout << "\n\n********************************\n";
  cout << "Enter a process to terminate: ";
  cin >> pr;

  if (pr == cp)
    cout << "**Error terminating process: Deadlock**" << endl;
  else
    cout << "**Process terminated successfully**" << endl;

  /* Kushagra: Begin after this line. */

  /* Rahul Das : Huffmann Encoding. 
Tasks :
1) Build a Huffman Tree from input characters along with their frequency.
2) Traverse the Huffman Tree and assign codes to characters.
3) Create a cumulative Huffmann String.
4) Decode this string by traversing the Huffmann Tree.
5) Take reference from : https://www.geeksforgeeks.org/huffman-decoding/
6) Also take reference from : https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
*/
  string str;
  cout << "\nEnter a string to decode and encode it with Huffman Encoding:\n";
  cin >> str;
  cout << "____________________________________________________\n";
  string encodedString, decodedString;
  calcFreq(str, str.length());
  HuffmanCodes(str.length());
  cout << "Input characters with there binary Huffman value:\n";
  for (auto v = codes.begin(); v != codes.end(); v++)
    cout << v->first << ' ' << v->second << endl;

  cout << "____________________________________________________\n";

  for (auto i : str)
    encodedString += codes[i];

  cout << "Encoded Huffman data:\n"
       << encodedString << endl;

  decodedString = decode_file(minHeap.top(), encodedString);
  cout << "\nDecoded Huffman Data:\n"
       << decodedString << endl;

  return 0;
}
