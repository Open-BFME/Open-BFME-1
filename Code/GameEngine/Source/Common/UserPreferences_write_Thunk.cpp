// cl: /DNDEBUG /MD /EHs-c-
// UserPreferences::write uses a UTF-16 filename and narrow preference entries.
// Retail calls MSVCR71 _wfopen at IAT0x01359368 with a wide mode literal.
typedef int Int;
typedef bool Bool;

struct FILEShim;

typedef unsigned short WideChar;
extern "C" __declspec(dllimport) FILEShim *__cdecl _wfopen(const WideChar *path, const WideChar *mode);
extern "C" __declspec(dllimport) int __cdecl fprintf(FILEShim *fp, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl fclose(FILEShim *fp);

struct StringDataHeaderShim
{
	unsigned char m_unreconstructed_00[4];
	unsigned short m_length;
	unsigned char m_unreconstructed_06[2];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Bool isEmpty(void) const { return m_data == 0 || m_data->m_length == 0; }
	const char *str(void) const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}
	StringDataHeaderShim *m_data;
};

// Retail opens the filename through _wfopen; the path is a UTF-16 string.
// Map keys and values remain narrow strings consumed by fprintf.
class Utf16StringView
{
public:
 Bool isEmpty(void) const { return m_data == 0 || m_data->m_length == 0; }
 const WideChar *str(void) const
 {
  return m_data ? (const WideChar *)((unsigned char *)m_data + 8) : L"";
 }
 StringDataHeaderShim *m_data;
};

struct PrefMapNodeShim
{
	unsigned char m_unreconstructed_00[0x10];
	AsciiString m_key;
	AsciiString m_value;
};

struct PrefMapShim
{
	unsigned char m_unreconstructed_00[8];
	PrefMapNodeShim *m_begin;
};

PrefMapNodeShim *prefMapIncrement(PrefMapNodeShim *node);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	virtual Bool write(void);

private:
	PrefMapShim *m_map;									///< this+0x04
	unsigned char m_unreconstructed_08[8];
	Utf16StringView m_filename;								///< this+0x10
};

// ?write@UserPreferences@@UAE_NXZ
Bool UserPreferences::write(void)
{
	if (m_filename.isEmpty())
		return false;

	FILEShim *fp = _wfopen(m_filename.str(), L"w");

	// Success is the fall-through and the open failure jumps forward to a tail
	// return: writing `if (!fp) return false;` inlines that exit instead, which
	// retail does only for the empty-filename case, where the register state
	// differs and the two cannot share an epilogue anyway.
	if (fp)
	{
		PrefMapNodeShim *node = m_map->m_begin;
		while (node != (PrefMapNodeShim *)m_map)
		{
			fprintf(fp, "%s = %s\n", node->m_key.str(), node->m_value.str());
			node = prefMapIncrement(node);
		}

		fclose(fp);
		return true;
	}

	return false;
}
