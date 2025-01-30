
#define UNIQUE_NUMBER_T (__TIME__[7] - '0') * 1 + (__TIME__[6] - '0') * 10 + \
                        (__TIME__[4] - '0') * 60 + (__TIME__[3] - '0') * 600 + \
                        (((__TIME__[1] - '0') + (__TIME__[0] - '0') *10) %18 ) * 3600 // cut down to 18h to stay below 65,000
                        
                        
const uint32_t uniqueId = UNIQUE_NUMBER_T + 10; // first 10 reseved for static usecases
                        // max value of 64,800 + 10, uint16_t fits up to 65,535
const uint32_t& getUniqueId() {return (uniqueId);}

const uint8_t getShortId() {
  return uniqueId % (127 - 7) + 8;
}  // wire.h lib only allows 7 bit addreses, with 0-7 being reserved
