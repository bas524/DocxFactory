
#ifndef __DOCXFACTORY_DOCX_MERGER_PASTE_CHART_VALUES_H__
#define __DOCXFACTORY_DOCX_MERGER_PASTE_CHART_VALUES_H__

#include <vector>
#include <cstdint>



namespace DocxFactory {
    using namespace std;

    class DocxMergerPasteChartValues {
    public:
        DocxMergerPasteChartValues();
        DocxMergerPasteChartValues(uint64_t p_serLength, uint64_t p_catLength);
        virtual ~DocxMergerPasteChartValues();

        virtual void setValue(uint64_t p_series, uint64_t p_category, double p_value);

        const vector<vector<double>>*getValues() const;

    protected:

    private:
        DocxMergerPasteChartValues(const DocxMergerPasteChartValues& p_other);
        DocxMergerPasteChartValues& operator=(const DocxMergerPasteChartValues& p_other);

        vector<vector<double>> m_values;

    };
};

#endif
