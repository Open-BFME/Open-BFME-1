# Sourced by every hook before its first python3 call.
#
# The hooks, build.sh and the tools they call all run `python3`. On Windows
# that name is often the Microsoft Store shortcut, which prints "Python was not
# found" and exits 9009; post-merge read that as a failed check, reported a
# clean ledger as corrupt and told a new contributor to dedup and commit it.
# So: when python3 does not start Python 3 but the Windows launcher `py -3`
# does (build.cmd already relies on it), put a python3 that runs `py -3` first
# on PATH; when neither does, say so instead of failing a check.

# require_python3 HOOK [warn]: return when python3 runs Python 3. Otherwise
# explain on stderr and exit the hook: 1, or 0 with "warn" for the hooks that
# cannot block anyway.
require_python3() {
    local probe="import sys; sys.exit(sys.version_info[0] != 3)" shim
    python3 -c "$probe" >/dev/null 2>&1 && return 0
    if py -3 -c "$probe" >/dev/null 2>&1; then
        shim="$(cd "$(git rev-parse --git-common-dir)" && pwd)/python3-shim"
        mkdir -p "$shim" \
            && printf "#!/bin/sh\nexec py -3 \"\$@\"\n" > "$shim/python3" \
            && chmod +x "$shim/python3" \
            && export PATH="$shim:$PATH" \
            && python3 -c "$probe" >/dev/null 2>&1 && return 0
    fi
    cat >&2 <<MSG
=============== $1: NO WORKING PYTHON 3 ===============
\`python3\` here does not start Python 3 (on Windows it is usually the
Microsoft Store shortcut that prints "Python was not found"), and neither
does \`py -3\`. The $1 hook checked NOTHING. Nothing is known to be wrong
with the ledgers: do not run dedup_csv.py or commit ledger changes over it.
  1. Install Python 3 from python.org (tick "Add python.exe to PATH").
  2. Windows: Settings > Apps > Advanced app settings > App execution
     aliases: turn off python.exe and python3.exe.
  3. In a new terminal, \`py -3 --version\` or \`python3 --version\` works.
  4. Rerun: bash tools/setup_hooks.sh
========================================================
MSG
    [ "${2:-}" = warn ] && exit 0
    exit 1
}
