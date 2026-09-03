// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

void j_00045c7d();
void j_00041eca();

typedef void (__stdcall *Rva00372BA0TrueHandler)(void *);

class Rva00371090Owner
{
public:
	void remove(void *value);
};

typedef void (Rva00371090Owner::*Rva00372BA0FalseHandler)(void *);

void Rva00372BA0ConditionalDispatcher(void *first, void *second, bool enabled)
{
	void *firstValue = first;
	Rva00371090Owner *secondValue = (Rva00371090Owner *)second;
	if (secondValue)
	{
		if (enabled)
		{
			void *value = firstValue;
			((Rva00372BA0TrueHandler)j_00045c7d)(value);
			return;
		}

		union { void *asVoid; Rva00372BA0FalseHandler asMember; } removeCast;
		removeCast.asVoid = (void *)j_00041eca;
		(secondValue->*removeCast.asMember)(firstValue);
	}
}
