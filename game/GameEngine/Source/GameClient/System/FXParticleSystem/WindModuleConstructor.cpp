// Wind-family constructor at RVA 0x005FEAD0, complete 271 bytes.
// The DefaultModuleTag<7> factory and the retail source-path/name literals
// establish the family; the concrete historical class name is unresolved.
// The retail primary address point is [deleting dtor, update, purecall,
// refresh].  The +0x14 and +0x18 address points each contain one pure
// virtual entry; the +0x1c WindInfo address point is [dtor, no-op, name,
// refresh].  The constructor body and float/RNG semantics are frozen from
// the exact shape3 source.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

extern float GetGameClientRandomValueReal(float low, float high,
	char *file, int line);

namespace FXParticleSystem
{

class ParticleSystem;
class BfmeFlagTarget;
template <class T> class TrackingPtr { };

class Rva005FEA50PrimaryBase
{
public:
	virtual ~Rva005FEA50PrimaryBase();
	virtual void update();
	virtual void unknown() = 0;
	virtual void refresh(BfmeFlagTarget *target);
private:
	unsigned int m_padding[4];
};

class Rva005FEA50SecondBase
{
public:
	virtual void unknown() = 0;
};

class Rva005FEA50ThirdBase
{
public:
	virtual void unknown() = 0;
};

class Rva005FEA50WindInfoBase
{
public:
	virtual ~Rva005FEA50WindInfoBase();
	virtual void noOp();
	virtual const char *name() const;
	virtual void refresh(BfmeFlagTarget *target);
};

class Rva005FEA50Base
	: public Rva005FEA50PrimaryBase,
	  public Rva005FEA50SecondBase,
	  public Rva005FEA50ThirdBase,
	  public Rva005FEA50WindInfoBase
{
public:
	Rva005FEA50Base(TrackingPtr<ParticleSystem> &system, const void *source);
	virtual ~Rva005FEA50Base();
};

class DefaultModuleTemplate7 { };

class Rva005FEAD0DefaultModule7 : public Rva005FEA50Base
{
public:
	Rva005FEAD0DefaultModule7(TrackingPtr<ParticleSystem> &system,
		const DefaultModuleTemplate7 *source);
	virtual void update();
	virtual void refresh(BfmeFlagTarget *target);
private:
	unsigned int m_value20;
	unsigned int m_value24;
	unsigned int m_value28;
	unsigned int m_value2c;
	float m_windAngle;
	unsigned int m_windAngleChange;
	unsigned int m_windAngleChangeMin;
	unsigned int m_windAngleChangeMax;
	float m_windMotionStartAngle;
	float m_windMotionStartAngleMin;
	float m_windMotionStartAngleMax;
	float m_windMotionEndAngle;
	float m_windMotionEndAngleMin;
	float m_windMotionEndAngleMax;
	unsigned char m_windMotionMovingToEndAngle;
	unsigned char m_padding59[3];
	unsigned int m_value5c;
	unsigned int m_value60;
};

Rva005FEAD0DefaultModule7::Rva005FEAD0DefaultModule7(
	TrackingPtr<ParticleSystem> &system,
	const DefaultModuleTemplate7 *source)
	: Rva005FEA50Base(system, source)
{
	const unsigned char *sourceBytes = (const unsigned char *)source;
	const char *file =
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp";
	m_value20 = *(const unsigned int *)(sourceBytes + 0x0c);
	m_value24 = *(const unsigned int *)(sourceBytes + 0x10);
	m_value28 = *(const unsigned int *)(sourceBytes + 0x14);
	m_value2c = *(const unsigned int *)(sourceBytes + 0x18);
	m_windAngleChange = *(const unsigned int *)(sourceBytes + 0x20);
	m_windAngleChangeMin = *(const unsigned int *)(sourceBytes + 0x24);
	m_windAngleChangeMax = *(const unsigned int *)(sourceBytes + 0x28);
	m_windMotionStartAngleMin = *(const float *)(sourceBytes + 0x30);
	m_windMotionStartAngleMax = *(const float *)(sourceBytes + 0x34);
	m_windMotionEndAngleMin = *(const float *)(sourceBytes + 0x3c);
	m_windMotionEndAngleMax = *(const float *)(sourceBytes + 0x40);
	m_windMotionMovingToEndAngle = *(sourceBytes + 0x44);
	m_windMotionStartAngle = GetGameClientRandomValueReal(
		m_windMotionStartAngleMin, m_windMotionStartAngleMax, (char *)file, 0xe1);
	m_windMotionEndAngle = GetGameClientRandomValueReal(
		m_windMotionEndAngleMin, m_windMotionEndAngleMax, (char *)file, 0xe2);
	m_windAngle = GetGameClientRandomValueReal(
		m_windMotionStartAngle, m_windMotionEndAngle, (char *)file, 0xe3);
	m_value5c = *(const unsigned int *)(sourceBytes + 0x48);
	m_value60 = *(const unsigned int *)(sourceBytes + 0x4c);
}

}
