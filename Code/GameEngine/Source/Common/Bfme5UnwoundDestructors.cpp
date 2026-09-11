// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION 1
#include "PreRTS.h"
#include <vector>

// The retail byte-vector teardown evaluates the capacity delta before testing
// the start pointer.  Keep that source-level order explicit; STLport's vector
// base destructor tests the pointer first and therefore emits a different
// schedule for these five one-byte buffers.
class BfmeDtorByteVector
{
public:
	~BfmeDtorByteVector(void)
	{
		unsigned char *start = m_start;
		size_t bytes = m_end_of_storage - m_start;
		if (start != 0) {
			_STL::allocator<unsigned char> allocator;
			allocator.deallocate(start, bytes);
		}
	}

private:
	unsigned char *m_start;
	unsigned char *m_finish;
	unsigned char *m_end_of_storage;
};

// Five destructors over a base whose own destructor folds in.
//
// Each body is empty in source. What it emits is a full unwind frame -- the
// -1 trylevel, the scope table, the linked fs:[0] record -- because the member
// at +0x0C has a destructor that must run if anything above throws; the state
// word going -1 to 0 is that member becoming live.
//
// The two vftable stores are the two destructors: the derived one on entry and
// the base one on exit, the latter inlined because the base destructor is
// defined in its own class body. Twelve bytes of base -- vptr plus two fields
// -- is what puts the member at +0x0C.


class BfmeDtorMemberA
{
public:
	~BfmeDtorMemberA(void);				// retail 0x00836300

private:
	_STL::vector<ICoord2D> m_vectors0[14];
	_STL::vector<ICoord2D> m_vectorsA8[24];
	_STL::vector<ICoord2D> m_vectors1C8[2];
	BfmeDtorByteVector m_vector1E0;
	BfmeDtorByteVector m_vector1EC;
	BfmeDtorByteVector m_vector1F8;
	BfmeDtorByteVector m_vector204;
	BfmeDtorByteVector m_vector210;
};

class BfmeDtorMemberB
{
public:
	~BfmeDtorMemberB(void);				// retail 0x0000B109

private:
	int m_bfmeValue;
};

template <int RetailCopy>
class BfmeDtorBase
{
public:
	virtual ~BfmeDtorBase(void) {}

private:
	int m_bfmeFields[2];					// +0x04
};

class Gen_00837480 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_00837480(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_008374F0 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_008374F0(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_00837560 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_00837560(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_008375D0 : public BfmeDtorBase<0>
{
public:
	virtual ~Gen_008375D0(void);

private:
	BfmeDtorMemberA m_bfmeMember;				// +0x0C
};

class Gen_009D9C00 : public BfmeDtorBase<1>
{
public:
	virtual ~Gen_009D9C00(void);

private:
	BfmeDtorMemberB m_bfmeMember;				// +0x0C
};

BfmeDtorMemberA::~BfmeDtorMemberA(void)
{
}

// ??1Gen_00837480@@UAE@XZ
Gen_00837480::~Gen_00837480(void)
{
}

// ??1Gen_008374F0@@UAE@XZ
Gen_008374F0::~Gen_008374F0(void)
{
}

// ??1Gen_00837560@@UAE@XZ
Gen_00837560::~Gen_00837560(void)
{
}

// ??1Gen_008375D0@@UAE@XZ
Gen_008375D0::~Gen_008375D0(void)
{
}

// ??1Gen_009D9C00@@UAE@XZ
Gen_009D9C00::~Gen_009D9C00(void)
{
}
