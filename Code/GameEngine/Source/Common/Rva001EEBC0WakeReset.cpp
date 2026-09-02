// Open-BFME5: clean C++ conversion of the indefinite wake-frame reset.

class Object;

class UpdateModule
{
public:
	void resetWakeState();

protected:
	void setWakeFrame(Object *object, unsigned int frame);

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0C[0x20];
	unsigned int m_wakeFrame;
	bool m_isAwake;
};

void UpdateModule::resetWakeState()
{
	m_isAwake = true;
	m_wakeFrame = 0x3FFFFFFF;
	setWakeFrame(m_object, 0x3FFFFFFF);
}
