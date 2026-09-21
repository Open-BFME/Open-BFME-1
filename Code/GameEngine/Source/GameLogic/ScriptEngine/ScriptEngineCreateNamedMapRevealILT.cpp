// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString;
typedef float Real;

class ScriptEngine
{
public:
	void createNamedMapReveal(const AsciiString &, const AsciiString &, Real,
		const AsciiString &);
};

class Rva0002C8EAThunk
{
public:
	void forward(const AsciiString &, const AsciiString &, Real,
		const AsciiString &);
};

void Rva0002C8EAThunk::forward(const AsciiString &revealName,
	const AsciiString &waypointName, Real radiusToReveal,
	const AsciiString &playerName)
{
	((ScriptEngine *)this)->createNamedMapReveal(revealName, waypointName,
		radiusToReveal, playerName);
}
