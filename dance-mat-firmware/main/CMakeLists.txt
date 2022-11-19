idf_component_register(SRCS "./main.c"
  "./logger.c"
  "./logger.h"
  "./status.cpp"
  "./status.h"
  "./ansi_colour.h"
  "./touch.c"
  "./touch.h"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
