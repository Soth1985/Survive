file(GLOB Survive_CPP "*.cpp")
file(GLOB Survive_H "*.h")

set(Survive_Src ${Survive_CPP} ${Survive_H})

add_executable( Survive ${Survive_Src} )

target_link_libraries( 	Survive
						debug sfgui-d
						debug sfml-graphics-d
						debug sfml-window-d
						debug sfml-system-d
						optimized sfgui-d
						optimized sfml-graphics-d
						optimized sfml-window-d
						optimized sfml-system-d
						opengl32.lib )
						
survive_install(Survive)
