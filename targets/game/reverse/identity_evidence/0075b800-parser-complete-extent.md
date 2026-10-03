# Animation speed-factor callback extent

Retail table record VA011240F0 is four DWORDs:
0112402C, 00B5B800, 00000000, 00000000. The key at0112402C is
AnimationSpeedFactorRange; callback VA00B5B800 is RVA0075B800.
GeneralsMD W3DModelDraw.cpp calls this callback parseRealRange and assigns
m_animMinSpeedFactor/m_animMaxSpeedFactor in that order.

The old24B claim ends within the load at0075B815. Full retail and independently
created Ghidra function span55B, returning at0075B836 before INT3 padding.
Two calls each to INI::getNextToken at850970 and INI::scanReal at8526E0
write float results to receiver+1C and+20. Current reference ModelConditionInfo
puts the named fields at98/9C, producing61B. name_oracle also exposes this
incompatible reference view: it reports m_publicBones at1C/20, not the float
stores proven by this callback. Do not rewrite the shared witness or header.
Use a distinct address-labelled local view of the callback storage, retaining
the two twin-proven member names and four-argument callback declaration.
