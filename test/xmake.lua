add_defines("TEST")
add_rules("mode.release", "mode.debug")
target("Solver-Test")
    set_kind("binary")
    set_languages("gnu++20")

    add_includedirs("$(curdir)/include")

    add_files("$(curdir)/test/**.cc")
target_end()