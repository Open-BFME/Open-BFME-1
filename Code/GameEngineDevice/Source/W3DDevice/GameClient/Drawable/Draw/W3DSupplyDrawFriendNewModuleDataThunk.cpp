// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DSupplyDraw::friend_newModuleData factory, retail 0x006BF3E0,
// converted out of a machine byte dump and repointed off 0x00118990.
//
// The registration block pairs the AsciiString "W3DSupplyDraw" with this address. The
// allocation size settles it against the row the name sat on: this body hands
// operator new 0x160, which is sizeof(W3DSupplyDrawModuleData) with its vptr, where
// 0x00118990 hands it 0x84.
//
// The constructor is reached through link thunk 0x0001E76D, landing on
// 0x0077DD50.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
class W3DSupplyDrawModuleData
{
public:
	W3DSupplyDrawModuleData();
	virtual ~W3DSupplyDrawModuleData();

private:
	unsigned char m_pad[0x15C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DSupplyDrawFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
class W3DSupplyDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DSupplyDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DSupplyDraw::friend_newModuleData(INI *ini)
{
	W3DSupplyDrawModuleData *data = new W3DSupplyDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DSupplyDrawFieldParse);
	return (ModuleData *)data;
}
