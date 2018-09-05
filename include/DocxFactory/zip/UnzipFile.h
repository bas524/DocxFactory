
#ifndef __DOCXFACTORY_UNZIP_FILE_H__
#define __DOCXFACTORY_UNZIP_FILE_H__

#include "DocxFactory/zip/ZipFunc.h"
#include "DocxFactory/util/DocxFactoryDefs.h"

//#if defined (WIN32) | defined (_WIN32)
//#include "zlib/unzip.h"
//#else
#include <minizip/unzip.h>
//#endif

#include <type_traits>
#include <map>
#include <string>
#include <vector>


namespace DocxFactory {
    using namespace std;

    class FileInfo;

    class UnzipFile {
    public:
        UnzipFile();
        virtual ~UnzipFile();

        void open(const string& p_fileName);
        void close();



        // functions for extracting file entries content from the zip file

        std::vector<byte> extractEntryToBuf(
                const string& p_path,
                uint64_t& p_bufSize) const;

        std::vector<byte> extractEntryToRaw(
                const string& p_path,
                int& p_method,
                int& p_level,
                FileInfo*& p_fileInfo,
                uint64_t& p_bufSize) const;

        void extractEntryToFile(
                const string& p_fileName,
                const string& p_path) const;



        // file streaming functions

        void openStream(const string& p_path);
        void closeStream();

        template <class T>
        typename std::enable_if<std::is_integral<T>::value, T>::type readNum();

        template <class T>
        typename std::enable_if<std::is_floating_point<T>::value, T>::type readNum();

        string readStr();
        void read(char* p_buf, uint64_t p_bufSize);

        void insertPtrBySeq(uint64_t p_key, void* p_ptr);
        const map<uint64_t, void*>* getPtrsBySeq() const;

        bool isFileOpen() const;
        string getFileName() const;
        uint64_t getStreamPos() const;
        const map<string, FileInfo*>* getEntryList() const;

    protected:

    private:
        UnzipFile(const UnzipFile& p_other);
        UnzipFile operator=(const UnzipFile& p_other);

        void fillEntryList();
        void clearEntryList();

        unzFile m_unzipFile;
        string m_fileName;

        bool m_fileOpen;
        bool m_streamOpen;
        uint64_t m_streamPos;

        map<string, FileInfo*> m_entryList;
        map<uint64_t, void*> m_ptrsBySeq;

    };

    template <class T>
    typename std::enable_if<std::is_integral<T>::value, T>::type UnzipFile::readNum() {
        T l_retVal;

        read((char*) &l_retVal, sizeof ( l_retVal));

        ZipFunc::fromLittleEndian(l_retVal);

        return l_retVal;
    } // readNum<integral>

    template <class T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type UnzipFile::readNum() {
        DoublePack l_pack;
        double l_retVal;

        l_pack.m_exp = readNum<int32>();
        l_pack.m_frac = readNum<int64>();

        l_retVal = ZipFunc::unpack(l_pack);

        return (T) l_retVal;
    } // readNum<floating_point>

};

#endif
