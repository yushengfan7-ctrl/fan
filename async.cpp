#include<iostream>
#include<thread>
#include<vector>
#include<future>
#include<cmath>
#include<numeric>

int compute_square_sum(int start,int end)
{
    int sum=0;
    for(int i=start;i<=end;i++)
    {
        sum+=i*i;
    }
    return sum;
}

int main()
{
    const int num_elements=1000;
    const int num_threads=4;

    std::vector<std::future<int>> future;
    int chunk_size=num_elements/num_threads;

    for(int i=0;i<num_threads;i++)
    {
        int start=i*chunk_size+1;
        int end=(i==num_threads-1)?num_elements:(start+chunk_size-1);

        future.push_back(std::async(std::launch::async,compute_square_sum,start,end));

    }
    int total_sum=0;
        for(auto& fut:future)
        {
            total_sum+=fut.get();
        }
    std::cout<<"Total square sum from 1 to "<<num_elements<<" :"<<total_sum<<std::endl;
}