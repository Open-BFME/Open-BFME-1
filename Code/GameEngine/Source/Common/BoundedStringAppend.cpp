// The 129-byte body at 0x0068D730, one slot family with the bounded byte
// writers at 0x0068D6D0 and 0x0068D700 and the bounded memcpy at 0x0068D7E0.
//
// WHAT THE BYTES SHOW.  Three dword arguments, no `this`, no stack cleanup:
// __cdecl.  The first and third are compared with an unsigned branch, so both
// are pointers into the same buffer; the second is walked one byte at a time by
// an inlined strlen, so it is a string.  A null limit jumps straight to an
// inlined strcpy, which is the same "a null limit disables checking" rule the
// byte writers use.  With a limit the body calls the imported strncpy through
// __imp__strncpy with the remaining room as the count, then terminates the
// buffer and returns the limit when the text would have reached it.  Otherwise
// it returns the cursor advanced past the terminator it wrote, which is what
// `lea eax,[eax+esi+1]` computes.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the writer or the
// stream it writes into, so the name is address-derived like its neighbours.
//
// SHAPE.  The two bounds tests are two separate early returns, not one
// conjunction.  Written as `cursor >= limit || limit - cursor < 1` MSVC sinks
// the shared `return cursor` block below the copy; written as two statements it
// leaves that block between the guard and the copy, which is where retail has
// it at +0x1c.

// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *, const char *, unsigned int);
extern "C" char *__cdecl strcpy(char *, const char *);
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strcpy, strlen)

char *rva68d730(char *cursor, char *text, char *limit)
{
	if (limit != 0)
	{
		if (cursor >= limit)
			return cursor;

		if (limit - cursor < 1)
			return cursor;

		strncpy(cursor, text, limit - cursor);

		if (cursor + strlen(text) >= limit)
		{
			limit[-1] = '\0';
			return limit;
		}
	}
	else
	{
		strcpy(cursor, text);
	}

	return cursor + strlen(text) + 1;
}
