//
// Created by martin.maliska on 9/22/2019.
//

#ifndef HOMEPI_REPORTBUILDER_H
#define HOMEPI_REPORTBUILDER_H

#include <string>
#include <vector>

using namespace std;

class ReportBuilder {
public:
    virtual vector<string> build() = 0;
};


#endif //HOMEPI_REPORTBUILDER_H
