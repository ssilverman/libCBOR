// ***************************************************************************
//  Negative tests
// ***************************************************************************

test(negative_zero) {
  uint8_t b[] = { (1 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -1);
}

test(negative_19) {
  uint8_t b[] = { (1 << 5) + 19 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -20);
}

test(negative_23) {
  uint8_t b[] = { (1 << 5) + 23 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -24);
}

test(negative_1_byte) {
  uint8_t b[] = { (1 << 5) + 24, 0x12 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x13);
}

test(negative_2_bytes) {
  uint8_t b[] = { (1 << 5) + 25, 0x12, 0x34 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x1235);
}

test(negative_4_bytes) {
  uint8_t b[] = { (1 << 5) + 26, 0x12, 0x34, 0x56, 0x78 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x12345679L);
}

test(negative_8_bytes) {
  uint8_t b[] = { (1 << 5) + 27, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -0x123456789abcdef1LL);
}
