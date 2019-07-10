// Copyright (c) 2010-2019 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Internal.hpp"

#include "internal/blockchain/bitcoin/Bitcoin.hpp"
#include "internal/blockchain/p2p/P2P.hpp"

#include <boost/endian/buffers.hpp>

#include <array>
#include <map>
#include <string>

namespace be = boost::endian;

namespace opentxs::blockchain::p2p::bitcoin
{
using CompactSize = blockchain::bitcoin::CompactSize;

using BitVector8 = std::uint64_t;
using Nonce = std::uint64_t;
using ServiceBits = std::uint64_t;
using TxnCount = std::uint32_t;

using AddressByteField = ba::ip::address_v6::bytes_type;
using BitVectorField = be::little_uint64_buf_t;
using BlockHeaderField = std::array<std::byte, 80>;
using BlockHeaderHashField = std::array<std::byte, 32>;
using ChecksumField = std::array<std::byte, 4>;
using CommandField = std::array<std::byte, 12>;
using HeightField = be::little_int32_buf_t;
using MagicField = be::little_uint32_buf_t;
using MerkleBlockFlagsField = be::little_uint8_buf_t;
using NonceField = be::little_uint64_buf_t;
using PayloadSizeField = be::little_uint32_buf_t;
using PortField = be::big_uint16_buf_t;
using ProtocolVersionField = be::little_uint32_buf_t;
using ProtocolVersionFieldSigned = be::little_int32_buf_t;
using TimestampField32 = be::little_uint32_buf_t;
using TimestampField64 = be::little_int64_buf_t;
using TxnCountField = be::little_uint32_buf_t;

enum class Command : int {
    unknown = 0,
    addr,
    alert,
    block,
    blocktxn,
    cfcheckpt,
    cfheaders,
    cfilter,
    checkorder,
    cmpctblock,
    feefilter,
    filteradd,
    filterclear,
    filterload,
    getaddr,
    getblocks,
    getblocktxn,
    getcfcheckpt,
    getcfheaders,
    getcfilters,
    getdata,
    getheaders,
    headers,
    inv,
    mempool,
    merkleblock,
    notfound,
    ping,
    pong,
    reject,
    reply,
    sendcmpct,
    sendheaders,
    submitorder,
    tx,
    verack,
    version,
};

enum class Magic : std::uint32_t {
    Unknown = 0,
    BTCTestnet3 = 118034699,
    Bitcoin = 3652501241,
    BitcoinCash = 3908297187,
    BCHTestnet3 = 4109624820,
};

enum class RejectCode : std::uint8_t {
    None = 0x00,
    DecodeFailed = 0x01,
    Invalid = 0x10,
    Obsolete = 0x11,
    Duplicate = 0x12,
    NonStandard = 0x40,
    DustThreshold = 0x41,
    LowPriority = 0x42,
    WrongChain = 0x43,
};

enum class Service : std::uint8_t {
    None = 0,
    Bit1 = 1,
    Bit2 = 2,
    Bit3 = 3,
    Bit4 = 4,
    Bit5 = 5,
    Bit6 = 6,
    Bit7 = 7,
    Bit8 = 8,
    Bit9 = 9,
    Bit10 = 10,
    Bit11 = 11,
    Bit12 = 12,
    Bit13 = 13,
    Bit14 = 14,
    Bit15 = 15,
    Bit16 = 16,
    Bit17 = 17,
    Bit18 = 18,
    Bit19 = 19,
    Bit20 = 20,
    Bit21 = 21,
    Bit22 = 22,
    Bit23 = 23,
    Bit24 = 24,
    Bit25 = 25,
    Bit26 = 26,
    Bit27 = 27,
    Bit28 = 28,
    Bit29 = 29,
    Bit30 = 30,
    Bit31 = 31,
    Bit32 = 32,
    Bit33 = 33,
    Bit34 = 34,
    Bit35 = 35,
    Bit36 = 36,
    Bit37 = 37,
    Bit38 = 38,
    Bit39 = 39,
    Bit40 = 40,
    Bit41 = 41,
    Bit42 = 42,
    Bit43 = 43,
    Bit44 = 44,
    Bit45 = 45,
    Bit46 = 46,
    Bit47 = 47,
    Bit48 = 48,
    Bit49 = 49,
    Bit50 = 50,
    Bit51 = 51,
    Bit52 = 52,
    Bit53 = 53,
    Bit54 = 54,
    Bit55 = 55,
    Bit56 = 56,
    Bit57 = 57,
    Bit58 = 58,
    Bit59 = 59,
    Bit60 = 60,
    Bit61 = 61,
    Bit62 = 62,
    Bit63 = 63,
    Bit64 = 64,
};

struct AddressVersion {
    static const OTData cjdns_prefix_;
    static const OTData ipv4_prefix_;
    static const OTData onion_prefix_;

    BitVectorField services_;
    AddressByteField address_;
    PortField port_;

    static AddressByteField Encode(const Network type, const Data& bytes);

    AddressVersion(
        const std::set<bitcoin::Service>& services,
        const tcp::endpoint& endpoint) noexcept;
    AddressVersion(
        const blockchain::Type chain,
        const ProtocolVersion version,
        const internal::Address& address) noexcept;
    AddressVersion() noexcept;
};

using MagicMap = std::map<blockchain::Type, Magic>;
using MagicReverseMap = std::map<Magic, blockchain::Type>;
using CommandMap = std::map<Command, std::string>;
using CommandReverseMap = std::map<std::string, Command>;

OTData BitcoinString(const std::string& in) noexcept;
std::string CommandName(const Command command) noexcept;
Command GetCommand(const CommandField& bytes) noexcept;
Magic GetMagic(const blockchain::Type type) noexcept;
Magic GetMagic(const std::uint32_t magic) noexcept;
blockchain::Type GetNetwork(const Magic magic) noexcept;
BitVector8 GetServiceBytes(const std::set<bitcoin::Service>& services) noexcept;
std::set<bitcoin::Service> GetServices(const BitVector8 data) noexcept;
CommandField SerializeCommand(const Command command) noexcept;
std::set<bitcoin::Service> TranslateServices(
    const blockchain::Type chain,
    const ProtocolVersion version,
    const std::set<p2p::Service>& input) noexcept;
std::set<p2p::Service> TranslateServices(
    const blockchain::Type chain,
    const ProtocolVersion version,
    const std::set<bitcoin::Service>& input) noexcept;

bitcoin::Service convert_service_bit(BitVector8 value) noexcept;
BitVector8 convert_service_bit(const bitcoin::Service value) noexcept;
template <typename OuterKey, typename InnerKey, typename InnerValue>
std::map<OuterKey, std::map<InnerValue, InnerKey>> reverse_nested_map(
    const std::map<OuterKey, std::map<InnerKey, InnerValue>>& map) noexcept
{
    std::map<OuterKey, std::map<InnerValue, InnerKey>> output{};

    for (const auto& [outerKey, innerMap] : map) {
        auto& outputMap = output[outerKey];

        for (const auto& [innerKey, innerValue] : innerMap) {
            outputMap.emplace(innerValue, innerKey);
        }
    }

    return output;
}
}  // namespace opentxs::blockchain::p2p::bitcoin
