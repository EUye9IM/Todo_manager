set_warnings("all", "error")
set_languages("c11")
set_optimize("aggressive")

target("todo")
	set_kind("binary")
	add_files("**.cpp")
target_end()
