set(SRC_FILES ${SRC_FILES}
  src/main.cpp

  src/Config.cpp
  src/Particle.cpp
  src/Window.cpp
  )

if (WIN32 OR MSYS)
  set(SRC_FILES ${SRC_FILES}
    src/platforms/Windows.cpp
    src/platforms/windows/Window.cpp
    )
else()
  set(SRC_FILES ${SRC_FILES}
    src/platforms/Posix.cpp
    src/platforms/x11/Window.cpp
    )
endif()

