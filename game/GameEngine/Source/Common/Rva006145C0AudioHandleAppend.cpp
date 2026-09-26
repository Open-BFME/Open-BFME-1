// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

class ClientSubsystem
{
public:
	virtual ~ClientSubsystem();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual unsigned int addAudioEvent(void *event);
};

extern ClientSubsystem *TheAudioClientUpdate;

class Rva006145C0Owner
{
public:
	void addAudioHandle(void *event);

private:
	char m_head[0x298];
	_STL::vector<unsigned int> m_handles;
};

void Rva006145C0Owner::addAudioHandle(void *event)
{
	m_handles.push_back(TheAudioClientUpdate->addAudioEvent(event));
}
