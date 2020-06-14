#include "include/circular_buffer.h"
#include "gtest/gtest.h"

namespace {

class TestFixture : public ::testing::Test {
protected:
  virtual void SetUp() {}

  virtual void TearDown() {}
};
} // namespace

TEST(TestFixture, test) { EXPECT_EQ('a', 'a'); }

struct A {
  int i{0};
  char c{0};
  std::string s{};
  A() = default;
  A(int i, char c, std::string s) : i(i), c(c), s(s) {}
  bool operator==(const struct A &two) const {
    return i == two.i && c == two.c && s == two.s;
  }
};

TEST(CircularBufferTest, DefaultConstruction) {
  circular_buffer<int> cb(10);
  EXPECT_EQ(true, cb.empty());
}

// PushFront, PopFront
TEST(CircularBufferTest, PushFrontPopFront) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  EXPECT_EQ("3, ", cb.print());
  EXPECT_EQ(false, cb.empty());
  EXPECT_EQ(false, cb.full());
  EXPECT_EQ(3, cb.front());
  EXPECT_EQ(3, cb.pop_front());
  EXPECT_EQ(true, cb.empty());
  EXPECT_EQ(false, cb.full());
}
TEST(CircularBufferTest, PushFrontPopFrontWithTwoElements) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  cb.push_front(4);
  EXPECT_EQ("4, 3, ", cb.print());
  EXPECT_EQ(false, cb.empty());
  EXPECT_EQ(4, cb.pop_front());
  EXPECT_EQ("3, ", cb.print());
}
TEST(CircularBufferTest, PushFrontPopFrontWithThreeElements) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  cb.push_front(4);
  cb.push_front(5);
  EXPECT_EQ("5, 4, 3, ", cb.print());
  EXPECT_EQ(5, cb.pop_front());
  EXPECT_EQ(4, cb.front());
  EXPECT_EQ(4, cb.pop_front());
  EXPECT_EQ(3, cb.pop_front());
  EXPECT_EQ(true, cb.empty());
}

// PushFront, PopBack
TEST(CircularBufferTest, PushFrontPopBack) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  EXPECT_EQ("3, ", cb.print());
  EXPECT_EQ(false, cb.empty());
  EXPECT_EQ(false, cb.full());
  EXPECT_EQ(3, cb.back());
  EXPECT_EQ(3, cb.pop_back());
  EXPECT_EQ(true, cb.empty());
  EXPECT_EQ(false, cb.full());
}

TEST(CircularBufferTest, PushFrontPopBackWithTwoElements) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  cb.push_front(4);
  EXPECT_EQ("4, 3, ", cb.print());
  EXPECT_EQ(false, cb.empty());
  EXPECT_EQ(3, cb.pop_back());
  EXPECT_EQ("4, ", cb.print());
}

TEST(CircularBufferTest, PushFrontPopBackWithThreeElements) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  cb.push_front(4);
  cb.push_front(5);
  EXPECT_EQ("5, 4, 3, ", cb.print());
  EXPECT_EQ(3, cb.pop_back());
  EXPECT_EQ(4, cb.pop_back());
  EXPECT_EQ(5, cb.back());
  EXPECT_EQ(5, cb.pop_back());
  EXPECT_EQ(true, cb.empty());
}

// Mix
TEST(CircularBufferTest, ThreeFrontPushTwoPushBack) {
  circular_buffer<int> cb(10);
  cb.push_front(3);
  cb.push_front(4);
  cb.push_front(5);
  cb.push_back(6);
  cb.push_back(7);
  cb.push_back(8);
  EXPECT_EQ("5, 4, 3, 6, 7, 8, ", cb.print());
  EXPECT_EQ(8, cb.pop_back());
  EXPECT_EQ(5, cb.pop_front());
  EXPECT_EQ(4, cb.pop_front());
  EXPECT_EQ(3, cb.pop_front());
  EXPECT_EQ(6, cb.pop_front());
  EXPECT_EQ(7, cb.pop_front());
  EXPECT_EQ(true, cb.empty());
}

TEST(CircularBufferTest, WithStruct) {
  A one{1, 1, "one"};
  A two{2, 2, "two"};
  A three{3, 3, "three"};
  A four{4, 4, "four"};
  circular_buffer<A> cb(3);
  cb.push_back(one);
  EXPECT_EQ(one, cb.pop_back());
  cb.push_back(two);
  cb.push_back(three);
  cb.push_back(four);
  EXPECT_EQ(four, cb.pop_back());
  EXPECT_EQ(three, cb.pop_back());
  EXPECT_EQ(two, cb.pop_back());
}
