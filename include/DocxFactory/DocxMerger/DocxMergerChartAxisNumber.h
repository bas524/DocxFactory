
#ifndef __DOCXFACTORY_DOCX_MERGER_CHART_AXIS_NUMBER_H__
#define __DOCXFACTORY_DOCX_MERGER_CHART_AXIS_NUMBER_H__

#include "DocxFactory/DocxMerger/DocxMergerChartAxis.h"



namespace DocxFactory {
    using namespace std;

    class DocxMergerPasteChartAxis;

    class DocxMergerChartAxisNumber : public DocxMergerChartAxis {
    public:
        DocxMergerChartAxisNumber();
        virtual ~DocxMergerChartAxisNumber();

        virtual uint64_t setValue(DocxMergerPasteChartAxis* p_pasteAxis, const string& p_value);
        virtual uint64_t setValue(DocxMergerPasteChartAxis* p_pasteAxis, double p_value);
        virtual string getValue(DocxMergerPasteChartAxis* p_pasteAxis, uint64_t p_index) const;
        virtual uint64_t getLength(DocxMergerPasteChartAxis* p_pasteAxis) const;

    protected:

    private:
        DocxMergerChartAxisNumber(const DocxMergerChartAxisNumber& p_other);
        DocxMergerChartAxisNumber& operator=(const DocxMergerChartAxisNumber& p_other);

    };
};

#endif
