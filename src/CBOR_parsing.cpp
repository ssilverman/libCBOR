// CBOR_parsing.cpp is part of libCBOR.
// (c) 2017 Shawn Silverman

#include "CBOR_parsing.h"

// C++ includes
#include <cmath>

// Other includes
#include <Arduino.h>

namespace qindesign {
namespace cbor {

// ***************************************************************************
//  Expectation functions.
// ***************************************************************************

bool expectValue(Reader r, DataType dt, uint64_t val) {
  if (r.readDataType() != dt) {
    return false;
  }
  switch (dt) {
    case DataType::kUnsignedInt:
      return r.getUnsignedInt() == val;
    case DataType::kNegativeInt:
      return r.getInt() == static_cast<int64_t>(val);
    case DataType::kSimpleValue:
      return r.getSimpleValue() == val;
    case DataType::kTag:
      return r.getTag() == val;
    case DataType::kBytes:
    case DataType::kText:
    case DataType::kArray:
    case DataType::kMap:
      return r.getLength() == val;
    default:
      return false;
  }
}

bool expectFloatValue(Reader r, float f) {
  if (r.readDataType() != DataType::kFloat) {
    return false;
  }
  float v = r.getFloat();
  if (std::isnan(f)) {
    return std::isnan(v);
  }
  if (f == 0.0f) {
    return (v == 0) && (std::signbit(v) == std::signbit(f));
  }
  return v == f;
}

bool expectDoubleValue(Reader r, double d) {
  if (r.readDataType() != DataType::kDouble) {
    return false;
  }
  float v = r.getDouble();
  if (std::isnan(d)) {
    return std::isnan(v);
  }
  if (d == 0.0) {
    return (v == 0) && (std::signbit(v) == std::signbit(d));
  }
  return v == d;
}

bool expectTrue(Reader r) {
  return (r.readDataType() == DataType::kBoolean) && r.getBoolean();
}

bool expectFalse(Reader r) {
  return (r.readDataType() == DataType::kBoolean) && !r.getBoolean();
}

bool expectUnsignedInt(Reader r, uint64_t *u) {
  if (r.readDataType() != DataType::kUnsignedInt) {
    return false;
  }
  *u = r.getUnsignedInt();
  return true;
}

bool expectInt(Reader r, int64_t *i) {
  if (r.readDataType() != DataType::kNegativeInt) {
    return false;
  }
  *i = r.getInt();
  return true;
}

bool expectBytes(Reader r, uint64_t *length) {
  if (r.readDataType() != DataType::kBytes || r.isIndefiniteLength()) {
    return false;
  }
  *length = r.getLength();
  return true;
}

bool expectIndefiniteBytes(Reader r) {
  return (r.readDataType() == DataType::kBytes) && r.isIndefiniteLength();
}

bool expectText(Reader r, uint64_t *length) {
  if (r.readDataType() != DataType::kText || r.isIndefiniteLength()) {
    return false;
  }
  *length = r.getLength();
  return true;
}

bool expectIndefiniteText(Reader r) {
  return (r.readDataType() == DataType::kText) && r.isIndefiniteLength();
}

bool expectArray(Reader r, uint64_t *length) {
  if (r.readDataType() != DataType::kArray || r.isIndefiniteLength()) {
    return false;
  }
  *length = r.getLength();
  return true;
}

bool expectIndefiniteArray(Reader r) {
  return (r.readDataType() == DataType::kArray) && r.isIndefiniteLength();
}

bool expectMap(Reader r, uint64_t *length) {
  if (r.readDataType() != DataType::kMap || r.isIndefiniteLength()) {
    return false;
  }
  *length = r.getLength();
  return true;
}

bool expectIndefiniteMap(Reader r) {
  return (r.readDataType() == DataType::kMap) && r.isIndefiniteLength();
}

bool expectBoolean(Reader r, bool *b) {
  if (r.readDataType() != DataType::kBoolean) {
    return false;
  }
  *b = r.getBoolean();
  return true;
}

bool expectFloat(Reader r, float *f) {
  if (r.readDataType() != DataType::kFloat) {
    return false;
  }
  *f = r.getFloat();
  return true;
}

bool expectDouble(Reader r, double *d) {
  if (r.readDataType() != DataType::kDouble) {
    return false;
  }
  *d = r.getDouble();
  return true;
}

bool expectNull(Reader r) {
  return (r.readDataType() == DataType::kNull);
}

bool expectUndefined(Reader r) {
  return (r.readDataType() == DataType::kUndefined);
}

bool expectSimpleValue(Reader r, uint8_t *v) {
  if (r.readDataType() != DataType::kSimpleValue) {
    return false;
  }
  *v = r.getSimpleValue();
  return true;
}

bool expectTag(Reader r, uint64_t *v) {
  if (r.readDataType() != DataType::kTag) {
    return false;
  }
  *v = r.getTag();
  return true;
}

// ***************************************************************************
//  Read functions.
// ***************************************************************************

unsigned int readFully(Reader r, uint8_t *b, size_t len) {
  size_t count = 0;
  while (true) {
    int read = r.readBytes(b, len);
    if (read < 0) {
      return count;
    }
    count += static_cast<size_t>(read);
    len -= static_cast<size_t>(read);
  }
}

DataType readUntilData(Reader r) {
  while (true) {
    DataType dt = r.readDataType();
    if (dt == DataType::kEOS) {
      yield();
      continue;
    }
    return dt;
  }
}

}  // namespace cbor
}  // namespace qindesign
