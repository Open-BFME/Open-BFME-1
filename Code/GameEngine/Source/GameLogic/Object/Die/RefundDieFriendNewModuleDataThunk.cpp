// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RefundDie::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RefundDieModuleData
{
public:
	RefundDieModuleData();
	virtual ~RefundDieModuleData();

private:
	unsigned char m_pad[0x3c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RefundDieFieldParse;

class RefundDie
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RefundDie@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RefundDie::friend_newModuleData(INI *ini)
{
	RefundDieModuleData *data = new RefundDieModuleData;
	if (ini)
		ini->initFromINI(data, &RefundDieFieldParse);
	return (ModuleData *)data;
}
