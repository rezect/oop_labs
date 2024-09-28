#include <gtest/gtest.h>
#include "../solution.cpp"

//
// Тесты для конструкторов
//

TEST(SevenConstructors, DefaultConstructor) {
    Seven s;
    EXPECT_EQ(s.size(), 0);
}

TEST(SevenConstructors, SizeConstructorWithDefaultChar) {
    Seven s(5);
    EXPECT_EQ(s.size(), 5);
    for (size_t i = 0; i < s.size(); ++i) {
        EXPECT_EQ(s[i], '0');
    }
}

TEST(SevenConstructors, SizeConstructorWithCustomChar) {
    Seven s(3, '5');
    EXPECT_EQ(s.size(), 3);
    for (size_t i = 0; i < s.size(); ++i) {
        EXPECT_EQ(s[i], '5');
    }
}

TEST(SevenConstructors, InitializerListConstructor) {
    Seven s = {'1', '2', '3', '4'};
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s[0], '1');
    EXPECT_EQ(s[1], '2');
    EXPECT_EQ(s[2], '3');
    EXPECT_EQ(s[3], '4');
}

TEST(SevenConstructors, StringConstructor) {
    Seven s("321");
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], '1');
    EXPECT_EQ(s[1], '2');
    EXPECT_EQ(s[2], '3');
}

TEST(SevenConstructors, CopyConstructor) {
    Seven s1 = {'1', '2', '3'};
    Seven s2(s1);
    EXPECT_EQ(s2.size(), s1.size());
    for (size_t i = 0; i < s1.size(); ++i) {
        EXPECT_EQ(s2[i], s1[i]);
    }
}

TEST(SevenConstructors, MoveConstructor) {
    Seven s1 = {'4', '5', '6'};
    Seven s2(std::move(s1));
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2[0], '4');
    EXPECT_EQ(s2[1], '5');
    EXPECT_EQ(s2[2], '6');

    EXPECT_EQ(s1.size(), 0);
}

//
// Тесты для операторов сложения/вычитания
//

TEST(SevenOperatorsPlusMinus, AdditionWithoutCarry) {
    Seven s1 = {'1', '2', '3'};
    Seven s2 = {'2', '3', '1'};

    Seven result = s1 + s2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '3');
    EXPECT_EQ(result[1], '5');
    EXPECT_EQ(result[2], '4');
}

TEST(SevenOperatorsPlusMinus, AdditionWithCarry) {
    Seven s1 = {'6', '6', '6'};
    Seven s2 = {'1', '1', '1'};

    Seven result = s1 + s2;
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], '0'); 
    EXPECT_EQ(result[1], '1');
    EXPECT_EQ(result[2], '1');
    EXPECT_EQ(result[3], '1');
}

TEST(SevenOperatorsPlusMinus, AdditionDifferentLengths) {
    Seven s1 = {'6', '2'};
    Seven s2 = {'3'};

    Seven result = s1 + s2;
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], '2');
    EXPECT_EQ(result[1], '3');
}

TEST(SevenOperatorsPlusMinus, SubtractionWithoutBorrow) {
    Seven s1 = {'4', '5', '3'};
    Seven s2 = {'1', '2', '1'};

    Seven result = s1 - s2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '3');
    EXPECT_EQ(result[1], '3');
    EXPECT_EQ(result[2], '2');
}

TEST(SevenOperatorsPlusMinus, SubtractionWithBorrow) {
    Seven s1 = {'3', '0', '1'};
    Seven s2 = {'2', '6'};

    Seven result = s1 - s2;
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], '1');
    EXPECT_EQ(result[1], '1');
}

TEST(SevenOperatorsPlusMinus, SubtractionDifferentLengths) {
    Seven s1 = {'2', '3', '4'};
    Seven s2 = {'1', '5'};

    Seven result = s1 - s2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '1');
    EXPECT_EQ(result[1], '5');
    EXPECT_EQ(result[2], '3');
}

