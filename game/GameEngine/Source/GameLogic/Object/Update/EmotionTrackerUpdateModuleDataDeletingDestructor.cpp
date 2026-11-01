// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: EmotionTrackerUpdateModuleData scalar-deleting destructor at
// retail RVA 0x00290160 (30 bytes).  Its wrapper calls the exact complete
// destructor at 0x0028FBB0 through ILT 0x0004AED5.  The matched constructor at
// 0x0028F910, typed module-data factory, and recovered module-data layout
// establish the class identity independently of the generated placeholder.

class EmotionTrackerUpdateModuleData
{
public:
	virtual ~EmotionTrackerUpdateModuleData();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceEmotionTrackerUpdateModuleDataDeletingDestructor(const EmotionTrackerUpdateModuleData &that)
{
	EmotionTrackerUpdateModuleData value(that);
}
