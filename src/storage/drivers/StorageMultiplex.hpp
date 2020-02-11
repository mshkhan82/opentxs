// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Internal.hpp"

namespace opentxs::storage::implementation
{
class StorageMultiplex final : virtual public opentxs::api::storage::Multiplex
{
public:
    bool EmptyBucket(const bool bucket) const final;
    bool LoadFromBucket(
        const std::string& key,
        std::string& value,
        const bool bucket) const final;
    bool Load(const std::string& key, const bool checking, std::string& value)
        const final;
    std::string LoadRoot() const final;
    bool Migrate(
        const std::string& key,
        const opentxs::api::storage::Driver& to) const final;
    bool Store(
        const bool isTransaction,
        const std::string& key,
        const std::string& value,
        const bool bucket) const final;
    void Store(
        const bool isTransaction,
        const std::string& key,
        const std::string& value,
        const bool bucket,
        std::promise<bool>& promise) const final;
    bool Store(
        const bool isTransaction,
        const std::string& value,
        std::string& key) const final;
    bool StoreRoot(const bool commit, const std::string& hash) const final;

    std::string BestRoot(bool& primaryOutOfSync) final;
    void InitBackup() final;
    void InitEncryptedBackup(crypto::key::Symmetric& key) final;
    opentxs::api::storage::Driver& Primary() final;
    void SynchronizePlugins(
        const std::string& hash,
        const storage::Root& root,
        const bool syncPrimary) final;

    ~StorageMultiplex() final;

private:
    friend Factory;

    const api::storage::Storage& storage_;
    const Flag& primary_bucket_;
    const StorageConfig& config_;
    std::unique_ptr<opentxs::api::storage::Plugin> primary_plugin_;
    std::vector<std::unique_ptr<opentxs::api::storage::Plugin>> backup_plugins_;
    const Digest digest_;
    const Random random_;
    OTSymmetricKey null_;

    StorageMultiplex(
        const api::storage::Storage& storage,
        const Flag& primaryBucket,
        const StorageConfig& config,
        const String& primary,
        const bool migrate,
        const String& previous,
        const Digest& hash,
        const Random& random);
    StorageMultiplex() = delete;
    StorageMultiplex(const StorageMultiplex&) = delete;
    StorageMultiplex(StorageMultiplex&&) = delete;
    StorageMultiplex& operator=(const StorageMultiplex&) = delete;
    StorageMultiplex& operator=(StorageMultiplex&&) = delete;

    void Cleanup();
    void Cleanup_StorageMultiplex();
    void init(
        const std::string& primary,
        std::unique_ptr<opentxs::api::storage::Plugin>& plugin);
#if OT_STORAGE_FS == 0
    [[noreturn]]
#endif
    void
    init_fs(std::unique_ptr<opentxs::api::storage::Plugin>& plugin);

#if OT_STORAGE_LMDB == 0
    [[noreturn]]
#endif
    void
    init_lmdb(std::unique_ptr<opentxs::api::storage::Plugin>& plugin);
    void init_memdb(std::unique_ptr<opentxs::api::storage::Plugin>& plugin);

#if OT_STORAGE_SQLITE == 0
    [[noreturn]]
#endif
    void
    init_sqlite(std::unique_ptr<opentxs::api::storage::Plugin>& plugin);
    void Init_StorageMultiplex(
        const String& primary,
        const bool migrate,
        const String& previous);
    void migrate_primary(const std::string& from, const std::string& to);
};
}  // namespace opentxs::storage::implementation
