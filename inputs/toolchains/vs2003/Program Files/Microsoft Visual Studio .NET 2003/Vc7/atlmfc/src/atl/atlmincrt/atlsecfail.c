// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

// Copied from CRT source file secfail.c
// Modified to not depend on the rest of the CRT
//
//Report a /GS security check failure
//Purpose:
//       Define function used to report a security check failure, along with a
//       routine for registering a new handler.
//
//       Entrypoints:/
//       __security_error_handler
//       _set_security_error_handler
//

#pragma warning(disable : 4668)	// is not defined as a preprocessor macro, replacing with '0' for '#if/#elif
#pragma warning(disable : 4820)	// padding added after member
#pragma warning(disable : 4255)	// no function prototype given: converting '()' to '(void)'
#pragma warning(disable : 4711)	// function selected for automatic inline expansion

#include <windows.h>

/*
 * User-registered failure reporting routine.
 */

static _secerr_handler_func user_handler;

/*
 * Default messagebox string components
 */

#define PROGINTRO   "Program: "
#define DOTDOTDOT   "..."

#define BOXINTRO_0  "Unknown security failure detected!"
#define MSGTEXT_0   \
	"A security error of unknown cause has been detected which has\n"      \
	"corrupted the program's internal state.  The program cannot safely\n" \
	"continue execution and must now be terminated.\n"

#define BOXINTRO_1  "Buffer overrun detected!"
#define MSGTEXT_1   \
	"A buffer overrun has been detected which has corrupted the program's\n"  \
	"internal state.  The program cannot safely continue execution and must\n"\
	"now be terminated.\n"

#define MAXLINELEN  60 /* max length for line in message box */

/***
*__security_error_handler() - Report security error.
*
*Purpose:
*       A /GS security error has been detected.  If a user-registered failure
*       reporting function is available, call it, otherwise bring up a default
*       message box describing the problem and terminate the program.
*
*Entry:
*       int code - security failure code
*       void *data - code-specific data
*
*Exit:
*       Does not return.
*
*Exceptions:
*
*******************************************************************************/

void __cdecl __security_error_handler(
	int code,
	void *data)
{
	/* Use user-registered handler if available. */
	if (user_handler != NULL) {
		__try {
			user_handler(code, data);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			/*
			 * If user handler raises an exception, capture it and terminate
			 * the program, since the EH stack may be corrupted above this
			 * point.
			 */
		}
	}
	else {
		char progname[MAX_PATH + 1];
		char * pch;
		char * outmsg;
		char * boxintro;
		char * msgtext;
		size_t subtextlen;

		switch (code) {
		default:
			/*
			 * Unknown failure code, which probably means an older CRT DLL is
			 * being used with a newer compiler.
			 */
			boxintro = BOXINTRO_0;
			msgtext = MSGTEXT_0;
			subtextlen = sizeof(BOXINTRO_0) + sizeof(MSGTEXT_0);
			break;
		case _SECERR_BUFFER_OVERRUN:
			/*
			 * Buffer overrun detected which may have overwritten a return
			 * address.
			 */
			boxintro = BOXINTRO_1;
			msgtext = MSGTEXT_1;
			subtextlen = sizeof(BOXINTRO_1) + sizeof(MSGTEXT_1);
			break;
		}

        progname[MAX_PATH] = '\0';
        if (!GetModuleFileName(NULL, progname, MAX_PATH))
            strcpy(progname, "<program name unknown>");

		pch = progname;

		/* sizeof(PROGINTRO) includes the NULL terminator */
		if (sizeof(PROGINTRO) + lstrlen(progname) + 1 > MAXLINELEN)
		{
			pch += (sizeof(PROGINTRO) + lstrlen(progname) + 1) - MAXLINELEN;
			memcpy(pch, DOTDOTDOT, sizeof(DOTDOTDOT) - 1);
		}

		outmsg = (char *)_alloca(subtextlen - 1 + 2
								 + sizeof(PROGINTRO) - 1
								 + lstrlen(pch) + 2);

		lstrcpy(outmsg, boxintro);
		lstrcat(outmsg, "\n\n");
		lstrcat(outmsg, PROGINTRO);
		lstrcat(outmsg, pch);
		lstrcat(outmsg, "\n\n");
		lstrcat(outmsg, msgtext);

		MessageBox(NULL, 
			outmsg, 
			"Microsoft Visual C++ Runtime Library", 
			MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);
	}

	ExitProcess(3);
}

/***
*_set_security_error_handler(handler) - Register user handler
*
*Purpose:
*       Register a user failure reporting function.
*
*Entry:
*       _secerr_handler_func handler - the user handler
*
*Exit:
*       Returns the previous user handler
*
*Exceptions:
*
*******************************************************************************/

_secerr_handler_func __cdecl _set_security_error_handler(
	_secerr_handler_func handler)
{
	_secerr_handler_func old_handler;

	old_handler = user_handler;
	user_handler = handler;

	return old_handler;
}

/* TEMPORARY - old handler name, to be removed when tools are updated. */
void __cdecl __buffer_overrun()
{
	__security_error_handler(_SECERR_BUFFER_OVERRUN, NULL);
}

/* TEMPORARY - old handler name, to be removed when tools are updated. */
_secerr_handler_func __cdecl __set_buffer_overrun_handler(
	_secerr_handler_func handler)
{
	return _set_security_error_handler(handler);
}

