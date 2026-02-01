add_rules("mode.debug", "mode.release")

add_repositories("levimc-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("lordbombardir-repo https://github.com/LordBombardir/xmake-repo.git")

if is_config("target_type", "server") then
    add_requires("levilamina 1.9.2", {configs = {target_type = "server"}})
else
    add_requires("levilamina 1.9.2", {configs = {target_type = "client"}})
end

if is_config("target_type", "server") then
    add_requires("placeholderapi 1.0.0", {configs = {target_type = "server", mode = "release"}})
else
    add_requires("placeholderapi 1.0.0", {configs = {target_type = "client", mode = "release"}})
end

add_requires("levibuildscript")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

option("target_type")
    set_default("server")
    set_showmenu(true)
    set_values("server", "client")
option_end()

target("Translator") -- Change this to your mod name.
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")

    add_cxflags("/EHa", "/utf-8", "/W4", "/w44265", "/w44289", "/w44296", "/w45263", "/w44738", "/w45204")
    add_defines("NOMINMAX", "UNICODE")

    add_packages("levilamina")
    add_packages("placeholderapi")

    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")

    add_headerfiles("src/**.h")
    add_files("src/**.cpp")
    add_includedirs("src")

    if is_config("target_type", "server") then
        add_defines("LL_PLAT_S")
    else
        add_defines("LL_PLAT_C")
    end

    after_build(function (target)
        local binDirectory = path.join(os.projectdir(), "bin")
        
        os.cp(path.join(os.projectdir(), "assets", "data"), path.join(path.join(binDirectory, target:name()), "data"))
    end)
