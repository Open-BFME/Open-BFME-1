// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DTruckDraw::friend_newModuleData factory, retail 0x006BF4F0,
// converted out of a machine byte dump and repointed off 0x0011FAD0.
//
// The registration block pairs the AsciiString "W3DTruckDraw" with this address. The
// allocation size settles it against the row the name sat on: this body hands
// operator new 0x1C4, which is sizeof(W3DTruckDrawModuleData) with its vptr, where
// 0x0011FAD0 hands it 0xD0.
//
// The constructor is reached through link thunk 0x0003616F, landing on
// 0x0077F830.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h
class W3DTruckDrawModuleData
{
public:
	W3DTruckDrawModuleData();
	virtual ~W3DTruckDrawModuleData();

private:
	unsigned char m_pad[0x1C0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char W3DTruckDrawFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h
class W3DTruckDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@W3DTruckDraw@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *W3DTruckDraw::friend_newModuleData(INI *ini)
{
	W3DTruckDrawModuleData *data = new W3DTruckDrawModuleData;
	if (ini)
		ini->initFromINI(data, &W3DTruckDrawFieldParse);
	return (ModuleData *)data;
}