TEST(SevenOperatorsPlusMinus, SubtractionWithNegativeResult) {
    Seven s1 = {'1', '0', '0'};
    Seven s2 = {'2', '0', '1'};

    EXPECT_THROW({
        Seven result = s1 - s2;
    }, std::invalid_argument);
}

TEST(SevenOperatorsPlusMinus, AdditionWithEmptySeven) {
    Seven s1 = {'3', '2', '1'};
    Seven s2;

    Seven result = s1 + s2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '3');
    EXPECT_EQ(result[1], '2');
    EXPECT_EQ(result[2], '1');
}

TEST(SevenOperatorsPlusMinus, SubtractionWithEmptySeven) {
    Seven s1 = {'3', '2', '1'};
    Seven s2;

    Seven result = s1 - s2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], '3');
    EXPECT_EQ(result[1], '2');
    EXPECT_EQ(result[2], '1');
}

//
// Тесты для операторов присваивания (копирующий и перемещающий)
//

TEST(SevenAssignments, CopyAssignment) {
    Seven s1 = {'1', '2', '3'};
    Seven s2;
    s2 = s1;

    EXPECT_EQ(s2.size(), s1.size());
    for (size_t i = 0; i < s1.size(); ++i) {
        EXPECT_EQ(s2[i], s1[i]);
    }
}

TEST(SevenAssignments, MoveAssignment) {
    Seven s1 = {'4', '5', '6'};
    Seven s2;
    s2 = std::move(s1);

    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2[0], '4');
    EXPECT_EQ(s2[1], '5');
    EXPECT_EQ(s2[2], '6');

    EXPECT_EQ(s1.size(), 0);
}

TEST(SevenAssignments, SelfAssignment) {
    Seven s1 = {'4', '5', '6'};

    s1 = s1;
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s1[0], '4');
    EXPECT_EQ(s1[1], '5');
    EXPECT_EQ(s1[2], '6');
}

//
// Тесты для операторов += и -=
//

TEST(SevenArifmeticAssignments, AdditionAssignment) {
    Seven s1 = {'1', '2', '3'};
    Seven s2 = {'3', '2', '1'};

    s1 += s2;
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s1[0], '4');
    EXPECT_EQ(s1[1], '4');
    EXPECT_EQ(s1[2], '4');
}

TEST(SevenArifmeticAssignments, SubtractionAssignment) {
    Seven s1 = {'4', '5', '3'};
    Seven s2 = {'4', '5', '3'};

    s1 -= s2;
    EXPECT_EQ(s1.size(), 1);
    EXPECT_EQ(s1[0], '0');
}

TEST(SevenArifmeticAssignments, SubtractionAssignmentWithInvalidOperation) {
    Seven s1 = {'1', '2', '3'};
    Seven s2 = {'3', '2', '1'};

    EXPECT_THROW({
        s2 -= s1;
    }, std::invalid_argument);
}

//
// Тесты для операторов сравнения
//

TEST(SevenCompareOperators, ComparisonGreaterThan) {
    Seven s1 = {'4', '5', '3'};
    Seven s2 = {'3', '2', '1'};

    EXPECT_TRUE(s1 > s2);
    EXPECT_FALSE(s2 > s1);
}

TEST(SevenCompareOperators, ComparisonLessThan) {
    Seven s1 = {'1', '2', '3'};
    Seven s2 = {'2', '3', '4'};

    EXPECT_TRUE(s1 < s2);
    EXPECT_FALSE(s2 < s1);
}

TEST(SevenCompareOperators, ComparisonEqual) {
    Seven s1 = {'3', '2', '1'};
    Seven s2 = {'3', '2', '1'};

    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == Seven({'1', '2', '3'}));
}

TEST(SevenCompareOperators, ComparisonDifferentLengths) {
    Seven s1 = {'1', '2'};
    Seven s2 = {'1', '2', '3'};

    EXPECT_TRUE(s2 > s1);
    EXPECT_FALSE(s1 > s2);
    EXPECT_TRUE(s1 < s2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
