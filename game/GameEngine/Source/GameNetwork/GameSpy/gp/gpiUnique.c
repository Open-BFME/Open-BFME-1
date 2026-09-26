// cl: /MD -Iinputs/reference/shims/gamespy
/* GameSpy SDK, 2004 vintage -- pristine upstream C source.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from inputs/reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only. */
/*
gpiUnique.c
GameSpy Presence SDK 
Dan "Mr. Pants" Schoenblum

Copyright 1999-2003 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com

***********************************************************************
Please see the GameSpy Presence SDK documentation for more information
**********************************************************************/

//INCLUDES
//////////
#include "gpi.h"

//FUNCTIONS
///////////
static GPResult
gpiSendRegisterUniqueNick(
  GPConnection * connection,
  const char uniquenick[GP_UNIQUENICK_LEN],
  const char cdkey[GP_CDKEY_LEN],
  int operationid
)
{
	GPIConnection * iconnection = (GPIConnection*)*connection;

	gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, "\\registernick\\\\sesskey\\");
	gpiAppendIntToBuffer(connection, &iconnection->outputBuffer, iconnection->sessKey);
	gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, "\\uniquenick\\");
	gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, uniquenick);
	if(cdkey)
	{
		gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, "\\cdkey\\");
		gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, cdkey);
	}
	gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, "\\id\\");
	gpiAppendIntToBuffer(connection, &iconnection->outputBuffer, operationid);
	gpiAppendStringToBuffer(connection, &iconnection->outputBuffer, "\\final\\");
	
	return GP_NO_ERROR;
}

GPResult gpiRegisterUniqueNick(
  GPConnection * connection,
  const char uniquenick[GP_UNIQUENICK_LEN],
  const char cdkey[GP_CDKEY_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
)
{
	GPIOperation * operation = NULL;
	GPResult result;

	// Add the operation.
	/////////////////////
	CHECK_RESULT(gpiAddOperation(connection, GPI_REGISTER_UNIQUENICK, NULL, &operation, blocking, callback, param));

	// Send a request for info.
	///////////////////////////
	result = gpiSendRegisterUniqueNick(connection, uniquenick, cdkey, operation->id);
	CHECK_RESULT(result);

	// Process it if blocking.
	//////////////////////////
	if(blocking)
	{
		result = gpiProcess(connection, operation->id);
		CHECK_RESULT(result);
	}

	return GP_NO_ERROR;
}

GPResult gpiProcessRegisterUniqueNick(
  GPConnection * connection,
  GPIOperation * operation,
  const char * input
)
{
	GPICallback callback;

	// Check for an error.
	//////////////////////
	if(gpiCheckForError(connection, input, GPITrue))
		return GP_SERVER_ERROR;

	// This should be \rn\.
	///////////////////////
	if(strncmp(input, "\\rn\\", 4) != 0)
		CallbackFatalError(connection, GP_NETWORK_ERROR, GP_PARSE, "Unexpected data was received from the server.");

	// Call the callback.
	/////////////////////
	callback = operation->callback;
	if(callback.callback != NULL)
	{
		GPRegisterUniqueNickResponseArg * arg;
		arg = (GPRegisterUniqueNickResponseArg *)gsimalloc(sizeof(GPRegisterUniqueNickResponseArg));
		if(arg == NULL)
			Error(connection, GP_MEMORY_ERROR, "Out of memory.");

		arg->result = GP_NO_ERROR;

		CHECK_RESULT(gpiAddCallback(connection, callback, arg, operation, 0));
	}

	// This operation is complete.
	//////////////////////////////
	gpiRemoveOperation(connection, operation);

	return GP_NO_ERROR;
}
