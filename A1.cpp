#include <bits/stdc++.h>
using namespace std;

// Function to find the shortest path using BFS
void shortestPathBFS(int start, const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<int> dist(n, -1);  // Distance array initialized to -1 (unreachable)
    vector<int> parent(n, -1);  // To track the path

    queue<int> q;
    dist[start] = 0;
    q.push(start);

    // Perform BFS
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adjList[node]) {
            if (dist[neighbor] == -1) {  // If the node is unvisited
                dist[neighbor] = dist[node] + 1;  // Set the distance
                parent[neighbor] = node;  // Track the parent node
                q.push(neighbor);
            }
        }
    }

    // Print the shortest path distances
    cout << "Shortest path distances from node " << start + 1 << ":\n";
    for (int i = 0; i < n; i++) {
        if (dist[i] != -1) {
            cout << "Node " << i + 1 << " is at distance " << dist[i] << "\n";  // Print 1-based index
        } else {
            cout << "Node " << i + 1 << " is unreachable\n";
        }
    }

    // Optionally, print the shortest path from start to each node
    for (int i = 0; i < n; i++) {
        if (i != start && dist[i] != -1) {
            cout << "Path from node " << start + 1 << " to node " << i + 1 << ": ";
            vector<int> path;
            for (int v = i; v != -1; v = parent[v]) {
                path.push_back(v + 1);  // Store the path (1-based index)
            }
            reverse(path.begin(), path.end());
            for (int p : path) {
                cout << p << " ";
            }
            cout << endl;
        }
    }
}

// BFS for disconnected graph with grouped levels
void bfsRecursiveHelper(const vector<vector<int>>& adjList, queue<pair<int, int>>& q, vector<bool>& visited, map<int, vector<int>>& levelMap, vector<int>& traversalOrder) {
    if (q.empty()) return;

    auto [node, level] = q.front();
    q.pop();
    levelMap[level].push_back(node);
    traversalOrder.push_back(node); // Store node in the traversal order

    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            q.push({neighbor, level + 1});
        }
    }
    bfsRecursiveHelper(adjList, q, visited, levelMap, traversalOrder);
}

// BFS for disconnected graph with recursion and final traversal order
void bfsDisconnected(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<bool> visited(n, false);

    // To store the final BFS traversal order
    vector<int> finalTraversalOrder;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            queue<pair<int, int>> q;
            visited[i] = true;
            q.push({i, 0}); // {node, level}
            map<int, vector<int>> levelMap; // To group nodes by levels

            vector<int> traversalOrder;  // Store the order of traversal for this component
            bfsRecursiveHelper(adjList, q, visited, levelMap, traversalOrder);

            // Print the grouped levels
            cout << "BFS starting from node " << i + 1 << ":\n";
            for (auto& [level, nodes] : levelMap) {
                cout << "Level " << level << ": ";
                for (int node : nodes) {
                    cout << node + 1 << " ";  // Print nodes in 1-based index
                }
                cout << "\n";
            }

            // Append the current component's traversal to the final result
            finalTraversalOrder.insert(finalTraversalOrder.end(), traversalOrder.begin(), traversalOrder.end());
            cout << endl;
        }
    }

    // Print the final BFS traversal order
    cout << "Final BFS traversal order: ";
    for (int node : finalTraversalOrder) {
        cout << node + 1 << " ";  // Print nodes in 1-based index
    }
    cout << endl;
}

// Recursive DFS utility function
void dfsUtil(int node, const vector<vector<int>>& adjList, vector<bool>& visited, int level, vector<int>& simpleOutput) {
    visited[node] = true;
    simpleOutput.push_back(node); 
    cout << "Level " << level << " (" << node + 1 << ") -> ";

    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            dfsUtil(neighbor, adjList, visited, level + 1, simpleOutput);
            cout << "Level " << level << " (" << node + 1 << ") -> "; // Print as recursion unwinds
        }
    }
}

// DFS for disconnected graph
void dfsDisconnected(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<int> simpleOutput; // To store the simple traversal order

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "DFS starting from node " << i + 1 << ":\n";
            dfsUtil(i, adjList, visited, 0, simpleOutput); // Pass simpleOutput here
            cout << "\n";
        }
    }

    // Print the simple output
    cout << "Simple DFS Traversal: ";
    for (int node : simpleOutput) {
        cout << node + 1 << " ";
    }
    cout << "\n";
}

