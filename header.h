//
// Created by nothingholy on 09.11.2019.
//

#ifndef TSISA_04_HEADER_H
#define TSISA_04_HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

vector<vector<double>> marks;

void normalize(vector<double>& exp){
    double temp=0;
    for(const double &i:exp)
        temp+=i;

    for(double &i:exp)
        i/=temp;
}

void printCarTable(int i){
    if(i==0)
        cout << "S | ";
    if(i==1)
        cout << "M | ";
    if(i==2)
        cout << "H | ";
    if(i==3)
        cout << "T | ";
}

void printMatrix(vector<vector<double>> vec){
    int iter=0;
    cout << "\t--------------------------------------\n";
    cout << "\t# | Cost | Expenses | Gas | Comfort |\n\t--------------------------------------\n\t";
    for(const auto &i:vec) {
        printCarTable(iter);
        for (const auto &j:i)
            cout << setw(3) << j << "   | ";
        cout << "\n\t";
        iter++;
    }
    cout << "--------------------------------------";
}

void cars(int i){
    if(i==0)
        cout << "Suzuki";
    if(i==1)
        cout << "Mitsubishi";
    if(i==2)
        cout << "Honda";
    if(i==3)
        cout << "Toyota";
}

void setMarks(){
    //Suzuki
    vector<double> temp={8,4,7,2};
    marks.push_back(temp);
    //Mitsubishi
    temp={4,8,3,6};
    marks.push_back(temp);
    //Honda
    temp={5,2,6,4};
    marks.push_back(temp);
    //Toyota
    temp={1,5,2,8};
    marks.push_back(temp);

    cout << endl << setw(10) << "MATRIX ASSESSMENTS" << endl;
    printMatrix(marks);
}

void criteria_change(){
    vector<double> min,max;
    vector<vector<double>> temp(marks);

    for(size_t i=0;i<temp.size();i++){
        for(size_t j=1;j<temp[i].size();j++){
            int tempo= temp[i][j];
            if(i==0){
                min.push_back(tempo);
                max.push_back(tempo);
            }
            else{
                if(tempo<min[j-1])
                    min[j-1]=tempo;
                if(tempo>max[j-1])
                    max[j-1]=tempo;
            }
        }
    }

    for(size_t i=0;i<temp.size();i++){
        for(size_t j=1;j< temp[i].size();j++){
            temp[i][j]=(temp[i][j]-min[j-1]/(max[j-1]-min[j-1]));
        }
    }

    cout << "\nNormalized Matrix\n";
    printMatrix(temp);

    vector<double> best;
    vector<double>::iterator result;
    best.resize(4);
    for(size_t i=0;i<temp.size();i++){
        for(const double &j : temp[i])
            best[i]+=j;
    }
    result = max_element(best.begin(),best.end());

    cout << "\n\nBest choice is: ";
    cars(distance(best.begin(),result));

    temp.clear();
    best.clear();
}

#endif //TSISA_04_HEADER_H
