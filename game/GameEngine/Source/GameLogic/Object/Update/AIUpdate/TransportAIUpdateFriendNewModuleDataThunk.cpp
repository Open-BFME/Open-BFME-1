// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TransportAIUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

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

// Retail's factory does not push the field-parse builder itself: at +0x4E it
// pushes VA 0x0043572E, which is the 5-byte ILT thunk RVA 0x0003572E
// (e9 1d aa 23 00 -> RVA 0x00270150, the 17-byte table-register forwarder
// ?Rva00270150@@YAXPAVGen00850920@@@Z in Common/MidTableRegisterForwarders.cpp,
// which registers the .rdata table 0x010B94F0).  The thunk is the address retail
// pushes, so the reference spells the thunk the ledger owns there; the real EA
// identity of the builder it reaches is
// ?buildFieldParse@TransportAIUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// still address-derived in the ledger.
void __cdecl j_0003572e();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h
class TransportAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@TransportAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TransportAIUpdate::friend_newModuleData(INI *ini)
{
	TransportAIUpdateModuleData *data = new TransportAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>( &j_0003572e ));
	return (ModuleData *)data;
}
