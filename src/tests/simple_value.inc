// simple_value.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Simple-value tests
// ***************************************************************************

test(boolean_false) {
  uint8_t b[] = { (7 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBoolean));
  assertEqual(cbor.getBoolean(), false);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(boolean_true) {
  uint8_t b[] = { (7 << 5) + 21 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBoolean));
  assertEqual(cbor.getBoolean(), true);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(null) {
  uint8_t b[] = { (7 << 5) + 22 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNull));
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(undefined) {
  uint8_t b[] = { (7 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUndefined));
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(simple_value_break) {
  uint8_t b[] = { (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertFalse(cbor.isWellFormed());  // TODO: Can't have just a break?
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBreak));
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(simple_value_zero) {
  uint8_t b[] = { (7 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 0);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(simple_value_19) {
  uint8_t b[] = { (7 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 19);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(simple_value_32_1_byte) {
  uint8_t b[] = { (7 << 5) + 24, 32 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{2});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 32);
  assertEqual(cbor.getReadSize(), size_t{4});
}

test(simple_value_255_1_byte) {
  uint8_t b[] = { (7 << 5) + 24, 255 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{2});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 255);
  assertEqual(cbor.getReadSize(), size_t{4});
}
