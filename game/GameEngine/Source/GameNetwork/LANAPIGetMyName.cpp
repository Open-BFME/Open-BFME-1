// cl: /DNDEBUG /MD /EHsc
// LANAPI::GetMyName, RVA685660,32B. The actual LANAPI vtable111AF50 slot47
// points through ILT15D4D to this body. It copies the Unicode name at+10
// through StringBase<unsigned short>888400. Former canonical4C7970 belongs
// to DownloadManager::getErrorString; its caller establishes that separate owner.
template<class T> class StringBase {
    friend class UnicodeString;
private:
    StringBase(const StringBase<T>&);
    ~StringBase();
    void *data;
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString(const UnicodeString& other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};
class LANAPI {
public:
    virtual UnicodeString GetMyName();
private:
    char preceding[0xC];
    UnicodeString m_name;
};
UnicodeString LANAPI::GetMyName() { return m_name; }
