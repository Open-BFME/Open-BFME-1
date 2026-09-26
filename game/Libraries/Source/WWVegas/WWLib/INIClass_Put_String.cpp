// cl: /DNDEBUG /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include "always.h"
#include "b64pipe.h"
#include "b64straw.h"
#include "cstraw.h"
#include "ini.h"
#include "readline.h"
#include "trim.h"
#include "win.h"
#include "xpipe.h"
#include "xstraw.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "rawfile.h"
#include "ffactory.h"
#include "inisup.h"
#include "trect.h"
#include "wwfile.h"
#include "pipe.h"
#include "wwstring.h"
#include "nstrdup.h"

bool INIClass::Put_String(char const * section, char const * entry, char const * string)
{
	if (section == NULL || entry == NULL) return(false);

	INISection * secptr = Find_Section(section);

	if (secptr == NULL) {
		secptr = W3DNEW INISection(strdup(section));
		if (secptr == NULL) return(false);
		SectionList->Add_Tail(secptr);
		SectionIndex->Add_Index(secptr->Index_ID(), secptr);
	}

	/*
	**	Remove the old entry if found and print debug message
	*/
	INIEntry * entryptr = secptr->Find_Entry(entry);
	if (entryptr != NULL) {
		if (strcmp(entryptr->Entry, entry)) {
			DuplicateCRCError("INIClass::Put_String", section, entry);
		} else {
#if 0
			OutputDebugString("INIClass::Put_String - Duplicate Entry \"");
			OutputDebugString(entry);
			OutputDebugString("\"\n");
#endif
		}
		secptr->EntryIndex.Remove_Index(entryptr->Index_ID());
		delete entryptr;
	}

	/*
	**	Create and add the new entry.
	*/
	if (string != NULL && strlen(string) > 0) {
		entryptr = W3DNEW INIEntry(strdup(entry), strdup(string));

		// If this assert fires, then the string will be truncated on load, because
		// there will not be enough room in the loading buffer!
		WWASSERT(strlen(string) < MAX_LINE_LENGTH);

		if (entryptr == NULL) {
			return(false);
		}
		secptr->EntryList.Add_Tail(entryptr);
		secptr->EntryIndex.Add_Index(entryptr->Index_ID(), entryptr);
	}
	return(true);
}
