// Copyright (c) 2010-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "OTTestEnvironment.hpp"

#include <boost/endian/buffers.hpp>

namespace be = boost::endian;

namespace
{
class Test_NumericHash : public ::testing::Test
{
public:
    const ot::api::client::internal::Manager& api_;

    Test_NumericHash()
        : api_(dynamic_cast<const ot::api::client::internal::Manager&>(
              ot::Context().StartClient(OTTestEnvironment::test_args_, 0)))
    {
    }
};

TEST_F(Test_NumericHash, init_opentxs) {}

TEST_F(Test_NumericHash, number_low_1)
{
    // Little endian
    const auto raw = ot::Data::Factory("0x01", ot::Data::Mode::Hex);
    const std::string decimal{"1"};
    // Big endian
    const std::string hex{
        "0000000000000000000000000000000000000000000000000000000000000001"};

    const ot::OTNumericHash number{ot::Factory::NumericHash(raw)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, number_low_32)
{
    // Little endian
    const auto raw = ot::Data::Factory(
        "0x0100000000000000000000000000000000000000000000000000000000000000",
        ot::Data::Mode::Hex);
    const std::string decimal{"1"};
    // Big endian
    const std::string hex{
        "0000000000000000000000000000000000000000000000000000000000000001"};

    const ot::OTNumericHash number{ot::Factory::NumericHash(raw)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, number_high)
{
    // Little endian
    const auto raw = ot::Data::Factory(
        "0xf1ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
        ot::Data::Mode::Hex);
    const std::string decimal{"115792089237316195423570985008687907853269984665"
                              "640564039457584007913129639921"};
    // Big endian
    const std::string hex{
        "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff1"};

    const ot::OTNumericHash number{ot::Factory::NumericHash(raw)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, nBits_1)
{
    const std::int32_t nBits{83923508};  // 0x05009234
    const std::string decimal{"2452881408"};
    const std::string hex{
        "0000000000000000000000000000000000000000000000000000000092340000"};

    const ot::OTNumericHash number{ot::Factory::NumericHashNBits(nBits)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, nBits_2)
{
    const std::int32_t nBits{68301910};  // 0x04123456
    const std::string decimal{"305419776"};
    const std::string hex{
        "0000000000000000000000000000000000000000000000000000000012345600"};

    const ot::OTNumericHash number{ot::Factory::NumericHashNBits(nBits)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, nBits_3)
{
    const std::int32_t nBits{404472624};  // 0x81bc330
    const std::string decimal{
        "680733321990486529407107157001552378184394215934016880640"};
    const std::string hex{
        "00000000000000001bc330000000000000000000000000000000000000000000"};

    const ot::OTNumericHash number{ot::Factory::NumericHashNBits(nBits)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, nBits_4)
{
    const std::int32_t nBits{453248203};  // 0x1b0404cb
    const std::string decimal{
        "1653206561150525499452195696179626311675293455763937233695932416"};
    const std::string hex{
        "00000000000404cb000000000000000000000000000000000000000000000000"};

    const ot::OTNumericHash number{ot::Factory::NumericHashNBits(nBits)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
}

TEST_F(Test_NumericHash, nBits_5)
{
    const std::int32_t nBits{486604799};  // 0x1d00ffff
    const std::string decimal{
        "26959535291011309493156476344723991336010898738574164086137773096960"};
    const std::string hex{
        "00000000ffff0000000000000000000000000000000000000000000000000000"};

    const ot::OTNumericHash number{ot::Factory::NumericHashNBits(nBits)};

    EXPECT_EQ(decimal, number->Decimal());
    EXPECT_EQ(hex, number->asHex());
    EXPECT_STREQ("1", ot::Factory::Work(number)->Decimal().c_str());
}
}  // namespace
