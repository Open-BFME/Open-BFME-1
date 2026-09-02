class BfmeRecordSet
{
public:
	void bfmeAssign(void *records);

private:
	char m_bfmeFields[0x4C];
};

class Object;

class UpdateModule
{
protected:
	void setWakeFrame(Object *object, unsigned int frame);
};

class Gen_0028BFF0 : public UpdateModule
{
public:
	void bfmeSetup(int mode, void *records, unsigned int wakeFrame,
		int value, unsigned char enabled, unsigned char pending);

private:
	char m_bfmeFields[0x20];
	int m_bfmeMode;
	BfmeRecordSet m_bfmeRecords;
	int m_bfmeValue;
	unsigned char m_bfmeEnabled;
	unsigned char m_bfmePending;
};

// ?bfmeSetup@Gen_0028BFF0@@QAEXHPAXIHEE@Z
void Gen_0028BFF0::bfmeSetup(int mode, void *records, unsigned int wakeFrame,
	int value, unsigned char enabled, unsigned char pending)
{
	m_bfmeMode = mode;
	m_bfmeRecords.bfmeAssign(records);
	m_bfmeValue = value;
	m_bfmeEnabled = enabled;
	m_bfmePending = pending;

	if (!(wakeFrame > 0))
		wakeFrame = 1;

	setWakeFrame(*reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 8), wakeFrame);
}
