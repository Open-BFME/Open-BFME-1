// cl: /DNDEBUG /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /EHsc
// Focused native bodies split from WWLib ini.cpp. Keeping the byte-buffer
// Get_String definition in this TU lets the compiler inline it into the wide
// string wrapper as it does in the original translation unit.
#include "always.h"
#include "ini.h"
#include "inisup.h"
#include "trim.h"
#include "widestring.h"
#include "b64pipe.h"
#include "xpipe.h"
#include <string.h>

inline int INIClass::Get_String(char const * section, char const * entry,
	char const * defvalue, char * buffer, int size) const
{
	if (buffer == NULL || size < 2 || section == NULL || entry == NULL)
		return(0);

	INIEntry * entryptr = Find_Entry(section, entry);
	if (entryptr != NULL && entryptr->Value != NULL)
		defvalue = entryptr->Value;

	if (defvalue == NULL) {
		buffer[0] = '\0';
		return(0);
	} else {
		strncpy(buffer, defvalue, size);
		buffer[size-1] = '\0';
		strtrim(buffer);
		return(strlen(buffer));
	}
}

const WideStringClass& INIClass::Get_Wide_String(WideStringClass& new_string,
	char const * section, char const * entry, wchar_t const * defvalue) const
{
	wchar_t out[1024];
	char buffer[1024];

	Base64Pipe b64pipe(Base64Pipe::DECODE);
	BufferPipe bpipe(out, sizeof(out));
	b64pipe.Put_To(&bpipe);

	int length = Get_String(section, entry, "", buffer, sizeof(buffer));
	if (length == 0) {
		new_string = defvalue;
	} else {
		int outcount = b64pipe.Put(buffer, length);
		outcount += b64pipe.End();
		new_string = out;
	}
	return(new_string);
}
