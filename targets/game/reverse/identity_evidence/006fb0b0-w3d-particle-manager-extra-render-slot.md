# 0x006FB0B0: extra particle-render slot in table VA 0x0112039C

Correction: this document establishes an address-qualified owner/table association,
not the native spelling W3DParticleSystemManager. This supersedes the original
OWNER PROVEN claim in commit b6d2b8873e and its outcome record. Existing
constructor/getter/queue labels are reconstruction names, not independent native
naming evidence. The original class and virtual spellings remain unresolved.
Addresses are retail RVAs except explicitly labelled VAs. Retail-1.03-unpacked
PE/Capstone inspection supplies all routes and instructions below.

Only ILT RVA `0x0002B161` transfers to the 835-byte body. Its stub VA
`0x0042B161` occurs once at VA `0x011203CC`, slot 12 of primary table VA
`0x0112039C`. The existing matched constructor-shaped body
`0x006FA630` installs this final primary table (immediate at `0x006FA671`);
matched destructor `0x006FA6F0` restores it (immediate at `0x006FA70F`). Both
are reconstructed in `W3DDisplay_ctor.cpp`; their source labels alone do not
prove the native class names.

Nearby primary slots corroborate the shared receiver layout and rendering role:
The identities below are existing labels or shape descriptions, not native naming proof:

| Slot | Body RVA | Existing label / shape |
|---:|---:|---|
| 9 | 0x006FA6D0 | W3DParticleSystemManager::getOnScreenParticleCount |
| 10 | 0x005BE6F0 | ParticleSystemManager::setOnScreenParticleCount |
| 11 | 0x006FA9B0 | separate doParticles-shaped rendering body |
| **12** | **0x006FB0B0** | **this BFME extra rendering virtual** |
| 13 | 0x006FA030 | W3DParticleSystemManager::queueParticleRender |
| 14 | 0x005CB720 | separate asset-preload-shaped body |

The slot-9 getter reads receiver `+0x90`; this body resets that same particle
count at `0x006FB0D3`, then takes its sole stack argument's first pointer as a
CameraClass receiver and calls Update_Frustum at `0x006FB0DE`. Native camera,
particle processing and SortingRendererClass::Flush calls corroborate a render
pass receiving a RenderInfoClass-like argument. Final RET 4 at `0x006FB3F0`,
followed by INT3 at `0x006FB3F3`, establishes 835 bytes and one stack word.

Zero Hour's ParticleSystemManager declaration has doParticles immediately before
queueParticleRender. BFME inserts this additional slot between the sibling
`0x006FA9B0` and the slot-13 queue-shaped virtual. The canonical queue
source explicitly associates the ready-to-render flag at `+0xBC` with the
separate `0x006FA9B0` body. Thus the extra slot must not inherit doParticles's
name merely by using a shifted Zero Hour declaration order.

A future conversion should retain an address-qualified owner and method until
an independent native naming anchor establishes the original spellings. Existing 840-byte/560-difference bank remains
nonmatching and unchanged; no row, pin or production source is changed here.
