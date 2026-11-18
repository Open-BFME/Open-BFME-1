// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME: retail 0x001C5620. Transfer the Object name and the live
// TemporarilyDefectUpdate relationship when an Object is replaced.

#include "Common/AsciiString.h"

#include "../../../Include/Common/ScalarTypes.h"
typedef int ObjectID;

#include "../../../Include/Common/NameKeyType.h"




// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Object;
class Module;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class TemporarilyDefectUpdate
{
public:
	void bfmeTransferDefection(Object *source, UnsignedInt endFrame);

	unsigned char m_pad[0x20];
	UnsignedInt m_endFrame;
	UnsignedInt m_startFrame;
	ObjectID m_defectorID;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
// Declaration-only receiver for the existing 78-byte setter at 0x001C4240.
// No object, member access, sizeof or layout is formed through this view.
class Gen001C4240
{
public:
	void bfmeSet(AsciiString value);
};

class Object
{
public:
	void bfmeTransferReplacementState(Object *replacement);
	const AsciiString &getName() const { return m_name; }

protected:
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad[0x240];
	AsciiString m_name;
};

void Object::bfmeTransferReplacementState(Object *replacement)
{
	if (replacement != 0)
	{
		((Gen001C4240 *)replacement)->bfmeSet(getName());

		static NameKeyType key_TemporarilyDefectUpdate =
			TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");

		TemporarilyDefectUpdate *oldUpdate =
			(TemporarilyDefectUpdate *)findModule(key_TemporarilyDefectUpdate);
		TemporarilyDefectUpdate *newUpdate =
			(TemporarilyDefectUpdate *)replacement->findModule(key_TemporarilyDefectUpdate);

		if (newUpdate != 0 && oldUpdate != 0)
		{
			Object *defector = TheGameLogic->findObjectByID(oldUpdate->m_defectorID);
			if (defector != 0)
				newUpdate->bfmeTransferDefection(defector, oldUpdate->m_endFrame);
		}
	}
}
