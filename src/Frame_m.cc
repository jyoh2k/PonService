//
// Generated file, do not edit! Created by nedtool 5.0 from Frame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Frame_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(GenericFrame);

GenericFrame::GenericFrame(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->src = 0;
    this->dest = 0;
    this->type = 0;
    this->seqNum = 0;
    this->responseBytes = 0;
}

GenericFrame::GenericFrame(const GenericFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

GenericFrame::~GenericFrame()
{
}

GenericFrame& GenericFrame::operator=(const GenericFrame& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GenericFrame::copy(const GenericFrame& other)
{
    this->src = other.src;
    this->dest = other.dest;
    this->type = other.type;
    this->seqNum = other.seqNum;
    this->responseBytes = other.responseBytes;
}

void GenericFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->src);
    doParsimPacking(b,this->dest);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->seqNum);
    doParsimPacking(b,this->responseBytes);
}

void GenericFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->src);
    doParsimUnpacking(b,this->dest);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->seqNum);
    doParsimUnpacking(b,this->responseBytes);
}

int GenericFrame::getSrc() const
{
    return this->src;
}

void GenericFrame::setSrc(int src)
{
    this->src = src;
}

int GenericFrame::getDest() const
{
    return this->dest;
}

void GenericFrame::setDest(int dest)
{
    this->dest = dest;
}

int GenericFrame::getType() const
{
    return this->type;
}

void GenericFrame::setType(int type)
{
    this->type = type;
}

long GenericFrame::getSeqNum() const
{
    return this->seqNum;
}

void GenericFrame::setSeqNum(long seqNum)
{
    this->seqNum = seqNum;
}

long GenericFrame::getResponseBytes() const
{
    return this->responseBytes;
}

void GenericFrame::setResponseBytes(long responseBytes)
{
    this->responseBytes = responseBytes;
}

class GenericFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GenericFrameDescriptor();
    virtual ~GenericFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GenericFrameDescriptor);

GenericFrameDescriptor::GenericFrameDescriptor() : omnetpp::cClassDescriptor("GenericFrame", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

GenericFrameDescriptor::~GenericFrameDescriptor()
{
    delete[] propertynames;
}

bool GenericFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GenericFrame *>(obj)!=nullptr;
}

const char **GenericFrameDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GenericFrameDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GenericFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int GenericFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *GenericFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "src",
        "dest",
        "type",
        "seqNum",
        "responseBytes",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int GenericFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNum")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "responseBytes")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GenericFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "long",
        "long",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **GenericFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GenericFrameDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GenericFrameDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GenericFrame *pp = (GenericFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GenericFrameDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GenericFrame *pp = (GenericFrame *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSrc());
        case 1: return long2string(pp->getDest());
        case 2: return long2string(pp->getType());
        case 3: return long2string(pp->getSeqNum());
        case 4: return long2string(pp->getResponseBytes());
        default: return "";
    }
}

bool GenericFrameDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GenericFrame *pp = (GenericFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrc(string2long(value)); return true;
        case 1: pp->setDest(string2long(value)); return true;
        case 2: pp->setType(string2long(value)); return true;
        case 3: pp->setSeqNum(string2long(value)); return true;
        case 4: pp->setResponseBytes(string2long(value)); return true;
        default: return false;
    }
}

const char *GenericFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *GenericFrameDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GenericFrame *pp = (GenericFrame *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(GenericFrameWithWMControl);

GenericFrameWithWMControl::GenericFrameWithWMControl(const char *name, int kind) : ::GenericFrame(name,kind)
{
}

GenericFrameWithWMControl::GenericFrameWithWMControl(const GenericFrameWithWMControl& other) : ::GenericFrame(other)
{
    copy(other);
}

GenericFrameWithWMControl::~GenericFrameWithWMControl()
{
}

GenericFrameWithWMControl& GenericFrameWithWMControl::operator=(const GenericFrameWithWMControl& other)
{
    if (this==&other) return *this;
    ::GenericFrame::operator=(other);
    copy(other);
    return *this;
}

void GenericFrameWithWMControl::copy(const GenericFrameWithWMControl& other)
{
    this->header = other.header;
    this->payload = other.payload;
}

void GenericFrameWithWMControl::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::GenericFrame::parsimPack(b);
    doParsimPacking(b,this->header);
    doParsimPacking(b,this->payload);
}

