// ***************************************************************************
//  Unsigned tests
// ***************************************************************************

test(unsigned_zero) {
  uint8_t b[] = { (0 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0);
}

test(unsigned_19) {
  uint8_t b[] = { (0 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 19);
}

test(unsigned_23) {
  uint8_t b[] = { (0 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 23);
}

test(unsigned_1_byte) {
  uint8_t b[] = { (0 << 5) + 24, 0x12 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x12);
}

test(unsigned_2_bytes) {
  uint8_t b[] = { (0 << 5) + 25, 0x12, 0x34 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x1234);
}

test(unsigned_4_bytes) {
  uint8_t b[] = { (0 << 5) + 26, 0x12, 0x34, 0x56, 0x78 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x12345678L);
}

test(unsigned_8_bytes) {
  uint8_t b[] = { (0 << 5) + 27, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 0x123456789abcdef0LL);
}
