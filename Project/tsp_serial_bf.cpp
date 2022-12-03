/*
 This is the traveling salesman problem done serially using the brute force method.
 This is the absolute worst method to use since the algorithm has a time complexity
 of O(n!) (also known as the fastest rising computations which ends up the slowest).
 Program more or less written to prove a point
*/
#include<iostream>
#include<algorithm>
#include<climits>
#include<ctime>
#include<vector>
#include<stdlib.h>

using namespace std;

void tsp(int **graph, int start_vertex, int n){
    vector<int> v;
    for(int i=0;i<n;i++){
        if(start_vertex-1!=i)
            v.push_back(i);
    }

    int minimum = INT_MAX;
    vector<int> result;
    while(next_permutation(v.begin(),v.end())){
        int curr_vert=start_vertex-1;
        int curr_weight=0;
        vector<int> temp;
        temp.push_back(start_vertex);

        for(int i=0;i<v.size();i++){
            temp.push_back(v[i]+1);
            curr_weight+=graph[curr_vert][v[i]];
            curr_vert=v[i];
        }
        curr_weight+=graph[curr_vert][start_vertex-1];
        minimum=min(minimum,curr_weight);

        if(minimum==curr_weight)
            result=temp;

    }

    cout<<"Minimum Path: ";
    for(int i=0;i<result.size();i++)
        cout<<result[i]<<" -> ";
    cout<<start_vertex<<" ("<<minimum<<")"<<endl;
}

int main(int argc, char **argv){
    clock_t begin,end;
    int start,vertices;
    srand(time(0));
    
    cout<<"Verticies for random graph (n): ";
    cin>>vertices;
    
    cout<<"Starting Node (1 to n): ";
    cin>>start;

    cout<<endl;
    int **graph = new int*[vertices];

    for(int i=0;i<vertices;i++){
        graph[i]=new int[vertices];
        for(int j=0;j<vertices;j++){
            if(i!=j)
                graph[i][j]=rand()%100+1;
            else
                graph[i][j]=0;
        }
    }

    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    begin=clock();
    tsp(graph,start,vertices);
    end=clock();
    cout<<"tsp() Elapsed Time: "<<(double)(end-begin)/CLOCKS_PER_SEC<<" sec"<<endl;

    return 0;
}