void GenericFrameWithWMControl::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::GenericFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->header);
    doParsimUnpacking(b,this->payload);
}

WMHeader& GenericFrameWithWMControl::getHeader()
{
    return this->header;
}

void GenericFrameWithWMControl::setHeader(const WMHeader& header)
{
    this->header = header;
}

WMPayload_Array& GenericFrameWithWMControl::getPayload()
{
    return this->payload;
}

void GenericFrameWithWMControl::setPayload(const WMPayload_Array& payload)
{
    this->payload = payload;
}

class GenericFrameWithWMControlDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GenericFrameWithWMControlDescriptor();
    virtual ~GenericFrameWithWMControlDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GenericFrameWithWMControlDescriptor);

GenericFrameWithWMControlDescriptor::GenericFrameWithWMControlDescriptor() : omnetpp::cClassDescriptor("GenericFrameWithWMControl", "GenericFrame")
{
    propertynames = nullptr;
}

GenericFrameWithWMControlDescriptor::~GenericFrameWithWMControlDescriptor()
{
    delete[] propertynames;
}

bool GenericFrameWithWMControlDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GenericFrameWithWMControl *>(obj)!=nullptr;
}

const char **GenericFrameWithWMControlDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GenericFrameWithWMControlDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GenericFrameWithWMControlDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int GenericFrameWithWMControlDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GenericFrameWithWMControlDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "header",
        "payload",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int GenericFrameWithWMControlDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "header")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GenericFrameWithWMControlDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WMHeader",
        "WMPayload_Array",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **GenericFrameWithWMControlDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GenericFrameWithWMControlDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GenericFrameWithWMControlDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithWMControl *pp = (GenericFrameWithWMControl *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GenericFrameWithWMControlDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithWMControl *pp = (GenericFrameWithWMControl *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getHeader(); return out.str();}
        case 1: {std::stringstream out; out << pp->getPayload(); return out.str();}
        default: return "";
    }
}

bool GenericFrameWithWMControlDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithWMControl *pp = (GenericFrameWithWMControl *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GenericFrameWithWMControlDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WMHeader));
        case 1: return omnetpp::opp_typename(typeid(WMPayload_Array));
        default: return nullptr;
    };
}

void *GenericFrameWithWMControlDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithWMControl *pp = (GenericFrameWithWMControl *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getHeader()); break;
        case 1: return (void *)(&pp->getPayload()); break;
        default: return nullptr;
    }
}

Register_Class(GenericFrameWithPHYControl);

GenericFrameWithPHYControl::GenericFrameWithPHYControl(const char *name, int kind) : ::GenericFrame(name,kind)
{
    this->command = 0;
    this->tuningWavelength = 0;
    this->sleepTime = 0;
    this->sleepDuration = 0;
}

GenericFrameWithPHYControl::GenericFrameWithPHYControl(const GenericFrameWithPHYControl& other) : ::GenericFrame(other)
{
    copy(other);
}

GenericFrameWithPHYControl::~GenericFrameWithPHYControl()
{
}

GenericFrameWithPHYControl& GenericFrameWithPHYControl::operator=(const GenericFrameWithPHYControl& other)
{
    if (this==&other) return *this;
    ::GenericFrame::operator=(other);
    copy(other);
    return *this;
}

void GenericFrameWithPHYControl::copy(const GenericFrameWithPHYControl& other)
{
    this->command = other.command;
    this->tuningWavelength = other.tuningWavelength;
    this->sleepTime = other.sleepTime;
    this->sleepDuration = other.sleepDuration;
}

