#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<ctime>
#include<stdlib.h>
#include <omp.h>
using namespace std;
#define MAX_SIZE 16 //sets up the maximum size
#define INFINITE 1e9 //sets up infitiy

long long factorial[MAX_SIZE+1]; //factorial array

//set up the factorial array for # of iterations
void set_factorial_arr(){
    factorial[0]=1;
    for(int i=1;i<=MAX_SIZE;i++)
        factorial[i]=factorial[i-1]*i;
}

// function sets up the cost matrix using a vector of vectors
void set_weights(vector<vector<int>>&matrix){
    int n = matrix.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            matrix[i][j]=rand()%11+1;
        matrix[i][i]=0;
    }
}

// function collects the current permutations for the thread
vector<int> curr_permutation(vector<int>&arr,long long fact){
    int size = arr.size(); // store size of array ie # of vertices
    sort(arr.begin(),arr.end()); //sorts array in case its shuffled

    set<int> nodes; // declares an unordered set of nodes
    
    // loop stores all nodes into nodes
    for(int val:arr)
        nodes.insert(val); 

    vector<int> retval; // the return value of all permutations
    
    /*
     Loop utilizes the factorial to calculate the permutations for the thread to loop through
     which is n!/num_of_threads possible paths it makes for a not so efficient algorithm however 
     still faster than the serial program
    */
    for(int i=0;i<size;i++){
        int iter = 1;
        long long curr_val = factorial[size-1-i];
        while(curr_val<fact){
            iter++;
            curr_val=(long long)curr_val*iter;
            curr_val=(long long)curr_val/(iter-1);
        }

        /* The rest stores the appropriate nodes to the retval vector */
        long long per_val=curr_val*(iter-1)/iter;
        fact-=per_val;

        auto viter = nodes.begin();

        for(int j=0;j<iter-1;j++)
            viter++;
        
        retval.push_back(*viter);
        nodes.erase(viter);
    }
    return retval;
}

// figures out the path cost of the input path
int path_cost(vector<vector<int>>&cost_matrix,vector<int>&path){
    int cost = 0;
    for(int i=1;i<(int)path.size();i++)
        cost+=cost_matrix[path[i]][path[i-1]];
    return cost;
}

// actual function for the travelling salesman problem threaded
void tsp_omp(vector<vector<int>>costs){
    int msize = costs.size();
    int min_val = INFINITE;

    vector<int> retval;
    vector<int> nodes;

    long int k=factorial[msize-1];

    // parallelization portion
    #pragma omp parallel private(nodes) shared(retval,min_val)
    {
        for(int i=1;i<msize;i++)
            nodes.push_back(i);
        
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        long int iter_thread=k/num_threads;
        int mod = k%num_threads;

        /* This portion calculates the permutations and compares them */
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
            
            //critical section
            #pragma omp critial
            {
                if(cost<min_val){
                    min_val=cost;
                    retval=temp_path;
                }
            }
            i++;
            next_permutation(nodes.begin(),nodes.end());//steps to the next permutation but stops when the iter_thread function is done
        }
    }
    /* Prints out minimum path for our theoretical salesperson */
    cout<<"Min Path: ";
    for(int i=0;i<retval.size()-1;i++)
        cout<<retval[i]<<" -> ";
    cout<<retval[0]<<" ("<<min_val<<")"<<endl;
}

/* All the main does is set up and time the function using the command line arguements */
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