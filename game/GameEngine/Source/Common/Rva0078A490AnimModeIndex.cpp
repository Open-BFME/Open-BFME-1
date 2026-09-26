// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0078A490 (164 bytes): the index of an AsciiString in the anim-mode
// name table, 0 when it is absent.  The table at VA 0x012BB88C is BFME's
// TheAnimModeNames from rendobj.h ("MANUAL", "LOOP", "ONCE", "LOOP_PINGPONG",
// "PLAY_TO_FRAME", "LOOP_BACKWARDS", "ONCE_BACKWARDS", NULL); rendobj.h
// defines it static, so every including TU owns a copy and this one is named
// by its address.  The compare is StringBase<char>::compareNoCase(const char *)
// inlined: strlen of the name, then _memicmp over the shorter length.  The
// only caller is bfmeUpdateQW (0x0078A560), which declares the item as void *.

// Linked against the dynamic CRT: _memicmp goes through the import table.
#define _DLL
#include <string.h>

template <class T> class StringBase
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	int compareNoCase(const T *str) const
	{
		return compareNoCase(str, str ? (int)strlen(str) : 0);
	}

	int compareNoCase(const T *str, int len) const
	{
		const int myLen = m_data ? m_data->length : 0;
		const T *data = m_data ? &m_data->data[0] : "";
		int result = _memicmp(data, str, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
};

extern const char *Rva012BB88CAnimModeNames[];	///< VA 0x012BB88C, NULL-terminated

// ?bfmeComputeQW@@YAHPAX@Z
int __cdecl bfmeComputeQW(void *item)
{
	const AsciiString &name = *(const AsciiString *)item;
	for (int i = 0; Rva012BB88CAnimModeNames[i]; ++i)
	{
		if (name.compareNoCase(Rva012BB88CAnimModeNames[i]) == 0)
			return i;
	}
	return 0;
}
