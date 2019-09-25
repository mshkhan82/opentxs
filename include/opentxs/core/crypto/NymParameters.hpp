// Copyright (c) 2019 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_CORE_CRYPTO_NYMPARAMETERS_HPP
#define OPENTXS_CORE_CRYPTO_NYMPARAMETERS_HPP

#include "opentxs/Forward.hpp"

#if OT_CRYPTO_SUPPORTED_KEY_HD
#include "opentxs/core/crypto/OTPassword.hpp"
#endif
#include "opentxs/crypto/key/Asymmetric.hpp"
#include "opentxs/identity/credential/Base.hpp"
#include "opentxs/Proto.hpp"
#include "opentxs/Types.hpp"

#include <cstdint>
#include <string>
#include <memory>

namespace opentxs
{
class NymParameters
{
public:
    NymParameterType nymParameterType();

    proto::AsymmetricKeyType AsymmetricKeyType() const;

    void setNymParameterType(NymParameterType theKeytype);

    proto::CredentialType credentialType() const;

    void setCredentialType(proto::CredentialType theCredentialtype);

    inline proto::SourceType SourceType() const { return sourceType_; }

    inline void SetSourceType(proto::SourceType sType) { sourceType_ = sType; }

    inline proto::SourceProofType SourceProofType() const
    {
        return sourceProofType_;
    }

    inline void SetSourceProofType(proto::SourceProofType sType)
    {
        sourceProofType_ = sType;
    }

    inline std::shared_ptr<proto::ContactData> ContactData() const
    {
        return contact_data_;
    }

    inline std::shared_ptr<proto::VerificationSet> VerificationSet() const
    {
        return verification_set_;
    }

    void SetContactData(const proto::ContactData& contactData);
    void SetVerificationSet(const proto::VerificationSet& verificationSet);

#if OT_CRYPTO_SUPPORTED_KEY_RSA
    std::int32_t keySize();

    void setKeySize(std::int32_t keySize);
    explicit NymParameters(const std::int32_t keySize);
#endif

#if OT_CRYPTO_SUPPORTED_KEY_HD
    const std::unique_ptr<OTPassword>& Entropy() const;
    void SetEntropy(const OTPassword& entropy);

    inline std::string Seed() const { return seed_; }
    inline void SetSeed(const std::string& seed) { seed_ = seed; }

    inline Bip32Index Nym() const { return nym_; }
    inline void SetNym(const Bip32Index path) { nym_ = path; }

    inline Bip32Index Credset() const { return credset_; }
    inline void SetCredset(const Bip32Index path) { credset_ = path; }

    inline Bip32Index CredIndex() const { return cred_index_; }
    inline void SetCredIndex(const Bip32Index path) { cred_index_ = path; }

    inline bool Default() const { return default_; }
    inline void SetDefault(const bool in) { default_ = in; }

    inline bool UseAutoIndex() const { return use_auto_index_; }
    inline void SetUseAutoIndex(const bool use) { use_auto_index_ = use; }
#endif

    NymParameters();
    explicit NymParameters(proto::CredentialType theCredentialtype);
    NymParameters(const NymParameters& rhs);

    ~NymParameters() = default;

private:
    proto::SourceType sourceType_;
    proto::SourceProofType sourceProofType_;
    std::shared_ptr<proto::ContactData> contact_data_;
    std::shared_ptr<proto::VerificationSet> verification_set_;
    NymParameterType nymType_;
    proto::CredentialType credentialType_;

#if OT_CRYPTO_SUPPORTED_KEY_HD
    std::unique_ptr<OTPassword> entropy_;
    std::string seed_;
    Bip32Index nym_;
    Bip32Index credset_;
    Bip32Index cred_index_;
    bool default_;
    bool use_auto_index_;
#endif
#if OT_CRYPTO_SUPPORTED_KEY_RSA
    std::int32_t nBits_;
#endif
};
}  // namespace opentxs
#endif
