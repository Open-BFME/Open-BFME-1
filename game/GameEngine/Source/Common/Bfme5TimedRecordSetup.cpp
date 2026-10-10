// Retail ILT 0x00011DB0 -> 0x0028BDF0, the matched record-set assignment
// (Rva0028BDF0RecordCopy.cpp); only the first 0x4C bytes are laid out here.
class Rva0028BDF0Object
{
public:
	Rva0028BDF0Object &operator=(const Rva0028BDF0Object &other);

private:
	char m_bfmeFields[0x4C];
};

class Object;
enum UpdateSleepTime;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
};

class Gen_0028BFF0 : public UpdateModule
{
public:
	void bfmeSetup(int mode, void *records, unsigned int wakeFrame,
		int value, unsigned char enabled, unsigned char pending);

private:
	char m_bfmeFields[0x20];
	int m_bfmeMode;
	Rva0028BDF0Object m_bfmeRecords;
	int m_bfmeValue;
	unsigned char m_bfmeEnabled;
	unsigned char m_bfmePending;
};

// ?bfmeSetup@Gen_0028BFF0@@QAEXHPAXIHEE@Z
void Gen_0028BFF0::bfmeSetup(int mode, void *records, unsigned int wakeFrame,
	int value, unsigned char enabled, unsigned char pending)
{
	m_bfmeMode = mode;
	m_bfmeRecords = *static_cast<Rva0028BDF0Object *>(records);
	m_bfmeValue = value;
	m_bfmeEnabled = enabled;
	m_bfmePending = pending;

	if (!(wakeFrame > 0))
		wakeFrame = 1;

	setWakeFrame(*reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 8),
		static_cast<UpdateSleepTime>(wakeFrame));
}
