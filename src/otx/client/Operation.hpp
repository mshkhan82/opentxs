// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <atomic>
#include <future>
#include <iosfwd>
#include <map>
#include <memory>
#include <set>

#include "core/StateMachine.hpp"
#include "internal/otx/client/Client.hpp"
#include "opentxs/Proto.hpp"
#include "opentxs/Types.hpp"
#include "opentxs/Version.hpp"
#include "opentxs/api/Editor.hpp"
#include "opentxs/consensus/ManagedNumber.hpp"
#include "opentxs/consensus/ServerContext.hpp"
#include "opentxs/core/Account.hpp"
#include "opentxs/core/Identifier.hpp"
#include "opentxs/core/Ledger.hpp"
#include "opentxs/core/Message.hpp"
#include "opentxs/core/PasswordPrompt.hpp"
#include "opentxs/core/String.hpp"
#include "opentxs/core/contract/peer/PeerReply.hpp"
#include "opentxs/core/contract/peer/PeerRequest.hpp"
#include "opentxs/core/identifier/Nym.hpp"
#include "opentxs/core/identifier/Server.hpp"
#include "opentxs/core/identifier/UnitDefinition.hpp"

namespace opentxs
{
namespace api
{
namespace client
{
namespace internal
{
struct Manager;
}  // namespace internal
}  // namespace client
}  // namespace api

namespace blind
{
class Purse;
}  // namespace blind

namespace proto
{
class UnitDefinition;
}  // namespace proto

class Armored;
class Cheque;
class Context;
class Factory;
class OTPayment;
class OTTransaction;
class PeerObject;
}  // namespace opentxs

