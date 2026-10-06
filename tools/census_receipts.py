"""Fresh compile evidence for census inputs that cannot use the reusable cache.

These receipts never make build.compile_is_current true. Every later --build
recompiles these TUs; verifying an existing census reruns the actual preprocessor
and checks the successful compilation's object and opened-input hashes.
"""
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import uuid

import build


_VOLATILE = re.compile(rb'\b__(?:TIME|DATE|TIMESTAMP)__\b')
_LINE = re.compile(rb'^#line\s+\d+\s+"((?:\\.|[^"\\])*)"', re.MULTILINE)
_CLOCK_OUTPUT = re.compile(rb'\b\d{2}:\d{2}:\d{2}\b|\b(?:Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec) +\d{1,2} +\d{4}\b')


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _search_root_keys(output):
    try:
        meta = json.loads(build._deps_sidecar(output).read_text())
        keys = meta.get("search_roots", [])
    except (OSError, ValueError, TypeError):
        return []
    if not isinstance(keys, list):
        return []
    return [key for key in keys if isinstance(key, str)]


def _has_external_search_root(output):
    """Whether the reusable sidecar depends on a directory above this tree."""
    for key in _search_root_keys(output):
        root = build._root_from_key(key)
        if root is None:
            return True
        try:
            root.resolve().relative_to(build.ROOT.resolve())
        except (OSError, RuntimeError, ValueError):
            return True
    return False


def _has_checkout_root_search_root(output):
    """Whether the sidecar inventories the whole checkout as an /I root.

    link_census stages link_status.tmp under the checkout while judging. That
    transient file changes this broad inventory even though it is not a C/C++
    input. Keep a fresh preprocessor proof for such TUs so judgment can check
    actual opened inputs instead of treating every checkout file as an input.
    """
    checkout = build.ROOT.resolve()
    for key in _search_root_keys(output):
        root = build._root_from_key(key)
        if root is not None:
            try:
                if root.resolve() == checkout:
                    return True
            except (OSError, RuntimeError):
                continue
    return False


def needs_fresh_receipt(output):
    """Whether a mutable broad search root needs a fresh input proof."""
    return (_has_external_search_root(output)
            or _has_checkout_root_search_root(output))


def _normal_cache_current(source, output):
    try:
        return build.compile_is_current(source, output)
    except (OSError, ValueError, TypeError, subprocess.SubprocessError, SystemExit):
        return False


def signature(command, env):
    return {"command": command, "fingerprint": build._cmd_fingerprint(command, env),
            "implicit_flags": [env.get("CL", ""), env.get("_CL_", "")]}


def opened_paths(source, include_output):
    paths = {str(source.resolve())}
    for line in include_output.decode("latin-1").splitlines():
        if not line.startswith("Note: including file:"):
            continue
        name = line.split("Note: including file:", 1)[1].strip()
        host = build._host_path(name)
        resolved = build._case_resolve(host) if host else None
        if resolved is None:
            raise ValueError(f"unresolved preprocessor include: {name}")
        paths.add(str(Path(resolved).resolve()))
    return paths


PREPROCESS_TIMEOUT = 600  # seconds; BFME_PREPROCESS_TIMEOUT overrides it


def preprocess_timeout():
    value = os.environ.get("BFME_PREPROCESS_TIMEOUT", "").strip()
    if not value:
        return PREPROCESS_TIMEOUT
    try:
        seconds = float(value)
    except ValueError:
        seconds = 0
    if seconds <= 0:
        raise ValueError(f"BFME_PREPROCESS_TIMEOUT must be a positive number of seconds, not {value!r}")
    return seconds


def capture_preprocessor(command, env):
    # cl.exe -E can spin forever under Wine after reporting C1083. A fatal
    # error that does not end the process, or a process still running at the
    # timeout, has its whole process tree killed and takes the ordinary
    # failed-preprocess path (build.watch_compiler).
    timeout = preprocess_timeout()
    return build.watch_compiler(
        command, env, merge_output=False, timeout=timeout,
        timeout_note=b"preprocessor timed out after %g s (BFME_PREPROCESS_TIMEOUT)" % timeout)


def snapshot(source, command, env):
    # VC7.1 ML /EP fails with A1018 writing NUL; do not treat its partial output
    # as complete input evidence. Header-free assembler uses the normal cache.
    if source.suffix.lower() == ".asm":
        raise ValueError("MASM preprocessing does not provide complete input evidence")
    pp = [arg for arg in command if not arg.startswith(("-Fo", "/Fo"))]
    if "-c" not in pp:
        raise ValueError("unrecognized compilation command")
    pp[pp.index("-c")] = "-E"
    result = capture_preprocessor(pp + ["-showIncludes"], env)
    if result.returncode:
        raise ValueError("preprocessor failed: " + result.stderr.decode("latin-1")[-1200:])
    # MSVC 7.1 ignores /D and /U attempts to replace these reserved macros.
    # Token-pasting can construct their names without a literal source token.
    # Their expansion is a date/time string (also in #line/include operands),
    # so reject such output conservatively, including constant lookalikes.
    if _CLOCK_OUTPUT.search(result.stdout):
        raise ValueError("date/time output cannot prove the actual compile")
    files = {}
    generations = {}
    # /E sends actual /showIncludes reads to stderr. #line names are display
    # provenance and can deliberately name nonexistent historical paths.
    # Preserve those in the PP hash; only actual include notes name read files.
    paths = opened_paths(source, result.stderr + b"\n" + result.stdout)
    directives = build._directive_text(source)
    if len(paths) == 1 and (directives is None or build._INCLUDE_DIRECTIVE.search(directives)):
        raise ValueError("preprocessor omitted actual include notes")
    for path in sorted(paths):
        prior = Path(path).stat()
        raw = Path(path).read_bytes()
        following = Path(path).stat()
        stamp = lambda st: (st.st_dev, st.st_ino, st.st_size, st.st_mtime_ns, st.st_ctime_ns)
        if stamp(prior) != stamp(following):
            raise ValueError(f"input changed while reading: {path}")
        # Conservative rejection also covers inactive branches and comments.
        # These compiler-generated values cannot prove the actual compile from
        # a separate preprocessor invocation, even when two probes happen in
        # the same second. Never normalize them away.
        spliced = re.sub(rb'\\\r?\n', b'', raw)
        if _VOLATILE.search(spliced):
            raise ValueError(f"volatile predefined macro in {path}")
        files[path] = hashlib.sha256(raw).hexdigest()
        generations[path] = list(stamp(following))
    if not _LINE.search(result.stdout):
        raise ValueError("preprocessor omitted input provenance")
    return {"preprocessed": hashlib.sha256(result.stdout).hexdigest(), "files": files,
            "signature": signature(command, env), "generations": generations}


