# Verified BFME2 donor refresh at2026-11-16T18:38:17.430214+00:00

The clean read-only donor checkout advances aa505f34c898e6fb7c9a1f1632e75ce232f4829a ->0630f0ef47d0a818bb2e97583b43cfb1ecd35491, official Open-BFME/Open-BFME-2 master fetched this session. No nested reference was initialized. Changed donor paths/flags were inventoried locally; no BFME1 build path was redirected into the donor.

The successful stable-input scan checks53,267 donor bodies and791,090 placements:4,821 exact-unique,25,778 near,759,888 exact-multi,450 truncated,153 string-conflict. These are discovery buckets, not recovered identities or new verified rows. Linking and source sweeps completed against those inputs. The earlier concurrent scan was rejected after the native EH writer changed functions.csv; that obsolete scan is not used as verification.

Both old AddDecal trial manifests were stale (source, build.py and donor string_base.h hashes). The same donor source Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/Rva0010C065AddDecal.cpp was recompiled through bfme2_sweep.py compile; all mapped include directories exist and the native trial records actual dependency/include traces. Fresh trial2db8c8083a6646fcbcd744608b432805 matches only two exact-multi placements, with no recovery landed. Those old stale hashes are not all attributed to this particular pointer update.

The ordinary BFME1 compile-receipt inventory contains22,723 receipts and zero references to open-bfme-2. No BFME1 shared compiler input, header, flag, image or function identity/extent changes in this refresh. The reference is evidence, not an engine build dependency. No full-byte-gate pass is claimed: the existing two independent DIR32 blockers are recorded separately. Normal hooks still apply.

Local evidence: diagnostics/continue-20261116-fivehundred/bfme2-scan-0630f0ef-stable-ledger.log, bfme2-linking-0630f0ef.log, bfme2-sources-0630f0ef.log, bfme2-trials-0630f0ef.json and no-bfme2-build-input.json. The ignored successful-check marker is written only after these checks. Native tools/verifiers/baselines are unchanged. This housekeeping does not increment the500-task counter, currently115.
