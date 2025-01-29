#include <bits/stdc++.h>
using namespace std;

map<string, set<string>> graph;
map<string, bool> vis;
map<string, string> parent;
string source;
vector<string> cycle;
bool deadlock = false;

void dfs(string node)
{
    vis[node] = true;
    for (string n : graph[node])
    {
        if (vis[n])
        {
            if (n == source)
            {
                deadlock = true;
                string current = node;
                while (current != source)
                {
                    cycle.push_back(current);
                    current = parent[current];
                }
                cycle.push_back(source);
                reverse(cycle.begin(), cycle.end());
                return;
            }
        }
        else
        {
            parent[n] = node;
            dfs(n);
            if (deadlock)
                return;
        }
    }
}

int main()
{
    set<string> nodes;
    string from, to;
    while (cin >> from >> to) // ctrl + z then enter to stop input.
    {
        graph[from].insert(to);
        nodes.insert(from);
        nodes.insert(to);
    }

    for (string node : nodes)
    {
        for (string n : nodes)
        {
            vis[n] = false;
            parent[n] = "";
        }
        cycle.clear();
        source = node;
        dfs(node);
        if (deadlock)
        {
            cout << "Deadlock detected!\n";
            cout << "Nodes in the deadlock: ";
            for (size_t i = 0; i < cycle.size(); ++i)
            {
                cout << cycle[i];
                if (i < cycle.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
            return 0;
        }
    }
    cout << "No Deadlock\n";
    return 0;
}
