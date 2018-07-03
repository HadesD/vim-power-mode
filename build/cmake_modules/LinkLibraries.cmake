if (WIN32 OR MSYS)
  set(LIBS_REQUIRED ${LIBS_REQUIRED}
    )
else()
  set(LIBS_REQUIRED ${LIBS_REQUIRED}
    X11
    )
endif()

