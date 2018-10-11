
#include "DocxFactory/DocxMerger/DocxMergerItem.h"
#include "DocxFactory/DocxMerger/DocxMergerField.h"
#include "DocxFactory/DocxMerger/DocxMergerChartField.h"
#include "DocxFactory/DocxMerger/DocxMergerChartAxis.h"
#include "DocxFactory/DocxMerger/DocxMergerPasteChartAxis.h"

using namespace DocxFactory;
using namespace std;

DocxMergerChartAxis::DocxMergerChartAxis(DocxMergerField::FieldType p_axisType) {

} // c'tor

DocxMergerChartAxis::~DocxMergerChartAxis() {

} // d'tor

uint64_t DocxMergerChartAxis::setValue(DocxMergerPasteChartAxis* p_pasteAxis, const string& p_value) {
  return 0;
} // setValue

uint64_t DocxMergerChartAxis::setValue(DocxMergerPasteChartAxis* p_pasteAxis, double p_value) {
  return 0;
} // setValue

string DocxMergerChartAxis::getValue(DocxMergerPasteChartAxis* p_pasteAxis, uint64_t p_index) const {
  return "";
} // getValue

uint64_t DocxMergerChartAxis::getLength(DocxMergerPasteChartAxis* p_pasteAxis) const {
  return 0;
} // getLength
