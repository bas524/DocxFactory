
#ifndef __DOCXFACTORY_FILE_INFO_H__
#define __DOCXFACTORY_FILE_INFO_H__

#if defined (WIN32) | defined (_WIN32)
#include "zlib/zip.h"
#include "zlib/unzip.h"
#else
#include <minizip/zip.h>
#include <minizip/unzip.h>
#endif


namespace DocxFactory {
    using namespace std;

    class FileInfo {
    public:
        FileInfo(unz_file_info p_unzFileInfo);
        virtual ~FileInfo();

        const unz_file_info* getUnzFileInfo() const;
        const zip_fileinfo* getZipFileInfo() const;

    protected:

    private:
        FileInfo(const FileInfo& p_other);
        FileInfo operator=(const FileInfo& p_other);

        unz_file_info m_unzFileInfo;
        zip_fileinfo m_zipFileInfo;
    };
};

#endif
