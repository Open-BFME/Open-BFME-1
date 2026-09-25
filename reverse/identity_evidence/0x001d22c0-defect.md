# `Object::defect` identity and field names

The matched `CaveContain::changeTeamOnAllConnectedCaves` body in
`Code/GameEngine/Source/GameLogic/Object/Contain/CaveContainChangeTeamOnAllConnectedCaves.cpp`
calls `Object::defect` for each connected cave. That call names the retail
body at RVA `0x001D22C0` as `Object::defect`.

The Zero Hour reference implementation of `Object::defect` in
`reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Object.cpp`
checks whether the object is contained. It checks radar data before raising the
infiltration event. It changes the team, idles the AI, marks partition data
dirty, and starts the defection timer. The reference header at
`reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h`
declares those members as `m_ai`, `m_radarData`, `m_containedBy`, and
`m_partitionData`. Retail instructions place them in BFME at offsets `0x204`,
`0x20C`, `0x214`, and `0x3B0`.

The banked draft called its local ABI adapter `BfmeDefectAICommandCall`. That
adapter did not name a retail class. The indirect lookup thunk at RVA
`0x00024D70` already has the `AICommandInterface::aiIdle` pin in
`reverse/symbols.csv`, the ledger that maps thunk addresses to symbols. The
landed adapter keeps that address in `Rva00024D70AICommandCall` and does not
claim a separate class identity.
