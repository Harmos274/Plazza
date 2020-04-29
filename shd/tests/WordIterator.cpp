#include <catch2.hpp>

#include <WordIterator.hpp>

TEST_CASE("Simple string iteration", "[WordIterator]")
{
    auto iter = shd::WordIterator<' '>{"Thank you for summing that up"};

    REQUIRE(*(iter + 0) == "Thank");
    REQUIRE(*(iter + 1) == "you");
    REQUIRE(*(iter + 2) == "for");
    REQUIRE(*(iter + 3) == "summing");
    REQUIRE(*(iter + 4) == "that");
    REQUIRE(*(iter + 5) == "up");
}

TEST_CASE("Multiple separators", "[WordIterator]")
{
    auto iter =
        shd::WordIterator<' ', ';'>{";Thank you;for  ;summing ; that up "};

    REQUIRE(*(iter + 0) == "Thank");
    REQUIRE(*(iter + 1) == "you");
    REQUIRE(*(iter + 2) == "for");
    REQUIRE(*(iter + 3) == "summing");
    REQUIRE(*(iter + 4) == "that");
    REQUIRE(*(iter + 5) == "up");
}

TEST_CASE("No separator", "[WordIterator]")
{
    auto iter = shd::WordIterator{"Thank you for nothing, you useless reptile"};

    REQUIRE(*iter == "Thank you for nothing, you useless reptile");
}

TEST_CASE("Increment operators", "[WordIterator]")
{
    auto iter = shd::WordIterator<' ', ','>{"Nightfury, get down"};
    auto original = shd::WordIterator{iter};
    auto plus_one = iter + 1;

    REQUIRE(iter == original);

    REQUIRE(iter++ == original);
    REQUIRE(iter == plus_one);

    iter = original;

    REQUIRE(++iter == plus_one);
    REQUIRE(iter == plus_one);

    iter = original;

    REQUIRE(*(iter + 2) == "down");
    REQUIRE(iter == original);

    iter += 1;
    REQUIRE(iter == plus_one);
}

TEST_CASE("Constexpr-ness", "[WordIterator]")
{
    constexpr auto iter = shd::WordIterator<' '>{"It's an occupational hazard"};

    constexpr auto first_word = *(iter + 0);
    constexpr auto second_word = *(iter + 1);
    constexpr auto third_word = *(iter + 2);
    constexpr auto fourth_word = *(iter + 3);
    constexpr auto end_iter = iter + 4;

    if constexpr (first_word == "It's" && second_word == "an" &&
                  third_word == "occupational" && fourth_word == "hazard" &&
                  end_iter == iter.end())
    {
        REQUIRE(true);
    }
    else
    {
        REQUIRE(false);
    }
}
