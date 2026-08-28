// cl: /DNDEBUG /MD /EHs-c-
// Lift the parseName window-file parser to clean C++.
//
// The same skeleton as parseInputCallback -- scan to the opening quote, step
// past it, find the next quote with strstr on the one-character needle, store
// the result with an explicit guarded length -- with two differences.
//
// It writes to the AsciiString member at instData+0x18C rather than to a global,
// and it null-checks the name-key generator before using it where
// parseInputCallback does not. The resulting key goes to instData+0x04.
//
// The generator call at ILT 0x0003ADD7 is the same one parseInputCallback and
// Player::getProductionCostChangePercent reach, still unidentified beyond its
// address.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl strstr(const char *haystack, const char *needle);
extern "C" unsigned int __cdecl strlen(const char *s);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const char *s, Int len);					///< ILT thunk at 0x00887D20

	const char *str(void) const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}

	void *m_data;
};

class NameKeyGeneratorShim
{
public:
	/// address-derived name -- do not treat as an identity.
	Int unidentified_0003ADD7(const char *name);		///< ILT thunk at 0x0003ADD7
};

extern NameKeyGeneratorShim *TheNameKeyGeneratorShim;	///< retail [0x012ED600]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
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

	char *close = strstr(p, "\"");

	// Named before the length is measured: retail loads instData and computes
	// the member address ahead of the null branch, which folding the access into
	// the set() call defers past it.
	AsciiString *name = &instData->m_name;
	name->set(close, close ? (Int)strlen(close) : 0);

	if (TheNameKeyGeneratorShim)
	{
		instData->m_id =
			TheNameKeyGeneratorShim->unidentified_0003ADD7(name->str());
	}

	return true;
}
