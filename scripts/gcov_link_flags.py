"""
Extra PlatformIO build script: adds -lgcov to the native-coverage linker
command. PlatformIO's build_flags passes -fprofile-arcs/-ftest-coverage to
the compiler but not the gcov library to the linker — this bridges that gap.
"""
Import("env")  # noqa: F821 (SCons environment injected by PlatformIO)
env.Append(LIBS=["gcov"])  # LIBS appends after object files; LINKFLAGS goes before (wrong order for ld)
