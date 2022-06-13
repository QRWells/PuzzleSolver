add_defines("SRC")
add_rules("mode.release", "mode.debug")
target("PuzzleSolver")
    set_kind("binary")
    set_languages("c++20")

    add_includedirs("$(curdir)/include")

    add_files("$(curdir)/src/**.cc")
target_end()