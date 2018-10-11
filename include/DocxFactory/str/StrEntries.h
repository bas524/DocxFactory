
#ifndef __DOCXFACTORY_STR_ENTRIES_H__
#define __DOCXFACTORY_STR_ENTRIES_H__

#include <vector>
#include <string>



namespace DocxFactory {
    using namespace std;

    class StrEntries {
    public:

        // since uint64_t is unsigned the following line will
        // assign npos with the maximum value of uint64_t
        static const uint64_t npos = -1;

        StrEntries(const string& p_str, const string& p_delim = ",");
        virtual ~StrEntries();

        void setEntry(uint64_t p_index, const string& p_entry);
        void addEntry(const string& p_entry);
        void deleteEntry(uint64_t p_index);

        uint64_t lookup(const string& p_entry) const;
        uint64_t getNumEntries() const;
        string getEntry(uint64_t p_index) const;
        string getStr() const;

    protected:

    private:
        StrEntries(const StrEntries& p_other);
        StrEntries operator=(const StrEntries& p_other);

        string m_delim;
        vector<string> m_entryVec;

    };
};

#endif
