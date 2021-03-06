// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <iosfwd>
#include <memory>
#include <optional>
#include <vector>

#include "internal/blockchain/block/bitcoin/Bitcoin.hpp"
#include "opentxs/Bytes.hpp"
#include "opentxs/Types.hpp"
#include "opentxs/api/client/blockchain/Types.hpp"
#include "opentxs/blockchain/Blockchain.hpp"
#include "opentxs/blockchain/Types.hpp"
#include "opentxs/blockchain/block/bitcoin/Output.hpp"
#include "opentxs/blockchain/block/bitcoin/Outputs.hpp"
#include "opentxs/core/Identifier.hpp"
#include "opentxs/core/identifier/Nym.hpp"
#include "opentxs/protobuf/BlockchainTransactionOutput.pb.h"

namespace opentxs
{
namespace api
{
namespace client
{
class Blockchain;
}  // namespace client
}  // namespace api

namespace proto
{
class BlockchainTransaction;
}  // namespace proto
}  // namespace opentxs

namespace opentxs::blockchain::block::bitcoin::implementation
{
class Outputs final : public internal::Outputs
{
public:
    using OutputList = std::vector<std::unique_ptr<internal::Output>>;

    auto AssociatedLocalNyms(
        const api::client::Blockchain& blockchain,
        std::vector<OTNymID>& output) const noexcept -> void final;
    auto AssociatedRemoteContacts(
        const api::client::Blockchain& blockchain,
        std::vector<OTIdentifier>& output) const noexcept -> void final;
    auto at(const std::size_t position) const noexcept(false)
        -> const value_type& final
    {
        return *outputs_.at(position);
    }
    auto begin() const noexcept -> const_iterator final { return cbegin(); }
    auto CalculateSize() const noexcept -> std::size_t final;
    auto cbegin() const noexcept -> const_iterator final
    {
        return const_iterator(this, 0);
    }
    auto cend() const noexcept -> const_iterator final
    {
        return const_iterator(this, outputs_.size());
    }
    auto clone() const noexcept -> std::unique_ptr<internal::Outputs> final
    {
        return std::make_unique<Outputs>(*this);
    }
    auto end() const noexcept -> const_iterator final { return cend(); }
    auto ExtractElements(const filter::Type style) const noexcept
        -> std::vector<Space> final;
    auto FindMatches(
        const api::client::Blockchain& blockchain,
        const ReadView txid,
        const FilterType type,
        const ParsedPatterns& elements) const noexcept -> Matches final;
    auto GetPatterns() const noexcept -> std::vector<PatternID> final;
    auto NetBalanceChange(
        const api::client::Blockchain& blockchain,
        const identifier::Nym& nym) const noexcept -> opentxs::Amount final;
    auto Serialize(const AllocateOutput destination) const noexcept
        -> std::optional<std::size_t> final;
    auto Serialize(
        const api::client::Blockchain& blockchain,
        proto::BlockchainTransaction& destination) const noexcept -> bool final;
    auto size() const noexcept -> std::size_t final { return outputs_.size(); }

    auto at(const std::size_t position) noexcept(false) -> value_type& final
    {
        return *outputs_.at(position);
    }
    auto ForTestingOnlyAddKey(
        const std::size_t index,
        const api::client::blockchain::Key& key) noexcept -> bool final;
    auto MergeMetadata(const Output::SerializeType& rhs) noexcept(false)
        -> void final
    {
        outputs_.at(rhs.index())->MergeMetadata(rhs);
    }

    Outputs(
        OutputList&& outputs,
        std::optional<std::size_t> size = {}) noexcept(false);
    Outputs(const Outputs&) noexcept;

    ~Outputs() final = default;

private:
    const OutputList outputs_;
    mutable std::optional<std::size_t> size_;

    static auto clone(const OutputList& rhs) noexcept -> OutputList;

    Outputs() = delete;
    Outputs(Outputs&&) = delete;
    auto operator=(const Outputs&) -> Outputs& = delete;
    auto operator=(Outputs&&) -> Outputs& = delete;
};
}  // namespace opentxs::blockchain::block::bitcoin::implementation
