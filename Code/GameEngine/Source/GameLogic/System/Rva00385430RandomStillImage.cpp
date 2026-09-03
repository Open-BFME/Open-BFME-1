// cl: /O2 /DNDEBUG /MD /EHsc
// Builds the BFME film-frame resource name chosen by the client RNG.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const char *text, Int length);
};

extern Int GetGameClientRandomValue(Int low, Int high, char *file, Int line);
extern "C" __declspec(dllimport) Int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" unsigned int __cdecl strlen(const char *text);

void assignRandomStillImage(AsciiString *result, Int, Int)
{
	char buffer[60];
	unsigned int image = GetGameClientRandomValue(
		1,
		21,
		"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\System\\GameLogic.cpp",
		0x573);
	if (image < 1)
		image = 1;
	else if (image > 21)
		image = 21;

	sprintf(buffer, "StillImage_Film%02d", image);
	result->set(buffer, strlen(buffer));
}
