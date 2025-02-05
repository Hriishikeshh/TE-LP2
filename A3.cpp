#include<bits/stdc++.h>
using namespace std;

struct Job {
    char id;
    int deadline;
    int profit;
};


bool compare(Job a, Job b) {
    return a.profit > b.profit;
}


void printPath(vector<int>& parent, int node) {
    stack<int> path;
    while (node != -1) {
        path.push(node);
        node = parent[node];
    }

 
    cout << "Path: ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

class greedy{
    public:
    void jobScheduling(vector<Job>& jobs) {

        sort(jobs.begin(), jobs.end(), compare);

        int n = jobs.size();
        vector<char> result(n, '-'); // To store job sequence
        vector<bool> slot(n, false); // To track free time slots

        int totalProfit = 0;

        for (int i = 0; i < n; i++) {
            for (int j = min(n, jobs[i].deadline) - 1; j >= 0; j--) {
                if (!slot[j]) {
                    slot[j] = true;
                    result[j] = jobs[i].id;
                    totalProfit += jobs[i].profit;
                    break;
                }
            }
        }

    
        cout << "Scheduled Jobs: ";
        for (char job : result) {
            if (job != '-') cout << job << " ";
        }
        cout << "\nTotal Profit: " << totalProfit << endl;
    }

    void dijkstra(vector<vector<pair<int, int>>>& graph, int source) {
        int n = graph.size();
        vector<int> distance(n, INT_MAX);    // Distance from source to each node
        vector<int> parent(n, -1);           // To track the path
        distance[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int current = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();

            for (auto neighbor : graph[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

             
                if (current_dist + weight < distance[next]) {
                    distance[next] = current_dist + weight;
                    parent[next] = current;  // Track the path
                    pq.push({distance[next], next});
                }
            }
        }

        cout << "Shortest distances from node " << source << ":\n";
        for (int i = 0; i < n; i++) {
            cout << "Node " << i << " - Distance: " << distance[i] << " ";
            printPath(parent, i);  // Print the actual path
            cout << endl;
        }
    }

    void primsAlgorithm(vector<vector<pair<int, int>>>& adj) {
        int n = adj.size();
        vector<int> key(n, INT_MAX);   
        vector<int> parent(n, -1);     
        vector<bool> vis(n, false);    

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});  // {weight, node}
        key[0] = 0;

        int sum = 0;    

        while (!pq.empty()) {
            int node = pq.top().second;
            pq.pop();

            if (vis[node]) continue;
            vis[node] = true;

            sum += key[node];  
         
            for (auto neighbor : adj[node]) {
                int adjNode = neighbor.first;
                int weight = neighbor.second;

                if (!vis[adjNode] && weight < key[adjNode]) {
                    key[adjNode] = weight;
                    pq.push({weight, adjNode});
                    parent[adjNode] = node; 
                }
            }
        }

        cout << "---------------------\n";
        cout << "Minimum Weight of MST: " << sum << endl;
        cout << "Edges in the MST:\n";
        for (int i = 1; i < n; i++) {
            cout << parent[i] << " - " << i << " (Weight: " << key[i] << ")\n";
        }
    }


};

int main() {
    greedy obj;
    vector<Job> jobs = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    obj.jobScheduling(jobs); // Job scheduling to maximize profit

    vector<vector<pair<int, int>>> graph(7);

    // Adding edges (u, v, weight)
    // Making the graph undirected
    graph[0].push_back({1, 28});
    graph[1].push_back({0, 28});
    
    graph[1].push_back({2, 16});
    graph[2].push_back({1, 16});

    graph[1].push_back({6, 14});
    graph[6].push_back({1, 14});

    // graph[2].push_back({7, 14});
    // graph[7].push_back({2, 14});

    graph[2].push_back({3, 12});
    graph[3].push_back({2, 12});

    graph[6].push_back({3, 18});
    graph[3].push_back({6, 18});

    graph[3].push_back({4, 22});
    graph[4].push_back({3, 22});

    graph[6].push_back({4, 24});
    graph[4].push_back({6, 24});

    graph[4].push_back({5, 25});
    graph[5].push_back({4, 25});

    graph[5].push_back({0, 10});
    graph[0].push_back({5, 10});

    obj.dijkstra(graph, 0); 
    obj.primsAlgorithm(graph); 
}