void GenericFrameWithPHYControl::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::GenericFrame::parsimPack(b);
    doParsimPacking(b,this->command);
    doParsimPacking(b,this->tuningWavelength);
    doParsimPacking(b,this->sleepTime);
    doParsimPacking(b,this->sleepDuration);
}

void GenericFrameWithPHYControl::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::GenericFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->command);
    doParsimUnpacking(b,this->tuningWavelength);
    doParsimUnpacking(b,this->sleepTime);
    doParsimUnpacking(b,this->sleepDuration);
}

int GenericFrameWithPHYControl::getCommand() const
{
    return this->command;
}

void GenericFrameWithPHYControl::setCommand(int command)
{
    this->command = command;
}

int GenericFrameWithPHYControl::getTuningWavelength() const
{
    return this->tuningWavelength;
}

void GenericFrameWithPHYControl::setTuningWavelength(int tuningWavelength)
{
    this->tuningWavelength = tuningWavelength;
}

double GenericFrameWithPHYControl::getSleepTime() const
{
    return this->sleepTime;
}

void GenericFrameWithPHYControl::setSleepTime(double sleepTime)
{
    this->sleepTime = sleepTime;
}

double GenericFrameWithPHYControl::getSleepDuration() const
{
    return this->sleepDuration;
}

void GenericFrameWithPHYControl::setSleepDuration(double sleepDuration)
{
    this->sleepDuration = sleepDuration;
}

class GenericFrameWithPHYControlDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    GenericFrameWithPHYControlDescriptor();
    virtual ~GenericFrameWithPHYControlDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(GenericFrameWithPHYControlDescriptor);

GenericFrameWithPHYControlDescriptor::GenericFrameWithPHYControlDescriptor() : omnetpp::cClassDescriptor("GenericFrameWithPHYControl", "GenericFrame")
{
    propertynames = nullptr;
}

GenericFrameWithPHYControlDescriptor::~GenericFrameWithPHYControlDescriptor()
{
    delete[] propertynames;
}

bool GenericFrameWithPHYControlDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GenericFrameWithPHYControl *>(obj)!=nullptr;
}

const char **GenericFrameWithPHYControlDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *GenericFrameWithPHYControlDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int GenericFrameWithPHYControlDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int GenericFrameWithPHYControlDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *GenericFrameWithPHYControlDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "command",
        "tuningWavelength",
        "sleepTime",
        "sleepDuration",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int GenericFrameWithPHYControlDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "command")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "tuningWavelength")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sleepTime")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sleepDuration")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *GenericFrameWithPHYControlDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "double",
        "double",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **GenericFrameWithPHYControlDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GenericFrameWithPHYControlDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GenericFrameWithPHYControlDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithPHYControl *pp = (GenericFrameWithPHYControl *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GenericFrameWithPHYControlDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithPHYControl *pp = (GenericFrameWithPHYControl *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCommand());
        case 1: return long2string(pp->getTuningWavelength());
        case 2: return double2string(pp->getSleepTime());
        case 3: return double2string(pp->getSleepDuration());
        default: return "";
    }
}

bool GenericFrameWithPHYControlDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithPHYControl *pp = (GenericFrameWithPHYControl *)object; (void)pp;
    switch (field) {
        case 0: pp->setCommand(string2long(value)); return true;
        case 1: pp->setTuningWavelength(string2long(value)); return true;
        case 2: pp->setSleepTime(string2double(value)); return true;
        case 3: pp->setSleepDuration(string2double(value)); return true;
        default: return false;
    }
}

const char *GenericFrameWithPHYControlDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *GenericFrameWithPHYControlDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    GenericFrameWithPHYControl *pp = (GenericFrameWithPHYControl *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(TC);

TC::TC(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->wavelength = 0;
    this->type = 0;
}

TC::TC(const TC& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

TC::~TC()
{
}

TC& TC::operator=(const TC& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void TC::copy(const TC& other)
{
    this->wavelength = other.wavelength;
    this->type = other.type;
    this->EMs = other.EMs;
}

void TC::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->wavelength);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->EMs);
}

