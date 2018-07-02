set(SRC_FILES ${SRC_FILES}
  src/main.cpp

  src/Particle.cpp
  src/Window.cpp
  )

if (WIN32)
  set(SRC_FILES ${SRC_FILES}
    src/platforms/Windows.cpp
    )
else()
  set(SRC_FILES ${SRC_FILES}
    src/platforms/Posix.cpp
    src/platforms/x11/Window.cpp
    )
endif()

