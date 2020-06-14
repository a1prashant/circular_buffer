#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

template <typename T> class circular_buffer {
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using const_reference = const T &;

  using hand_t = std::size_t;

public:
  explicit circular_buffer(std::size_t size) : _capacity(size), _arr(size) {}
  void push_back(const T &i) {
    if (_full) {
      throw "circular_buffer FULL";
    }

    _arr[_tail] = i;
    clockwise(_tail);
    if (_tail == _head) {
      _full = true;
    }
  }
  void push_front(const T &i) {
    if (_full) {
      throw "circular_buffer FULL";
    }

    anticlockwise(_head);
    _arr[_head] = i;
    if (_tail == _head) {
      _full = true;
    }
  }
  T pop_front() {
    auto &t = front();
    clockwise(_head);
    _full = false;
    return t;
  }
  T pop_back() {
    if (empty()) {
      throw "circular_buffer EMPTY";
    }

    anticlockwise(_tail);
    _full = false;
    return _arr[_tail];
  }
  reference front() {
    if (empty()) {
      throw "circular_buffer EMPTY";
    }
    return _arr[_head];
  }
  reference back() {
    if (empty()) {
      throw "circular_buffer EMPTY";
    }
    auto t = _tail;
    anticlockwise(t);
    return _arr[t];
  }
  const_reference front() const {
    if (empty()) {
      throw "circular_buffer EMPTY";
    }
    return _arr[_head];
  }
  const_reference back() const {
    if (empty()) {
      throw "circular_buffer EMPTY";
    }
    auto t = _tail;
    anticlockwise(t);
    return _arr[t];
  }
  std::string print() {
    std::stringstream ss;
    hand_t t = _head;
    for (size_t i = 0; i < size(); ++i) {
      ss << _arr[t] << ", ";
      clockwise(t);
    }
    return ss.str();
  }
  bool empty() const { return !_full && _head == _tail; }
  bool full() const { return _full; }

private:
  hand_t clockwise(hand_t &hand) const {
    if (hand == _capacity - 1) {
      hand = 0;
    } else {
      hand++;
    }
    return hand;
  }
  hand_t anticlockwise(hand_t &hand) const {
    if (hand == 0) {
      hand = _capacity - 1;
    } else {
      hand--;
    }
    return hand;
  }
  std::size_t size() {
    if (_full) {
      return _capacity;
    }
    if (_head == _tail) {
      return 0;
    }
    if (_head < _tail) {
      return _tail - _head;
    }
    return (_capacity - 1 - _head) + _tail + 1;
  }
  hand_t _head = 0;
  hand_t _tail = 0;
  bool _full = false;
  std::size_t _capacity;
  std::vector<T> _arr;
};

#endif // CIRCULAR_BUFFER_H