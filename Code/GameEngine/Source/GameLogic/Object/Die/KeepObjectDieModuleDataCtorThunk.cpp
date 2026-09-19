// cl: /DNDEBUG /MD /EHsc

// No intermediate class here: retail stores exactly one vtable, this class's
// own, and then constructs the member at 0x08 through an out-of-line call
// resolved by the pin for ??0InstantDeathDieMuxData@@QAE@XZ at 0x000071E4.
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
	unsigned char m_body[0x2c];
};

class KeepObjectDieModuleData : public ModuleData
{
public:
	KeepObjectDieModuleData();

	virtual void moduleDataAnchor();

	InstantDeathDieMuxData m_mux;			///< 0x08
};

// ??0KeepObjectDieModuleData@@QAE@XZ
KeepObjectDieModuleData::KeepObjectDieModuleData()
{
}
