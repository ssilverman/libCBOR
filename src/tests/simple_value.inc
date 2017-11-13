// ***************************************************************************
//  Simple-value tests
// ***************************************************************************

test(boolean_false) {
  uint8_t b[] = { (7 << 5) + 20 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBoolean));
  assertEqual(cbor.getBoolean(), false);
}

test(boolean_true) {
  uint8_t b[] = { (7 << 5) + 21 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBoolean));
  assertEqual(cbor.getBoolean(), true);
}

test(null) {
  uint8_t b[] = { (7 << 5) + 22 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNull));
}

test(undefined) {
  uint8_t b[] = { (7 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUndefined));
}

test(simple_value_break) {
  uint8_t b[] = { (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertFalse(cbor.isWellFormed());  // TODO: Can't have just a break?
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBreak));
}

test(simple_value_zero) {
  uint8_t b[] = { (7 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 0);
}

test(simple_value_19) {
  uint8_t b[] = { (7 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 19);
}

test(simple_value_32_1_byte) {
  uint8_t b[] = { (7 << 5) + 24, 32 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 32);
}

test(simple_value_255_1_byte) {
  uint8_t b[] = { (7 << 5) + 24, 255 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kSimpleValue));
  assertEqual(cbor.getSimpleValue(), 255);
}
