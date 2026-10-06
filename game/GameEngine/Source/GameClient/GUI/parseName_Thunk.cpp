// cl: /DNDEBUG /MD /EHs-c-
// Lift the parseName window-file parser to clean C++.
//
// The same skeleton as parseInputCallback -- scan to the opening quote, step
// past it, extract the quoted field with strtok and the quote delimiter, and
// store the result with an explicit guarded length -- with two differences.
//
// It writes to the AsciiString member at instData+0x18C rather than to a global,
// and it null-checks the name-key generator before using it where
// parseInputCallback does not. The resulting key goes to instData+0x04.
//
// strtok is the retail MSVCR71 import at IAT 0x013594D8 and terminates the
// token in the caller-owned line buffer. The generator call at ILT 0x0003ADD7
// is the same one parseInputCallback and
// Player::getProductionCostChangePercent reach; that ILT routes to the matched
// body at 0x0008FFC0, so this TU spells it NameKeyGenerator::nameToKey (the
// other two TUs still carry the old address-derived shim spelling).

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *s, const char *delim);
extern "C" unsigned int __cdecl strlen(const char *s);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <typename T>
class StringBase
{
public:
	void set(const T *s, Int len);					///< ILT thunk at 0x00887D20
};

class AsciiString : public StringBase<char>
{
public:
	const char *str(void) const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}

	void *m_data;
};

// Retail calls NameKeyGenerator::nameToKey here: the ILT thunk at 0x0003ADD7
// routes to the matched body at 0x0008FFC0, whose mangled name is
// ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z (W4 = enum return).
// NameKeyType is an enum here, not a typedef of int.
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;	///< retail [0x012ED600]

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	unsigned char m_unreconstructed_00[4];
	Int m_id;											///< retail this+0x04
	unsigned char m_unreconstructed_08[0x18C - 0x08];
	AsciiString m_name;									///< retail this+0x18C
};

// ?parseName@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseName(char *token, WinInstanceData *instData, char *line, void *userData)
{
	char *p = line;
	while (*p != '"')
	{
		++p;
	}
	++p;

	char *fieldText = strtok(p, "\"");

	// Named before the length is measured: retail loads instData and computes
	// the member address ahead of the null branch, which folding the access into
	// the set() call defers past it.
	AsciiString *name = &instData->m_name;
	name->set(fieldText, fieldText ? (Int)strlen(fieldText) : 0);

	if (TheNameKeyGenerator)
	{
		instData->m_id =
			TheNameKeyGenerator->nameToKey(name->str());
	}

	return true;
}
