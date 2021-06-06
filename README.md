# Simple template based circular_buffer implementation

Supports functions:

- empty()
- full()
- front()
- back()
- push_front()
- push_back()
- pop_front()
- pop_back()
- print()

# Illustrating with a test

```
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
```

# Circular buffer for structures

```
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
```
