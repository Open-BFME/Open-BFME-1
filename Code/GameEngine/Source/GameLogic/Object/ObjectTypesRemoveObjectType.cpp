// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves

// ObjectTypes::removeObjectType (retail 0x001DC470, 104 bytes).
// Identity: ScriptEngine::doObjectTypeListMaintenance (0x0034E370) calls it
// through ILT 0x000014C4; the ObjectTypes +0x08 vector overlay is the one the
// matched isInSet (0x001DC2D0) and addObjectType (0x001DC520) use.
// Source: the Zero Hour body as written (GeneralsMD ObjectTypes.cpp).  isInSet
// is defined in this TU so VC7.1 inlines it and, seeing both __find bodies,
// keeps m_finish in a register across the two find calls exactly as retail.

#include "PreRTS.h"
#include "GameLogic/ObjectTypes.h"

// The vendored GeneralsMD AsciiString destructor is a fully inline refcount
// decrement (Common/AsciiString.h); BFME's is out of line.  Route the erase's
// element destructor through the established ??1BFMERetailAsciiString alias
// (reverse/symbols.csv, VA 0x0000D828) so it stays one call, as at retail+0x5c.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString();
private:
	void *m_data;
};

// vector::erase's element copy goes through ILT 0x000485EF to the four-byte
// __copy body at 0x000653C0, whose identity the ledger holds only by address.
extern void j_000485ef();

static __forceinline void bfmeCopyObjectTypes(
	AsciiString *first, AsciiString *last, AsciiString *result,
	const _STL::random_access_iterator_tag &tag)
{
	typedef AsciiString *(*Function)(AsciiString *, AsciiString *,
		AsciiString *, const _STL::random_access_iterator_tag &, int *);
	union { void (*raw)(void); Function call; } fn;
	fn.raw = j_000485ef;
	fn.call(first, last, result, tag, 0);
}

// STLport 4.5.3 vector<AsciiString>::erase(iterator), inlined as retail does,
// with BFME's out-of-line element destructor.  Deriving reaches the real
// _Vector_base members; only the erase is supplied here.
struct BFMEObjectTypesVec : public std::vector<AsciiString>
{
	AsciiString *erase(AsciiString *pos)
	{
		if (pos + 1 != end())
			bfmeCopyObjectTypes(pos + 1, _M_finish, pos, _STL::random_access_iterator_tag());
		--_M_finish;
		((BFMERetailAsciiString *)_M_finish)->~BFMERetailAsciiString();
		return pos;
	}
};

//-------------------------------------------------------------------------------------------------
Bool ObjectTypes::isInSet(const AsciiString& objectType) const
{
	// m_objectTypes starts at ObjectTypes+0x08 in BFME; this tree lands it at
	// +0x0c (see ObjectTypes.cpp).  The overlay has to be function-local:
	// AsciiStringVec is a nested typedef and does not name at file scope.
	struct BFMEObjectTypes { char pad[0x08]; AsciiStringVec m_objectTypes; };
	const BFMEObjectTypes *self = (const BFMEObjectTypes *)this;
	return (std::find(self->m_objectTypes.begin(), self->m_objectTypes.end(), objectType) != self->m_objectTypes.end());

}

//-------------------------------------------------------------------------------------------------
void ObjectTypes::removeObjectType(const AsciiString &objectType)
{
	// same +0x08 overlay as isInSet above
	struct BFMEObjectTypes { char pad[0x08]; BFMEObjectTypesVec m_objectTypes; };
	BFMEObjectTypes *self = (BFMEObjectTypes *)this;
	if (!isInSet(objectType)) {
		DEBUG_CRASH(("Attempted to remove '%s' from '%s', but it wasn't there.", objectType.str(), m_listName.str()));
		return;
	}

	AsciiStringVec::iterator it = std::find(self->m_objectTypes.begin(), self->m_objectTypes.end(), objectType);

	self->m_objectTypes.erase(it);
}
