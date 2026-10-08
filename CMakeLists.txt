cmake_minimum_required(VERSION 3.10)

project(upse C)

include(GNUInstallDirs)
include(TestBigEndian)

test_big_endian(IS_BIG_ENDIAN)

find_package(ZLIB REQUIRED)

add_library(upse SHARED
    Neill/spu.c
    Neill/spucore.c
    upse_bios_manager.c
    upse_container_xsf.c
    upse_eventloop.c
    upse_filesystem.c
    upse_loader.c
    upse_loader_psf1.c
    upse_loader_psf2.c
    upse_module.c
    upse_ps1_bios_base.c
    upse_ps1_counters.c
    upse_ps1_dma_manager.c
    upse_ps1_executive.c
    upse_ps1_gpu.c
    upse_ps1_hal.c
    upse_ps1_memory_manager.c
    upse_ps1_spu_base.c
    upse_ps1_spu_dma_handler.c
    upse_ps1_spu_lowpass_filter.c
    upse_ps1_spu_nyquist_filter.c
    upse_ps1_spu_register_io.c
    upse_ps2_iop_base.c
    upse_r3000_abstract.c
    upse_r3000_bytecode_evaluator.c
    upse_string.c
    upse_util.c
)

target_include_directories(upse PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/upse>
)
target_include_directories(upse PRIVATE Neill)

# Unix path separators on all targets (Linux + Android).
target_compile_definitions(upse PRIVATE PSS_STYLE=1 EMU_COMPILE)

if(IS_BIG_ENDIAN)
    target_compile_definitions(upse PRIVATE EMU_BIG_ENDIAN)
else()
    target_compile_definitions(upse PRIVATE EMU_LITTLE_ENDIAN)
endif()

set_target_properties(upse PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(upse PRIVATE ZLIB::ZLIB)

install(TARGETS upse
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/upse
    FILES_MATCHING PATTERN "upse*.h" PATTERN "build*" EXCLUDE PATTERN "CMakeFiles" EXCLUDE
)
install(FILES Neill/spu.h Neill/spucore.h Neill/emuconfig.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/upse/Neill
)
