// cl: /DNDEBUG /MD /EHsc
// stlport
// Five-member destructor at retail 0x002D4C00.

namespace _STL
{
	template <bool threads, int instance>
	class __node_alloc
	{
	public:
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

class AttributeModifierAuraUpdateModuleDataMemberC
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberC();

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
				_STL::__node_alloc<false, 0>::_M_deallocate(m_start, bytes);
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
	AttributeModifierAuraUpdateModuleDataMemberC m_memberC;
	Gen002D4C00Vector m_vector;
	unsigned char m_flags[4];
	BFMERetailAsciiString m_string;
};

// ??1CostModifierUpgradeModuleData@@UAE@XZ
CostModifierUpgradeModuleData::~CostModifierUpgradeModuleData()
{
}
