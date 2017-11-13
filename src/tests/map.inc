// ***************************************************************************
//  Map tests
// ***************************************************************************

test(map_empty) {
  uint8_t b[] = { (5 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::CBORReader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kMap));
  assertTrue(cbor.getLength() == 0);
}

test(map_indefinite_empty) {
  uint8_t b[] = { (5 << 5) + 31, (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::CBORReader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kMap));
  assertTrue(cbor.isIndefiniteLength());
  assertEqual(static_cast<int>(cbor.readDataType(true)), static_cast<int>(cbor::DataType::kBreak));
}

test(map_something) {
  uint8_t b[] = { (5 << 5) + 2, 0x01, 0x02, (1 << 5) | 0x03, (0 << 5) + 24, 24 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::CBORReader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kMap));
  assertTrue(cbor.getLength() == 2);

  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 1);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 2);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -4);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 24);
}

test(map_indefinite) {
  uint8_t b[] = { (5 << 5) + 31, 0x01, 0x02, (1 << 5) | 0x03, (0 << 5) + 24, 24, (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::CBORReader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kMap));
  assertTrue(cbor.isIndefiniteLength());

  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 1);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 2);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -4);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 24);

  assertEqual(static_cast<int>(cbor.readDataType(true)), static_cast<int>(cbor::DataType::kBreak));
}
