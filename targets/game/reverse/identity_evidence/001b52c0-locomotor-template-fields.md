# LocomotorTemplate fields measured with the retail compiler

The established constructor (RVA 0x001B52C0, 520 bytes) and assignment
(RVA 0x001B4250, 849 bytes) identify the same 0x140-byte LocomotorTemplate.
Their source comments cite the named allocation/parser callers and vtable.

The offset model refuses their Overridable base. Scratch copies compiled with
their unchanged MSVC 7.1 options instead add nonvirtual static methods returning
each original field address relative to null and its sizeof. Extern-C wrappers
force emission; only relocation-free constant-return machine bodies are accepted.
Both TUs give the offsets below independently. No production layout, base, type,
packing, signature, or size changes, and no probe method enters production.

Names come separately from retail FieldParse table RVA 0x00C9D860 and the same
INI keys' offsetof(LocomotorTemplate, member) in the shipped ZH Locomotor.cpp.
Raw retail records were re-read, not inferred from ZH offsets. field_names.csv
records the join. A field spanning another witnessed offset is refused, as are
non-placeholder names, duplicate declaration spellings and existing target names.

Only these unique field spellings and their uses change in the two TU-local views:

| Original field | Proven offset | New field | Retail INI key |
|---|---:|---|---|
| `m_d50` | `0x50` | `m_minTurnSpeed` | `MinTurnSpeed` |
| `m_d60` | `0x60` | `m_circlingRadius` | `CirclingRadius` |
| `m_d64` | `0x64` | `m_speedLimitZ` | `SpeedLimitZ` |
| `m_d68` | `0x68` | `m_maxThrustAngle` | `MaxThrustAngle` |
| `m_d6c` | `0x6c` | `m_behaviorZ` | `ZAxisBehavior` |
| `m_d70` | `0x70` | `m_appearance` | `Appearance` |
| `m_d84` | `0x84` | `m_accelPitchLimit` | `AccelerationPitchLimit` |
| `m_d88` | `0x88` | `m_bounceKick` | `BounceAmount` |
| `m_d8c` | `0x8c` | `m_pitchStiffness` | `PitchStiffness` |
| `m_d90` | `0x90` | `m_rollStiffness` | `RollStiffness` |
| `m_d94` | `0x94` | `m_pitchDamping` | `PitchDamping` |
| `m_d98` | `0x98` | `m_rollDamping` | `RollDamping` |
| `m_d9c` | `0x9c` | `m_pitchByZVelCoef` | `PitchInDirectionOfZVelFactor` |
| `m_da4` | `0xa4` | `m_forwardVelCoef` | `ForwardVelocityPitchFactor` |
| `m_da8` | `0xa8` | `m_lateralVelCoef` | `LateralVelocityRollFactor` |
| `m_db0` | `0xb0` | `m_lateralAccelCoef` | `LateralAccelerationRollFactor` |
| `m_db4` | `0xb4` | `m_uniformAxialDamping` | `UniformAxialDamping` |
| `m_db8` | `0xb8` | `m_turnPivotOffset` | `TurnPivotOffset` |
| `m_dc0` | `0xc0` | `m_closeEnoughDist` | `CloseEnoughDist` |
| `m_c4` | `0xc4` | `m_isCloseEnoughDist3D` | `CloseEnoughDist3D` |
| `m_dc8` | `0xc8` | `m_ultraAccurateSlideIntoPlaceFactor` | `SlideIntoPlaceTime` |
| `m_d0` | `0xd0` | `m_stickToGround` | `StickToGround` |
| `m_dd4` | `0xd4` | `m_canMoveBackward` | `CanMoveBackwards` |
| `m_dc4` | `0xd4` | `m_canMoveBackward` | `CanMoveBackwards` |
| `m_d8` | `0xd8` | `m_hasSuspension` | `HasSuspension` |
| `m_de0` | `0xe0` | `m_maximumWheelCompression` | `MaximumWheelCompression` |
| `m_de4` | `0xe4` | `m_wheelTurnAngle` | `FrontWheelTurnAngle` |
| `m_df0` | `0xf0` | `m_wanderLengthFactor` | `WanderLengthFactor` |
| `m_df4` | `0xf4` | `m_wanderAboutPointRadius` | `WanderAboutPointRadius` |
| `m_e00` | `0x100` | `m_rudderCorrectionDegree` | `RudderCorrectionDegree` |
| `m_e04` | `0x104` | `m_rudderCorrectionRate` | `RudderCorrectionRate` |
| `m_e08` | `0x108` | `m_elevatorCorrectionDegree` | `ElevatorCorrectionDegree` |
| `m_e0c` | `0x10c` | `m_elevatorCorrectionRate` | `ElevatorCorrectionRate` |