namespace opentxs::otx::client::implementation
{
class Operation final : virtual public otx::client::internal::Operation,
                        public opentxs::internal::StateMachine
{
public:
    const identifier::Nym& NymID() const override { return nym_id_; }
    const identifier::Server& ServerID() const override { return server_id_; }

    bool AddClaim(
        const proto::ContactSectionName section,
        const proto::ContactItemType type,
        const String& value,
        const bool primary) override;
    bool ConveyPayment(
        const identifier::Nym& recipient,
        const std::shared_ptr<const OTPayment> payment) override;
#if OT_CASH
    bool DepositCash(
        const Identifier& depositAccountID,
        const std::shared_ptr<blind::Purse> purse) override;
#endif
    bool DepositCheque(
        const Identifier& depositAccountID,
        const std::shared_ptr<Cheque> cheque) override;
    bool DownloadContract(const Identifier& ID, const ContractType type)
        override;
    Future GetFuture() override;
    bool IssueUnitDefinition(
        const std::shared_ptr<const proto::UnitDefinition> unitDefinition,
        const ServerContext::ExtraArgs& args) override;
    void join() override;
    bool PublishContract(const identifier::Nym& id) override;
    bool PublishContract(const identifier::Server& id) override;
    bool PublishContract(const identifier::UnitDefinition& id) override;
    bool RequestAdmin(const String& password) override;
#if OT_CASH
    bool SendCash(
        const identifier::Nym& recipient,
        const Identifier& workflowID) override;
#endif
    bool SendMessage(
        const identifier::Nym& recipient,
        const String& message,
        const SetID setID) override;
    bool SendPeerReply(
        const identifier::Nym& targetNymID,
        const OTPeerReply peerreply,
        const OTPeerRequest peerrequest) override;
    bool SendPeerRequest(
        const identifier::Nym& targetNymID,
        const OTPeerRequest peerrequest) override;
    bool SendTransfer(
        const Identifier& sourceAccountID,
        const Identifier& destinationAccountID,
        const Amount amount,
        const String& memo) override;
    void SetPush(const bool on) override { enable_otx_push_.store(on); }
    void Shutdown() override;
    bool Start(const Type type, const ServerContext::ExtraArgs& args) override;
    bool Start(
        const Type type,
        const identifier::UnitDefinition& targetUnitID,
        const ServerContext::ExtraArgs& args) override;
    bool Start(
        const Type type,
        const identifier::Nym& targetNymID,
        const ServerContext::ExtraArgs& args) override;
    bool UpdateAccount(const Identifier& accountID) override;
#if OT_CASH
    bool WithdrawCash(const Identifier& accountID, const Amount amount)
        override;
#endif

    ~Operation() override;

private:
    using Promise = std::promise<Result>;
    friend opentxs::Factory;

    enum class Category : int {
        Invalid = 0,
        Basic = 1,
        NymboxPost = 2,
        NymboxPre = 4,
        CreateAccount = 5,
        UpdateAccount = 6,
        Transaction = 7,
    };
    enum class State : int {
        Invalid,
        Idle,
        NymboxPre,
        TransactionNumbers,
        AccountPre,
        Execute,
        AccountPost,
        NymboxPost,
    };
    enum class BoxType : std::int32_t {
        Nymbox = 0,
        Inbox = 1,
        Outbox = 2,
    };

    static const std::map<Type, Category> category_;
    static const std::map<Type, std::size_t> transaction_numbers_;

    const api::client::internal::Manager& api_;
    const OTPasswordPrompt reason_;
    const OTNymID nym_id_;
    const OTServerID server_id_;
    std::atomic<Type> type_;
    std::atomic<State> state_;
    std::atomic<bool> refresh_account_;
    ServerContext::ExtraArgs args_;
    std::shared_ptr<Message> message_;
    std::shared_ptr<Message> outmail_message_;
    std::atomic<bool> result_set_;
    std::atomic<bool> enable_otx_push_;
    Promise result_;
    OTNymID target_nym_id_;
    OTServerID target_server_id_;
    OTUnitID target_unit_id_;
    ContractType contract_type_;
    std::shared_ptr<const proto::UnitDefinition> unit_definition_;
    OTIdentifier account_id_;
    OTIdentifier generic_id_;
    Amount amount_;
    OTString memo_;
    bool bool_;
    proto::ContactSectionName claim_section_;
    proto::ContactItemType claim_type_;
    std::shared_ptr<Cheque> cheque_;
    std::shared_ptr<const OTPayment> payment_;
    std::shared_ptr<Ledger> inbox_;
    std::shared_ptr<Ledger> outbox_;
#if OT_CASH
    std::shared_ptr<blind::Purse> purse_;
#endif
    std::set<OTIdentifier> affected_accounts_;
    std::set<OTIdentifier> redownload_accounts_;
    std::set<OTManagedNumber> numbers_;
    std::atomic<std::size_t> error_count_;
    OTPeerReply peer_reply_;
    OTPeerRequest peer_request_;
    SetID set_id_;

    static bool check_future(ServerContext::SendFuture& future);
    static void set_consensus_hash(
        OTTransaction& transaction,
        const Context& context,
        const Account& account,
        const PasswordPrompt& reason);

    Editor<ServerContext> context() const;
    bool evaluate_transaction_reply(
        const Identifier& accountID,
        const Message& reply) const;
    bool hasContext() const;
    void update_workflow(
        const Message& request,
        const ServerContext::DeliveryResult& result) const;
    void update_workflow_convey_payment(
        const Message& request,
        const ServerContext::DeliveryResult& result) const;
    void update_workflow_send_cash(
        const Message& request,
        const ServerContext::DeliveryResult& result) const;

    void account_pre();
    void account_post();
    std::shared_ptr<Message> construct();
    std::shared_ptr<Message> construct_add_claim();
    std::shared_ptr<Message> construct_check_nym();
    std::shared_ptr<Message> construct_convey_payment();
#if OT_CASH
    std::shared_ptr<Message> construct_deposit_cash();
#endif
    std::shared_ptr<Message> construct_deposit_cheque();
    std::shared_ptr<Message> construct_download_contract();
#if OT_CASH
    std::shared_ptr<Message> construct_download_mint();
#endif
    std::shared_ptr<Message> construct_get_account_data(
        const Identifier& accountID);
    std::shared_ptr<Message> construct_get_transaction_numbers();
    std::shared_ptr<Message> construct_issue_unit_definition();
    std::shared_ptr<Message> construct_process_inbox(
        const Identifier& accountID,
        const Ledger& payload,
        ServerContext& context);
    std::shared_ptr<Message> construct_publish_nym();
    std::shared_ptr<Message> construct_publish_server();
    std::shared_ptr<Message> construct_publish_unit();
    std::shared_ptr<Message> construct_register_account();
    std::shared_ptr<Message> construct_register_nym();
    std::shared_ptr<Message> construct_request_admin();
    std::shared_ptr<Message> construct_send_nym_object(
        const PeerObject& object,
        const Nym_p recipient,
        ServerContext& context,
        const RequestNumber number = -1);
    std::shared_ptr<Message> construct_send_nym_object(
        const PeerObject& object,
        const Nym_p recipient,
        ServerContext& context,
        Armored& envelope,
        const RequestNumber number = -1);
    std::shared_ptr<Message> construct_send_peer_reply();
    std::shared_ptr<Message> construct_send_peer_request();
#if OT_CASH
    std::shared_ptr<Message> construct_send_cash();
#endif
    std::shared_ptr<Message> construct_send_message();
    std::shared_ptr<Message> construct_send_transfer();
#if OT_CASH
    std::shared_ptr<Message> construct_withdraw_cash();
#endif
    std::size_t download_account(
        const Identifier& accountID,
        ServerContext::DeliveryResult& lastResult);
    bool download_accounts(
        const State successState,
        const State failState,
        ServerContext::DeliveryResult& lastResult);
    bool download_box_receipt(
        const Identifier& accountID,
        const BoxType box,
        const TransactionNumber number);
    void evaluate_transaction_reply(ServerContext::DeliveryResult&& result);
    void execute();
    bool get_account_data(
        const Identifier& accountID,
        std::shared_ptr<Ledger> inbox,
        std::shared_ptr<Ledger> outbox,
        ServerContext::DeliveryResult& lastResult);
    bool get_receipts(
        const Identifier& accountID,
        std::shared_ptr<Ledger> inbox,
        std::shared_ptr<Ledger> outbox);
    bool get_receipts(
        const Identifier& accountID,
        const BoxType type,
        Ledger& box);
    void nymbox_post();
    void nymbox_pre();
    bool process_inbox(
        const Identifier& accountID,
        std::shared_ptr<Ledger> inbox,
        std::shared_ptr<Ledger> outbox,
        ServerContext::DeliveryResult& lastResult);
    void refresh();
    void reset();
    void set_result(ServerContext::DeliveryResult&& result);
    bool start(
        const Lock& decisionLock,
        const Type type,
        const ServerContext::ExtraArgs& args);
    bool state_machine();
    void transaction_numbers();

    Operation(
        const api::client::internal::Manager& api,
        const identifier::Nym& nym,
        const identifier::Server& server,
        const PasswordPrompt& reason);
    Operation() = delete;
    Operation(const Operation&) = delete;
    Operation(Operation&&) = delete;
    Operation& operator=(const Operation&) = delete;
    Operation& operator=(Operation&&) = delete;
};
}  // namespace opentxs::otx::client::implementation
