#include<iostream>
#include<omp.h>

int main(int argc,char *argv[]){
    bool flag=false;
    std::cout<<"Hello from main()"<<std::endl;
    omp_set_num_threads(5);

    #pragma omp parallel shared(flag)
    {
        int threadId = omp_get_thread_num();
        int num_of_threads = omp_get_num_threads();
        #pragma omp critical
        {
	        std::cout<<"Hello world from thread "<<threadId<<" of "<<num_of_threads<<std::endl;
            if(!flag){
                std::cout<<"Thread "<<threadId<<" wins!\n";
                flag=true;
            }
            else
                std::cout<<"Aw, shucks"<<std::endl;
        }
    }
}