// Depth-Limited Search (DLS)
void depthLimitedSearch(int start, const vector<vector<int>>& adjList, int end, int limit) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    stack<pair<int, int>> s;  // Stack holds pair of node and its current depth
    vector<int> traversalResult; // To store the order of traversal

    s.push({start, 0});
    visited[start] = true;

    // DLS traversal
    cout << "Depth-Limited Search starting from node " << start + 1 << " to node " << end + 1 
         << " with depth limit " << limit << ":\n";
    
    bool found = false;

    while (!s.empty()) {
        auto [node, depth] = s.top();
        s.pop();

        if (depth > limit) continue;  // Skip if the current depth exceeds the limit
        traversalResult.push_back(node);  // Store the node in traversal order

        // If the current node is the destination
        if (node == end) {
            found = true;
            break;
        }

        // Explore neighbors
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor] && depth + 1 <= limit) {
                visited[neighbor] = true;
                s.push({neighbor, depth + 1});
            }
        }
    }

    // Print the level-wise traversal nodes
    cout << "Level-wise Traversal: ";
    for (int node : traversalResult) {
        cout << node + 1 << " ";  // Print nodes in 1-based index
    }
    cout << endl;

    // Print if the end node is found or not
    if (found) {
        cout << "End node " << end + 1 << " found!\n";
    } else {
        cout << "End node " << end + 1 << " not found within depth limit.\n";
    }
}

// Iterative Deepening Search (IDS)
void iterativeDeepeningSearch(int start, const vector<vector<int>>& adjList, int end) {
    int n = adjList.size();
    vector<bool> visited(n, false);  // To keep track of visited nodes
    bool found = false;

    // Perform DFS with increasing depth limits
    for (int limit = 0; limit < n; limit++) {
        // Reset visited array for each depth limit
        fill(visited.begin(), visited.end(), false);

        cout << "\nPerforming DFS with depth limit " << limit+1 << "...\n";
        stack<pair<int, int>> s;  // Stack holds a pair of node and current depth
        s.push({start, 0});
        visited[start] = true;

        vector<int> traversalResult; // To store the order of traversal

        while (!s.empty()) {
            auto [node, depth] = s.top();
            s.pop();

            // If we reach the depth limit, we stop exploring deeper nodes
            if (depth > limit) continue;

            traversalResult.push_back(node); // Store the node in traversal order

            // If the current node is the destination
            if (node == end) {
                found = true;
                break;
            }

            // Visit neighbors
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor] && depth + 1 <= limit) {
                    visited[neighbor] = true;
                    s.push({neighbor, depth + 1});
                }
            }
        }

        // Print the traversal result for the current depth limit
        cout << "Traversal at depth " << limit << ": ";
        for (int node : traversalResult) {
            cout << node + 1 << " ";  // Print nodes in 1-based index
        }
        cout << endl;

        // If the goal node is found, break the loop
        if (found) {
            cout << "End node " << end + 1 << " found at depth " << limit+1 << "!\n";
            return;
        }
    }

    // If the end node was not found
    cout << "End node " << end + 1 << " not found within depth limits.\n";
}


int main() {
    vector<vector<int>> graph;
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    // Initialize the graph with V vertices (index 0 to V-1)
    graph.resize(V); // Resize graph to hold V vertices

    cout << "Enter the edges (u, v) where u and v are connected nodes:" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);  // Convert to 0-based indexing
        graph[v - 1].push_back(u - 1);  // Convert to 0-based indexing
    }

    int startNode, choice;

    do {
        cout << "\nMenu: \n";
        cout << "1. BFS Recursive\n";
        cout << "2. DFS Recursive\n";
        cout << "3. Shortest Path using BFS\n";
        cout << "4. Depth-Limited Search\n";
        cout << "5. Iterative Deepening Search\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice != 6) {
            startNode=1;
            startNode--; // Convert to 0-based indexing
        }

        switch (choice) {
        case 1:
            cout << "\nBFS Recursive traversal starting from node " << startNode + 1 << ": " << endl;
            bfsDisconnected(graph);
            break;

        case 2:
            cout << "\nDFS Recursive traversal:" << endl;
            dfsDisconnected(graph);
            break;

        case 3:
            cout << "\nShortest Path using BFS from node " << startNode + 1 << ": " << endl;
            shortestPathBFS(startNode, graph);
            break;

        case 4:
            int endNode,depthLimit;
            cout << "\nEnter the end node for Depth-Limited Search: ";
            cin >> endNode;
            cout << "Enter the depth limit for Depth-Limited Search: ";
            cin >> depthLimit;
            depthLimitedSearch(startNode, graph, endNode - 1, depthLimit);  // Convert end node to 0-based
            break;

        case 5:
            int endnode;
            cout << "\nEnter the end node for Iterative Deepening Search: ";
            cin >> endnode;
            iterativeDeepeningSearch(1, graph, endnode - 1);  // Convert end node to 0-based
            break;

        case 6:
            cout << "\nExiting the program.\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
