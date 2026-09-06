// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// Destructor lifted from its MASM dump to C++, retail 0x0020F8E0, 178 bytes.
//
// Fuzzy twin of PhysicsBehaviorDestructorThunk.cpp (0x0029AA30, 172 B): same
// UpdateModule chain shape (a class-specific vptr at +0x00/+0x0C/+0x10, a
// single std::vector<12-byte-POD> member torn down inline, then the same
// three vptrs re-installed -- the shared BehaviorModule/PB_Iface1 constants
// 0x0109CB5C/0x0109CA98 at +0x00/+0x0C match the twin exactly, only the
// class-specific +0x10 value (0x010A7418) differs -- before chaining to the
// same pinned base dtor ??1BFU_DeepBase@@UAE@XZ @ 0x00047C53). The only
// difference from the twin is the vector's offset (this+0xC0 instead of
// +0x20) and the class-specific initial vtable set (0x010A78B0/0x010A77E8/
// 0x010A7718).
//
// Landed neighbours getClassMemoryPool@ActiveBody (0x0020F9C0) and
// ActiveBodyModuleData ctor (0x0020F7C0) sit immediately either side of this
// row, but no caller names this destructor directly, so the class is spelled
// address-derived rather than asserted as ActiveBody itself.

#include <vector>

class ModuleData;
class Object;

class Rva0020F8E0_DeepBase
{
public:
	virtual ~Rva0020F8E0_DeepBase();		// retail 0x00047C53, pinned ??1BFU_DeepBase@@UAE@XZ

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class Rva0020F8E0_Iface1 { public: virtual void slot(); };
class Rva0020F8E0_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public Rva0020F8E0_DeepBase, public Rva0020F8E0_Iface1
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public Rva0020F8E0_Iface2
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

struct Gen_p12pod { int a[3]; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class Rva0020F8E0Owner : public UpdateModule
{
public:
	virtual ~Rva0020F8E0Owner();

private:
	unsigned char m_unreconstructed_20[0xa0];
	std::vector<Gen_p12pod> m_vector;			///< retail this+0xC0
};

// ?d_0020f8e0@@YAXXZ
Rva0020F8E0Owner::~Rva0020F8E0Owner()
{
}
