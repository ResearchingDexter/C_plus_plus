#include <iostream>
#include<set>
#include<vector>
#include<functional>
#include<queue>
#include<utility>
#include<algorithm>
#include<iterator>
#define INF 99999999
using namespace std;
int dijkstra(int start,vector<vector<int>> &adjacent_matrix);
bool Bellman_Ford(int start,vector<vector<int>> &adjacent_matrix);
bool SPFA(int start,vector<vector<int>> adjacent_matrix);
int Floyd(vector<vector<int>> &adjacent_matrix);
int main()
{
    cout << "Hello world!" << endl;
    int R,C;
    cout<<"please input R and C:"<<endl;
    int a,b;
    char c;
    cin>>a>>b>>c;
    cout<<a<<b<<c<<endl;
    cin>>R>>C;
    vector<vector<int>> adjacent_matrix(R,vector<int>(C));

    for(int r=0;r<R;r++)
    {
        //copy(istream_iterator<int>{cin},istream_iterator<int>{},back_inserter(adjacent_matrix[r]));
        for(int c=0;c<C;c++)
        {
            cin>>adjacent_matrix[r][c];
        }
        //copy(adjacent_matrix[r].begin(),adjacent_matrix[r].end(),ostream_iterator<int>{cout," "});
    }
    dijkstra(0,adjacent_matrix);
    Bellman_Ford(0,adjacent_matrix);
    SPFA(0,adjacent_matrix);
    Floyd(adjacent_matrix);
    return 0;
}
int dijkstra(int start,vector<vector<int>> &adjacent_matrix)
{
    cout<<"start dijkstra"<<endl;
    int length=adjacent_matrix.size();
    set<int,less<int>> A,B;
    //priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> dist_queue;
    int *dist=new int[length];
    int update_index=start;
    int min_val=INF;
    for(int i=0;i<length;i++)
    {
        dist[i]=adjacent_matrix[start][i];
        if(i!=start&&dist[i]<min_val)
        {
            update_index=i;
            min_val=dist[i];
        }
        //dist_queue.push(make_pair(dist[i],i));
    }
    //pair<int,int> temp=dist_queue.top();
    //dist_queue.pop();
    A.insert(start);
    //cout<<"update_index:"<<update_index<<endl;
    while(A.size()<length)
    {
        //pair<int,int> dist_index=dist_queue.top();
        //cout<<dist_index.first<<": "<<dist_index.second<<endl;
        //dist_queue.pop();
        int temp_idex;
        min_val=INF;
        for(int i=0;i<length;i++)
        {
            if(A.find(i)==A.end())
            {
                dist[i]=min(dist[i],dist[update_index]+adjacent_matrix[update_index][i]);
                if(i!=update_index&&dist[i]<min_val)
                {
                    min_val=dist[i];
                    temp_idex=i;
                    //cout<<min_val<<" "<<temp_idex<<endl;
                }
            }
        }
        A.emplace(update_index);
        update_index=temp_idex;
    }
    for_each(dist,dist+length,[](int &a){cout<<a<<" ";});
    cout<<endl;
    delete [] dist;
    return 0;

}
bool Bellman_Ford(int start,vector<vector<int>> &adjacent_matrix)
{
    cout<<"start Bellman_Ford"<<endl;
    for_each(adjacent_matrix.begin(),adjacent_matrix.end(),[](vector<int> vec){
             for_each(vec.begin(),vec.end(),[](int &a){cout<<a<<" ";});cout<<endl;});
    cout<<"*******************"<<endl;
    int length=adjacent_matrix.size();
    int *dist=new int[length];
    //delete [] dist;
    for(int i=0;i<length;i++)
    {
        dist[i]=adjacent_matrix[start][i];
    }
    for(int i=0;i<length-1;i++)
    {
        for(int j=0;j<length;j++)
        {
            for(int k=0;k<length;k++)
            {
                if(adjacent_matrix[j][k]!=INF)
                    {dist[k]=min(dist[k],dist[j]+adjacent_matrix[j][k]);/*cout<<k<<" "<<dist[k]<<endl;*/}
            }
        }
    }
    for_each(dist,dist+length,[](int &a){cout<<a<<" ";});
    for(int j=0;j<length;j++)
    {
        for(int k=0;k<length;k++)
            if(dist[k]>dist[j]+adjacent_matrix[j][k])
        {
            delete [] dist;
            return false;
        }
    }
    cout<<endl;
    delete [] dist;
    return true;
}
bool SPFA(int start,vector<vector<int>> adjacent_matrix)
{
    cout<<"start SPFA"<<endl;
    for_each(adjacent_matrix.begin(),adjacent_matrix.end(),[](vector<int> vec){
             for_each(vec.begin(),vec.end(),[](int &a){cout<<a<<" ";});cout<<endl;});
    cout<<"*******************"<<endl;
    int length=adjacent_matrix.size();
    int *dist=new int[length];
    bool *flag=new bool[length];
    queue<int> adjacent_queue;
    adjacent_queue.push(start);
    flag[start]=true;
    for(int i=0;i<length;i++)
    {
        dist[i]=adjacent_matrix[start][i];
        if(dist[i]!=INF&&flag[i]==false)
        {
            adjacent_queue.push(i);
            flag[i]=true;
        }
        //flag[i]=false;
    }
    while(adjacent_queue.empty()==false)
    {
        int adjacent_point=adjacent_queue.front();
        adjacent_queue.pop();
        flag[adjacent_point]=false;
        for(int k=0;k<length;k++)
        {
            if(adjacent_matrix[adjacent_point][k]!=INF)
            {
                int temp=dist[adjacent_point]+adjacent_matrix[adjacent_point][k];
                //cout<<"adjacent:"<<temp<<" _ "<<dist[k];

                if(temp<dist[k])
                {
                    //adjacent_matrix[start][k]=dist[k];
                    dist[k]=temp;
                    if(flag[k]==false)
                    {
                        adjacent_queue.push(k);
                        flag[k]=true;
                    }
                }
            }
        }
    }
    for_each(dist,dist+length,[](int &a){cout<<a<<" ";});
    cout<<endl;
    delete []dist;
    return true;
}
int Floyd(vector<vector<int>> &adjacent_matrix)
{
    cout<<"start Floyd"<<endl;
    vector<vector<int>> dist(adjacent_matrix);
    int length=adjacent_matrix.size();
    for(int k=0;k<length;k++)
    {
        for(int i=0;i<length;i++)
        {
            for(int j=0;j<length;j++)
            {
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
    for_each(dist.begin(),dist.end(),[](vector<int> vec){
             for_each(vec.begin(),vec.end(),[](int &a){cout<<a<<" ";});cout<<endl;});
    return 0;
}
