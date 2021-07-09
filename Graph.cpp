#include <set>
#include <map>
#include <string>
#include<queue>
#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include "Graph.h"

using namespace std;

Graph::Graph() {
}

int Graph::addVertex() {
	int n = vertices.size();
	vertices.insert(n);
	return n;
}

void Graph::addEdge(directedEdge newEdge, int weight) {
	if ((vertices.find(newEdge.first) == vertices.end()) || (vertices.find(newEdge.second) == vertices.end())) {
		cout << "no vertex" << endl;
		return;
	}

	edges.insert(newEdge);
	weights.insert(make_pair(newEdge, weight));
	edgemap[newEdge.first].insert({ newEdge.second ,weight });
	return;
}

int Graph::getNumVertices() {
	return vertices.size();
}

int Graph::getWeight(directedEdge edge) {
	int w;
	try {
		w = weights.at(edge);
	}
	catch (const std::out_of_range& e) {
		cout << "edge not found" << endl;
		return 0;
	}

	return w;
}

bool Graph::isEdge(directedEdge newEdge) {
	if (edges.find(newEdge) == edges.end()) {
		return false;
	}
	else {
		return true;
	}
}

void Graph::print() {
	/*
	for (auto& x :vertices) {
		
		cout << x << ": ";

		for (auto& y : weights) {
			if (y.first.first == x) {
				cout<<y.first.second << "(" << y.second << ") ";
			}
		}

		cout << endl;
	}
	cout << endl;
	*/

	for (int i = 0; i < edgemap.size(); i++) {
		cout << i << ": ";
		for (auto& x:edgemap[i]) {
			cout << x.first <<"("<< x.second << ") ";
		}
		cout << endl;
	}

	//cout << endl;
	return;
}

void Graph::generateGraph(string fileName) {
	
	ifstream input(fileName);
	if (!input.is_open()) {
		cout << "no file" << endl;
		return;
	}

	string line;
	string a, b, c, v;
	int x, y, z;

	input >> v;
	int n = stoi(v);

	for (int i = 0; i < n; i++) {
		vertices.insert(i);
	}

	edgemap.resize(n);

	input >> v;
	n = stoi(v);

	getline(input, line);

	for (int i = 0; i < n; i++) {

		if (input.eof()) {
			break;
		}

		input >> a >> b >> c;

		x = stoi(a);
		y = stoi(b);
		z = stoi(c);

		/*
		if ((x >= vertices.size()) || (y >= vertices.size())) {
			cout << "no vertex" << endl;
			continue;
		}
		directedEdge newedge = { x,y };
		edges.insert(newedge);
		weights.insert({ newedge,z });
		edgemap[x].insert({ y,z });
		*/

		this->addEdge({ x,y }, z);

		
	}
	

	return;
}

void Graph::modifiedDijkstra(int source) {

	if (source >= vertices.size()) {
		cout << "no vertex" << endl;
		return;
	}

	vector<int> cost(vertices.size(),-1);
	vector<int> path(vertices.size(),0);
	vector<bool> visit(vertices.size(), false);
	priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> node_queue;

	cost[source] = 0;
	path[source] = 1;
	node_queue.push({ 0,source });

	while (!node_queue.empty()) {
		int node_cost = node_queue.top().first;
		int node = node_queue.top().second;

		for (auto& x : edgemap[node]) {

			if (visit[x.first] == true) {
				continue;
			}

			if (cost[x.first] == -1) {
				cost[x.first] = cost[node]+ x.second;
				path[x.first] = path[node];
				node_queue.push({ cost[x.first],x.first });
			}
			else if (cost[x.first] == x.second + cost[node]) {
				path[x.first] = path[x.first] + path[node];
			}
			else if (cost[x.first] > x.second + cost[node]) {
				cost[x.first] = x.second + cost[node];
				path[x.first] = path[node];
				node_queue.push({ cost[x.first],x.first });
			}	
		}

		visit[node] = true;
		node_queue.pop();		
	}

	for (int i = 0; i < vertices.size(); i++) {
		if (i == source) {
			continue;
		}
		if (cost[i] == -1) {
			cost[i] = 2147483647;
		}
		cout << "distance to vertex " << i << " is " << cost[i] << " and there are " << path[i] <<" shortest paths" << endl;
	}

	return;
}