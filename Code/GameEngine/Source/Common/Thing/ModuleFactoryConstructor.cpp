// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /D_STLP_USE_STATIC_LIB
// stlport

#define __SUBSYSTEMINTERFACE_H_
#define __SNAPSHOT_H_

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void postProcessLoad() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() {}

private:
	void *m_name;
};

class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

#include <map>
#include <vector>

class ModuleFactory : public SubsystemInterface, public Snapshot
{
public:
	ModuleFactory();
	virtual void init();
	virtual void reset() {}
	virtual void update() {}
	virtual void draw() {}
	virtual void crc(Xfer *) {}
	virtual void xfer(Xfer *) {}
	virtual void loadPostProcess() {}

private:
	class ModuleTemplate
	{
	public:
		ModuleTemplate() : m_createProc(0), m_createDataProc(0), m_data(0), m_whichInterfaces(0) {}

	private:
		void *m_createProc;
		void *m_createDataProc;
		void *m_data;
		int m_whichInterfaces;
	};

	std::map<int, ModuleTemplate> m_moduleTemplateMap;
	std::vector<const void *> m_moduleDataList;
};

ModuleFactory::ModuleFactory()
{
	m_moduleTemplateMap.clear();
	m_moduleDataList.clear();
}
