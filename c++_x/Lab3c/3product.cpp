#include<iostream>
#include<iomanip>
using namespace std;
int N;
class product{
public:
     char name[15];
     float cost;
     float price;
     int quantity;
     float calcRevenue(){
        return price*quantity;    
     }
         
     float calcTax(){
              return 0.15*calcRevenue();
         }
     float calcProfit(){
                 return (calcRevenue()- (calcTax()+cost*quantity));
             } 
 };
void getData(product pro[]){
    for (int i=0; i<N; i++){
        cout << "---Product "<< i+1<< " ---"<< endl;
        cout << "Enter the name of the product: ";
        cin >> pro[i].name;
        cout << "Enter the cost of production per unit: ";
        cin >> pro[i].cost;
        cout << "Enter the price of production per unit: ";
        cin >> pro[i].price;
        cout<< "Enter the quantity that is supplied: ";
        cin>> pro[i].quantity;
  }
}
void DispData(product pro[]){
    cout<< "product name "<< setw(15)<< "cost "<< setw(15)<< "Quantity"<< setw(15)<< "Price"<<setw(15)<<"Revenue"<<setw(15)<<"Tax"<<setw(15)<<"Profit"<<endl;
   for (int i=0; i < N; i++){
      cout<<setw(9)<<pro[i].name
          <<setw(17)<<pro[i].cost
          <<setw(16)<<pro[i].quantity
          <<setw(15)<<pro[i].price
          <<setw(15)<<pro[i].calcRevenue()
          <<setw(15)<<pro[i].calcTax()
          <<setw(15)<<pro[i].calcProfit()
          << endl;
     }
  }
int main(){
    cout << "Enter the number of products: ";
    cin >> N;
    product* pro= new product[N];

    getData(pro);
    DispData(pro);
   return 0;
}