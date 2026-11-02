// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FreezingRainSpecialPowerModuleData scalar deleting destructor.
// The constructor installs vtable 0x010B5128; slot zero reaches this wrapper
// through ILT 0x0000B1D6.  The wrapped destructor is the empty derived
// destructor over SpecialPowerModuleData.

class __declspec(novtable) SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_data[ 0x20c ];
};

class FreezingRainSpecialPowerModuleData : public SpecialPowerModuleData
{
	friend void forceFreezingRainSpecialPowerModuleDataDeletingDestructorCopy(const FreezingRainSpecialPowerModuleData &that);
public:
	__declspec(noinline) virtual ~FreezingRainSpecialPowerModuleData();

private:
	float m_duration;
	unsigned int m_weatherType;
};

// ~FreezingRainSpecialPowerModuleData is matched out of line (SpecialPowerModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceFreezingRainSpecialPowerModuleDataDeletingDestructorCopy(const FreezingRainSpecialPowerModuleData &that)
{
	FreezingRainSpecialPowerModuleData value(that);
}
