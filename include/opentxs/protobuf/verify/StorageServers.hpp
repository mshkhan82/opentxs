// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_PROTOBUF_STORAGESERVERS_HPP
#define OPENTXS_PROTOBUF_STORAGESERVERS_HPP

#include "opentxs/Version.hpp"  // IWYU pragma: associated

namespace opentxs
{
namespace proto
{
class StorageServers;
}  // namespace proto
}  // namespace opentxs

namespace opentxs
{
namespace proto
{
OPENTXS_EXPORT bool CheckProto_1(
    const StorageServers& servers,
    const bool silent);
OPENTXS_EXPORT bool CheckProto_2(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_3(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_4(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_5(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_6(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_7(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_8(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_9(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_10(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_11(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_12(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_13(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_14(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_15(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_16(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_17(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_18(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_19(const StorageServers&, const bool);
OPENTXS_EXPORT bool CheckProto_20(const StorageServers&, const bool);
}  // namespace proto
}  // namespace opentxs

#endif  // OPENTXS_PROTOBUF_STORAGESERVERS_HPP
