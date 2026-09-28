// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0090BF00, complete 255-byte body ending at ret +0xfe.
// Identity: the matched W3DDebrisDraw::setAnimNames and bfmeAnimERC callers
// pass animation names and retain the returned HAnimClass pointer.
// The prefix/copy sequence is shared with matched bfmeHasVNV. The aggregate
// temporary-to-constructor expression follows matched bfmeMakeXY at 0x0090BE70.
// The registry prototype's class/virtual method names remain unknown: this
// local view records only the witnessed slots and pointer at offset 0x14.
// Its counted owner uses a 16-bit count (0x009EB7A0); the returned animation
// independently receives the retail 32-bit reference increment at offset 4.
extern "C" char *strcpy(char *, const char *);
#pragma intrinsic(strcpy)
extern void (__cdecl *g_bfmePrepVNV)(const char *);
class HAnimClass;
class Rva009EB7A0RefOwner { public: void Release_Ref(); };
class Rva009EBCE0AssetReference {
public:
    ~Rva009EBCE0AssetReference() { if (m_object) m_object->Release_Ref(); }
    Rva009EB7A0RefOwner *m_object;
};
Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *);
class Rva0090BF00Prototype {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual bool slot28(); virtual void slot2c();
    char field04[16];
    HAnimClass *field14;
};
class Gen0090BE20 {
public:
    Gen0090BE20(void *);
    ~Gen0090BE20() { if (m_object) ((Rva009EB7A0RefOwner *)m_object)->Release_Ref(); }
    Rva0090BF00Prototype *m_object;
};
HAnimClass *Get_HAnim(const char *name)
{
    char buffer[512];
    if (!name) return 0;
    strcpy(buffer, "a*");
    strcpy(buffer + 2, name);
    g_bfmePrepVNV(buffer);
    // MSVC 7.1 keeps the returned aggregate alive through this construction.
    Gen0090BE20 reference(&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(buffer));
    if (!reference.m_object) return 0;
    Rva0090BF00Prototype *prototype = reference.m_object;
    if (!prototype->slot28()) prototype->slot2c();
    if (prototype->field14) ++*(unsigned *)((char *)prototype->field14 + 4);
    return prototype->field14;
}
