#ifndef EXPORTCSV_H
#define EXPORTCSV_H
#include "abstractexport.h"

class ExportCSV : public AbstractExport
{
public:
    ExportCSV();
    virtual void write();
};

#endif // EXPORTCSV_H