void TC::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->wavelength);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->EMs);
}

int TC::getWavelength() const
{
    return this->wavelength;
}

void TC::setWavelength(int wavelength)
{
    this->wavelength = wavelength;
}

int TC::getType() const
{
    return this->type;
}

void TC::setType(int type)
{
    this->type = type;
}

EM_CHUNKS& TC::getEMs()
{
    return this->EMs;
}

void TC::setEMs(const EM_CHUNKS& EMs)
{
    this->EMs = EMs;
}

class TCDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TCDescriptor();
    virtual ~TCDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TCDescriptor);

TCDescriptor::TCDescriptor() : omnetpp::cClassDescriptor("TC", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

TCDescriptor::~TCDescriptor()
{
    delete[] propertynames;
}

bool TCDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TC *>(obj)!=nullptr;
}

const char **TCDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TCDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TCDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int TCDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *TCDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "wavelength",
        "type",
        "EMs",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int TCDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='w' && strcmp(fieldName, "wavelength")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='E' && strcmp(fieldName, "EMs")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TCDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "EM_CHUNKS",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **TCDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TCDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TCDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TC *pp = (TC *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TCDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TC *pp = (TC *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getWavelength());
        case 1: return long2string(pp->getType());
        case 2: {std::stringstream out; out << pp->getEMs(); return out.str();}
        default: return "";
    }
}

bool TCDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TC *pp = (TC *)object; (void)pp;
    switch (field) {
        case 0: pp->setWavelength(string2long(value)); return true;
        case 1: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *TCDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 2: return omnetpp::opp_typename(typeid(EM_CHUNKS));
        default: return nullptr;
    };
}

void *TCDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TC *pp = (TC *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getEMs()); break;
        default: return nullptr;
    }
}

Register_Class(TC_US);

TC_US::TC_US(const char *name, int kind) : ::TC(name,kind)
{
    this->ONU_ID = 0;
    this->Ind = 0;
    this->HEC = 0;
}

TC_US::TC_US(const TC_US& other) : ::TC(other)
{
    copy(other);
}

TC_US::~TC_US()
{
}

TC_US& TC_US::operator=(const TC_US& other)
{
    if (this==&other) return *this;
    ::TC::operator=(other);
    copy(other);
    return *this;
}

void TC_US::copy(const TC_US& other)
{
    this->ONU_ID = other.ONU_ID;
    this->Ind = other.Ind;
    this->HEC = other.HEC;
    this->PLOAMu = other.PLOAMu;
    this->DBRu = other.DBRu;
}

void TC_US::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TC::parsimPack(b);
    doParsimPacking(b,this->ONU_ID);
    doParsimPacking(b,this->Ind);
    doParsimPacking(b,this->HEC);
    doParsimPacking(b,this->PLOAMu);
    doParsimPacking(b,this->DBRu);
}

void TC_US::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TC::parsimUnpack(b);
    doParsimUnpacking(b,this->ONU_ID);
    doParsimUnpacking(b,this->Ind);
    doParsimUnpacking(b,this->HEC);
    doParsimUnpacking(b,this->PLOAMu);
    doParsimUnpacking(b,this->DBRu);
}

unsigned int TC_US::getONU_ID() const
{
    return this->ONU_ID;
}

void TC_US::setONU_ID(unsigned int ONU_ID)
{
    this->ONU_ID = ONU_ID;
}

unsigned int TC_US::getInd() const
{
    return this->Ind;
}

void TC_US::setInd(unsigned int Ind)
{
    this->Ind = Ind;
}

unsigned int TC_US::getHEC() const
{
    return this->HEC;
}

void TC_US::setHEC(unsigned int HEC)
{
    this->HEC = HEC;
}

