// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FadeAndDieOrnamentUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FadeAndDieOrnamentUpdateModuleData
{
public:
	FadeAndDieOrnamentUpdateModuleData();
	virtual ~FadeAndDieOrnamentUpdateModuleData();

private:
	unsigned char m_pad[0x34];
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

// The pushed immediate is 0x004318BD = the five-byte ILT thunk at 0x000318BD,
// which the ledger defines as ?j_000318bd@@YAXXZ (game/gen_small/gthunks_055.cpp)
// and which chains to the field-parse builder at 0x00124330.  Nothing defines a
// FadeAndDieOrnamentUpdateFieldParse, and naming the real builder would link
// straight to it and change the pushed immediate, so the thunk is referenced
// and the cast keeps the proc type initFromINIMultiProc declares for its
// second argument.
void __cdecl j_000318bd(void);
typedef void (__cdecl *FieldParseProc)(MultiIniFieldParse &);

class FadeAndDieOrnamentUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FadeAndDieOrnamentUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FadeAndDieOrnamentUpdate::friend_newModuleData(INI *ini)
{
	FadeAndDieOrnamentUpdateModuleData *data = new FadeAndDieOrnamentUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (FieldParseProc)&j_000318bd);
	return (ModuleData *)data;
}
