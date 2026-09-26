// cl: /O2 /DNDEBUG /MD
// The carved 5-byte ILT at 0x0002E802 routes to the matched
// QuickMatchPreferences constructor at 0x000AB6D0.

class Rva000AB6D0QuickMatchCtor
{
public:
	void run();
};

class Rva0002E802QuickMatchPreferences
{
public:
	void forward();
};

// ??0Rva0002E802QuickMatchPreferences@@QAE@XZ
void Rva0002E802QuickMatchPreferences::forward()
{
	((Rva000AB6D0QuickMatchCtor *)this)->run();
}
