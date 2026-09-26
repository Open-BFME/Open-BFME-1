// cl: /O2 /MD

class AsciiString;

class ScriptEngine
{
public:
	void doNamedMapReveal(const AsciiString &name);
};

class Rva0001FC3FScriptEngineNamedMapRevealThunk
{
public:
	void forward(const AsciiString &name);
};

void Rva0001FC3FScriptEngineNamedMapRevealThunk::forward(const AsciiString &name)
{
	((ScriptEngine *)this)->doNamedMapReveal(name);
}
