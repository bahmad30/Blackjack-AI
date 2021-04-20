#include <catch2/catch.hpp>
#include <card.h>

namespace blackjack {

TEST_CASE("Card constructor") {
    
    SECTION("Number card") {
        Card seven_of_diamonds(7, 'D');
        REQUIRE(seven_of_diamonds.GetValue() == 7);
        REQUIRE(seven_of_diamonds.IsFaceCard() == false);
        REQUIRE(seven_of_diamonds.IsAce() == false);
    }
    SECTION("Face card") {
        Card queen_of_hearts(12, 'H');
        REQUIRE(queen_of_hearts.GetValue() == 10);
        REQUIRE(queen_of_hearts.IsFaceCard() == true);
        REQUIRE(queen_of_hearts.IsAce() == false);
    }
    SECTION("Ace") {
        Card ace_of_spades(1, 'S');
        REQUIRE(ace_of_spades.GetValue() == 1);
        REQUIRE(ace_of_spades.IsFaceCard() == true);
        REQUIRE(ace_of_spades.IsAce() == true);
    }
}

TEST_CASE("Set ace") {
    Card ace(1, 'S');
    
    SECTION("Set to 11") {
        ace.SetAce(11);
        REQUIRE(ace.GetValue() == 11);
    }
    SECTION("Set to 1") {
        ace.SetAce(11);
        ace.SetAce(1);
        REQUIRE(ace.GetValue() == 1);
    }
    SECTION("Bad set value (not 1 or 11)") {
        REQUIRE_THROWS_AS(ace.SetAce(7), std::invalid_argument);
    }
    SECTION("Bad card (not ace)") {
        Card non_ace(7, 'D');
        REQUIRE_THROWS_AS(non_ace.SetAce(11), std::invalid_argument);
    }
}


} // namespace blackjack