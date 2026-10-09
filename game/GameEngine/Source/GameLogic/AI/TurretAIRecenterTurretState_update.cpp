// cl: /O2 /DNDEBUG /MD
// BFME Recenter/IdleScan updates: no OBJECT_STATUS_UNDER_CONSTRUCTION guard.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1
};

class TurretAIData
{
public:
	float m_turnRate;
	float m_pitchRate;
	float m_naturalTurretAngle;
	float m_naturalTurretPitch;
};

class TurretAI
{
public:
	bool friend_turnTowardsAngle(float desiredAngle, float rateModifier, float relThresh);
	bool friend_turnTowardsPitch(float pitch, float rateModifier);

	float getNaturalTurretAngle() const { return m_data->m_naturalTurretAngle; }
	float getNaturalTurretPitch() const { return m_data->m_naturalTurretPitch; }

private:
	unsigned char m_pad[8];
	const TurretAIData *m_data;
};

class TurretStateMachine
{
public:
	TurretAI *getTurretAI() const { return m_turretAI; }

private:
	unsigned char m_pad[0x44];
	TurretAI *m_turretAI;
};

class TurretState
{
public:
	virtual StateReturnType update() = 0;

protected:
	// TurretState::getTurretAI is expanded through a TU-static helper: this
	// partial layout's copy differs from the canonical COMDAT other TUs keep.
	friend TurretAI *turretOf(TurretState *state);

	unsigned char m_padAfterVptr[0x18];
	TurretStateMachine *m_machine;
};

static __forceinline TurretAI *turretOf(TurretState *state)
{
	return state->m_machine->getTurretAI();
}

class TurretAIRecenterTurretState : public TurretState
{
public:
	virtual StateReturnType update();
};

class TurretAIIdleScanState : public TurretState
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_pad20[4];
	float m_desiredAngle;
};

// ?update@TurretAIRecenterTurretState@@UAE?AW4StateReturnType@@XZ
StateReturnType TurretAIRecenterTurretState::update()
{
	TurretAI *turret = turretOf(this);
	bool angleAligned = turret->friend_turnTowardsAngle(turret->getNaturalTurretAngle(), 0.5f, 0.0f);
	bool pitchAligned = turret->friend_turnTowardsPitch(turret->getNaturalTurretPitch(), 0.5f);

	if (angleAligned && pitchAligned)
		return STATE_SUCCESS;

	return STATE_CONTINUE;
}

// ?update@TurretAIIdleScanState@@UAE?AW4StateReturnType@@XZ
StateReturnType TurretAIIdleScanState::update()
{
	bool angleAligned = turretOf(this)->friend_turnTowardsAngle(
		turretOf(this)->getNaturalTurretAngle() + m_desiredAngle, 0.5f, 0.0f);
	bool pitchAligned = turretOf(this)->friend_turnTowardsPitch(
		turretOf(this)->getNaturalTurretPitch(), 0.5f);

	if (angleAligned && pitchAligned)
		return STATE_SUCCESS;

	return STATE_CONTINUE;
}
