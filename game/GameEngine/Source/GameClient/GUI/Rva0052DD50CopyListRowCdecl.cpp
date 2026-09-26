// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail 0x0052DD50, 275 bytes. __cdecl twin of copyCustomMatchListRow
// (0x00538290): strncpy a 255-char name into a zeroed 256-byte buffer, then
// StringBase<char>::set the source name, the truncated copy, and the string
// at +0x34, plus the dword fields at +0xF4/+0xF8/+0xFC/+0x104/+0x10C/+0x110/
// +0x114/+0x324/+0x328/+0x32C.

extern "C" __declspec(dllimport) char *__cdecl strncpy( char *dest, const char *src, unsigned int count );
extern "C" unsigned int __cdecl strlen( const char *str );

class Rva0052DD50AsciiString
{
public:
	void set( const char *str, int len );

private:
	void *m_data;
};

struct Rva0052DD50ListRow
{
	Rva0052DD50AsciiString name;
	Rva0052DD50AsciiString truncatedName;
	Rva0052DD50AsciiString extra;
	int field0C;
	int field10;
	int field14;
	int field18;
	int field1C;
	int field20;
	int field24;
	int field28;
	int field2C;
	int field30;
};

struct Rva0052DD50ListSource
{
	unsigned char pad00[ 0x10 ];
	const char *name;
	unsigned char pad14[ 0x34 - 0x14 ];
	const char *extra;
	unsigned char pad38[ 0xF4 - 0x38 ];
	int fieldF4;
	int fieldF8;
	int fieldFC;
	unsigned char pad100[ 0x104 - 0x100 ];
	int field104;
	unsigned char pad108[ 0x10C - 0x108 ];
	int field10C;
	int field110;
	int field114;
	unsigned char pad118[ 0x324 - 0x118 ];
	int field324;
	int field328;
	int field32C;
};

void Rva0052DD50CopyListRow( const Rva0052DD50ListSource *src, Rva0052DD50ListRow *dst )
{
	char buf[ 256 ] = { 0 };
	strncpy( buf, src->name, 255 );
	dst->name.set( src->name, src->name ? (int)strlen( src->name ) : 0 );
	dst->truncatedName.set( buf, (int)strlen( buf ) );
	dst->field14 = src->fieldF4;
	dst->field18 = src->field104;
	dst->field0C = src->fieldF8;
	dst->field10 = src->fieldFC;
	const char *extra = src->extra;
	Rva0052DD50AsciiString *extraSlot = &dst->extra;
	extraSlot->set( extra, extra ? (int)strlen( extra ) : 0 );
	dst->field1C = src->field10C;
	dst->field2C = src->field110;
	dst->field30 = src->field114;
	dst->field28 = src->field32C;
	dst->field20 = src->field324;
	dst->field24 = src->field328;
}
