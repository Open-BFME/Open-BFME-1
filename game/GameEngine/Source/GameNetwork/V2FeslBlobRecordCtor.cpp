// EA FESL client SDK ("jabba") blob-service result record default constructor.
//
// The adjacent populated constructor at 0x007F0D40 reads the blob-service keys
// (`blobId`, `ownerType`, `ownerId`, `longDescription`, etc.), which identifies
// this 0x228-byte record.  Names below remain address-derived where the retail
// image supplies layout but not C++ type information.

// The two members at +0x30 and +0x3C are twelve bytes apart and the retail
// body calls 0x007FF700 on each of them before writing anything else.  That
// body is the calendar-date default constructor defined in
// game/GameEngine/Source/GameNetwork/Y4DirtySockDate.cpp as
// ??0Rva007FF700Date@@QAE@XZ, three ints wide, so the reference has to carry
// that type's name (only the name is shared: this TU never reads the fields).
struct Rva007FF700Date
{
	int m_month;
	int m_day;
	int m_year;

	Rva007FF700Date();
};

class Rva007F0CB0BlobRecord
{
public:
	Rva007F0CB0BlobRecord();

private:
	volatile int m_000;
	char m_pad004[ 0x04 ];
	volatile int m_008;
	volatile int m_00C;
	int m_010;
	int m_014;
	int m_018;
	char m_pad01C[ 0x04 ];
	volatile int m_020;
	volatile int m_024;
	volatile int m_028;
	volatile int m_02C;
	Rva007FF700Date m_030;
	Rva007FF700Date m_03C;
	volatile unsigned char m_048;
	char m_pad049[ 0x1F ];
	volatile unsigned char m_068;
	char m_pad069[ 0x1F ];
	volatile int m_088;
	volatile float m_08C;
	volatile int m_090;
	volatile unsigned char m_094;
	char m_pad095[ 0x1F ];
	volatile unsigned char m_0B4;
	char m_pad0B5[ 0x4F ];
	volatile unsigned char m_104;
	char m_pad105[ 0xFE ];
	volatile unsigned char m_203;
	char m_pad204[ 0x20 ];
	volatile int m_224;
};

Rva007F0CB0BlobRecord::Rva007F0CB0BlobRecord()
	: m_010( 0 ), m_014( 0 ), m_018( 0 )
{
	m_008 = -1;
	m_00C = -1;
	*reinterpret_cast<volatile int *>( &m_010 ) = -1;
	*reinterpret_cast<volatile int *>( &m_014 ) = -1;
	m_020 = -1;
	m_024 = -1;
	m_028 = -1;
	m_02C = -1;
	m_090 = -1;
	m_000 = 0;
	m_048 = 0;
	m_068 = 0;
	m_088 = 0;
	m_094 = 0;
	m_0B4 = 0;
	m_104 = 0;
	m_203 = 0;
	m_224 = 0;
	m_018 = 1;
	m_08C = -1.0f;
}
