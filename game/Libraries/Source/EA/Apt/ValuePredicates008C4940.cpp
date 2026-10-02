// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The old 217-byte scaffold consists of five 31-byte predicates separated by
// one INT3 each and a separate 57-byte case-insensitive string comparator.
struct ValuePredicates008C4940 {
    void *m_vtable;
    union {
        unsigned m_flags;
        struct { unsigned m_type:6; unsigned m_bits06:9; unsigned m_valid15:1; };
    };
    int isType8_008C4940();
    int isType5_008C4960();
    int isType4_008C4980();
    int isType6_008C49A0();
    int isType11_008C49C0();
};
int ValuePredicates008C4940::isType8_008C4940() {
    bool undefined=!m_valid15;
    if(m_type==8 && !undefined) return 1;
    return 0;
}
int ValuePredicates008C4940::isType5_008C4960() {
    bool undefined=!m_valid15;
    if(m_type==5 && !undefined) return 1;
    return 0;
}
int ValuePredicates008C4940::isType4_008C4980() {
    bool undefined=!m_valid15;
    if(m_type==4 && !undefined) return 1;
    return 0;
}
int ValuePredicates008C4940::isType6_008C49A0() {
    bool undefined=!m_valid15;
    if(m_type==6 && !undefined) return 1;
    return 0;
}
int ValuePredicates008C4940::isType11_008C49C0() {
    bool undefined=!m_valid15;
    if(m_type==11 && !undefined) return 1;
    return 0;
}
struct StringData008C49E0 { unsigned short refs,length,capacity,flags; };
extern "C" int __cdecl _strcmpi(const char *,const char *);
class StringEqual008C49E0 {
public:
    StringData008C49E0 *m_data;
    unsigned char equals(const StringEqual008C49E0 &) const;
};
unsigned char StringEqual008C49E0::equals(const StringEqual008C49E0 &other) const {
    if(m_data->length != other.m_data->length) return false;
    if(m_data == other.m_data) return true;
    return _strcmpi((const char *)(m_data+1),(const char *)(other.m_data+1))==0;
}
