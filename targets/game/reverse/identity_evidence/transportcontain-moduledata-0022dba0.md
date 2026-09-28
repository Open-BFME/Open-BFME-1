# TransportContainModuleData fields read by 0x0022DBA0

The banked attempt `targets/game/reverse/attempts/0x0022dba0.cpp`
(`TransportContain::isValidContainerFor`) renamed two module-data fields to
address-derived placeholders. Neither offset is witnessed by
`tools/name_oracle.py` (`TransportContainModuleData+0x1f9` and `+0x208`), and
retail's own body contradicts the earlier guessed names.

| field | old name | new name | retail evidence (`tools/dis_retail.py 0x0022DBA0 285`) |
|---|---|---|---|
| `+0x1f9` | `m_allowTransport` | `m_unknown1f9` | `+0x98..+0xd3`: the byte is read only after `isKindOf(rider, 0x83)` succeeds, and when set the body returns a plain `getContainCount(false) < getContainMax()` capacity test. It never rejects a rider when clear, so it is not an allow/deny gate. |
| `+0x208` | `m_playerMaskBit` | `m_unknown208` | `+0x22..+0x47`: the value is `-1`-guarded and used as a bit index into the container object's words at `Object+0x110`, which landed sources (`Rva0022D830PassengerConditions.cpp`, `AIMoveAndDeleteState_onEnter.cpp`, `SlowDeathBehavior_beginSlowDeath.cpp`) establish as the 320-bit `m_modelConditionFlags`. It is a model-condition bit, not a player-mask bit. |

The semantic name of either field is not proven, so both keep the address
token. The corrected body raised the bank's score from 0.72 to 0.88.