PLOAM& TC_US::getPLOAMu()
{
    return this->PLOAMu;
}

void TC_US::setPLOAMu(const PLOAM& PLOAMu)
{
    this->PLOAMu = PLOAMu;
}

DBRU& TC_US::getDBRu()
{
    return this->DBRu;
}

void TC_US::setDBRu(const DBRU& DBRu)
{
    this->DBRu = DBRu;
}

class TC_USDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TC_USDescriptor();
    virtual ~TC_USDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TC_USDescriptor);

TC_USDescriptor::TC_USDescriptor() : omnetpp::cClassDescriptor("TC_US", "TC")
{
    propertynames = nullptr;
}

TC_USDescriptor::~TC_USDescriptor()
{
    delete[] propertynames;
}

bool TC_USDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TC_US *>(obj)!=nullptr;
}

const char **TC_USDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TC_USDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TC_USDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int TC_USDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *TC_USDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ONU_ID",
        "Ind",
        "HEC",
        "PLOAMu",
        "DBRu",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int TC_USDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='O' && strcmp(fieldName, "ONU_ID")==0) return base+0;
    if (fieldName[0]=='I' && strcmp(fieldName, "Ind")==0) return base+1;
    if (fieldName[0]=='H' && strcmp(fieldName, "HEC")==0) return base+2;
    if (fieldName[0]=='P' && strcmp(fieldName, "PLOAMu")==0) return base+3;
    if (fieldName[0]=='D' && strcmp(fieldName, "DBRu")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TC_USDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "PLOAM",
        "DBRU",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **TC_USDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TC_USDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TC_USDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TC_US *pp = (TC_US *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TC_USDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TC_US *pp = (TC_US *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getONU_ID());
        case 1: return ulong2string(pp->getInd());
        case 2: return ulong2string(pp->getHEC());
        case 3: {std::stringstream out; out << pp->getPLOAMu(); return out.str();}
        case 4: {std::stringstream out; out << pp->getDBRu(); return out.str();}
        default: return "";
    }
}

bool TC_USDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TC_US *pp = (TC_US *)object; (void)pp;
    switch (field) {
        case 0: pp->setONU_ID(string2ulong(value)); return true;
        case 1: pp->setInd(string2ulong(value)); return true;
        case 2: pp->setHEC(string2ulong(value)); return true;
        default: return false;
    }
}

const char *TC_USDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 3: return omnetpp::opp_typename(typeid(PLOAM));
        case 4: return omnetpp::opp_typename(typeid(DBRU));
        default: return nullptr;
    };
}

void *TC_USDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TC_US *pp = (TC_US *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getPLOAMu()); break;
        case 4: return (void *)(&pp->getDBRu()); break;
        default: return nullptr;
    }
}

Register_Class(TC_DS);

TC_DS::TC_DS(const char *name, int kind) : ::TC(name,kind)
{
    this->BWmapLength = 0;
    this->PLOAMcount = 0;
    this->HEC = 0;
}

TC_DS::TC_DS(const TC_DS& other) : ::TC(other)
{
    copy(other);
}

TC_DS::~TC_DS()
{
}

TC_DS& TC_DS::operator=(const TC_DS& other)
{
    if (this==&other) return *this;
    ::TC::operator=(other);
    copy(other);
    return *this;
}

void TC_DS::copy(const TC_DS& other)
{
    this->BWmapLength = other.BWmapLength;
    this->PLOAMcount = other.PLOAMcount;
    this->HEC = other.HEC;
    this->BWMAPs = other.BWMAPs;
    this->PLOAMd = other.PLOAMd;
}

void TC_DS::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::TC::parsimPack(b);
    doParsimPacking(b,this->BWmapLength);
    doParsimPacking(b,this->PLOAMcount);
    doParsimPacking(b,this->HEC);
    doParsimPacking(b,this->BWMAPs);
    doParsimPacking(b,this->PLOAMd);
}

