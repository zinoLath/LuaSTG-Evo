# luasocket

CPMAddPackage(
    NAME luasocket
    VERSION 3.1.0
    GITHUB_REPOSITORY lunarmodules/luasocket
    DOWNLOAD_ONLY YES
)

if(luasocket_ADDED)
    set(LUA_SOCKET_ROOT ${luasocket_SOURCE_DIR})
    add_library(luasocket STATIC)
    luastg_target_common_options(luasocket)
    target_compile_definitions(luasocket
    PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _WINSOCK_DEPRECATED_NO_WARNINGS
        LUASOCKET_API= # static
        $<$<CONFIG:DEBUG>:LUASOCKET_DEBUG>
    )
    target_include_directories(luasocket
    PRIVATE
        ${LUA_SOCKET_ROOT}/src
    )
    # target_sources(luasocket
    # PRIVATE
    #     ${LUA_SOCKET_ROOT}/src/auxiliar.c
    #     ${LUA_SOCKET_ROOT}/src/auxiliar.h
    #     ${LUA_SOCKET_ROOT}/src/buffer.c
    #     ${LUA_SOCKET_ROOT}/src/buffer.h
    #     ${LUA_SOCKET_ROOT}/src/compat.c
    #     ${LUA_SOCKET_ROOT}/src/compat.h
    #     ${LUA_SOCKET_ROOT}/src/except.c
    #     ${LUA_SOCKET_ROOT}/src/except.h
    #     #${LUA_SOCKET_ROOT}/src/ftp.lua
    #     #${LUA_SOCKET_ROOT}/src/headers.lua
    #     #${LUA_SOCKET_ROOT}/src/http.lua
    #     ${LUA_SOCKET_ROOT}/src/inet.c
    #     ${LUA_SOCKET_ROOT}/src/inet.h
    #     ${LUA_SOCKET_ROOT}/src/io.c
    #     ${LUA_SOCKET_ROOT}/src/io.h
    #     #${LUA_SOCKET_ROOT}/src/ltn12.lua
    #     ${LUA_SOCKET_ROOT}/src/luasocket.c
    #     ${LUA_SOCKET_ROOT}/src/luasocket.h
    #     #${LUA_SOCKET_ROOT}/src/makefile
    #     #${LUA_SOCKET_ROOT}/src/mbox.lua
    #     ${LUA_SOCKET_ROOT}/src/mime.c
    #     ${LUA_SOCKET_ROOT}/src/mime.h
    #     #${LUA_SOCKET_ROOT}/src/mime.lua
    #     ${LUA_SOCKET_ROOT}/src/options.c
    #     ${LUA_SOCKET_ROOT}/src/options.h
    #     #${LUA_SOCKET_ROOT}/src/pierror.h
    #     ${LUA_SOCKET_ROOT}/src/select.c
    #     ${LUA_SOCKET_ROOT}/src/select.h
    #     #${LUA_SOCKET_ROOT}/src/serial.c
    #     #${LUA_SOCKET_ROOT}/src/smtp.lua
    #     #${LUA_SOCKET_ROOT}/src/socket.h
    #     #${LUA_SOCKET_ROOT}/src/socket.lua
    #     ${LUA_SOCKET_ROOT}/src/tcp.c
    #     ${LUA_SOCKET_ROOT}/src/tcp.h
    #     ${LUA_SOCKET_ROOT}/src/timeout.c
    #     ${LUA_SOCKET_ROOT}/src/timeout.h
    #     #${LUA_SOCKET_ROOT}/src/tp.lua
    #     ${LUA_SOCKET_ROOT}/src/udp.c
    #     ${LUA_SOCKET_ROOT}/src/udp.h
    #     #${LUA_SOCKET_ROOT}/src/unix.c
    #     #${LUA_SOCKET_ROOT}/src/unix.h
    #     #${LUA_SOCKET_ROOT}/src/unixdgram.c
    #     #${LUA_SOCKET_ROOT}/src/unixdgram.h
    #     #${LUA_SOCKET_ROOT}/src/unixstream.c
    #     #${LUA_SOCKET_ROOT}/src/unixstream.h
    #     #${LUA_SOCKET_ROOT}/src/url.lua
    #     #${LUA_SOCKET_ROOT}/src/usocket.c
    #     #${LUA_SOCKET_ROOT}/src/usocket.h
    #     ${LUA_SOCKET_ROOT}/src/wsocket.c
    #     ${LUA_SOCKET_ROOT}/src/wsocket.h
    # )
    set(luasocket_src
        ${LUA_SOCKET_ROOT}/src/auxiliar.c
        ${LUA_SOCKET_ROOT}/src/auxiliar.h
        ${LUA_SOCKET_ROOT}/src/buffer.c
        ${LUA_SOCKET_ROOT}/src/buffer.h
        ${LUA_SOCKET_ROOT}/src/compat.c
        ${LUA_SOCKET_ROOT}/src/compat.h
        ${LUA_SOCKET_ROOT}/src/except.c
        ${LUA_SOCKET_ROOT}/src/except.h
        #${LUA_SOCKET_ROOT}/src/ftp.lua
        #${LUA_SOCKET_ROOT}/src/headers.lua
        #${LUA_SOCKET_ROOT}/src/http.lua
        ${LUA_SOCKET_ROOT}/src/inet.c
        ${LUA_SOCKET_ROOT}/src/inet.h
        ${LUA_SOCKET_ROOT}/src/io.c
        ${LUA_SOCKET_ROOT}/src/io.h
        #${LUA_SOCKET_ROOT}/src/ltn12.lua
        ${LUA_SOCKET_ROOT}/src/luasocket.c
        ${LUA_SOCKET_ROOT}/src/luasocket.h
        #${LUA_SOCKET_ROOT}/src/makefile
        #${LUA_SOCKET_ROOT}/src/mbox.lua
        ${LUA_SOCKET_ROOT}/src/mime.c
        ${LUA_SOCKET_ROOT}/src/mime.h
        #${LUA_SOCKET_ROOT}/src/mime.lua
        ${LUA_SOCKET_ROOT}/src/options.c
        ${LUA_SOCKET_ROOT}/src/options.h
        #${LUA_SOCKET_ROOT}/src/pierror.h
        ${LUA_SOCKET_ROOT}/src/select.c
        ${LUA_SOCKET_ROOT}/src/select.h
        #${LUA_SOCKET_ROOT}/src/serial.c
        #${LUA_SOCKET_ROOT}/src/smtp.lua
        #${LUA_SOCKET_ROOT}/src/socket.h
        #${LUA_SOCKET_ROOT}/src/socket.lua
        ${LUA_SOCKET_ROOT}/src/tcp.c
        ${LUA_SOCKET_ROOT}/src/tcp.h
        ${LUA_SOCKET_ROOT}/src/timeout.c
        ${LUA_SOCKET_ROOT}/src/timeout.h
        #${LUA_SOCKET_ROOT}/src/tp.lua
        ${LUA_SOCKET_ROOT}/src/udp.c
        ${LUA_SOCKET_ROOT}/src/udp.h
        #${LUA_SOCKET_ROOT}/src/unix.c
        #${LUA_SOCKET_ROOT}/src/unix.h
        #${LUA_SOCKET_ROOT}/src/unixdgram.c
        #${LUA_SOCKET_ROOT}/src/unixdgram.h
        #${LUA_SOCKET_ROOT}/src/unixstream.c
        #${LUA_SOCKET_ROOT}/src/unixstream.h
        #${LUA_SOCKET_ROOT}/src/url.lua
        #${LUA_SOCKET_ROOT}/src/usocket.c
        #${LUA_SOCKET_ROOT}/src/usocket.h
        # ${LUA_SOCKET_ROOT}/src/wsocket.c
        # ${LUA_SOCKET_ROOT}/src/wsocket.h
    )
    if(WIN32)
        list(APPEND luasocket_src
            ${LUA_SOCKET_ROOT}/src/wsocket.c
            ${LUA_SOCKET_ROOT}/src/wsocket.h
        )
    elseif(UNIX)
        list(APPEND luasocket_src
            ${LUA_SOCKET_ROOT}/src/unix.c
            ${LUA_SOCKET_ROOT}/src/unix.h
            ${LUA_SOCKET_ROOT}/src/unixdgram.c
            ${LUA_SOCKET_ROOT}/src/unixdgram.h
            ${LUA_SOCKET_ROOT}/src/unixstream.c
            ${LUA_SOCKET_ROOT}/src/unixstream.h
            ${LUA_SOCKET_ROOT}/src/usocket.c
            ${LUA_SOCKET_ROOT}/src/usocket.h
        )
    endif()
    
    target_sources(luasocket PRIVATE ${luasocket_src})
    target_link_libraries(luasocket
    PUBLIC
        # lua51static
        libluajit
        "$<$<BOOL:${WIN32}>:ws2_32.lib>"
    )

    set_target_properties(luasocket PROPERTIES FOLDER lualib)
