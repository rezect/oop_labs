#include "../solution.cpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(TryTrue, Mon) {
  ASSERT_EQ(am_i_afraid("Понедельник", 12), true);
}

TEST(TryTrue, Tue) {
  ASSERT_EQ(am_i_afraid("Вторник", 122), true);
}

TEST(TryTrue, Wed) {
  ASSERT_EQ(am_i_afraid("Среда", 34), true);
}

TEST(TryTrue, Thu) {
  ASSERT_EQ(am_i_afraid("Четверг", 0), true);
}

TEST(TryTrue, Fri) {
  ASSERT_EQ(am_i_afraid("Пятница", 12), true);
}

TEST(TryTrue, Sat) {
  ASSERT_EQ(am_i_afraid("Суббота", 56), true);
}

TEST(TryTrue, Sun1) {
  ASSERT_EQ(am_i_afraid("Воскресенье", 666), true);
}

TEST(TryTrue, Sun2) {
  ASSERT_EQ(am_i_afraid("Воскресенье", -666), true);
}

TEST(TryFalse, Mon) {
  ASSERT_EQ(am_i_afraid("Понедельник", 11), false);
}

TEST(TryFalse, Tue) {
  ASSERT_EQ(am_i_afraid("Вторник", 95), false);
}

TEST(TryFalse, Wed) {
  ASSERT_EQ(am_i_afraid("Среда", 11), false);
}

TEST(TryFalse, Thu) {
  ASSERT_EQ(am_i_afraid("Четверг", 11), false);
}

TEST(TryFalse, Fri) {
  ASSERT_EQ(am_i_afraid("Пятница", 11), false);
}

TEST(TryFalse, Sat) {
  ASSERT_EQ(am_i_afraid("Суббота", 11), false);
}

TEST(TryFalse, Sun1) {
  ASSERT_EQ(am_i_afraid("Воскресенье", 11), false);
}

TEST(TryRandom, RandomDay) {
  ASSERT_EQ(am_i_afraid("abacaba", 100), false);
}