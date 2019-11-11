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
            temp[i][j]=(temp[i][j]-min[j-1])/(max[j-1]-min[j-1]);
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

void Pareto(){
    vector<pair<double,double>> temp;
    for(const auto &i:marks)
        temp.push_back({i[0],i[1]});
    cout << "\nChoose Cost and Expenses:\n\n";

    //поиск точки утопии
    pair<double,double> max=temp[0];
    for(const auto &i:temp){
        if(i.first>max.first)
            max.first=i.first;
        if(i.second>max.second)
            max.second=i.second;
    }
    cout << "Utopia point: ( " << max.first << " ; " << max.second << " )" << endl;

    vector<double> distance;
    vector<double>::iterator res;
    for(auto &i:temp){
        i.first=max.first-i.first;
        i.second=max.second-i.second;
    }

    for(auto &i:temp)
        distance.push_back(i.first+i.second);

    res=min_element(distance.begin(),distance.end());
    cout << "Minimum distance = " << distance[std::distance(distance.begin(),res)] << endl;
    cout << "Best choice is: ";
    cars(std::distance(distance.begin(),res));

    temp.clear();
    distance.clear();
}

void Enum(){
    vector<vector<double>> temp(marks);
    vector<double> length;
    vector<double>::iterator res;
    length.resize(4);
    for(auto &i:temp){
        for(size_t j=0;j<i.size();j++)
            length[j]+=i[j];
    }
    for(auto &i:temp){
        for(size_t j=0;j<i.size();j++)
            i[j] /= length[j];
    }

    cout << "\nNormalized Matrix\n";
    printMatrix(temp);


    vector<double> expertopinion={1,1,1,1,1,1};
    cout << "\nExpert Asseessment of criteria:";
    for(const auto &i:expertopinion){
        cout << setw(3) << i << " ";
        if(i!=expertopinion[expertopinion.size()-1])
            cout << " ; ";
    }
    cout << endl;

    expertopinion={3,2,1,0};
    cout << "Criteria weights vector: ";
    for(const auto &i:expertopinion){
        cout << setw(3) << i << " ";
        if(i != expertopinion[expertopinion.size()-1])
            cout << " ; ";
    }
    cout << endl;

    normalize(expertopinion);
    cout << "\nNormalized Vector of Weights:    \t";
    for(const auto &i:expertopinion){
        cout << setw(3) << i << " ";
        if(i != expertopinion[expertopinion.size()-1])
            cout << " ; ";
    }
    cout << endl;

    vector<double> result={0,0,0,0};
    for(size_t i=0;i<temp.size();i++){
        for(size_t j=0;j<temp[i].size();j++)
            result[i]+=temp[i][j]*expertopinion[j];
    }

    cout << "\n\nMatrix of values of the combined criterion:";
    for(const auto &i:result){
        cout << i << " ";
        if(i!=result[result.size()-1])
            cout << " ; ";
    }
    cout << endl;

    res=max_element(result.begin(),result.end());
    cout << "\nHighest Value = " << result[distance(result.begin(),res)];
    cout << "\nBest choice is: ";
    cars(std::distance(result.begin(),res));

    temp.clear();
    length.clear();
    expertopinion.clear();
    result.clear();
}


void Hierarchies(){
    vector<vector<vector<double>>> mat;
    vector<double> length;
    vector<vector<double>> norm_length;

    vector<double> result = {0,0,0,0};
    vector<double>::iterator res;

    mat.resize(5);
    length.resize(5);
    norm_length.resize(5);
    for(auto &i:norm_length)
        i.resize(4);

    mat[0]={{1,}};
}

#endif //TSISA_04_HEADER_H
