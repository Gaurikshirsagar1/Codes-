#include <iostream>
using namespace std;

int main(){
int n=5;

double x[5]={1,2,3,5,6};
double y[5]={8,4,3,5,1};

double sum_x=0;
double sum_y=0;
double sum_xy=0;
double sum_x2=0;

for(int i=0;i<n;i++){
    sum_x+=x[i];
    sum_y+=y[i];
    sum_xy+=x[i]*y[i];
    sum_x2+=x[i]*x[i];
}

double m=(n*sum_xy - sum_x *sum_y)/ (n*sum_x2 - sum_x*sum_x);
double b=(sum_y -m *sum_x)/n;

cout<<"value of slope"<<m;
cout<< "value of intercept- "<<n;



}
