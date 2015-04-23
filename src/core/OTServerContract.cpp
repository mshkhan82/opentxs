/************************************************************
 *
 *  OTServerContract.cpp
 *
 */

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1

 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- otlib.........A class library.......LICENSE:...LAGPLv3
 *   -- otapi.........A client API..........LICENSE:...LAGPLv3
 *   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 *   -- otserver......Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (bitcointrader4@gmail.com).
 *  The open-source community has since actively contributed.
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT API, then you
 *   don't have to open-source your code--only your changes to
 *   Open-Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open-Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open-Transactions terms remain respected, with regard to
 *   the Open-Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   See Lucre on Github:  https://github.com/benlaurie/lucre
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.

 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.9 (Darwin)

 iQIcBAEBAgAGBQJRSsfJAAoJEAMIAO35UbuOQT8P/RJbka8etf7wbxdHQNAY+2cC
 vDf8J3X8VI+pwMqv6wgTVy17venMZJa4I4ikXD/MRyWV1XbTG0mBXk/7AZk7Rexk
 KTvL/U1kWiez6+8XXLye+k2JNM6v7eej8xMrqEcO0ZArh/DsLoIn1y8p8qjBI7+m
 aE7lhstDiD0z8mwRRLKFLN2IH5rAFaZZUvj5ERJaoYUKdn4c+RcQVei2YOl4T0FU
 LWND3YLoH8naqJXkaOKEN4UfJINCwxhe5Ke9wyfLWLUO7NamRkWD2T7CJ0xocnD1
 sjAzlVGNgaFDRflfIF4QhBx1Ddl6wwhJfw+d08bjqblSq8aXDkmFA7HeunSFKkdn
 oIEOEgyj+veuOMRJC5pnBJ9vV+7qRdDKQWaCKotynt4sWJDGQ9kWGWm74SsNaduN
 TPMyr9kNmGsfR69Q2Zq/FLcLX/j8ESxU+HYUB4vaARw2xEOu2xwDDv6jt0j3Vqsg
 x7rWv4S/Eh18FDNDkVRChiNoOIilLYLL6c38uMf1pnItBuxP3uhgY6COm59kVaRh
 nyGTYCDYD2TK+fI9o89F1297uDCwEJ62U0Q7iTDp5QuXCoxkPfv8/kX6lS6T3y9G
 M9mqIoLbIQ1EDntFv7/t6fUTS2+46uCrdZWbQ5RjYXdrzjij02nDmJAm2BngnZvd
 kamH0Y/n11lCvo1oQxM+
 =uSzz
 -----END PGP SIGNATURE-----
 **************************************************************/

#include <opentxs/core/stdafx.hpp>
#include <opentxs/core/Nym.hpp>
#include <opentxs/core/OTServerContract.hpp>
#include <opentxs/core/crypto/OTASCIIArmor.hpp>
#include <opentxs/core/crypto/OTCrypto.hpp>
#include <opentxs/core/Log.hpp>
#include <opentxs/core/util/OTFolders.hpp>
#include <opentxs/core/OTStorage.hpp>
#include <opentxs/core/util/Tag.hpp>

#include <fstream>
#include <cstring>
#include <irrxml/irrXML.hpp>

// zcert_public_key returns a 32 bit public key.
const int32_t TRANSPORT_KEY_SIZE = 32;

