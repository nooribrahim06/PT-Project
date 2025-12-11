#include <iostream>
#include <cmath>
using namespace std;
int main () {
double price;
double discount;
cin >> price;
if (price > 100000){
discount = price * 0.01;
cout << discount ;
}
else
{
discount = 0.02 ;
cout << discount ;
}
return 0;
}