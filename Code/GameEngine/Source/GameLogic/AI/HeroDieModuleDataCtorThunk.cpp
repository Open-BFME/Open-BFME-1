// cl: /DNDEBUG /MD /EHsc

// An intermediate DieModuleData base whose constructor is inlined -- it stores
// its own vptr at 0x00 and constructs the member at 0x08 through an out-of-line
// call, resolved by the existing pin for ??0InstantDeathDieMuxData@@QAE@XZ at
// 0x000071E4. This class then overwrites the vptr with its own and zeroes 0x34.
//
// ModuleData needs a declared destructor: without one MSVC emits no EH frame,
// because a throw out of the member's constructor would have nothing to unwind.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();		///< vptr at 0x00
	~ModuleData();

	int m_04;
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();
	~InstantDeathDieMuxData();

private:
	unsigned char m_body[0x2c];				///< 0x08 .. 0x34
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public ModuleData
{
public:
	DieModuleData() {}

	virtual void moduleDataAnchor();

	InstantDeathDieMuxData m_mux;			///< 0x08
};

class HeroDieModuleData : public DieModuleData
{
public:
	HeroDieModuleData();

	virtual void moduleDataAnchor();

	int m_34;								///< 0x34
};

// ??0HeroDieModuleData@@QAE@XZ
HeroDieModuleData::HeroDieModuleData()
	: m_34( 0 )
{
}
