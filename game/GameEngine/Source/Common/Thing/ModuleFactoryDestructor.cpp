// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ??1ModuleFactory@@UAE@XZ: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp
//
// ModuleFactory::~ModuleFactory, retail 0x00128FA0, 273 bytes. Its entry stamps
// ModuleFactory's own two vftables (0x0108ECE0 for SubsystemInterface at +0,
// 0x0108ECCC for Snapshot at +8), and the matched constructor sits just before
// it at 0x00128E30. The body is Zero Hour's verbatim: clear the template map,
// delete every ModuleData in the list, clear the list; then the members and
// the two bases go in reverse order.
//
// This lives apart from ModuleFactory.cpp because that TU's STLport set-up
// routes the vector's deallocation through an import and destroys Snapshot out
// of line, where retail inlines both.

#include <map>
#include <vector>

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
#include "../../../Include/Common/NameKeyType.h"
class Thing;
class Module;
class INI;
class Xfer;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
// BFME's ModuleData keeps its virtual destructor in the first slot.
class ModuleData
{
public:
	virtual ~ModuleData();
};

typedef Module *(*NewModuleProc)(Thing *thing, const ModuleData *moduleData);
typedef ModuleData *(*NewModuleDataProc)(INI *ini);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void postProcessLoad();
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	AsciiString m_name;				// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	virtual ~Snapshot() {}

protected:
	virtual void crc( Xfer *xfer ) = 0;
	virtual void xfer( Xfer *xfer ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleFactory : public SubsystemInterface, public Snapshot
{
public:
	ModuleFactory( void );
	virtual ~ModuleFactory( void );

	virtual void init( void );
	virtual void reset( void ) { }
	virtual void update( void ) { }

protected:
	class ModuleTemplate
	{
	public:
		ModuleTemplate();

		NewModuleProc m_createProc;
		NewModuleDataProc m_createDataProc;
		int m_unreconstructed08;			// BFME-only, +0x08
		int m_whichInterfaces;				// +0x0C (ModuleFactory.cpp, findModuleInterfaceMask)
	};

	typedef std::map< NameKeyType, ModuleTemplate, std::less<NameKeyType> > ModuleTemplateMap;
	typedef std::vector< const ModuleData * > ModuleDataList;

	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	ModuleTemplateMap m_moduleTemplateMap;		// +0x0C
	ModuleDataList m_moduleDataList;		// +0x18
};

ModuleFactory::~ModuleFactory( void )
{
	m_moduleTemplateMap.clear();

	for (ModuleDataList::iterator i = m_moduleDataList.begin(); i != m_moduleDataList.end(); ++i)
	{
		const ModuleData* data = *i;
		delete data;
	}
	m_moduleDataList.clear();

}
