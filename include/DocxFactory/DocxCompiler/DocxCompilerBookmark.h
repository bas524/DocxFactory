
#ifndef __DOCXFACTORY_DOCX_COMPILER_BOOKMARK_H__
#define __DOCXFACTORY_DOCX_COMPILER_BOOKMARK_H__

#include "xercesc/util/XercesDefs.hpp"

#include <list>
#include <string>



XERCES_CPP_NAMESPACE_BEGIN

class DOMElement;

XERCES_CPP_NAMESPACE_END

        namespace DocxFactory {
    using namespace std;

    class DocxCompilerItemFile;

    class DocxCompilerBookmark {
    public:
        DocxCompilerBookmark(
                DocxCompilerItemFile* p_itemFile,
                DocxCompilerBookmark* p_parent,
                const string& p_name,
                uint64_t p_id,
                xercesc::DOMElement* p_startNode);

        virtual ~DocxCompilerBookmark();

        void normalize();

        void setGroupId(uint64_t p_groupId);
        void setEndNode(xercesc::DOMElement* p_node);
        void insertChild(DocxCompilerBookmark* p_bookmark);

        string getName() const;
        uint64_t getId() const;
        uint64_t getGroupId() const;
        xercesc::DOMElement* getStartNode() const;
        xercesc::DOMElement* getEndNode() const;
        DocxCompilerBookmark* getParent() const;
        const list<DocxCompilerBookmark*>* getChildren() const;

    protected:

    private:
        DocxCompilerBookmark(const DocxCompilerBookmark& p_other);
        DocxCompilerBookmark& operator=(const DocxCompilerBookmark& p_other);

        DocxCompilerItemFile* m_itemFile;
        DocxCompilerBookmark* m_parent;
        string m_name;

        uint64_t m_id;
        uint64_t m_groupId;

        xercesc::DOMElement* m_startNode;
        xercesc::DOMElement* m_endNode;

        list<DocxCompilerBookmark*> m_parents;
        list<DocxCompilerBookmark*> m_children;

    };
};

#endif
