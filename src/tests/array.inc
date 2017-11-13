// array.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Array tests
// ***************************************************************************

test(array_empty) {
  uint8_t b[] = { (4 << 5) + 0 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kArray));
  assertTrue(cbor.getLength() == 0);
}

test(array_indefinite_empty) {
  uint8_t b[] = { (4 << 5) + 31, (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kArray));
  assertTrue(cbor.isIndefiniteLength());
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBreak));
}

test(array_something) {
  uint8_t b[] = { (4 << 5) + 4, 0x01, 0x02, (1 << 5) | 0x03, (0 << 5) + 24, 24 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kArray));
  assertTrue(cbor.getLength() == 4);

  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 1);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 2);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -4);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 24);
}

test(array_indefinite) {
  uint8_t b[] = { (4 << 5) + 31, 0x01, 0x02, (1 << 5) | 0x03, (7 << 5) + 31 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kArray));
  assertTrue(cbor.isIndefiniteLength());

  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 1);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kUnsignedInt));
  assertTrue(cbor.getUnsignedInt() == 2);
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kNegativeInt));
  assertTrue(cbor.getInt() == -4);

  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kBreak));
}
