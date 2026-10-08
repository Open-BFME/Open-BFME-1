// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: OneRingPenaltyUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class OneRingPenaltyUpdateModuleData
{
public:
	OneRingPenaltyUpdateModuleData();
	virtual ~OneRingPenaltyUpdateModuleData();

private:
	unsigned char m_pad[0x20];
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
// thunk 0x0043777C, not of the builder body it jumps to (0x00298DF0); the
// ledger owns that five-byte thunk as ?j_0003777c@@YAXXZ.  The thunk carries no
// signature of its own, so it is declared bare and cast to the EA Module.h
// buildFieldParse contract at the use.
extern "C" void __cdecl __identifier("OneRingPenaltyUpdateFieldParse")();

typedef void (__cdecl *BuildFieldParseProc)(MultiIniFieldParse &parse);

class OneRingPenaltyUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@OneRingPenaltyUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OneRingPenaltyUpdate::friend_newModuleData(INI *ini)
{
	OneRingPenaltyUpdateModuleData *data = new OneRingPenaltyUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, reinterpret_cast<BuildFieldParseProc>(&__identifier("OneRingPenaltyUpdateFieldParse")));
	return (ModuleData *)data;
}
