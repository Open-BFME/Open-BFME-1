// cl: /DNDEBUG /MD /EHsc
// stlport
// Five-member destructor at retail 0x002D4C00.

class Gen002D4C00Vector;

// STLport's free-list node allocator.  Retail's out-of-line body for
// _M_deallocate is matched as
// ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z from
// game/Libraries/Source/WWVegas/WWLib/node_alloc_M_deallocateThunk.cpp: the
// <true, 0> instantiation of a template whose _M_deallocate is private, exactly
// as _alloc.h declares it.  The vector destructor is the friend that inlines
// the public deallocate() and calls through to it.
namespace _STL
{
	template <bool threads, int instance>
	class __node_alloc
	{
		friend class ::Gen002D4C00Vector;

		static void _M_deallocate(void *memory, unsigned int bytes);
	};
}

class BFMERetailAsciiString
{
public:
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

// The four-byte member at +0x70: retail calls retail RVA 0x0039D550 from this
// destructor, matched as AttributeHandleStandIn, so the member is spelled with
// that class's own name here.
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	unsigned char m_pad[4];
};

class UpgradeModuleDataSub
{
public:
	~UpgradeModuleDataSub();

private:
	unsigned char m_opaque[0x68];
};

class CostModifierUpgradeModuleDataPrimaryBase
{
public:
	virtual ~CostModifierUpgradeModuleDataPrimaryBase()
	{
	}

private:
	unsigned int m_04;
};

class __declspec(novtable) CostModifierUpgradeModuleDataIntermediateBase
	: public CostModifierUpgradeModuleDataPrimaryBase
{
	UpgradeModuleDataSub m_sub;
};

class Gen002D4C00Vector
{
public:
	__forceinline ~Gen002D4C00Vector()
	{
		if (m_start != 0)
		{
			unsigned int bytes = static_cast<unsigned int>((m_end - m_start) * 4);
			if (bytes > 0x80)
				::operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

	int *m_start;
	int *m_finish;
	int *m_end;
};

class __declspec(novtable) CostModifierUpgradeModuleData
	: public CostModifierUpgradeModuleDataIntermediateBase
{
public:
	virtual ~CostModifierUpgradeModuleData();

private:
	AttributeHandleStandIn m_memberC;
	Gen002D4C00Vector m_vector;
	unsigned char m_flags[4];
	BFMERetailAsciiString m_string;
};

// ??1CostModifierUpgradeModuleData@@UAE@XZ
CostModifierUpgradeModuleData::~CostModifierUpgradeModuleData()
{
}
