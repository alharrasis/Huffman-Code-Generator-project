/***********************************
Compile Using: Make file by typing make in console
Then Run Tests using ./a.out -s
************************************/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "HuffmanTree.hpp"
#include "TestStrings.hpp"

TEST_CASE("Project 4 Test Cases for Huffman Coding") {
  HuffmanTree t;

  // Turing String Tests
  SECTION("Should compress the turing string") {
    REQUIRE(t.compress(turing) == turingCode);
  }
    
  SECTION("Should serialize the tree for turing") {
    t.compress(turing);
    REQUIRE(t.serializeTree() == turingTree);
  }

  SECTION("Should decompress the turing string") {
    REQUIRE(t.decompress(turingCode, turingTree) == turing);
  }

  // Dijkstra String Tests
  SECTION("Should compress the dijkstra string") {
    REQUIRE(t.compress(dijkstra) == dijkstraCode);
  }
    
  SECTION("Should serialize the tree for dijkstra") {
    t.compress(dijkstra);
    REQUIRE(t.serializeTree() == dijkstraTree);
  }

  SECTION("Should decompress the dijkstra string") {
    REQUIRE(t.decompress(dijkstraCode, dijkstraTree) == dijkstra);
  }

  // Wikipedia String Tests
  SECTION("Should compress the wikipedia string") {
    REQUIRE(t.compress(wikipedia) == wikipediaCode);
  }
    
  SECTION("Should serialize the tree for wikipedia") {
    t.compress(wikipedia);
    REQUIRE(t.serializeTree() == wikipediaTree);
  }

  SECTION("Should decompress the wikipedia string") {
    REQUIRE(t.decompress(wikipediaCode, wikipediaTree) == wikipedia);
  }

  // Constitution String Tests
  SECTION("Should compress the constitution string") {
    REQUIRE(t.compress(constitution) == constitutionCode);
  }
    
  SECTION("Should serialize the tree for constitution") {
    t.compress(constitution);
    REQUIRE(t.serializeTree() == constitutionTree);
  }

  SECTION("Should decompress the constitution string") {
    REQUIRE(t.decompress(constitutionCode, constitutionTree) == constitution);
  }
}



