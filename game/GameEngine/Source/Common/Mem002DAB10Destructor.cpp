// Focused reconstruction of the pinned subobject destructor at 0x002DAB10.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc

// The +0x50 member is an attribute handle: retail destroys it through ILT
// 0x0001A401, which fronts the real AttributeHandleStandIn destructor at
// 0x0039D550, defined once in
// game/GameEngine/Source/GameLogic/Object/Update/
// AttributeHandleStandInDestructor.cpp (one handle word).
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	unsigned int m_bfmeHandle;
};

// The +0x38 and +0x44 members are twelve bytes each and retail destroys both
// through ILT 0x00026AB2. Nothing yet defines a C++ spelling that both keeps
// this reference external and reproduces retail's bytes; naming them as
// _STL::vector<AsciiString> (the real target) also emits the whole STLport
// template body here and the census then rejects four of those COMDAT copies,
// so the address-derived spelling is kept for now.
//
// Measured 2026-10-03: the only two names pinned at 0x00026AB2 that any object
// defines are ??1Gen00252DA0@@QAE@XZ (COMDAT, R5VectorDtorEHFramedMemberOffset
// .obj) and ??1?$vector@VAsciiString@@...@@QAE@XZ (COMDAT, five objects).
// Respelling the members to the first does byte-verify, but link_check then
// reports it as `selected`, not `unresolved`: those COMDAT copies are proven
// not to be retail's body. So there is no definition of this ILT in the build
// that a caller may name.
class Rva00026AB2Vec12
{
public:
	~Rva00026AB2Vec12();

private:
	unsigned int m_words[3];
};

// Retail's vftable for this subobject, 0x010CE8C0, holds a single slot and that
// slot is the scalar-deleting destructor (ILT 0x0043BAC0, which fronts
// ??_GGen_dtor_002dabe0@@UAEPAXI@Z), so retail's destructor is this class's only
// virtual and `anchor` stands in for it. The slot cannot be resolved in this
// TU: declaring `virtual ~Mem002DAB10()` does define the vector-deleting
// wrapper here (and removes the `anchor` reference), but it re-mangles the
// matched destructor from ??1Mem002DAB10@@QAE@XZ to ??1Mem002DAB10@@UAE@XZ,
// which is the name the ledger row pins. 0x010CE8C0 itself is not pinned, so
// there is no other spelling to aim at.
class Mem002DAB10
{
public:
	virtual void anchor();
	~Mem002DAB10();

private:
	unsigned char m_pad04[0x34];
	Rva00026AB2Vec12 m_38;
	Rva00026AB2Vec12 m_44;
	AttributeHandleStandIn m_50;
};

Mem002DAB10::~Mem002DAB10()
{
}
