// unsigned.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Unsigned tests
// ***************************************************************************

test(unsigned_zero) {
  uint8_t b[] = { (0 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(unsigned_19) {
  uint8_t b[] = { (0 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 19);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(unsigned_23) {
  uint8_t b[] = { (0 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{1});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 23);
  assertEqual(cbor.getReadSize(), size_t{2});
}

test(unsigned_1_byte) {
  uint8_t b[] = { (0 << 5) + 24, 0x12 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{2});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x12);
  assertEqual(cbor.getReadSize(), size_t{4});
}

test(unsigned_2_bytes) {
  uint8_t b[] = { (0 << 5) + 25, 0x12, 0x34 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{3});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x1234);
  assertEqual(cbor.getReadSize(), size_t{6});
}

test(unsigned_4_bytes) {
  uint8_t b[] = { (0 << 5) + 26, 0x12, 0x34, 0x56, 0x78 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{5});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x12345678UL);
  assertEqual(cbor.getReadSize(), size_t{10});
}

test(unsigned_8_bytes) {
  uint8_t b[] = { (0 << 5) + 27, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  assertEqual(cbor.getReadSize(), size_t{9});
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x123456789abcdef0ULL);
  assertEqual(cbor.getReadSize(), size_t{18});
}
