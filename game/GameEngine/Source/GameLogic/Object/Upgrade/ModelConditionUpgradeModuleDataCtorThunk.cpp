// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionUpgrade module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0011DD90 allocates 0xC0
// bytes and calls this constructor. Its matched destructor at 0x002D6B20
// independently fixes the UpgradeModuleData subobject at +0x08. The remaining
// eighty bytes are the two adjacent ten-word model-condition masks.

#include <string.h>

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_data[ 0x68 ];
};

class ModelConditionFlags
{
public:
	ModelConditionFlags()
	{
		memset( m_words, 0, sizeof( m_words ) );
	}

	void clear()
	{
		memset( m_words, 0, sizeof( m_words ) );
	}

private:
	unsigned int m_words[ 10 ];
};

class __declspec(novtable) ModelConditionUpgradeModuleDataPrimaryBase
{
public:
	virtual ~ModelConditionUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_moduleData;
};

class __declspec(novtable) ModelConditionUpgradeModuleDataIntermediateBase
	: public ModelConditionUpgradeModuleDataPrimaryBase
{
protected:
	UpgradeModuleDataSub m_upgradeData;
};

class ModelConditionUpgradeModuleData
	: public ModelConditionUpgradeModuleDataIntermediateBase
{
public:
	ModelConditionUpgradeModuleData();
	virtual ~ModelConditionUpgradeModuleData();

private:
	ModelConditionFlags m_conditionFlag;
	ModelConditionFlags m_forbiddenConditionFlag;
};

// ??0ModelConditionUpgradeModuleData@@QAE@XZ
ModelConditionUpgradeModuleData::ModelConditionUpgradeModuleData()
{
	m_conditionFlag.clear();
	m_forbiddenConditionFlag.clear();
}
