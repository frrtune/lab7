#include <gtest/gtest.h>
#include "../lazy_sequence/lazy_sequence.hpp"
#include "../generator/ordinal_generator.hpp"
#include "../transfinite_numbers/ordinals.hpp"

TEST(LazySequenceTest, ConstructorTest) {
    LazySequence<int> sequence;
    EXPECT_EQ(sequence.GetMaterializedCount(), 0);
}

TEST(LazySequenceTest, ConstructorFromArrayTest) {
    int items[] = {1, 2, 3, 4, 5};
    LazySequence<int> sequence(items, 5);
    EXPECT_EQ(sequence.GetFirst(), 1);
    EXPECT_EQ(sequence.GetLast(), 5);
    EXPECT_EQ(sequence.GetMaterializedCount(), 5);
}

TEST(LazySequenceTest, GetFirstTest) {
    int items[] = {1, 2, 3};
    LazySequence<int> sequence(items, 3);
    EXPECT_EQ(sequence.GetFirst(), 1);
}

TEST(LazySequenceTest, GetLastTest) {
    int items[] = {1, 2, 3};
    LazySequence<int> sequence(items, 3);
    EXPECT_EQ(sequence.GetLast(), 3);
}

TEST(LazySequenceTest, GetTest) {
    int items[] = {1, 2, 3, 4};
    LazySequence<int> sequence(items, 4);
    EXPECT_EQ(sequence.Get(0), 1);
    EXPECT_EQ(sequence.Get(2), 3);
    EXPECT_EQ(sequence.Get(3), 4);
}

TEST(LazySequenceTest, GetOutOfRangeTest) {
    int items[] = {1, 2, 3};
    LazySequence<int> sequence(items, 3);
    EXPECT_THROW(sequence.Get(3), RangeError);
}

TEST(LazySequenceTest, AppendTest) {
    int items[] = {1, 2, 3};
    LazySequence<int> sequence(items, 3);
    LazySequence<int>* new_sequence = sequence.Append(4);
    EXPECT_EQ(new_sequence->GetFirst(), 1);
    EXPECT_EQ(new_sequence->GetLast(), 3);
    delete new_sequence;
}