endif()

CPMAddPackage(
    NAME toml++
    GITHUB_REPOSITORY marzer/tomlplusplus
    VERSION 3.4.0
)

CPMAddPackage(
    NAME sol2
    GITHUB_REPOSITORY KaleiAlma/sol2
    GIT_TAG main
)

CPMAddPackage(
    NAME magic_enum
    GITHUB_REPOSITORY Neargye/magic_enum
    VERSION 0.9.6
)

CPMAddPackage(
    NAME toml.lua
    GITHUB_REPOSITORY LebJe/toml.lua
    GIT_TAG 0.4.0
    DOWNLOAD_ONLY YES
)

if(toml.lua_ADDED)
    add_library(toml.lua STATIC)
    target_sources(toml.lua
    PRIVATE 
        ${toml.lua_SOURCE_DIR}/src/toml.cpp
        ${toml.lua_SOURCE_DIR}/src/decoding/decoding.cpp
        ${toml.lua_SOURCE_DIR}/src/encoding/encoding.cpp
        ${toml.lua_SOURCE_DIR}/src/DataTypes/DateAndTime/dateAndTime.cpp
        ${toml.lua_SOURCE_DIR}/src/DataTypes/TOMLInt/TOMLInt.cpp
        ${toml.lua_SOURCE_DIR}/src/utilities/utilities.cpp
    )
    set_target_properties(toml.lua PROPERTIES
        FOLDER lualib
        OUTPUT_NAME "toml"
        PREFIX ""
    )
    target_include_directories(
        toml.lua PRIVATE
        # ${LUA_INCLUDE_DIR}
        ${toml.lua_SOURCE_DIR}/src
        ${toml.lua_SOURCE_DIR}/src/include
        ${toml++_SOURCE_DIR}
        ${sol2_SOURCE_DIR}/include
        ${magic_enum_SOURCE_DIR}/include
    )
    target_link_libraries(toml.lua libluajit tomlplusplus::tomlplusplus)
endif()
