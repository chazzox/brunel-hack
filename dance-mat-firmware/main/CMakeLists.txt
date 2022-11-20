idf_component_register(SRCS 
  "./main.c"
  "./logger.c"
  "./logger.h"
  "./ansi_colour.h"
  "./touch.c"
  "./touch.h"
  "./net.c"
  "./net.h"
  "./wifi.c"
  "./wifi.h"
  "./mongoose.h"
  "./mongoose.c"
                    INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
component_compile_options(-DMG_ENABLE_LINES)
