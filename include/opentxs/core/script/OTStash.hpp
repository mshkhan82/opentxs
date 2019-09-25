// Copyright (c) 2019 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_CORE_SCRIPT_OTSTASH_HPP
#define OPENTXS_CORE_SCRIPT_OTSTASH_HPP

#include "opentxs/Forward.hpp"

#include <map>
#include <string>
#include <cstdint>

namespace irr
{
namespace io
{
template <class char_type, class super_class>
class IIrrXMLReader;
class IXMLBase;
typedef IIrrXMLReader<char, IXMLBase> IrrXMLReader;
}  // namespace io
}  // namespace irr

namespace opentxs
{

class Identifier;
class OTStashItem;
class String;
class Tag;

typedef std::map<std::string, OTStashItem*> mapOfStashItems;

class OTStash
{
    std::string m_str_stash_name;

    mapOfStashItems m_mapStashItems;  // map of stash items by instrument
                                      // definition ID.
                                      // owned.
public:
    const std::string GetName() const { return m_str_stash_name; }
    OTStashItem* GetStash(const std::string& str_instrument_definition_id);

    std::int64_t GetAmount(const std::string& str_instrument_definition_id);
    bool CreditStash(
        const std::string& str_instrument_definition_id,
        const std::int64_t& lAmount);
    bool DebitStash(
        const std::string& str_instrument_definition_id,
        const std::int64_t& lAmount);

    void Serialize(Tag& parent) const;
    std::int32_t ReadFromXMLNode(
        irr::io::IrrXMLReader*& xml,
        const String& strStashName,
        const String& strItemCount);

    OTStash();
    OTStash(const std::string& str_stash_name);
    OTStash(const String& strInstrumentDefinitionID, std::int64_t lAmount = 0);
    OTStash(
        const Identifier& theInstrumentDefinitionID,
        std::int64_t lAmount = 0);
    virtual ~OTStash();
};

}  // namespace opentxs

#endif
