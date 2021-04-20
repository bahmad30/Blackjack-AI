#include <catch2/catch.hpp>
#include <deck.h>


TEST_CASE("Deck constructor") {
    blackjack::Deck deck;
    std::vector<blackjack::Card> cards = deck.GetCardsInDeck();
    
    SECTION("52 cards") {
        REQUIRE(cards.size() == 52);
    }
    SECTION("No cards in table") {
        REQUIRE(deck.GetCardsOnTable().empty());
    }
    SECTION("Correct ranks") {
        int sum = 0;
        for (blackjack::Card &card : cards) {
            sum += card.GetRank();
        }
        REQUIRE(sum == 364);
    }
    SECTION("Correct suits") {
        int diamonds = 0;
        int spades = 0;
        int hearts = 0;
        int clubs = 0;
        for (blackjack::Card &card : cards) {
            if (card.GetSuit() == 'D') {
                diamonds++;
            } else if (card.GetSuit() == 'S') {
                spades++;
            } else if (card.GetSuit() == 'H') {
                hearts++;
            } else if (card.GetSuit() == 'C') {
                clubs++;
            }
        }
        REQUIRE(diamonds == 13);
        REQUIRE(spades == 13);
        REQUIRE(hearts == 13);
        REQUIRE(clubs == 13);
    }
}

TEST_CASE("Shuffle") {
    blackjack::Deck deck;
    std::vector<blackjack::Card> before = deck.GetCardsInDeck();
    deck.Shuffle();
    std::vector<blackjack::Card> after = deck.GetCardsInDeck();

    SECTION("Cards in different order") {
        bool different_order = false;
        for (size_t i = 0; i < after.size(); i++) {
            if (before[i].GetRank() != after[i].GetRank() || before[i].GetSuit() != after[i].GetSuit()) {
                different_order = true;
            }
        }
        REQUIRE(different_order);
    }
}

TEST_CASE("Draw card") {
    blackjack::Deck deck;
    
    SECTION("Cards in deck loses correct card") {
        blackjack::Card drawn = deck.DrawCard();
        bool present = false;
        for (blackjack::Card &card : deck.GetCardsInDeck()) {
            if (card.GetRank() == drawn.GetRank() && card.GetSuit() == drawn.GetSuit()) {
                present = true;
            }
        }
        REQUIRE(!present);
    }
    SECTION("Cards on table gets correct card") {
        blackjack::Card drawn = deck.DrawCard();
        bool present = false;
        for (blackjack::Card &card : deck.GetCardsOnTable()) {
            if (card.GetRank() == drawn.GetRank() && card.GetSuit() == drawn.GetSuit()) {
                present = true;
            }
        }
        REQUIRE(present);
    }
    SECTION("Multiple draws") {
        deck.DrawCard();
        deck.DrawCard();
        REQUIRE(deck.GetCardsInDeck().size() == 50);
        REQUIRE(deck.GetCardsOnTable().size() == 2);
    }
    SECTION("Draw from empty deck") {
        while (!deck.GetCardsInDeck().empty()) {
            deck.DrawCard();
        }
        REQUIRE_THROWS_AS(deck.DrawCard(), std::invalid_argument);
    }
}

TEST_CASE("Reset") {
    blackjack::Deck deck;
    deck.DrawCard();
    deck.DrawCard();
    blackjack::Card drawn1 = deck.GetCardsOnTable()[0];
    blackjack::Card drawn2 = deck.GetCardsOnTable()[1];
    deck.Reset();

    SECTION("Correct cards are transferred") {
        bool first_present = false;
        bool second_present = false;
        for (blackjack::Card &card : deck.GetCardsInDeck()) {
            if (card.GetRank() == drawn1.GetRank() && card.GetSuit() == drawn1.GetSuit()) {
                first_present = true;
            } else if (card.GetRank() == drawn2.GetRank() && card.GetSuit() == drawn2.GetSuit()) {
                second_present = true;
            }
        }
        REQUIRE((first_present && second_present));
    }
}
