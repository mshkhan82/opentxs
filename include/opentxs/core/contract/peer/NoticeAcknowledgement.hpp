// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_CORE_CONTRACT_PEER_NOTICEACKNOWLEDGEMENT_HPP
#define OPENTXS_CORE_CONTRACT_PEER_NOTICEACKNOWLEDGEMENT_HPP

#include "opentxs/Forward.hpp"  // IWYU pragma: associated

#include "opentxs/core/contract/peer/PeerReply.hpp"

namespace opentxs
{
using OTReplyAcknowledgement =
    SharedPimpl<contract::peer::reply::Acknowledgement>;

namespace contract
{
namespace peer
{
namespace reply
{
class Acknowledgement : virtual public peer::Reply
{
public:
    OPENTXS_EXPORT ~Acknowledgement() override = default;

protected:
    Acknowledgement() noexcept = default;

private:
    friend OTReplyAcknowledgement;

#ifndef _WIN32
    OPENTXS_EXPORT Acknowledgement* clone() const noexcept override = 0;
#endif

    Acknowledgement(const Acknowledgement&) = delete;
    Acknowledgement(Acknowledgement&&) = delete;
    Acknowledgement& operator=(const Acknowledgement&) = delete;
    Acknowledgement& operator=(Acknowledgement&&) = delete;
};
}  // namespace reply
}  // namespace peer
}  // namespace contract
}  // namespace opentxs
#endif
