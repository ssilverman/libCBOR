#include "tests.h"

// C++ includes
#include <cmath>
#include <cstdint>

// Other includes
#include <Arduino.h>
#include <ArduinoUnit.h>

// Project includes
#include "CBOR.h"
#include "Streams.h"

namespace cbor = ::qindesign::cbor;

#include "tests/stream.inc"
#include "tests/syntax.inc"
#include "tests/unsigned.inc"
#include "tests/negative.inc"
#include "tests/simple_value.inc"
#include "tests/floating_point.inc"
#include "tests/bytes.inc"
#include "tests/tag.inc"
#include "tests/array.inc"
#include "tests/map.inc"
#include "tests/write.inc"
#include "tests/well_formed.inc"

// ***************************************************************************
//  Main program
// ***************************************************************************

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  delay(4000);
}

void loop() {
  Test::run();
}
