if (WIN32)
  set(LIBS_REQUIRED ${LIBS_REQUIRED}
    )
else()
  set(LIBS_REQUIRED ${LIBS_REQUIRED}
    X11
    )
endif()

