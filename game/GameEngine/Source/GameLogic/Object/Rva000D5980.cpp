// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame
// stlport
#include "Lib/BaseType.h"
#include "Common/GameMemory.h"
#include "Common/Overridable.h"
#include "Common/DisabledTypes.h"
#define OBJECT_TU_MEMBERS \
	bool clearDisabled(DisabledType); \
	void setDisabled(DisabledType);
#include "GameEngine/Source/GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

// Retail 0x000D5980, 78 bytes: final RET at 0x000D59CD,
// followed by INT3 padding. Keep this callback name address-derived.
// Existing matched callees prove the Object disabled-state methods and the
// Overridable resolver. Thing+0x04 m_template is witnessed by name_oracle.
// The template flag at +0xD0 bit 6 has no witnessed name and stays opaque.
// Preserve the original pointer on the null override path; a ternary emits
// an extra XOR/jump and changes the complete function by four bytes.

int __cdecl Rva000D5980(Object *object, const bool *enabled)
{
	bool enable = *enabled;
	if (object)
	{
		const Overridable *data =
			reinterpret_cast<const Overridable *>(object->m_template);
		const Overridable *finalData = data;
		if (data)
			finalData = data->getFinalOverride();

		if ((*(reinterpret_cast<const unsigned char *>(finalData) + 0xD0)
			& 0x40) != 0)
		{
			if (enable)
				object->setDisabled(DISABLED_UNDERPOWERED);
			else
				object->clearDisabled(DISABLED_UNDERPOWERED);
		}
	}
	return 1;
}