void TC_DS::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::TC::parsimUnpack(b);
    doParsimUnpacking(b,this->BWmapLength);
    doParsimUnpacking(b,this->PLOAMcount);
    doParsimUnpacking(b,this->HEC);
    doParsimUnpacking(b,this->BWMAPs);
    doParsimUnpacking(b,this->PLOAMd);
}

unsigned int TC_DS::getBWmapLength() const
{
    return this->BWmapLength;
}

void TC_DS::setBWmapLength(unsigned int BWmapLength)
{
    this->BWmapLength = BWmapLength;
}

unsigned int TC_DS::getPLOAMcount() const
{
    return this->PLOAMcount;
}

void TC_DS::setPLOAMcount(unsigned int PLOAMcount)
{
    this->PLOAMcount = PLOAMcount;
}

unsigned int TC_DS::getHEC() const
{
    return this->HEC;
}

void TC_DS::setHEC(unsigned int HEC)
{
    this->HEC = HEC;
}

BWMAP_ARRAY& TC_DS::getBWMAPs()
{
    return this->BWMAPs;
}

void TC_DS::setBWMAPs(const BWMAP_ARRAY& BWMAPs)
{
    this->BWMAPs = BWMAPs;
}

PLOAM_ARRAY& TC_DS::getPLOAMd()
{
    return this->PLOAMd;
}

void TC_DS::setPLOAMd(const PLOAM_ARRAY& PLOAMd)
{
    this->PLOAMd = PLOAMd;
}

class TC_DSDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TC_DSDescriptor();
    virtual ~TC_DSDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(TC_DSDescriptor);

TC_DSDescriptor::TC_DSDescriptor() : omnetpp::cClassDescriptor("TC_DS", "TC")
{
    propertynames = nullptr;
}

TC_DSDescriptor::~TC_DSDescriptor()
{
    delete[] propertynames;
}

bool TC_DSDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TC_DS *>(obj)!=nullptr;
}

const char **TC_DSDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TC_DSDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TC_DSDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int TC_DSDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *TC_DSDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "BWmapLength",
        "PLOAMcount",
        "HEC",
        "BWMAPs",
        "PLOAMd",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int TC_DSDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='B' && strcmp(fieldName, "BWmapLength")==0) return base+0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PLOAMcount")==0) return base+1;
    if (fieldName[0]=='H' && strcmp(fieldName, "HEC")==0) return base+2;
    if (fieldName[0]=='B' && strcmp(fieldName, "BWMAPs")==0) return base+3;
    if (fieldName[0]=='P' && strcmp(fieldName, "PLOAMd")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TC_DSDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "BWMAP_ARRAY",
        "PLOAM_ARRAY",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **TC_DSDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TC_DSDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TC_DSDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TC_DS *pp = (TC_DS *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TC_DSDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TC_DS *pp = (TC_DS *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getBWmapLength());
        case 1: return ulong2string(pp->getPLOAMcount());
        case 2: return ulong2string(pp->getHEC());
        case 3: {std::stringstream out; out << pp->getBWMAPs(); return out.str();}
        case 4: {std::stringstream out; out << pp->getPLOAMd(); return out.str();}
        default: return "";
    }
}

bool TC_DSDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TC_DS *pp = (TC_DS *)object; (void)pp;
    switch (field) {
        case 0: pp->setBWmapLength(string2ulong(value)); return true;
        case 1: pp->setPLOAMcount(string2ulong(value)); return true;
        case 2: pp->setHEC(string2ulong(value)); return true;
        default: return false;
    }
}

const char *TC_DSDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 3: return omnetpp::opp_typename(typeid(BWMAP_ARRAY));
        case 4: return omnetpp::opp_typename(typeid(PLOAM_ARRAY));
        default: return nullptr;
    };
}

void *TC_DSDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TC_DS *pp = (TC_DS *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getBWMAPs()); break;
        case 4: return (void *)(&pp->getPLOAMd()); break;
        default: return nullptr;
    }
}


