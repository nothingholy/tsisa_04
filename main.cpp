#include "header.h"

int main() {
    vector<double> criteria={8,5,4,2};
    for(size_t i=0;i<criteria.size();i++){
        if(i==0)
            cout << "Cost: ";
        if(i==1)
            cout << "Expenses for service: ";
        if(i==2)
            cout << "Gas consumption: ";
        if(i==3)
            cout << "Comfort: ";
        cout << criteria[i] << endl;
    }
    normalize(criteria);
    cout << "Normalized vector { ";
    for(const double &i : criteria)
        cout << setprecision(3) << i << " ";

    cout << "}\n";

    setMarks();

    cout << "\n\n\nReplacing criteria with restrictions\n";
    criteria_change();

    cout << "\n\n\nFormation and narrowing of the Parreto set\n";
    Pareto();

    cout << "\n\n\nWeighting and combining criteria\n";
    Enum();

    cout << "\n\n\nHeirarchies\n";
    Hierarchies();
}