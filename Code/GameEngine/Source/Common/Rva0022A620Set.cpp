// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
	~AsciiString();

private:
	void set(const AsciiString &other);
	void *m_data;
};

class Rva0022A620Obj
{
public:
	void set(AsciiString value);

private:
	char m_pad[0x328];
	AsciiString m_name;
};

void Rva0022A620Obj::set(AsciiString value)
{
	m_name = value;
}
