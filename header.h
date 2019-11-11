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

void print_helper(size_t &i) {
    if (i == 0)
        std::cout << "|  Suzuki ";
    if (i == 1)
        std::cout << "|  Mitsub ";
    if (i == 2)
        std::cout << "|  Honda  ";
    if (i == 3)
        std::cout << "|  Toyota ";

}

void print_helper2(size_t &i) {
    if (i == 0)
        std::cout << "|  Cost  ";
    if (i == 1)
        std::cout << "|  Exp   ";
    if (i == 2)
        std::cout << "|  Gas   ";
    if (i == 3)
        std::cout << "|  Comf  ";

}

void Hierarchies(){
    vector<vector<vector<double>>> mat;
    vector<double> length;
    vector<vector<double>> norm_length,multipl,add;

    vector<double> result = {0,0,0,0};
    vector<double>::iterator res;

    mat.resize(5);
    multipl.resize(5);
    add.resize(5);
    for(auto &i:multipl){
        for(size_t j=0;j<4;j++)
            i.push_back(1);
    }
    for(auto &i:add){
        for(size_t j=0;j<4;j++)
            i.push_back(0);
    }

    length.resize(5);
    norm_length.resize(5);
    for(auto &i:norm_length)
        i.resize(4);
    //cost
    mat[0]={{1,    5,       3, 9, 0, 0},
            {1./5, 1,    1./3, 5, 0, 0},
            {1./3, 3,       1, 7, 0, 0},
            {1./9, 1./5, 1./7, 1, 0, 0}};
    //expenses
    mat[1]={{   1, 1./5, 3, 1./3,0,0},
            {   5,    1, 7,    3,0,0},
            {1./3, 1./7, 1, 1./5,0,0},
            {   3, 1./3, 5,    1,0,0}};
    //gas
    mat[2]={{   1, 7,    3, 9, 0,0},
            {1./7, 1, 1./5, 3, 0,0},
            {1./3, 5,    1, 7, 0,0},
            {1./9, 3, 1./7, 1, 0,0}};
    //comfort
    mat[3]={{ 1, 1./7, 3, 1./9, 0,0},
            { 7,    1, 3, 1./3, 0,0},
            { 3, 1./3, 1, 1./5, 0,0},
            { 9,    3, 5,    1, 0,0}};
    //priority
    mat[4]={{1,3,5,9,0,0},
            {1./3,1,3,5,0,0},
            {1./5,1./3,1,3,0,0},
            {1./9,1./5,1./3,1,0,0}};

    for (auto &i : mat) {
        for (auto &j: i)
            for (size_t k = 0; k < j.size() - 2; k++) {
                j[4] += j[k];
            }
    }

    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            length[i] += mat[i][j][4];
        }
    }

    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            mat[i][j][5] = mat[i][j][4] / length[i];
        }
    }

    std::vector<double> geomSum = {0, 0, 0, 0, 0}, lambda = {0, 0, 0, 0, 0}, IS = {0, 0, 0, 0, 0}, OS = {0, 0, 0, 0, 0};
    double PSS = 0.9;

    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            for (size_t k = 0; k < mat[i][j].size() - 2; k++) {
                multipl[i][j] *= mat[i][j][k];
                add[i][j] += mat[i][k][j];
            }
            geomSum[i] += std::pow(multipl[i][j], 0.25);
        }
    }

    for (size_t i = 0; i < multipl.size(); i++) {
        for (size_t j = 0; j < multipl[i].size(); j++) {
            multipl[i][j] /= geomSum[i];
            lambda[i] += add[i][j] * multipl[i][j];
        }
    }

    for (size_t i = 0; i < lambda.size(); i++) {
        IS[i] = (lambda[i] - 4) / (4 - 1);
        OS[i] = IS[i] / PSS;

    }

    std::cout << "\nNormalized matrix:\n";
    for (size_t i = 0; i < mat.size(); i++) {
        std::cout << "-----------------------------------------------------------------------\n";
        if (i < mat.size() - 1)
            std::cout << "|/////////|  Suzuki |  Mitsu  |   Honda   |  Toyota  |  Sum  |  Norm.  |\n";
        else
            std::cout << "|/////////|   Cost  |   Expen  |  Gas |  Comf  |  Sum  |  Norm.  |\n";

        std::cout << "-----------------------------------------------------------------------\n";
        for (size_t j = 0; j < mat[i].size(); j++) {
            if (i < mat.size() - 1)
                print_helper(j);
            else
                print_helper2(j);
            std::cout << "| ";
            for (const auto &k: mat[i][j]) {
                std::cout << std::setw(7) << k << " | ";
            }
            std::cout << std::endl;
        }
        std::cout << "-----------------------------------------------------------------------";
        std::cout << "\nLambda = " << lambda[i] << "\nIS = " << IS[i] << "\nOS = " << OS[i] << "\n\n";

    }

    // i = 0 4
    for (size_t i = 0; i < mat.size(); i++) {
        // j = 0 5
        for (size_t j = 0; j < mat[i].size(); j++) {
            norm_length[i][j] = mat[i][j][5];
        }
    }

    for (size_t i = 0; i < norm_length.size() - 1; i++) {
        for (size_t j = 0; j < norm_length[i].size(); j++) {
            result[i] += norm_length[i][j] * norm_length[4][j];
        }
    }
    std::cout << "The product of the matrix of alternative criteria by the priority vector:\n";
    for (auto &i: result)
        std::cout << " | " << std::setw(6) << i << " | " << std::endl;

    res = std::max_element(result.begin(), result.end());
    std::cout << "\n\nHighest value = " << result[std::distance(result.begin(), res)];
    std::cout << "\nThe best alternative: ";
    cars(std::distance(result.begin(), res));
}

#endif //TSISA_04_HEADER_H
