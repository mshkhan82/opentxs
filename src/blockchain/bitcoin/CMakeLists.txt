# Copyright (c) 2010-2020 The Open-Transactions developers
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

set(cxx-sources Bitcoin.cpp CompactSize.cpp Inventory.cpp)

set(cxx-headers
    ${opentxs_SOURCE_DIR}/src/internal/blockchain/bitcoin/Bitcoin.hpp
    CompactSize.hpp Inventory.hpp
)

add_library(opentxs-blockchain-bitcoin OBJECT ${cxx-sources} ${cxx-headers})
target_link_libraries(
  opentxs-blockchain-bitcoin PRIVATE Boost::headers opentxs::messages
)
add_dependencies(opentxs-blockchain-bitcoin generated_code)
