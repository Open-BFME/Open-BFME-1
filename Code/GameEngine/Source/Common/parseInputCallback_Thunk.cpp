// cl: /DNDEBUG /MD /EHs-c-
// Lift the parseInputCallback window-file parser to clean C++.
//
// The third argument is a line from a window file. Scan to the opening quote,
// step past it, then extract the field with strtok and the quote
// delimiter. strtok is the retail import at IAT 0x013594D8 and terminates the token in the
// caller-owned line buffer.
//
// The result is stored into the global AsciiString at 0x012F2574 with an
// explicit length, guarded so a missing token stores nothing rather than
// measuring a null pointer. strtok mutates the caller-owned line buffer, matching
// the retail C runtime call. Its characters then go through the name-to-key call
// on the generator at 0x012ED600 -- the same one Player::getProductionCostChange
// Percent uses, and still not identified beyond its address -- and the key is
// looked up on the global at 0x012ED88C with a second argument of 1. The result
// lands in 0x012F255C and the function reports success unconditionally.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *s, const char *delim);
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

class WindowLookupShim
{
public:
	/// address-derived name -- do not treat as an identity.
	void *unidentified_00025CD4(Int key, Int flag);		///< ILT thunk at 0x00025CD4
};

class WinInstanceData;

extern AsciiString TheParsedCallbackName;				///< retail [0x012F2574]
extern NameKeyGeneratorShim *TheNameKeyGeneratorShim;	///< retail [0x012ED600]
extern WindowLookupShim *TheWindowLookupShim;			///< retail [0x012ED88C]
extern void *TheParsedCallbackResult;					///< retail [0x012F255C]

// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseInputCallback(char *token, WinInstanceData *instData, char *line, void *userData)
{
	char *p = line;
	while (*p != '"')
	{
		++p;
	}
	++p;

	char *fieldText = strtok(p, "\"");
	TheParsedCallbackName.set(fieldText, fieldText ? (Int)strlen(fieldText) : 0);

	Int key = TheNameKeyGeneratorShim->unidentified_0003ADD7(TheParsedCallbackName.str());
	TheParsedCallbackResult = TheWindowLookupShim->unidentified_00025CD4(key, 1);

	return true;
}
