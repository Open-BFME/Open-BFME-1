"""The bash that runs the repository's shell scripts: `[bash_path.bash(), script, ...]` with `env=bash_path.env()`.

On Windows a bare "bash" reaches WSL's System32\\bash.exe before PATH is searched, and
`shutil.which("bash")` does too outside Git Bash; WSL cannot run build.sh or the hooks.
This returns Git for Windows' usr/bin/bash.exe, which keeps PATH as given, and env() puts
Git's mingw64/bin and usr/bin before System32 but behind a caller's stub folders (bin/bash.exe
would put them in front of the stubs). Elsewhere: "bash" and os.environ.
"""
import os
from pathlib import Path
import shutil


def _roots(git, program_files):
    """Candidate Git for Windows installation roots, the one on PATH first."""
    roots = list(Path(git).parents) if git else []
    roots.append(Path(program_files) / "Git")
    return roots


def _find(system, git, program_files):
    if system != "nt":
        return "bash"
    for root in _roots(git, program_files):
        candidate = root / "usr" / "bin" / "bash.exe"
        if candidate.is_file():
            return str(candidate)
    raise RuntimeError("Git for Windows' usr/bin/bash.exe not found (is git on PATH?); "
                       "WSL's bash.exe cannot run the repository's shell scripts")


def _key(folder):
    return os.path.normcase(os.path.normpath(folder))


def bash():
    """Path of the bash to run a repository shell script with."""
    return _find(os.name, shutil.which("git"), os.environ.get("ProgramFiles", r"C:\Program Files"))


def env(base=None):
    """A copy of `base` (default os.environ) whose PATH reaches Git's tools before System32 on Windows.
    Git's folders go in front of the inherited PATH, as Git sets it for hooks, but behind any folder a caller put first."""
    result = dict(os.environ if base is None else base)
    if os.name != "nt":
        return result
    root = Path(bash()).parents[2]
    git = [str(root / "mingw64" / "bin"), str(root / "usr" / "bin")]
    ours = {_key(p) for p in git}
    parts = [p for p in result.get("PATH", "").split(os.pathsep) if p and _key(p) not in ours]
    host = {_key(p) for p in os.environ.get("PATH", "").split(os.pathsep) if p}
    cut = next((i for i, p in enumerate(parts) if _key(p) in host), len(parts))
    result["PATH"] = os.pathsep.join(parts[:cut] + git + parts[cut:])
    return result
