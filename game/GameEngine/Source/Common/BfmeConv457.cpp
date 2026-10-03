class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
enum UpdateSleepTime;

class BfmeThingBHA;

// Declaration only: the spelling of the reference this call site makes. The
// definition is UpdateModule.cpp's body at 0x002B2040, which this TU does not
// include; retail encodes the call through its ILT thunk 0x000157DA. The member
// is protected upstream ('I' in the mangled name), so friendship keeps the
// access check satisfied without inventing an inheritance.
class UpdateModule
{
	friend class BfmeThingBHA;

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class BfmeThingBHA
{
public:
	void bfmeGoBHA(void *what);
	unsigned char m_bfmeHead[8];
	void *m_bfmeSub;
	unsigned char m_bfmeGap[0x14];
	void *m_bfmeSaved;
};

void BfmeThingBHA::bfmeGoBHA(void *what)
{
	m_bfmeSaved = what;
	reinterpret_cast<UpdateModule *>(this)->setWakeFrame(
		static_cast<Object *>(m_bfmeSub), static_cast<UpdateSleepTime>(1));
}