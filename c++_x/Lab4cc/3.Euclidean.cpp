#include<iostream>
#include<cmath>
using namespace std;
template <typename T>
struct point
{
    T x,y;
};
template<typename T>
double euclideanDistance(const point<T>& p1, const point<T>& p2){
    return sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2));
}
int main()
{
    point<double> point1 = {2.5,3.5};
    point<double> point2 = {7.7,8.2};
    point <int> point3 = {3, 6};
    point <int> point4 = {8, 9};
    cout << "distance bn 2 double types points: "<<euclideanDistance(point1,point2)<< endl;
    cout<< "distance bn 2 int type points: "<<euclideanDistance(point3,point4)<< endl;
   return 0;
}