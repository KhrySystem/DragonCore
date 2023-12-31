include(GNUInstallDirs)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/external/VulkanMemoryAllocator/include/vk_mem_alloc.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS ${CORE_LIB_NAME} ${VMA_LIB_NAME}
    EXPORT DragonCore_EXPORT
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/dragon
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PATTERN "*.in" EXCLUDE
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tools DESTINATION ${CMAKE_INSTALL_DATADIR})

install(EXPORT DragonCore_EXPORT
    FILE DragonEngine_CoreTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dragon
)