// negative.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Negative tests
// ***************************************************************************

test(negative_zero) {
  uint8_t b[] = { (1 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -1);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(negative_19) {
  uint8_t b[] = { (1 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -20);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(negative_23) {
  uint8_t b[] = { (1 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -24);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(negative_1_byte) {
  uint8_t b[] = { (1 << 5) + 24, 0x12 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{2});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x13);
  assertEqual(cbor.getReadSize(), size_t{4});
}

test(negative_2_bytes) {
  uint8_t b[] = { (1 << 5) + 25, 0x12, 0x34 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{3});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x1235);
  assertEqual(cbor.getReadSize(), size_t{6});
}

test(negative_4_bytes) {
  uint8_t b[] = { (1 << 5) + 26, 0x12, 0x34, 0x56, 0x78 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{5});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x12345679L);
  assertEqual(cbor.getReadSize(), size_t{10});
}

test(negative_8_bytes) {
  uint8_t b[] = { (1 << 5) + 27, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{9});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x123456789abcdef1LL);
  assertEqual(cbor.getReadSize(), size_t{18});
}
