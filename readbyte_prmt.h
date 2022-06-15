#pragma once
#include <stdint.h>
static inline uint8_t ReadByte_f4e(uint8_t control, uint64_t value, uint8_t pos) {
uint8_t byte = 0;
  if(control == 0) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  if(control == 1) {
     switch(pos) {
       case 0: byte = 1; break;
       case 1: byte = 2; break;
       case 2: byte = 3; break;
       case 3: byte = 4; break;
     }
   }
  if(control == 2) {
     switch(pos) {
       case 0: byte = 2; break;
       case 1: byte = 3; break;
       case 2: byte = 4; break;
       case 3: byte = 5; break;
     }
   }
  if(control == 3) {
     switch(pos) {
       case 0: byte = 3; break;
       case 1: byte = 4; break;
       case 2: byte = 5; break;
       case 3: byte = 6; break;
     }
   }
  return (value >> (byte * 8)) & 0xff;
}
static inline uint8_t ReadByte_b4e(uint8_t control, uint64_t value, uint8_t pos) {
uint8_t byte = 0;
  if(control == 0) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 7; break;
       case 2: byte = 6; break;
       case 3: byte = 5; break;
     }
   }
  if(control == 1) {
     switch(pos) {
       case 0: byte = 1; break;
       case 1: byte = 0; break;
       case 2: byte = 7; break;
       case 3: byte = 6; break;
     }
   }
  if(control == 2) {
     switch(pos) {
       case 0: byte = 2; break;
       case 1: byte = 1; break;
       case 2: byte = 0; break;
       case 3: byte = 7; break;
     }
   }
  if(control == 3) {
     switch(pos) {
       case 0: byte = 3; break;
       case 1: byte = 2; break;
       case 2: byte = 1; break;
       case 3: byte = 0; break;
     }
   }
  return (value >> (byte * 8)) & 0xff;
}
static inline uint8_t ReadByte_rc8(uint8_t control, uint64_t value, uint8_t pos) {
uint8_t byte = 0;
  if(control == 0) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 0; break;
       case 2: byte = 0; break;
       case 3: byte = 0; break;
     }
   }
  if(control == 1) {
     switch(pos) {
       case 0: byte = 1; break;
       case 1: byte = 1; break;
       case 2: byte = 1; break;
       case 3: byte = 1; break;
     }
   }
  if(control == 2) {
     switch(pos) {
       case 0: byte = 2; break;
       case 1: byte = 2; break;
       case 2: byte = 2; break;
       case 3: byte = 2; break;
     }
   }
  if(control == 3) {
     switch(pos) {
       case 0: byte = 3; break;
       case 1: byte = 3; break;
       case 2: byte = 3; break;
       case 3: byte = 3; break;
     }
   }
  return (value >> (byte * 8)) & 0xff;
}
static inline uint8_t ReadByte_ecl(uint8_t control, uint64_t value, uint8_t pos) {
uint8_t byte = 0;
  if(control == 0) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  if(control == 1) {
     switch(pos) {
       case 0: byte = 1; break;
       case 1: byte = 1; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  if(control == 2) {
     switch(pos) {
       case 0: byte = 2; break;
       case 1: byte = 2; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  if(control == 3) {
     switch(pos) {
       case 0: byte = 3; break;
       case 1: byte = 3; break;
       case 2: byte = 3; break;
       case 3: byte = 3; break;
     }
   }
  return (value >> (byte * 8)) & 0xff;
}
static inline uint8_t ReadByte_ecr(uint8_t control, uint64_t value, uint8_t pos) {
uint8_t byte = 0;
  if(control == 0) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 0; break;
       case 2: byte = 0; break;
       case 3: byte = 0; break;
     }
   }
  if(control == 1) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 1; break;
       case 3: byte = 1; break;
     }
   }
  if(control == 2) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 2; break;
       case 3: byte = 2; break;
     }
   }
  if(control == 3) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  return (value >> (byte * 8)) & 0xff;
}
static inline uint8_t ReadByte_rc16(uint8_t control, uint64_t value, uint8_t pos) {
uint8_t byte = 0;
  if(control == 0) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 0; break;
       case 3: byte = 1; break;
     }
   }
  if(control == 1) {
     switch(pos) {
       case 0: byte = 2; break;
       case 1: byte = 3; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  if(control == 2) {
     switch(pos) {
       case 0: byte = 0; break;
       case 1: byte = 1; break;
       case 2: byte = 0; break;
       case 3: byte = 1; break;
     }
   }
  if(control == 3) {
     switch(pos) {
       case 0: byte = 2; break;
       case 1: byte = 3; break;
       case 2: byte = 2; break;
       case 3: byte = 3; break;
     }
   }
  return (value >> (byte * 8)) & 0xff;
}
