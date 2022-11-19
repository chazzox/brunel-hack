idf_component_register(SRCS "./main.c"
  "./logger.c"
  "./logger.h"
  "./status.c"
  "./status.h"
  "./ansi_colour.h"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
