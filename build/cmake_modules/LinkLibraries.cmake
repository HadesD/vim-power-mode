if (WIN32 OR MSYS)
  set(LIBS_REQUIRED ${LIBS_REQUIRED}
    User32
    Gdi32
    Shell32
    )
else()
  set(LIBS_REQUIRED ${LIBS_REQUIRED}
    X11
    )
endif()

