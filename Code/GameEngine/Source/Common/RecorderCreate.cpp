// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	RecorderClass();

private:
	unsigned char m_data[0x2b4];
};

RecorderClass *createRecorder()
{
	return new RecorderClass;
}
