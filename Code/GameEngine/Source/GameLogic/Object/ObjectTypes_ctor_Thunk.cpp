// cl: /DNDEBUG /MD /EHsc
// Open-BFME: lift the gen-asm dump for ObjectTypes::ObjectTypes() (GameLogic/Object/ObjectTypes.cpp)
// to a standalone C++ thunk.
//
// reverse/symbols.csv already pins address 0x0003D415 (the 5-byte gen-thunk
// `?j_0003d415@@YAXXZ`, whose ghidra note reads target=FUN_005dc220, i.e. RVA
// 0x001DC220) to ??0ObjectTypes@@QAE@XZ, noting it is "pin for ObjectTypesTemp
// ctor callee (packet 002ed6c0)". ObjectTypesTemp::ObjectTypesTemp() (already
// matched -- see ObjectTypesTemp_ctor_Thunk.cpp) does `m_types = new ObjectTypes;`,
// and the sole call after that allocation is to this constructor: callers_of.py
// 0x001dc220 shows ??0ObjectTypesTemp@@QAE@XZ as its one and only named caller.
//
// GameLogic/ObjectTypes.h (ZH reference) declares
//     class ObjectTypes : public MemoryPoolObject, public Snapshot { ... };
// with data members AsciiString m_listName (4 bytes) and a
// std::vector<AsciiString> m_objectTypes (3 pointers, 12 bytes). MemoryPoolObject
// contributes exactly one vtable slot in BFME -- its virtual destructor -- and
// retail installs only ONE vftable here (see docs/lessons-archive.md's "A vtable
// slot belongs to the class that DECLARES the virtual" / MemoryPoolObject entry):
// Snapshot's crc/xfer/loadPostProcess slots land in that same vtable rather than
// a second base-subobject pointer. Total object size is one vptr + 4 zeroed data
// words = 20 bytes, matching the caller's `push 0x14` allocation (see
// ObjectTypesTemp_ctor_Thunk.cpp's comment on the same allocation size).
//
// A local minimal replica keeps that shape without pulling in the project's own
// AsciiString/vector<AsciiString> ABI: Code/GameEngine/Source/GameLogic/Object/
// ObjectTypes.cpp already carries the real ZH class body for this constructor
// under a `present-unmatched` marker, but compiling it under this repo's own
// stlport/AsciiString headers currently produces a wider vector<AsciiString> (one
// readable body of ??0ObjectTypes@@: Code/GameEngine/Source/GameLogic/Object/ObjectTypes.cpp
// extra data word) and an out-of-line AsciiString call retail does not have, so
// it is not the byte-exact source yet. Four plain zero-initialized pointer-sized
// members reproduce retail's exact "xor ecx,ecx; mov [x+N],ecx" sequence without
// depending on that unresolved layout question.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectTypes.h
class ObjectTypes
{
public:
    ObjectTypes();
    virtual ~ObjectTypes() {}
private:
    void *m_listName;
    void *m_objTypesBegin;
    void *m_objTypesEnd;
    void *m_objTypesCap;
};

// ??0ObjectTypes@@QAE@XZ
ObjectTypes::ObjectTypes()
    : m_listName(0)
    , m_objTypesBegin(0)
    , m_objTypesEnd(0)
    , m_objTypesCap(0)
{
}
