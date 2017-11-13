// floating_point.inc is part of libCBOR.
// (c) 2017 Shawn Silverman

// ***************************************************************************
//  Floating-point tests
// ***************************************************************************

test(half_zero) {
  uint8_t b[] = { (7 << 5) + 25, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 0.0f);
  assertFalse(std::signbit(cbor.getFloat()));
}

test(half_negative_zero) {
  uint8_t b[] = { (7 << 5) + 25, 0x80, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 0.0f);
  assertTrue(std::signbit(cbor.getFloat()));
}

test(half_one) {
  uint8_t b[] = { (7 << 5) + 25, 0x3c, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 1.0f);
}

test(half_1p5) {
  uint8_t b[] = { (7 << 5) + 25, 0x3e, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 1.5f);
}

test(half_65504) {
  uint8_t b[] = { (7 << 5) + 25, 0x7b, 0xff };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 65504.0f);
}

test(half_small) {
  uint8_t b[] = { (7 << 5) + 25, 0x00, 0x01 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 5.960464477539063e-8f);
}

test(half_medium_small) {
  uint8_t b[] = { (7 << 5) + 25, 0x04, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 0.00006103515625f);
}

test(half_negative_4) {
  uint8_t b[] = { (7 << 5) + 25, 0xc4, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), -4.0f);
}

test(half_infinity) {
  uint8_t b[] = { (7 << 5) + 25, 0x7c, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), INFINITY);
}

test(half_negative_infinity) {
  uint8_t b[] = { (7 << 5) + 25, 0xfc, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), -INFINITY);
}

test(half_nan) {
  uint8_t b[] = { (7 << 5) + 25, 0x7e, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertTrue(std::isnan(cbor.getFloat()));
}

test(float_100000) {
  uint8_t b[] = { (7 << 5) + 26, 0x47, 0xc3, 0x50, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 100000.0f);
}

test(float_large) {
  uint8_t b[] = { (7 << 5) + 26, 0x7f, 0x7f, 0xff, 0xff };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), 3.4028234663852886e+38f);
}

test(float_infinity) {
  uint8_t b[] = { (7 << 5) + 26, 0x7f, 0x80, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), INFINITY);
}

test(float_negative_infinity) {
  uint8_t b[] = { (7 << 5) + 26, 0xff, 0x80, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertEqual(cbor.getFloat(), -INFINITY);
}

test(float_nan) {
  uint8_t b[] = { (7 << 5) + 26, 0x7f, 0xc0, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kFloat));
  assertTrue(std::isnan(cbor.getFloat()));
}

test(double_1p1) {
  uint8_t b[] = { (7 << 5) + 27, 0x3f, 0xf1, 0x99, 0x99, 0x99, 0x99, 0x99, 0x9a };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kDouble));
  assertEqual(cbor.getDouble(), 1.1);
}

test(double_negative_4p1) {
  uint8_t b[] = { (7 << 5) + 27, 0xc0, 0x10, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kDouble));
  assertEqual(cbor.getDouble(), -4.1);
}

test(double_large) {
  uint8_t b[] = { (7 << 5) + 27, 0x7e, 0x37, 0xe4, 0x3c, 0x88, 0x00, 0x75, 0x9c };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kDouble));
  assertEqual(cbor.getDouble(), 1.0e+300);
}

test(double_infinity) {
  uint8_t b[] = { (7 << 5) + 27, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kDouble));
  assertEqual(cbor.getDouble(), INFINITY);
}

test(double_negative_infinity) {
  uint8_t b[] = { (7 << 5) + 27, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kDouble));
  assertEqual(cbor.getDouble(), -INFINITY);
}

test(double_nan) {
  uint8_t b[] = { (7 << 5) + 27, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  cbor::BytesStream bs{b, sizeof(b)};
  cbor::Reader cbor{bs};
  assertTrue(cbor.isWellFormed());
  bs.reset();
  assertEqual(static_cast<int>(cbor.readDataType()), static_cast<int>(cbor::DataType::kDouble));
  assertTrue(std::isnan(cbor.getDouble()));
}
