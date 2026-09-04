// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoAbilityBehavior command-ready predicate, retail 0x001EDC00
// size 125. Layout is the landed dtor's: Object* at +8, AsciiString at +0x20.
// TheControlBar->findCommandButton, CommandButton::isReady, and
// Object::bfmeCanUseCommandButton are already matched. Status / model-condition
// masks and AI+0x34 are the remaining gates. Called from the 1944B body at
// 0x001EDCA0 (naked ModuleData-dtor claim; identity-suspect). No matched
// caller names this symbol; bfmeCanAutoFire is descriptive.

typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
class CommandButton;
class AsciiString
{
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

extern ControlBar *TheControlBar;

class CommandButton
{
public:
	Bool isReady(const Object *sourceObj) const;
};

class AIUpdateInterface
{
public:
	unsigned char m_pad_000[0x34];
	void *m_34;
};

class Object
{
public:
	Bool bfmeCanUseCommandButton(const CommandButton *button) const;

	unsigned char m_pad_000[0x90];
	UnsignedInt m_status90;
	unsigned char m_pad_094[4];
	UnsignedInt m_status98;
	unsigned char m_pad_09C[0x11C - 0x9C];
	UnsignedInt m_model11C;
	UnsignedInt m_model120;
	unsigned char m_pad_124[0x204 - 0x124];
	AIUpdateInterface *m_ai;
};

class AutoAbilityBehavior
{
public:
	Bool bfmeCanAutoFire() const;

private:
	unsigned char m_pad_000[8];
	Object *m_object;
	unsigned char m_pad_00C[0x20 - 0x0C];
	AsciiString m_command;
};

// ?bfmeCanAutoFire@AutoAbilityBehavior@@QBE_NXZ
Bool AutoAbilityBehavior::bfmeCanAutoFire() const
{
	Object *obj = m_object;
	const CommandButton *button = TheControlBar->findCommandButton(m_command);
	if (!button->isReady(obj))
		return false;
	if (!obj->bfmeCanUseCommandButton(button))
		return false;
	if (obj->m_model11C & 0x03000000)
		return false;
	if (obj->m_model120 & 0x02000000)
		return false;

	UnsignedInt status90 = obj->m_status90;
	if ((status90 & 0x8000) != 0 && (status90 & 0x20000) == 0)
		return false;
	if (obj->m_status98 & 0x200)
		return false;

	AIUpdateInterface *ai = obj->m_ai;
	if (ai != 0 && ai->m_34 != 0)
		return false;
	return true;
}