class Receipts:
    def __init__(self, path, *, run=None, entries=None):
        self.path = Path(path)
        self.run = run or uuid.uuid4().hex
        self.entries = entries or {}

    @classmethod
    def load(cls, path, run):
        try:
            data = json.loads(Path(path).read_text())
            if not run or data["version"] != 1 or data["run"] != run:
                return None
            return cls(path, run=run, entries=data["entries"])
        except (OSError, ValueError, KeyError, TypeError):
            return None

    def save(self):
        self.path.parent.mkdir(parents=True, exist_ok=True)
        temporary = self.path.with_suffix(".tmp")
        temporary.write_text(json.dumps({"version": 1, "run": self.run, "entries": self.entries}))
        temporary.replace(self.path)

    def before(self, source, output, command, env):
        # Header-free inputs can always prove their build with the normal
        # cache. For all other stale TUs, capture before the actual compiler.
        text = source.read_bytes()
        implicit = env.get("CL") or env.get("_CL_")
        forced = any(arg.lower().startswith(("-fi", "/fi", "-yu", "/yu", "-yc", "/yc", "@"))
                     for arg in command)
        if source.suffix.lower() == ".asm" or (not re.search(rb'^\s*#', text, re.MULTILINE)
                                               and not implicit and not forced):
            return None
        try:
            return snapshot(source, command, env)
        except (OSError, ValueError):
            return None  # A missing-header attempt may be retried by build.py.

    def after(self, source, output, command, env, before, compiler_output):
        sidecar = build._deps_sidecar(output)
        mutable_search = sidecar.exists() and needs_fresh_receipt(output)
        if before is None:
            if sidecar.exists() and not mutable_search and _normal_cache_current(source, output):
                return  # No fresh proof captured; use the normal cache gate.
            raise SystemExit(f"census input proof unavailable: {source}")
        try:
            after = snapshot(source, command, env)
            if before != after:
                raise ValueError("compiler inputs changed during compile")
            # Check each input reported by the actual compile too, including an
            # empty header that a preprocessor could otherwise elide.
            for line in compiler_output.splitlines():
                if not line.startswith("Note: including file:"):
                    continue
                host = build._host_path(line.split("Note: including file:", 1)[1])
                resolved = build._case_resolve(host) if host else None
                if not resolved or before["files"].get(str(Path(resolved).resolve())) != digest(resolved):
                    raise ValueError(f"actual compiler input was not witnessed: {line}")
        except (OSError, ValueError) as error:
            # The normal sidecar may describe the changed files after this
            # compile. Do not leave that receipt able to bless this object.
            build._deps_sidecar(output).unlink(missing_ok=True)
            raise SystemExit(f"census input proof failed: {source}: {error}") from error
        # A normal sidecar inventories directory names, including the entire
        # checkout for /I. and any higher-priority parent include roots. Those
        # roots can gain unrelated files during judgment, so keep the fresh PP
        # proof for such objects even when the sidecar itself remains current.
        if sidecar.exists() and not mutable_search and _normal_cache_current(source, output):
            return  # Captured proof agreed; keep the normal cache semantics.
        self.entries[str(output.resolve())] = {"source": str(source.resolve()),
                                               "object": digest(output), "input": before,
                                               "command": command}

    def current(self, source, output):
        try:
            entry = self.entries[str(output.resolve())]
            if entry["source"] != str(source.resolve()) or entry["object"] != digest(output):
                return False
            command, env = build.compiler_command(source, output)
            # Retry flags are deterministic and stored only for this fresh
            # successful compile; require the base command to be its prefix.
            actual = entry["command"]
            if actual[:len(command)] != command:
                return False
            if actual != command:
                retry = actual[len(command):]
                allowed = [f"-I{build.wine_path(d)}" for d in build._SWEEP_INCLUDE_DIRS if d.exists()]
                if retry != allowed:
                    return False
                env = dict(env)
                env["INCLUDE"] += ";" + ";".join(build.wine_path(d) for d in build._SWEEP_INCLUDE_DIRS if d.exists())
            found = snapshot(source, actual, env)
            # File generations only detect writes across the actual compile,
            # including change-and-restore. Currency requires content hashes
            # and the complete fresh PP stream, never timestamps as proof.
            found.pop("generations")
            expected = {k: v for k, v in entry["input"].items() if k != "generations"}
            return found == expected and digest(output) == entry["object"]
        except (OSError, ValueError, KeyError, TypeError):
            return False