namespace opentxs
{

OTServerContract::OTServerContract()
    : Contract()
{
    m_nPort = 0;
}

OTServerContract::OTServerContract(String& name, String& foldername,
                                   String& filename, String& strID)
    : Contract(name, foldername, filename, strID)
{
    m_nPort = 0;
}

OTServerContract::~OTServerContract()
{
}

bool OTServerContract::GetConnectInfo(String& strHostname, int32_t& nPort) const
{
    if (m_strHostname.GetLength()) {
        strHostname = m_strHostname;
        nPort = m_nPort;
        return true;
    }
    return false;
}

unsigned char* OTServerContract::GetTransportKey() const
{
    return m_transportKey;
}

bool OTServerContract::DisplayStatistics(String& strContents) const
{
    const String strID(m_ID);

    strContents.Concatenate(" Notary Provider: %s\n"
                            " NotaryID: %s\n"
                            "\n",
                            m_strName.Get(), strID.Get());

    return true;
}

bool OTServerContract::SaveContractWallet(Tag& parent) const
{
    const String strID(m_ID);

    // Name is in the clear in memory,
    // and base64 in storage.
    OTASCIIArmor ascName;
    if (m_strName.Exists()) {
        ascName.SetString(m_strName, false); // linebreaks == false
    }

    TagPtr pTag(new Tag("notaryProvider"));

    pTag->add_attribute("name", m_strName.Exists() ? ascName.Get() : "");
    pTag->add_attribute("notaryID", strID.Get());

    parent.add_tag(pTag);

    return true;
}

zcert_t* OTServerContract::LoadOrCreateTransportKey(const String& nymID)
{
    std::string filepath;
    OTDB::FormPathString(filepath, OTFolders::Credential().Get(), nymID.Get(),
                         "transportKey");

    if (!zcert_load(filepath.c_str())) {
        // File does not exist: create keypair and store.
        // This creates two files: `filepath` and `filepath`_secret.
        zcert_save(zcert_new(), filepath.c_str());
    }

    return zcert_load(filepath.c_str());
}

void OTServerContract::CreateContents()
{
    m_xmlUnsigned.Release();

    Tag tag("notaryProviderContract");

    tag.add_attribute("version", m_strVersion.Get());

    // Entity
    {
        TagPtr pTag(new Tag("entity"));
        pTag->add_attribute("shortname", m_strEntityShortName.Get());
        pTag->add_attribute("longname", m_strEntityLongName.Get());
        pTag->add_attribute("email", m_strEntityEmail.Get());
        pTag->add_attribute("serverURL", m_strURL.Get());
        tag.add_tag(pTag);
    }
    // notaryServer
    {
        TagPtr pTag(new Tag("notaryServer"));
        pTag->add_attribute("hostname", m_strHostname.Get());
        pTag->add_attribute("port", formatInt(m_nPort));
        pTag->add_attribute("URL", m_strURL.Get());
        tag.add_tag(pTag);
    }

    // Write the transportKey
    const Nym* nym = m_mapNyms["signer"];
    const unsigned char* transportKey = zcert_public_key(
        OTServerContract::LoadOrCreateTransportKey(String(nym->GetConstID())));
    // base64-encode the binary public key because the encoded key
    // (zcert_public_txt()) does Z85 encoding, which contains the '<','>' chars.
    // See http://rfc.zeromq.org/spec:32.

    tag.add_tag("transportKey", OTCrypto::It()->Base64Encode(
                                    transportKey, TRANSPORT_KEY_SIZE, false));

    // This is where OTContract scribes tag with its keys,
    // conditions, etc.
    CreateInnerContents(tag);

    std::string str_result;
    tag.output(str_result);

    m_xmlUnsigned.Format("%s", str_result.c_str());
}

// This is the serialization code for READING FROM THE CONTRACT
// return -1 if error, 0 if nothing, and 1 if the node was processed.
int32_t OTServerContract::ProcessXMLNode(irr::io::IrrXMLReader*& xml)
{
    // Here we call the parent class first.
    // If the node is found there, or there is some error,
    // then we just return either way.  But if it comes back
    // as '0', then nothing happened, and we'll continue executing.
    //
    // -- Note you can choose not to call the parent if
    // you don't want to use any of those xml tags.

    auto result = Contract::ProcessXMLNode(xml);
    if (result) return result;

    if (!strcmp("notaryProviderContract", xml->getNodeName())) {
        m_strVersion = xml->getAttributeValue("version");

        otWarn << "\n"
                  "===> Loading XML portion of server contract into memory "
                  "structures...\n\n"
                  "Notary Server Name: " << m_strName
               << "\nContract version: " << m_strVersion << "\n----------\n";
        return 1;
    }
    if (!strcmp("notaryServer", xml->getNodeName())) {
        m_strHostname = xml->getAttributeValue("hostname");
        m_nPort = atoi(xml->getAttributeValue("port"));
        m_strURL = xml->getAttributeValue("URL");

        otWarn << "\n"
                  "Notary Server connection info:\n --- Hostname: "
               << m_strHostname << "\n --- Port: " << m_nPort
               << "\n --- URL:" << m_strURL << "\n\n";
        return 1;
    }
    if (!strcmp("transportKey", xml->getNodeName())) {
        if (!SkipToTextField(xml)) {
            return -1;
        }
        const char* transportKeyB64 = xml->getNodeData();
        if (!transportKeyB64) return -1;
        std::string transportKeyB64Trimmed(transportKeyB64);
        String::trim(transportKeyB64Trimmed);
        size_t outLen;
        m_transportKey = OTCrypto::It()->Base64Decode(
            transportKeyB64Trimmed.c_str(), &outLen, false);
        if (outLen != TRANSPORT_KEY_SIZE) {
            return -1;
        }
        return 1;
    }

    return 0;
}

} // namespace opentxs
