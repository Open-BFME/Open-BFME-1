// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: BFME audio-request type name at retail 0x00691330 (460 B).
// The request int selects one of eight literals (AR_Play, AR_StopHandle,
// AR_StopMusic, AR_PushMusic, AR_PopMusic, AR_ActivateMusicSystem,
// AR_DeactivateMusicSystem, AR_ClearOutMusicSystem); anything else formats
// "<Unknown %d>". The string comes back through the hidden return slot and
// the callee cleans nothing (plain ret), so this is a __cdecl free
// function; the name is unproven so it keeps the retail address.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ?rva00691330Name@@YA?AVAsciiString@@H@Z
AsciiString __cdecl rva00691330Name(int request)
{
	switch (request)
	{
	case 0:
		return AsciiString("AR_Play");
	case 1:
		return AsciiString("AR_StopHandle");
	case 2:
		return AsciiString("AR_StopMusic");
	case 3:
		return AsciiString("AR_PushMusic");
	case 4:
		return AsciiString("AR_PopMusic");
	case 5:
		return AsciiString("AR_ActivateMusicSystem");
	case 6:
		return AsciiString("AR_DeactivateMusicSystem");
	case 7:
		return AsciiString("AR_ClearOutMusicSystem");
	default:
		break;
	}

	AsciiString result;
	result.format(AsciiString("<Unknown %d>"), request);
	return result;
}
