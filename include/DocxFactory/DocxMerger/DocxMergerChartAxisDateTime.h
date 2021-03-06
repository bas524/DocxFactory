
#ifndef __DOCXFACTORY_DOCX_MERGER_CHART_AXIS_DATE_TIME_H__
#define __DOCXFACTORY_DOCX_MERGER_CHART_AXIS_DATE_TIME_H__

#include "DocxFactory/DocxMerger/DocxMergerChartAxis.h"



namespace DocxFactory {
    using namespace std;

    class DocxMergerPasteChartAxis;

    class DocxMergerChartAxisDateTime : public DocxMergerChartAxis {
    public:
        DocxMergerChartAxisDateTime();
        virtual ~DocxMergerChartAxisDateTime();

        virtual uint64_t setValue(DocxMergerPasteChartAxis* p_pasteAxis, const string& p_value);
        virtual uint64_t setValue(DocxMergerPasteChartAxis* p_pasteAxis, double p_value);
        virtual string getValue(DocxMergerPasteChartAxis* p_pasteAxis, uint64_t p_index) const;
        virtual uint64_t getLength(DocxMergerPasteChartAxis* p_pasteAxis) const;

    protected:

    private:
        DocxMergerChartAxisDateTime(const DocxMergerChartAxisDateTime& p_other);
        DocxMergerChartAxisDateTime& operator=(const DocxMergerChartAxisDateTime& p_other);

    };
};

#endif
