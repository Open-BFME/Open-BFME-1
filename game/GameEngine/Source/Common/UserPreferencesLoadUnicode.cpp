// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <stdio.h>
#include <string.h>
#include <map>
#include "ascii_string.h"

typedef bool Bool;

#pragma intrinsic(strlen)

// Retail inlines these narrow StringBase accessors at the call sites below; the
// bodies are the ones matched in game/Libraries/Source/string/StringBase.cpp.
template<> inline const char *StringBase<char>::str() const
{
	return m_data ? &m_data->data[0] : "";
}

template<> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

template<> inline void StringBase<char>::set(const char *s)
{
	set(s, s ? (int)strlen(s) : 0);
}

inline AsciiString &AsciiString::operator=(const char *s)
{
	((StringBase<char> *)this)->set(s);
	return *this;
}

// The wide string this body handles by value.  Retail destroys the returned
// temporary with a direct call to 0x008881D0, the body the private
// releaseBuffer and the destructor fold to, so the destructor is an inline
// forwarder; the caller being able to destroy the temporary is what the
// explicit specialization adds over string_base.h, whose destructor is private.
// Only the members this body reaches are declared.
template <>
class StringBase<unsigned short>
{
public:
	~StringBase() { releaseBuffer(); }

	const unsigned short *str() const { return m_data ? &m_data->data[0] : (const unsigned short *)L""; }

	void set(const StringBase<unsigned short> &src);
	void concat(const unsigned short *str, int len);
	void concat(const StringBase<unsigned short> &str)
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const unsigned short *data = str.m_data ? &str.m_data->data[0] : (const unsigned short *)L"";
		concat(data, len);
	}

private:
	void releaseBuffer();

	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		unsigned short data[1];
	};

	Header *m_data;
};

class UnicodeString;

// The wide user-data directory accessor on TheWritableGlobalData; its owner
// and name are unproven, so the ledger keeps the address-derived host.
class Rva00083DA0Host
{
public:
	StringBase<unsigned short> copyStringAt1280(void);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

typedef std::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences(void);
	virtual Bool load(const UnicodeString &fname);

protected:
	StringBase<unsigned short> m_filename;
};

enum { LINE_LEN = 2048 };

// ?load@UserPreferences@@UAE_NABVUnicodeString@@@Z
// UserPreferences vtable 0x01080FD0 slot +0x04 (ILT 0x00021AD5); the ASCII
// load at 0x000A9230 (slot +0x08) widens its filename and forwards here.
// Zero Hour's UserPreferences::load line for line, with BFME's wide path.
Bool UserPreferences::load(const UnicodeString &fname)
{
	m_filename.set(((Rva00083DA0Host *)TheWritableGlobalData)->copyStringAt1280());
	// UnicodeString is a single StringBase<unsigned short> handle.
	m_filename.concat(*(const StringBase<unsigned short> *)&fname);

	FILE *fp = _wfopen((const wchar_t *)m_filename.str(), L"r");
	if (fp)
	{
		char buf[LINE_LEN];
		while (fgets(buf, LINE_LEN, fp) != NULL)
		{
			AsciiString line = buf;
			line.trim();

			AsciiString key, val;
			line.nextToken(&key, "=");
			val = line.str() + 1;

			key.trim();
			val.trim();

			if (key.isEmpty() || val.isEmpty())
				continue;

			(*this)[key] = val;
		}
		fclose(fp);
		return true;
	}
	return false;
}
