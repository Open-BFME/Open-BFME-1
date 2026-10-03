// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Constructor paired with the polymorphic member destructor at retail
// 0x004B1670. The last member is the inline BFME buffer constructor.

// Retail's base here is SubsystemInterface: the constructor at 0x004B18B0
// calls 0x009A1A30 (??0SubsystemInterface@@QAE@XZ) and Gen_004B1670's vtable
// at 0x010FD1D8 inherits slots 2, 3, 6, 7 and 8 of SubsystemInterface's own
// vtable at 0x01141640 unchanged. Use the real header, not a stand-in base.
#include "PreRTS.h"
#include "System/subsystem_interface.h"

// Retail's buffer allocation at 0x0082E540 is STLport's __new_alloc::allocate,
// matched in game/Libraries/Source/WWVegas/WWLib/STL_new_alloc_allocateThunk.cpp
// (ledgered under both its own name and the ICF twin
// ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z).  Same cdecl shape as the
// old local shim, so the call site keeps its single pushed argument.
//
// The declaration below is deliberately TU-local and does NOT include
// <stl/_alloc.h>: STLport's own __new_alloc::allocate is an inline body
// (__stl_new -> operator new), so pulling the real header in would collapse
// this call to ??2@YAPAXI@Z and lose the retail identity, and it would also
// collide with the class this file declares (C2011).
namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate( unsigned int n );
	};
}

struct BfmeTailT
{
	BfmeTailT(unsigned int bytes)
	{
		m_bfmeData = 0;
		m_bfmeData = (char *)_STL::__new_alloc::allocate(bytes);
		m_bfmeLength = 0;
		m_bfmeData[0] = 0;
		*(int *)(m_bfmeData + 4) = 0;
		*(char **)(m_bfmeData + 8) = m_bfmeData;
		*(char **)(m_bfmeData + 12) = m_bfmeData;
	}
	~BfmeTailT(void);

	char *m_bfmeData;
	int m_bfmeLength;
};

// The +0x0C member is STLport's vector storage in retail: the ctor's unwind
// state 1 (tools/eh_info.py 0x004B18B0) destroys this+0x0C through ILT
// 0x0042905A to 0x004835A0, whose only real definition is the matched
// ??1?$_Vector_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ at 0x0081D920
// (game/Libraries/Source/WWVegas/WWLib/stlport_vector_base_int_dtor.cpp;
// 0x004835A0 is its ICF twin, ledgered as tg_004835a0).  The member is spelled
// as STLport's own _Vector_base<int> through a TU-local minimal declaration:
// pulling <vector> would drag in stl/_alloc.h whose __new_alloc collides with
// the declaration above (C2011) and would inline the allocate call below to
// operator new, so both shims stay local.
//
// The local view follows the vendor header (inputs/vendor/stlport/stl/
// _vector.h and _alloc.h): _Vector_base<T, A> holds _M_start, _M_finish and
// the _STLP_alloc_proxy<T *, T, A> _M_end_of_storage, whose own user-provided
// constructor is what makes the proxy a constructed subobject.  That is not
// cosmetic: retail's constructor writes its EH state word
// (`mov [esp+0x14], ebx`, between the second and third zero store of the
// member) exactly where MSVC 7.1 puts it for that shape.  Flattening the proxy
// into a plain pointer member moves the state word ahead of all three stores
// and no longer matches retail, so the proxy stays.
//
// Two deliberate deviations from the header, neither of which changes the
// class layout or the destructor this file calls:
//   - the constructor takes no allocator and supplies _Alloc() itself, so its
//     COMDAT is ??0?$_Vector_base@HV?$allocator@H@_STL@@@_STL@@QAE@XZ. The
//     header's own (const _Alloc &) instantiation is defined by
//     stlport_vector_base_int_dtor.cpp with different bytes; a shared name
//     would be a COMDAT conflict at link time.
//   - the destructor is declared, not defined: the body is the matched one in
//     stlport_vector_base_int_dtor.cpp, which this file must not redefine.
namespace _STL
{
	template<class _Tp> class allocator
	{
	};

	template<class _Value, class _Tp, class _MaybeReboundAlloc>
	class _STLP_alloc_proxy : public _MaybeReboundAlloc
	{
	public:
		_STLP_alloc_proxy(const _MaybeReboundAlloc &__a, _Value __p) : _M_data(__p)
		{
		}

		_Value _M_data;
	};

	template<class _Tp, class _Alloc> class _Vector_base
	{
	public:
		_Vector_base() :
			_M_start(0),
			_M_finish(0),
			_M_end_of_storage(_Alloc(), 0)
		{
		}
		~_Vector_base();

	protected:
		_Tp *_M_start;
		_Tp *_M_finish;
		_STLP_alloc_proxy<_Tp *, _Tp, _Alloc> _M_end_of_storage;
	};
}

class Gen_004B1670 : public SubsystemInterface
{
public:
	Gen_004B1670(void);
	virtual ~Gen_004B1670(void);

private:
	char m_bfme08;
	_STL::_Vector_base<int, _STL::allocator<int> > m_bfmeVector;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	BfmeTailT m_bfmeBuffer;
};

// ??0Gen_004B1670@@QAE@XZ
Gen_004B1670::Gen_004B1670(void) :
	SubsystemInterface(),
	m_bfme08(0),
	m_bfmeVector(),
	m_bfme18(0),
	m_bfme1c(0),
	m_bfme30(0),
	m_bfme34(0),
	m_bfme38(0),
	m_bfme3c(0),
	m_bfme40(0),
	m_bfmeBuffer(0x18)
{
}
