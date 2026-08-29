// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Object model-condition replacement wrapper, retail 0x001C4830,
// 92 bytes.  BFME keeps ten condition-mask dwords on Object at +0x110.  It
// snapshots and replaces all ten, then notifies the Drawable at +0x80 when the
// value changed or the caller explicitly forces a refresh.

typedef unsigned int UnsignedInt;
typedef bool Bool;

class ModelConditionFlags
{
public:
	Bool operator!=(const ModelConditionFlags &other) const;

private:
	UnsignedInt m_bits[10];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		Bool forceReplace, UnsignedInt value);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void replaceModelConditionFlags(const ModelConditionFlags &flags,
		Bool forceReplace);

private:
	unsigned char m_unmodelled_000[0x80];
	Drawable *m_drawable;
	unsigned char m_unmodelled_084[0x110 - 0x84];
	ModelConditionFlags m_modelConditionFlags;
};

// ?replaceModelConditionFlags@Object@@QAEXABVModelConditionFlags@@_N@Z
void Object::replaceModelConditionFlags(const ModelConditionFlags &flags,
	Bool forceReplace)
{
	ModelConditionFlags oldFlags = m_modelConditionFlags;
	m_modelConditionFlags = flags;

	if (oldFlags != m_modelConditionFlags || forceReplace)
	{
		if (m_drawable)
		{
			m_drawable->replaceModelConditionState(m_modelConditionFlags,
				forceReplace, 0);
		}
	}
}
