# Copyright (c) 2010-2020 The Open-Transactions developers
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

set(cxx-sources
    Callback.cpp
    Handler.cpp
    Reply.cpp
    Request.cpp
)
set(cxx-install-headers
    "${opentxs_SOURCE_DIR}/include/opentxs/network/zeromq/zap/Callback.hpp"
    "${opentxs_SOURCE_DIR}/include/opentxs/network/zeromq/zap/Handler.hpp"
    "${opentxs_SOURCE_DIR}/include/opentxs/network/zeromq/zap/Reply.hpp"
    "${opentxs_SOURCE_DIR}/include/opentxs/network/zeromq/zap/Request.hpp"
    "${opentxs_SOURCE_DIR}/include/opentxs/network/zeromq/zap/ZAP.hpp"
)
set(cxx-headers
    ${cxx-install-headers}
    ${CMAKE_CURRENT_SOURCE_DIR}/Callback.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Handler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reply.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Request.hpp
)

add_library(opentxs-network-zeromq-zap OBJECT ${cxx-sources} ${cxx-headers})

target_link_libraries(
  opentxs-network-zeromq-zap PRIVATE opentxs::messages "${OT_ZMQ_TARGET}"
)
add_dependencies(opentxs-network-zeromq-zap generated_code)

if(OPENTXS_STANDALONE)
  install(
    FILES ${cxx-install-headers}
    DESTINATION include/opentxs/network/zeromq/zap
    COMPONENT dev
  )
endif()
