# CDownload: use the existing FTP providers

Base `fa0e931f56333ff7723620bf920a5715baa2b709`. Consumer
`game/Libraries/Source/WWVegas/WWDownload/CDownloadDownloadFile.cpp`.
Only three external call bindings change; its three existing row identities,
class layout, inline RestartFrom implementation and behavior are preserved.

## Independent BFME1 contracts

The complete caller/callee evidence in `00884ec0-pumpmessages.md` was read
before editing. Fresh `tools/callees.py 0x00884EC0 1065` corroborates:

| Caller relocation | Direct retail body | Existing provider and contract |
| --- | --- | --- |
| +0xBE | 0x00885D90 | `Cftp::LoginToServer(const char *, const char *)`, thiscall, EAX status, RET8 |
| +0x22D | 0x00886A20 | `Rva00886A20Class::d_00886a20(const char *, int)`, thiscall, EAX file position, RET8 |
| +0x2A7 | 0x00886520 | `Cftp::GetNextFileBlock(const char *, int *)`, thiscall, EAX status, RET8 |

The receiver is unchanged. Recovery's second word is unused by its complete
114-byte implementation; passing the existing registry-pointer bits as its
established int parameter preserves that ABI without a second name or pin.
The local Cftp declaration takes no ownership of layout or provider bodies.
The retained Rva00884Ftp view still owns the existing RestartFrom row and
provides the same +4 socket / +2C file-position accesses.
No ILT substitution occurs: these three calls remain direct body calls.

## Donor evidence and adaptation

Read-only BFME2 `76f0baefa6f285d54bc1ca922397674312a5913f` already contains
this repair in `Code/Libraries/Source/WWVegas/WWDownload/Download.cpp`, including
the neutral recovery-provider declaration, pointer-to-int argument, and Cftp
LoginToServer/GetNextFileBlock bindings. Its `FTP.CPP` supplies the related
provider implementations and records their donor context. This is inherited
binding guidance, not independent proof of BFME1 addresses or layout.

BFME2's Download.cpp corresponds to BFME1's split CDownloadDownloadFile.cpp;
its consolidated FTP.CPP corresponds to the three existing BFME1 provider TUs.
No donor TU, include flags, class layout or provider body is imported. Local
casts preserve the existing BFME1 RestartFrom identity rather than adopting
the donor's broader consolidated class declaration. The donor gitlink stays
unchanged; the newer fetched official HEAD was not used for this repair.

## Validation and limits

Same lane-private Wine11.16 WoW64/MSVC7.1 runner as the water batch, with
WINEARCH=win64 and BUILD_POOL=2 (supervisor-approved host correction).
Before: normal scoped consumer gate3/3. After: normal build of consumer,
CftpLoginToServer.cpp, CftpGetNextFileBlock.cpp and Rva00886A20.cpp passes
**7/7** functions,20 literals,30 DIR32 references and zero body-guard findings.
A diagnostic asserts strict unmasked bytes and each canonical-name relocation
against the exact direct target above (`build/sol12h-bindings/check_download_routes.py`).

Historical census9ac0d06c54: caller1529non-CC bytes blocked by exactly these
three undefined names; all three provider units linked (2113non-CC bytes).
Current227.4-second preview reports **UNKNOWN for all4 units**, no unresolved
or duplicate diagnostics, because22805current ledger objects cannot be read
in this cold worktree. Consequently current LINKED remains0->0 for the caller;
no census-confirmed unique-byte or new matched-byte gain is claimed. Exact
logs are `build/sol12h-bindings/download-{before-build,after-build,routes,link-after}.log`.
