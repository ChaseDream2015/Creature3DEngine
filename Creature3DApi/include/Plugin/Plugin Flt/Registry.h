// Modify Registry to store a flt::AttrData object instead of a CRCore::crStateSet
// Julian Ortiz, June 18th 2003.

#ifndef __FLT_REGISTRY_H
#define __FLT_REGISTRY_H

#if defined(_MSC_VER)
#pragma warning( disable : 4786 )
#endif

#include <CRCore/Referenced.h>
#include <CRCore/ref_ptr.h>
#include <CRCore/crStateSet.h>

#include <Plugin flt/FltFile.h>
#include <Plugin flt/AttrData.h>

#include <map>
#include <vector>
#include <string>

namespace flt {

// forward declare referenced classes to help avoid mutiple includes
class Record;
class Input;

/**
    Registry is a singleton factory which stores
    the Objects types available at runtime for loading,
    and any Object reader or writers which are linked in
    at runtime for reading non-native file formats.

    The RegisterObjectProxy defined in Object.h can be
    used to automatically register at runtime a Object
    with the Registry.

    The RegisterReaderWriterProxy defined in ReaderWriter.h can
    be used to automatically register at runtime a reader/writer
    with the Registry.
*/

class Registry
{
    public:

        ~Registry() {}

        static Registry* instance();

        void addPrototype(Record* rec);
        Record* getPrototype(const int opcode);

        //void addTexture(const std::string& name, CRCore::crStateSet* texture);
        void addTexture(const std::string& name, AttrData* texture);
        //CRCore::crStateSet* getTexture(const std::string name);
        AttrData * getTexture(const std::string name);

        void addFltFile(const std::string& name, FltFile* file);
        FltFile* getFltFile(const std::string& name);
        
        void clearObjectCache();

        void addRecordForFutureDelete(Record* rec) { _recordForFutureDeleteList.push_back(rec); }
        
    private:

        typedef std::map<int, CRCore::ref_ptr<Record> > RecordProtoMap;
        //typedef std::map<std::string, CRCore::ref_ptr<CRCore::crStateSet> > TextureMap;
        typedef std::map<std::string, CRCore::ref_ptr<AttrData> > TextureMap;
        typedef std::map<std::string, CRCore::ref_ptr<FltFile> > FltFileMap;
        
        typedef std::vector<CRCore::ref_ptr<Record> > RecordsForFutureDeleteList;

        /** constructor is private, as its a singleton, preventing
            construction other than via the instance() method and
            therefore ensuring only one copy is ever constructed*/
        Registry() {}

        RecordProtoMap  _recordProtoMap;
        TextureMap      _textureMap;
        FltFileMap      _fltFileMap;
        
        RecordsForFutureDeleteList _recordForFutureDeleteList;
};


/**  Proxy class for automatic registration of reader/writers with the
     Registry.*/
template<class T>
class RegisterRecordProxy
{
    public:

        RegisterRecordProxy()
        {
            if (Registry::instance())
            {
                _obj = new T;
                Registry::instance()->addPrototype(_obj.get());
            }
        }

        ~RegisterRecordProxy() {}
        
    protected:

        CRCore::ref_ptr<T> _obj;

};



}; // end namespace flt

#endif // __FLT_REGISTRY_H

