// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <memory>
#include <string>

#include "core/contract/Signable.hpp"
#include "internal/identity/credential/Credential.hpp"
#include "opentxs/Proto.hpp"
#include "opentxs/Types.hpp"
#include "opentxs/core/Data.hpp"
#include "opentxs/core/Identifier.hpp"
#include "opentxs/core/contract/Signable.hpp"
#include "opentxs/protobuf/Credential.pb.h"
#include "opentxs/protobuf/Enums.pb.h"

namespace opentxs
{
namespace api
{
namespace internal
{
struct Core;
}  // namespace internal
}  // namespace api

namespace identity
{
namespace internal
{
struct Authority;
}  // namespace internal

class Source;
}  // namespace identity

namespace proto
{
class ContactData;
class Signature;
class VerificationSet;
}  // namespace proto

class NymParameters;
class OTPassword;
class PasswordPrompt;
class Secret;
}  // namespace opentxs

namespace opentxs::identity::credential::implementation
{
class Base : virtual public credential::internal::Base,
             public opentxs::contract::implementation::Signable
{
public:
    using SerializedType = proto::Credential;

    auto asString(const bool asPrivate = false) const -> std::string final;
    auto CredentialID() const -> const Identifier& final { return id_.get(); }
    auto GetContactData(std::unique_ptr<proto::ContactData>& output) const
        -> bool override
    {
        return false;
    }
    auto GetVerificationSet(
        std::unique_ptr<proto::VerificationSet>& output) const -> bool override
    {
        return false;
    }
    auto hasCapability(const NymCapability& capability) const -> bool override
    {
        return false;
    }
    auto MasterSignature() const -> Signature final;
    auto Mode() const -> proto::KeyMode final { return mode_; }
    auto Role() const -> proto::CredentialRole final { return role_; }
    auto Private() const -> bool final
    {
        return (proto::KEYMODE_PRIVATE == mode_);
    }
    auto Save() const -> bool final;
    auto SelfSignature(CredentialModeFlag version = PUBLIC_VERSION) const
        -> Signature final;
    auto Serialize() const -> OTData final;
    auto Serialized(
        const SerializationModeFlag asPrivate,
        const SerializationSignatureFlag asSigned) const
        -> std::shared_ptr<SerializedType> final;
    auto SourceSignature() const -> Signature final;
    auto TransportKey(
        Data& publicKey,
        Secret& privateKey,
        const PasswordPrompt& reason) const -> bool override;
    auto Type() const -> proto::CredentialType final { return type_; }
    auto Validate() const -> bool final;
    auto Verify(
        const Data& plaintext,
        const proto::Signature& sig,
        const proto::KeyRole key = proto::KEYROLE_SIGN) const -> bool override
    {
        return false;
    }
    auto Verify(
        const proto::Credential& credential,
        const proto::CredentialRole& role,
        const Identifier& masterID,
        const proto::Signature& masterSig) const -> bool override
    {
        return false;
    }

    void ReleaseSignatures(const bool onlyPrivate) final;

    ~Base() override = default;

protected:
    const identity::internal::Authority& parent_;
    const identity::Source& source_;
    const std::string nym_id_;
    const std::string master_id_;
    const proto::CredentialType type_;
    const proto::CredentialRole role_;
    const proto::KeyMode mode_;

    static auto get_master_id(const internal::Primary& master) noexcept
        -> std::string;
    static auto get_master_id(
        const proto::Credential& serialized,
        const internal::Primary& master) noexcept(false) -> std::string;

    virtual auto serialize(
        const Lock& lock,
        const SerializationModeFlag asPrivate,
        const SerializationSignatureFlag asSigned) const
        -> std::shared_ptr<SerializedType>;
    auto validate(const Lock& lock) const -> bool final;
    virtual auto verify_internally(const Lock& lock) const -> bool;

    void init(
        const identity::credential::internal::Primary& master,
        const PasswordPrompt& reason) noexcept(false);
    virtual void sign(
        const identity::credential::internal::Primary& master,
        const PasswordPrompt& reason) noexcept(false);

    Base(
        const api::internal::Core& api,
        const identity::internal::Authority& owner,
        const identity::Source& source,
        const NymParameters& nymParameters,
        const VersionNumber version,
        const proto::CredentialRole role,
        const proto::KeyMode mode,
        const std::string& masterID) noexcept;
    Base(
        const api::internal::Core& api,
        const identity::internal::Authority& owner,
        const identity::Source& source,
        const proto::Credential& serialized,
        const std::string& masterID) noexcept(false);

private:
    static auto extract_signatures(const SerializedType& serialized)
        -> Signatures;

    auto clone() const noexcept -> Base* final { return nullptr; }
    auto GetID(const Lock& lock) const -> OTIdentifier final;
    // Syntax (non cryptographic) validation
    auto isValid(const Lock& lock) const -> bool;
    // Returns the serialized form to prevent unnecessary serializations
    auto isValid(const Lock& lock, std::shared_ptr<SerializedType>& credential)
        const -> bool;
    auto Name() const -> std::string final { return id_->str(); }
    auto verify_master_signature(const Lock& lock) const -> bool;

    void add_master_signature(
        const Lock& lock,
        const identity::credential::internal::Primary& master,
        const PasswordPrompt& reason) noexcept(false);

    Base() = delete;
    Base(const Base&) = delete;
    Base(Base&&) = delete;
    auto operator=(const Base&) -> Base& = delete;
    auto operator=(Base&&) -> Base& = delete;
};
}  // namespace opentxs::identity::credential::implementation
