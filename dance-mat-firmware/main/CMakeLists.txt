idf_component_register(SRCS 
  "./main.c"
  "./logger.c"
  "./logger.h"
  "./status.c"
  "./status.h"
  "./ansi_colour.h"
  "./net.c"
  "./wifi.c"
  "./mongoose.h"
  "./mongoose.c"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
component_compile_options(-DMG_ENABLE_LINES)
