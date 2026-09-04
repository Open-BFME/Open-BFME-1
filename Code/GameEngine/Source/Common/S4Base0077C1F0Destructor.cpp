// Open-BFME5: clean reconstruction of the 0x0077C1F0 S4Base destructor.
// The member offsets and unwind order are taken from the retail body.  The
// address-derived member types retain the established destructor pins.

class Inner01073744
{
public:
	virtual ~Inner01073744() {}
};

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

#define S4_MEMBER( NAME, SIZE ) \
	class NAME \
	{ \
	public: \
		~NAME(); \
	private: \
		char m_body[ SIZE ]; \
	}

S4_MEMBER( Gen_uwm_0002303d, 1 );
S4_MEMBER( Gen_uw_000395d1, 1 );
S4_MEMBER( Gen_uwm_00003b6b, 1 );
S4_MEMBER( Gen_uwm_00026ab2, 1 );
S4_MEMBER( Gen_uwm_0002c868, 1 );
S4_MEMBER( Gen_uwm_00022c2d, 1 );
S4_MEMBER( Gen_uwm_0002a8ba, 1 );
S4_MEMBER( Gen_uwm_00041745, 1 );
S4_MEMBER( Gen_uwm_0000e746, 0x14 );

class S4Base0077C1F0 : public Inner01073744
{
public:
	virtual ~S4Base0077C1F0();

private:
	char m_pad04[ 4 ];
	Gen_uwm_0002303d m_at08;
	char m_pad09[ 0x0B ];
	AsciiString m_at14;
	Gen_uw_000395d1 m_at18;
	char m_pad19[ 0x0B ];
	Gen_uwm_00003b6b m_at24;
	char m_pad25[ 0x0B ];
	Gen_uwm_00026ab2 m_at30;
	char m_pad31[ 0x0B ];
	AsciiString m_at3c;
	AsciiString m_at40;
	AsciiString m_at44;
	AsciiString m_at48;
	char m_pad4c[ 0x20 ];
	Gen_uwm_0002c868 m_at6c;
	char m_pad6d[ 0x0B ];
	Gen_uwm_00022c2d m_at78;
	char m_pad79[ 0x0B ];
	Gen_uwm_0002a8ba m_at84;
	char m_pad85[ 0x5B ];
	AsciiString m_ate0;
	AsciiString m_ate4;
	AsciiString m_ate8;
	AsciiString m_atec;
	Gen_uwm_00041745 m_atf0;
	char m_padf1[ 0x43 ];
	Gen_uwm_0000e746 m_items[ 2 ];
};

// ??1S4Base0077C1F0@@UAE@XZ
S4Base0077C1F0::~S4Base0077C1F0()
{
}
