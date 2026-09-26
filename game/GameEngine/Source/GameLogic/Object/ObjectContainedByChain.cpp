// cl: /DNDEBUG /MD /EHsc

// The two Object bodies that climb the containment chain to find a helper:
//
//   forceEmotion                   0x001C2030  up to the first object that HAS one
//   bfmeApplySpecialModelCondition 0x001C1FB0  up to the last object in the chain
//
// They read the same two fields, +0x1F8 and +0x214, and they sat in two files
// that named both of them differently -- forceEmotion said m_emotionTracker and
// m_containedBy, bfmeApplySpecialModelCondition said m_smcHelper and m_next. Two
// names for one field is the ordinary shape here; what makes this pair worth
// separating out is that the disagreement was about what the chain IS.
//
// +0x214 is m_containedBy. Object.h has m_containedBy and has no m_next at all,
// and the semantics fit both bodies once it is read that way: walking it to the
// end is walking out to the outermost container, which is a sensible target for a
// forced model condition, and stopping at the first link that has an emotion
// tracker is a sensible way to find the tracker that owns you. The merged
// declaration says m_containedBy.
//
// +0x1F8 is one pointer, so it has one type, and the two bodies call two
// different non-virtual methods on it:
//
//   ?bfmeApply@BfmeSMCTarget@@QAEXHPBXH@Z              ILT 0x0002AD88, body 0x0028EEB0
//   ?forceEmotion@EmotionTrackerUpdate@@QAEXW4EmotionType@@MPBVObject@@@Z
//                                                      ILT 0x0003F4EF, body 0x0028F3E0
//
// Those two bodies are 0x530 apart, in the same stretch of the image as
// EmotionTrackerUpdate's other matched rows (createEmotion's ILT, the entry
// destructor at 0x00028FCE). That is evidence -- not proof -- that BfmeSMCTarget
// is EmotionTrackerUpdate under an address-derived name given by a converter who
// could only see the one body. Both spellings are kept because
// ?bfmeApply@BfmeSMCTarget@@... is a matched pin and renaming it is identity work,
// but the member is declared once, as the emotion tracker, and the model-condition
// body casts. If the two classes are later shown to be one, this file is the only
// place that has to change.
//
// bfmeApplySpecialModelCondition came here out of ObjectModelConditions.cpp. It
// was grouped there by its name, but it never touches the condition flags at
// +0x110: its whole job is this walk.

typedef int Int;

class Object;

enum EmotionType
{
	EMOTION_INVALID = -1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EmotionTracker.h
class EmotionTrackerUpdate
{
public:
	void forceEmotion(EmotionType emotion, float duration, const Object *source);
};

// The same object at Object+0x1F8, under the spelling its other matched method is
// pinned as; see the note above.
class BfmeSMCTarget
{
public:
	void bfmeApply(Int condition, const void *animation, Int frames);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void forceEmotion(EmotionType emotion, float duration, const Object *source);
	void bfmeApplySpecialModelCondition(Int condition, const void *animation, Int frames);

private:
	unsigned char m_unmodelled_000[0x1f8];
	EmotionTrackerUpdate *m_emotionTracker;		// +0x1F8
	unsigned char m_unmodelled_1fc[0x214 - 0x1fc];
	Object *m_containedBy;				// +0x214
};

// ?forceEmotion@Object@@QAEXW4EmotionType@@MPBV1@@Z
void Object::forceEmotion(EmotionType emotion, float duration, const Object *source)
{
	Object *object = this;
	while (object->m_emotionTracker == 0)
	{
		object = object->m_containedBy;
		if (object == 0)
			return;
	}

	object->m_emotionTracker->forceEmotion(emotion, duration, source);
}

// ?bfmeApplySpecialModelCondition@Object@@QAEXHPBXH@Z
//
// The retail spelling and the optional descriptor's canonical type are
// unrecovered. The bytes prove the chain traversal and all three arguments
// forwarded unchanged to the outermost object's helper.
void Object::bfmeApplySpecialModelCondition(Int condition, const void *animation, Int frames)
{
	Object *last = this;
	while (last->m_containedBy != 0)
		last = last->m_containedBy;

	if (last->m_emotionTracker != 0)
		reinterpret_cast<BfmeSMCTarget *>(last->m_emotionTracker)->bfmeApply(
			condition, animation, frames);
}
