file(GLOB Survive_CPP "*.cpp")
file(GLOB Survive_H "*.h")

set(Survive_Src ${Survive_CPP} ${Survive_H})

add_executable( Survive ${Survive_Src} )

target_link_libraries( 	Survive
						debug sfgui-d
						debug sfml-graphics-d
						debug sfml-window-d
						debug sfml-system-d
						debug sfml-main-d
						optimized sfgui
						optimized sfml-graphics
						optimized sfml-window
						optimized sfml-system
						optimized sfml-main
						opengl32.lib )
						
survive_install(Survive)
