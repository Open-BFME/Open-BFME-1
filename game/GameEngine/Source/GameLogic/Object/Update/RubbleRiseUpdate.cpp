// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: RubbleRiseUpdate.cpp's copy of buildNonDupRandomIndexList,
// retail 0x002A35A0, zh_sweep packet 002a35a0.
//
// The body is the reference one unchanged. What placed it was not the code but
// the two immediates the random-value macro expands to: retail pushes the
// __FILE__ pointer of RubbleRiseUpdate.cpp and 272 for __LINE__. Four BFME
// sources carry a byte-identical copy of this helper -- StructureCollapse,
// StructureTopple, BoneFX and RubbleRise -- so the code alone cannot say which
// address belongs to which, and only those two immediates can. The neighbours
// agree: ?inList@@YA_NHHQBH@Z sits at 0x002A3570 and RubbleRiseUpdate's own
// constructor at 0x002A3640, immediately below and above this address.
//
// Its own TU because #line in a shared file renumbers everything beneath it.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

Int GetGameLogicRandomValue( Int lo, Int hi, char *file, Int line );
#define GameLogicRandomValue(lo, hi) GetGameLogicRandomValue((lo), (hi), (char *)__FILE__, __LINE__)

static Bool inList( Int value, Int count, const Int idxList[] )
{
	for( Int j = 0; j < count; ++j )
	{
		if( idxList[j] == value )
			return true;
	}
	return false;
}

// ?buildNonDupRandomIndexList@@YAXHHQAH@Z
#line 265 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\RubbleRiseUpdate.cpp"
static void buildNonDupRandomIndexList( Int range, Int count, Int idxList[] )
{
	for( Int i = 0; i < count; ++i )
	{
		Int idx;
		do
		{
			idx = GameLogicRandomValue(0, range-1);
		}
		while( inList( idx, i, idxList ) );
		idxList[i] = idx;
	}
}

// The helper is static, so retail's register convention -- range in eax and the
// list in edi -- only survives while a call site in the same TU exists to pin
// it. This is that call site.
void RubbleRiseUpdate_buildIndexList( Int range, Int count, Int idxList[] )
{
	buildNonDupRandomIndexList( range, count, idxList );
}

struct Coord3D;
class Matrix3D;
class Object;
class FXList;
class ObjectCreationList;

template <typename T> struct RubbleRiseVector
{
	const T **m_begin;
	const T **m_end;
	const T **m_capacity;

	Int size() const { return static_cast<Int>(m_end - m_begin); }
	const T *operator[]( Int index ) const { return m_begin[index]; }
};

struct RubbleRiseUpdateModuleDataLayout
{
	unsigned char m_beforeOCLs[0x54];
	RubbleRiseVector<ObjectCreationList> m_ocls[4];
	RubbleRiseVector<FXList> m_fxs[4];
	Int m_oclCounts[4];
	Int m_fxCounts[4];
};

// Retail calls go through ILT 0x00011F77 (FXList::bfmeIsBlocked, 0x0042DAA0),
// ILT 0x0001BB21 (FXList::doFXPos, 0x004280D0) and ILT 0x00002A59
// (BfmeThingFB::bfmeTellFB, 0x001D67C0); declared as those rows name them.
class FXList
{
public:
	Bool bfmeIsBlocked();
	void doFXPos( const Coord3D *, const Matrix3D *, Real, const Coord3D * ) const;
};

class BfmeThingFB
{
public:
	void bfmeTellFB( void *, void *, void *, void * );
};

enum RubbleRisePhaseType {};

class RubbleRiseUpdate
{
protected:
	void doPhaseStuff( RubbleRisePhaseType, const Coord3D * );
};

// ?doPhaseStuff@RubbleRiseUpdate@@IAEXW4RubbleRisePhaseType@@PBUCoord3D@@@Z
void RubbleRiseUpdate::doPhaseStuff( RubbleRisePhaseType phase, const Coord3D *target )
{
	const RubbleRiseUpdateModuleDataLayout *data =
		*reinterpret_cast<const RubbleRiseUpdateModuleDataLayout *const *>(
			reinterpret_cast<const char *>(this) + 4);
	Int i, idx, count, listSize;
	Int idxList[32];

	listSize = data->m_fxs[static_cast<Int>(phase)].size();
	if (listSize > 0)
	{
		count = data->m_fxCounts[static_cast<Int>(phase)];
		buildNonDupRandomIndexList( listSize, count, idxList );
		for (i = 0; i < count; ++i)
		{
			idx = idxList[i];
			const RubbleRiseVector<FXList> &fxs = data->m_fxs[static_cast<Int>(phase)];
			const FXList *fx = fxs[idx];
			if (fx != 0 && !const_cast<FXList *>(fx)->bfmeIsBlocked())
				fx->doFXPos( target, 0, 0.0f, 0 );
		}
	}

	listSize = data->m_ocls[static_cast<Int>(phase)].size();
	if (listSize > 0)
	{
		count = data->m_oclCounts[static_cast<Int>(phase)];
		buildNonDupRandomIndexList( listSize, count, idxList );
		for (i = 0; i < count; ++i)
		{
			idx = idxList[i];
			const RubbleRiseVector<ObjectCreationList> &ocls =
				data->m_ocls[static_cast<Int>(phase)];
			const ObjectCreationList *ocl = ocls[idx];
			if (ocl != 0)
			{
				reinterpret_cast<BfmeThingFB *>(const_cast<ObjectCreationList *>(ocl))->bfmeTellFB(
					*reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this) + 8),
					const_cast<Coord3D *>(target), 0, 0 );
			}
		}
	}
}
