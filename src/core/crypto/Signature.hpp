// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// IWYU pragma: private
// IWYU pragma: friend ".*src/core/crypto/Signature.cpp"

#pragma once

#include "core/Armored.hpp"
#include "opentxs/core/crypto/OTSignatureMetadata.hpp"
#include "opentxs/core/crypto/Signature.hpp"

namespace opentxs
{
namespace api
{
namespace internal
{
struct Core;
}  // namespace internal
}  // namespace api
}  // namespace opentxs

namespace opentxs::implementation
{
class Signature final : virtual public opentxs::Signature, public Armored
{
public:
    const OTSignatureMetadata& getMetaData() const { return metadata_; }
    OTSignatureMetadata& getMetaData() { return metadata_; }

    Signature(const api::internal::Core& api);

    ~Signature() = default;

private:
    friend OTSignature;

    OTSignatureMetadata metadata_;
};
}  // namespace opentxs::implementation
