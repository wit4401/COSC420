#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<ctime>
#include<stdlib.h>
#include <omp.h>
using namespace std;
#define MAX_SIZE 16
#define INFINITE 1e9

long long factorial[MAX_SIZE+1];

void set_factorial_arr(){
    factorial[0]=1;
    for(int i=1;i<=MAX_SIZE;i++)
        factorial[i]=factorial[i-1]*i;
}

void set_weights(vector<vector<int>>&matrix){
    int n = matrix.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            matrix[i][j]=rand()%11+1;
        matrix[i][i]=0;
    }
}

vector<int> curr_permutation(vector<int>&arr,long long fact){
    int size = arr.size();
    sort(arr.begin(),arr.end());

    set<int> nodes;
    for(int val:arr)
        nodes.insert(val);

    vector<int> retval;
    for(int i=0;i<size;i++){
        int iter = 1;
        long long curr_val = factorial[size-1-i];
        while(iter<fact){
            iter++;
            curr_val=(long long)curr_val*iter;
            curr_val=(long long)curr_val/(iter-1);
        }
        long long per_val=curr_val*(iter-1)/iter;
        fact-=per_val;

        auto viter = nodes.begin();

        for(int i=0;i<iter-1;i++)
            viter++;
        
        retval.push_back(*viter);
        nodes.erase(viter);
    }
    return retval;
}

int path_cost(vector<vector<int>>&cost_matrix,vector<int>&path){
    int cost = 0;
    for(int i=1;i<(int)path.size();i++)
        cost+=cost_matrix[path[i]][path[i-1]];
    return cost;
}

void tsp_omp(vector<vector<int>>costs){
    int msize = costs.size();
    int min_val = INFINITE;

    vector<int> retval;
    vector<int> nodes;
    

    long int k=factorial[msize-1];

    #pragma omp parallel private(nodes) shared(retval,min_val)
    {
        for(int i=1;i<msize;i++)
            nodes.push_back(i);
        
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        long int iter_thread=k/num_threads;
        int mod = k%num_threads;

        if(thread_id<mod){
            nodes = curr_permutation(nodes,thread_id*(iter_thread+1));
            iter_thread++;
        }
        else
            nodes=curr_permutation(nodes,thread_id*(iter_thread+mod));
        int i=0;
        while(i<iter_thread){
            vector<int> temp_path = nodes;
            temp_path.push_back(0);
            temp_path.insert(temp_path.begin(),0);
            int cost = path_cost(costs,temp_path);
            #pragma omp critial
            {
                if(cost<min_val){
                    min_val=cost;
                    retval=temp_path;
                }
            }
            i++;
            next_permutation(nodes.begin(),nodes.end());
        }
    }
    cout<<"Min Path: ";
    for(int i=0;i<retval.size()-1;i++)
        cout<<retval[i]<<" -> ";
    cout<<retval[0]<<" ("<<min_val<<")"<<endl;
}

int main(int argc, char *argv[]){
    int matrix_size = stoi(argv[1]);
    int num_of_threads = stoi(argv[2]);
    clock_t start,end;
    srand(time(NULL));

    set_factorial_arr();
    omp_set_num_threads(num_of_threads);
    
    vector<vector<int>>cost_matrix(matrix_size,vector<int>(matrix_size,0));
    set_weights(cost_matrix);

    for(int i=0;i<cost_matrix.size();i++){
        for(int j=0;j<cost_matrix.size();j++){
            cout<<cost_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    start=clock();
    tsp_omp(cost_matrix);
    end=clock();

    cout<<"Elapsed Time: "<<(double)(end-start)/CLOCKS_PER_SEC<<" sec\n";
    
    return 0;
}