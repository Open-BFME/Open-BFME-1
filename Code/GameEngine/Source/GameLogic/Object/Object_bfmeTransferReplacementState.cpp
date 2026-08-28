// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib

// Open-BFME: retail 0x001C5620. Transfer the Object name and the live
// TemporarilyDefectUpdate relationship when an Object is replaced.

#include "Common/AsciiString.h"

typedef unsigned int UnsignedInt;
typedef int ObjectID;

enum NameKeyType
{
	INVALID_NAME_KEY = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Object;
class Module;

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

class Object
{
public:
	void bfmeTransferReplacementState(Object *replacement);
	void setName(AsciiString value);
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
		replacement->setName(getName());

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
