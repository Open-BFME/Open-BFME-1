// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

class ReplacementModel
{
public:
	AsciiString m_source;
	AsciiString m_replacement;
};

class UpgradeModuleDataSub
{
public:
	~UpgradeModuleDataSub() {}

private:
	char m_padding00[0x30];
	_STL::vector<AsciiString> m_namesA;
	_STL::vector<AsciiString> m_namesB;
	_STL::vector<AsciiString> m_namesC;
	char m_padding54[0x14];
};

class SubObjectsUpgradeModuleDataPrimaryBase
{
public:
	virtual ~SubObjectsUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_moduleData;
};

class __declspec(novtable) SubObjectsUpgradeModuleDataBase
	: public SubObjectsUpgradeModuleDataPrimaryBase
{
private:
	UpgradeModuleDataSub m_upgradeData;
};

class SubObjectsUpgradeModuleData : public SubObjectsUpgradeModuleDataBase
{
public:
	virtual ~SubObjectsUpgradeModuleData();

private:
	_STL::vector<AsciiString> m_showSubObjectNames;
	_STL::vector<AsciiString> m_hideSubObjectNames;
	_STL::vector<AsciiString> m_upgradeSubObjectNames;
	_STL::vector<ReplacementModel *> m_replacementModels;
	unsigned int m_defaultConditionState;
	unsigned int m_defaultAnimationState;
	unsigned char m_showOnlySelected;
	unsigned char m_hideOnlySelected;
};

SubObjectsUpgradeModuleData::~SubObjectsUpgradeModuleData()
{
	for(_STL::vector<ReplacementModel *>::iterator it = m_replacementModels.begin();
		it != m_replacementModels.end(); ++it)
		delete *it;
	m_replacementModels.clear();
}
