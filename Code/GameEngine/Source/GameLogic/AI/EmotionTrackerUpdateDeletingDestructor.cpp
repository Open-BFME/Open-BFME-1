// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: EmotionTrackerUpdate scalar-deleting destructor at retail RVA
// 0x00290190 (30 bytes).  Its wrapper calls the exact complete destructor at
// 0x0028FCC0 through ILT 0x0000922D.  The matched constructor at 0x00290740,
// typed module factories, and module-name getter establish the class identity
// independently of the generated placeholder.

class EmotionTrackerUpdate
{
public:
	virtual ~EmotionTrackerUpdate();
};

void forceEmotionTrackerUpdateDeletingDestructor()
{
	EmotionTrackerUpdate value;
}
