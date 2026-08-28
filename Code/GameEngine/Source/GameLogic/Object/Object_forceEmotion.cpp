// cl: /DNDEBUG /MD /EHsc

enum EmotionType
{
	EMOTION_INVALID = -1
};

class Object;

class EmotionTrackerUpdate
{
public:
	void forceEmotion(EmotionType emotion, float duration, const Object *source);
};

class Object
{
public:
	void forceEmotion(EmotionType emotion, float duration, const Object *source);

private:
	unsigned char m_bfmePrefix[0x1f8];
	EmotionTrackerUpdate *m_emotionTracker;
	unsigned char m_bfmeMiddle[0x18];
	Object *m_containedBy;
};

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
