# BuildAssistant::init (0x000FBE80) and BuildAssistant::reset (0x000FD0B0)

BuildAssistant's table 0x010860D8 (see `000febe0-buildassistant-update.md` and
`000fc010-buildassistant-buildtiledlocations.md`) opens with BFME's
SubsystemInterface block. Its anchored slots fix the order:

| slot | ILT | body | ledger before | evidence |
|---|---|---|---|---|
| 0 | 0x0002D934 | 0x000FE210 | deleting dtor | `??_G` shape |
| 1 | 0x0003620F | 0x000FBE80 | `Rva000FBE80Noop` | **init** |
| 2 | (direct) | 0x009A1A50 | `SubsystemInterface::loadIniFilesFromLegend` | BFME insertion |
| 3 | 0x000436B2 | 0x00067930 | `SubsystemInterface::postProcessLoad` | matched real name |
| 4 | 0x0004623B | 0x000FD0B0 | `BfmeListAndArray::bfmeClear` | **reset** |
| 5 | 0x0003FE72 | 0x000FEBE0 | `BuildAssistant::update` | matched real name |
| 6 | 0x00033497 | 0x00067940 | shared base default | draw |

Zero Hour's SubsystemInterface declares `~SubsystemInterface`, `init`,
`postProcessLoad`, `reset`, `update`, `draw`; BFME inserts
`loadIniFilesFromLegend` after `init`. With postProcessLoad (3) and update (5)
matched under their real names, slot 1 is `init` and slot 4 is `reset`.
`callers_of.py` finds no direct caller of either body: both are reached only
through these slots.

- 0x000FBE80 is a lone `ret`. Zero Hour's init allocated `m_buildPositions`;
  BFME's buildTiledLocations (0x000FC010) grows that array on demand.
- 0x000FD0B0 is Zero Hour's reset on BuildAssistant's layout: it destroys the
  ObjectSellInfo of every node of `m_sellList` (this+0x10, the list sellObject
  pushes onto and xferTheSellList serializes), frees the nodes and relinks the
  sentinel (`m_sellList.clear()`), then deletes the Coord3D array
  `m_buildPositions` (this+0x08) and zeroes `m_buildPositionSize` (this+0x0C),
  the two fields buildTiledLocations reallocates.
