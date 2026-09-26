// cl: /DNDEBUG /MD /EHsc

// The retail body at 0x0040B200 installs vtable 0x010F0648, destroys the
// narrow string at +0x08, then chains to SubsystemInterface.  The owning
// class name is not proven; keep the identity address-derived.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Rva0040B200Subsystem : public SubsystemInterface
{
public:
	virtual ~Rva0040B200Subsystem();

private:
	BFMERetailAsciiString m_string;
};

// ??1Rva0040B200Subsystem@@UAE@XZ
Rva0040B200Subsystem::~Rva0040B200Subsystem()
{
}
