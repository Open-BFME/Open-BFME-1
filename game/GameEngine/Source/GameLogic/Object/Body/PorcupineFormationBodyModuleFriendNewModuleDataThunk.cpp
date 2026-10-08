// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PorcupineFormationBodyModule::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class PorcupineFormationBodyModuleModuleData
{
public:
	PorcupineFormationBodyModuleModuleData();
	virtual ~PorcupineFormationBodyModuleModuleData();

private:
	unsigned char m_pad[0x60];
};

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

// Retail hands INI::initFromINIMultiProc the address of the incremental-link
// thunk 0x0044A061, not of the builder body it jumps to (0x00214140); the
// ledger owns that five-byte thunk as ?j_0004a061@@YAXXZ.  The thunk carries no
// signature of its own, so it is declared bare and cast to the EA Module.h
// buildFieldParse contract at the use.
extern "C" void __cdecl __identifier("PorcupineFormationBodyModuleFieldParse")();

typedef void (__cdecl *BuildFieldParseProc)(MultiIniFieldParse &parse);

class PorcupineFormationBodyModule
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@PorcupineFormationBodyModule@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PorcupineFormationBodyModule::friend_newModuleData(INI *ini)
{
	PorcupineFormationBodyModuleModuleData *data = new PorcupineFormationBodyModuleModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, reinterpret_cast<BuildFieldParseProc>(&__identifier("PorcupineFormationBodyModuleFieldParse")));
	return (ModuleData *)data;
}
