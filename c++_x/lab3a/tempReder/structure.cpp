#include<iostream>
using namespace std;
struct temp
{
    float high, low, avgDay;
}week[7];
void weeklyAvgcal(temp week[]){
    float weeklySum =0;
    for(int i=1; i<=7; i++){
        week[i].avgDay=(week[i].high+week[i].low)/2;
        cout<< "Daily average tempreture for day "<< i<< week[i].avgDay<<endl;
        weeklySum += week[i].avgDay;
    } 
    float weeklyAvg = weeklySum/7;
    cout << "For this tempreture recorde the weekly average is: "<< weeklyAvg;
}
int main()
{
    for (int i=1; i<=7; i++){
        cout<< "enter low and high tempreture for day "<< i<< ": ";
        cin>> week[i].low>>week[i].high;
        while (true)
        {
           if(week[i].low> week[i].high){
            cout << "Please insert the lower temp befor the higher one.";
            cin >> week[i].low>>week[i].high;

           }
            if (cin.fail())
           {
            cout<< "Invalid input.";
            cin >> week[i].avgDay;
           } else 
           {
           break;
           }
           
           
        }
        
    }

    weeklyAvgcal(week);
   return 0;
}