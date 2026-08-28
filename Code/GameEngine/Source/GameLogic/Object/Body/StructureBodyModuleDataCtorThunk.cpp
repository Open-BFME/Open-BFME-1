// cl: /DNDEBUG /MD /EHsc

// A base constructed out of line, this class's vptr, then one guarded lookup.
//
// The global's string is read once into a register and every test and use works
// from that copy, which is the two inline accessors sharing a common
// subexpression. isNotEmpty is the pair of jumps to the same target -- the data
// pointer non-null and the length word at +4 non-zero -- and str() is the
// conditional that yields m_data + 8 or the empty literal.
//
// The null test inside str() is not redundant despite the guard above it: the
// accessor is a separate inline function and the compiler does not carry the
// fact across.
class FXList;

class BFMERetailAsciiString
{
public:
	const char *str(void) const { return m_data ? m_data + 8 : ""; }

	bool isNotEmpty(void) const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}

	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_head[0xAA8];
	BFMERetailAsciiString m_structureDamageFX;
};

extern GlobalData *TheGlobalData;
extern FXListStore *TheFXListStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();

	virtual ~ActiveBodyModuleData();

private:
	unsigned char m_head[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h
class StructureBodyModuleData : public ActiveBodyModuleData
{
public:
	StructureBodyModuleData();

private:
	const FXList *m_fxList;
};

// ??0StructureBodyModuleData@@QAE@XZ
StructureBodyModuleData::StructureBodyModuleData()
{
	if (TheGlobalData->m_structureDamageFX.isNotEmpty()) {
		m_fxList = TheFXListStore->findFXList(TheGlobalData->m_structureDamageFX.str());
	}
}
