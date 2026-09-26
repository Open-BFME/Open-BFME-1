// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME5: CostModifierUpgradeModuleData constructor, retail 0x002D4B30.
//
// The module registry names the data factory at 0x0011DA50 as
// CostModifierUpgrade.  That factory allocates 0x88 bytes and calls ILT
// 0x0002B062, whose only jump target is this body.  The adjacent matched
// destructor at 0x002D4C00 independently fixes the subobject layout and
// destruction order used below.

namespace _STL
{
	template <bool threads, int instance>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *memory, unsigned int bytes);
	};
}

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString() { releaseBuffer(); }
	void set(const char *text, int length);

private:
	void releaseBuffer();
	char *m_data;
};

class AttributeModifierAuraUpdateModuleDataMemberC
{
public:
	AttributeModifierAuraUpdateModuleDataMemberC();
	~AttributeModifierAuraUpdateModuleDataMemberC();

private:
	unsigned int m_handle;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_opaque[0x68];
};

class CostModifierVector
{
public:
	CostModifierVector() : m_start(0), m_finish(0), m_end(0) {}
	~CostModifierVector()
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

private:
	int *m_start;
	int *m_finish;
	int *m_end;
};

class __declspec(novtable) CostModifierUpgradeModuleDataPrimaryBase
{
public:
	virtual ~CostModifierUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

class __declspec(novtable) CostModifierUpgradeModuleDataIntermediateBase
	: public CostModifierUpgradeModuleDataPrimaryBase
{
private:
	UpgradeModuleDataSub m_sub;
};

class CostModifierUpgradeModuleData
	: public CostModifierUpgradeModuleDataIntermediateBase
{
public:
	CostModifierUpgradeModuleData();
	virtual ~CostModifierUpgradeModuleData();

private:
	AttributeModifierAuraUpdateModuleDataMemberC m_attributeModifier;
	CostModifierVector m_values;
	bool m_enabled;
	bool m_initialized;
	unsigned char m_padding[2];
	RetailLayoutString m_name;
};

// ??0CostModifierUpgradeModuleData@@QAE@XZ
CostModifierUpgradeModuleData::CostModifierUpgradeModuleData()
	: m_enabled(false)
{
	m_name.set(">UNSPECIFIED<", 13);
	m_initialized = false;
}
