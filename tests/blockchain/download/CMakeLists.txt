# Copyright (c) 2010-2020 The Open-Transactions developers
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

add_opentx_test(
  unittests-opentxs-blockchain-download-manager Test_DownloadManager.cpp
)

add_opentx_test(
  unittests-opentxs-blockchain-download-manager-limits Test_Limits.cpp
)

add_opentx_test(
  unittests-opentxs-blockchain-download-manager-order Test_OutOfOrder.cpp
)
