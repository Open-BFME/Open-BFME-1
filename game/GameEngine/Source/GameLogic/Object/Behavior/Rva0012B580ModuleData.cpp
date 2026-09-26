// cl: /DNDEBUG /MD /EHsc

#include <string.h>

class __declspec(novtable) Rva0012B580PrimaryBase
{
public:
	virtual void primarySlot();

private:
	int m_primaryData;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char m_upgradeData[0x68];
};

struct Rva0012B580Vector
{
	float x;
	float y;
	float z;
};

class Rva0012B580ModuleData : public Rva0012B580PrimaryBase, public UpgradeModuleDataSub
{
public:
	Rva0012B580ModuleData();
	virtual void primarySlot();

private:
	Rva0012B580Vector m_first;
	Rva0012B580Vector m_second;
};

Rva0012B580ModuleData::Rva0012B580ModuleData()
{
	memset(&m_first, 0, sizeof(m_first));
	memset(&m_second, 0, sizeof(m_second));
}
