# Locomotor template field at +0xE9

Retail loads a byte at `+0xE9` and tests it before choosing between terrain samples at three box corners and the default normal path.

`python3 tools/name_oracle.py --class LocomotorTemplate --offset 0xE9` reports no BFME witness. It also reports no Zero Hour member at that offset. The banked source called the field `m_flagE9`, but no layout witness names its purpose. The landed source uses `m_fieldE9` to keep the offset and leave the purpose open.
