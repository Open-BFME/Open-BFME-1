// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WindowLayout's nonvirtual COMDAT spelling of runShutdown.

typedef void (*WindowLayoutFunc)(void *layout, void *userData);

class WindowLayout
{
public:
	void runShutdown(void *userData);

private:
	unsigned char m_pad[0x20];
	WindowLayoutFunc m_shutdown;
};

// ?runShutdown@WindowLayout@@QAEXPAX@Z
void WindowLayout::runShutdown(void *userData)
{
	if (m_shutdown)
		m_shutdown(this, userData);
}
