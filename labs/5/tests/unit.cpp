#include "../custom_memory_resourse.cpp"
#include "../my_iter.cpp"
#include <gtest/gtest.h>
#include <memory_resource>
#include <stdexcept>

TEST(MyIterTest, Constructor) {
  int value = 42;
  MyIter<int> iter(&value);
  EXPECT_EQ(*iter, 42);
}

TEST(MyIterTest, DereferenceOperator) {
  int value = 10;
  MyIter<int> iter(&value);
  EXPECT_EQ(*iter, 10);
  *iter = 20;
  EXPECT_EQ(*iter, 20);
}

TEST(MyIterTest, ArrowOperator) {
  struct TestStruct {
    int x;
  };

  TestStruct obj{100};
  MyIter<TestStruct> iter(&obj);
  EXPECT_EQ(iter->x, 100);
  iter->x = 200;
  EXPECT_EQ(iter->x, 200);
}

TEST(MyIterTest, PrefixIncrement) {
  int arr[] = {1, 2, 3};
  MyIter<int> iter(arr);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(MyIterTest, PostfixIncrement) {
  int arr[] = {4, 5, 6};
  MyIter<int> iter(arr);
  MyIter<int> oldIter = iter++;
  EXPECT_EQ(*oldIter, 4);
  EXPECT_EQ(*iter, 5);
  oldIter = iter++;
  EXPECT_EQ(*oldIter, 5);
  EXPECT_EQ(*iter, 6);
}

TEST(MyIterTest, EqualityOperator) {
  int arr[] = {1, 2, 3};
  MyIter<int> iter1(arr);
  MyIter<int> iter2(arr);
  EXPECT_TRUE(iter1 == iter2);

  ++iter1;
  EXPECT_FALSE(iter1 == iter2);
}

TEST(MyIterTest, InequalityOperator) {
  int arr[] = {7, 8, 9};
  MyIter<int> iter1(arr);
  MyIter<int> iter2(arr + 1);
  EXPECT_TRUE(iter1 != iter2);

  ++iter1;
  EXPECT_FALSE(iter1 != iter2);
}

TEST(CustomMemoryResourseTest, AllocationAndDeallocation) {
  const size_t memory_size = 1024;
  CustomMemoryResourse mem_res(memory_size);
  std::pmr::polymorphic_allocator<int> alloc(&mem_res);

  int *ptr1 = alloc.allocate(10);
  EXPECT_NE(ptr1, nullptr);

  alloc.deallocate(ptr1, 10);
  int *ptr2 = alloc.allocate(10);
  EXPECT_NE(ptr2, nullptr);
}

TEST(CustomMemoryResourseTest, AllocationThrowsWhenOutOfMemory) {
  const size_t memory_size = 10;
  CustomMemoryResourse mem_res(memory_size);
  std::pmr::polymorphic_allocator<int> alloc(&mem_res);

  EXPECT_THROW(
      {
        int *ptr = alloc.allocate(100);
        (void)ptr; // Явно указываем, что не используем ptr
      },
      std::bad_alloc);
}

TEST(MyStackTest, PushAndTop) {
  CustomMemoryResourse mem_res(1024);
  MyStack<int> stack{std::pmr::polymorphic_allocator<int>(&mem_res)};

  stack.push(1);
  stack.push(2);

  EXPECT_EQ(stack.top(), 2);
}

TEST(MyStackTest, Pop) {
  CustomMemoryResourse mem_res(1024);
  MyStack<int> stack{std::pmr::polymorphic_allocator<int>(&mem_res)};

  stack.push(1);
  stack.push(2);
  stack.pop();

  EXPECT_EQ(stack.top(), 1);
}

TEST(MyStackTest, EmptyAndSize) {
  CustomMemoryResourse mem_res(1024);
  MyStack<int> stack{std::pmr::polymorphic_allocator<int>(&mem_res)};

  EXPECT_TRUE(stack.empty());
  stack.push(1);
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.size(), 1);
}

TEST(MyStackTest, PopThrowsOnEmptyStack) {
  CustomMemoryResourse mem_res(1024);
  MyStack<int> stack{std::pmr::polymorphic_allocator<int>(&mem_res)};

  EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(MyStackTest, TopThrowsOnEmptyStack) {
  CustomMemoryResourse mem_res(1024);
  MyStack<int> stack{std::pmr::polymorphic_allocator<int>(&mem_res)};

  EXPECT_THROW(stack.top(), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
