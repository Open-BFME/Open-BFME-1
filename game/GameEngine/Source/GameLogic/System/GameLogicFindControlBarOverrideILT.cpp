// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString;
class CommandButton;

class GameLogic
{
public:
	bool findControlBarOverride(const AsciiString &, int,
		const CommandButton *&) const;
};

class Rva00002509Thunk
{
public:
	bool forward(const AsciiString &name, int slot,
		const CommandButton *&button) const;
};

bool Rva00002509Thunk::forward(const AsciiString &name, int slot,
	const CommandButton *&button) const
{
	return ((const GameLogic *)this)->findControlBarOverride(name, slot, button);
}
