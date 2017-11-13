#include "Streams.h"

// Other includes
#include <EEPROM.h>

namespace qindesign {
namespace cbor {

int BytesStream::available() {
  if (index_ >= length_) {
    return 0;
  }
  if (waiting_ > 0) {
    waiting_--;
    return 0;
  }
  return length_ - index_;
}

int BytesStream::read() {
  if (index_ >= length_) {
    return -1;
  }
  if (waiting_ > 0) {
    waiting_--;
    return -1;
  }
  waiting_ = waitStates_;
  return b_[index_++];
}

int BytesStream::peek() {
  if (index_ >= length_) {
    return -1;
  }
  if (waiting_ > 0) {
    waiting_--;
    return -1;
  }
  return b_[index_];
}

size_t BytesPrint::write(uint8_t b) {
  if (index_ < size_) {
    buf_[index_++] = b;
    return 1;
  }
  setWriteError();
  return 0;
}

int EEPROMStream::available() {
  if (static_cast<unsigned int>(address_) >= size_) {
    return 0;
  }
  return size_ - address_;
}

int EEPROMStream::read() {
  if (static_cast<unsigned int>(address_) >= size_) {
    return -1;
  }
  return EEPROM.read(address_++);
}

int EEPROMStream::peek() {
  if (static_cast<unsigned int>(address_) >= size_) {
    return -1;
  }
  return EEPROM.read(address_);
}

size_t EEPROMPrint::write(uint8_t b) {
  if (static_cast<unsigned int>(address_) < size_) {
#ifndef ESP8266
    EEPROM.update(address_++, b);
#else
    if (EEPROM.read(address_) != b) {
      EEPROM.write(address_, b);
    }
    address_++;
#endif
    return 1;
  }
  setWriteError();
  return 0;
}

void EEPROMPrint::flush() {
}

}  // namespace cbor
}  // namespace qindesign
