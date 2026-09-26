// Retail 0x00493FF0/125: three-argument thiscall (ret 0x0c), full EAX
// result, events 1/2/29. Matched assignment 0x00493FC0 proves the 16-byte
// message at +0x254; matched finishTransition 0x00493EA0 proves the owner
// and enabled flag +0x264. Calls on the embedded controller +0x218 use
// vtable slots +0x04 and +0x10. Names remain address-derived structural views.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

struct Rva00493FC0Message
{
	unsigned int m_words[4];

	Rva00493FC0Message &operator=(const Rva00493FC0Message &that);
};

class Rva00493FF0Controller
{
public:
	virtual void slot0();
	virtual void handleFirst();
	virtual void slot2();
	virtual void slot3();
	virtual void handleSecond();
};

class Rva00493F30TransitionState
{
public:
	int handleTransitionEvent(unsigned int event, unsigned int value,
		const Rva00493FC0Message *message);
	void finishTransition();

private:
	unsigned char m_padding0[0x218];
	Rva00493FF0Controller m_controller;
	unsigned char m_padding21C[0x38];
	Rva00493FC0Message m_message;
	bool m_enabled;
};

int Rva00493F30TransitionState::handleTransitionEvent(unsigned int event,
	unsigned int value, const Rva00493FC0Message *message)
{
	switch (event) {
		default:
			return false;
		case 29:
			if (value != 1000)
				return false;
			if (message != 0) {
				m_message = *message;
				m_enabled = true;
				finishTransition();
			}
			return true;
		case 2:
			m_controller.handleSecond();
			return true;
		case 1:
			m_controller.handleFirst();
			return true;
	}
}
