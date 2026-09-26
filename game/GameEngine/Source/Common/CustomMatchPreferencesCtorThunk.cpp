// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The retail ILT at 0x0000B0F5 jumps directly to the matched
// CustomMatchPreferences constructor at 0x000AB7F0.  A normal C++ placement
// construction adds a null check, so this focused thunk keeps the proven
// five-byte jump and resolves its target through the existing constructor.

#pragma comment(linker, "/alternatename:_customMatchPreferencesCtorTarget=??0CustomMatchPreferences@@QAE@XZ")
extern "C" __declspec(noreturn) void customMatchPreferencesCtorTarget();

class CustomMatchPreferencesCtorThunk
{
public:
	void forward();
};

// ?forward@CustomMatchPreferencesCtorThunk@@QAEXXZ
void CustomMatchPreferencesCtorThunk::forward()
{
	customMatchPreferencesCtorTarget();
}
