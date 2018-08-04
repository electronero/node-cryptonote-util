#pragma once

#define CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER          0
#define CURRENT_TRANSACTION_VERSION                     2
#define CURRENT_BLOCK_MAJOR_VERSION                     1
#define CURRENT_BLOCK_MINOR_VERSION                     0

#define BLOCK_MAJOR_VERSION_1                           1
#define BLOCK_MAJOR_VERSION_2                           11

// MONEY_SUPPLY - total number coins to be generated
#define MONEY_SUPPLY_ETN                               ((uint64_t)(2100000000000)) // ETN MONEY_SUPPLY
#define MONEY_SUPPLY                                   ((uint64_t)(21000000000000)) // after the ETNX fork
#define TOKENS                                         ((uint64_t)(20000000000000)) // after the 5% ETNX coin burn

#define EMISSION_SPEED_FACTOR_PER_MINUTE                (20)
#define FINAL_SUBSIDY_PER_MINUTE                        ((uint64_t)10000000) // 0 * pow(10, 0)

#define COIN                                            ((uint64_t)100) // pow(10, 12)
#define DEFAULT_FEE                                     ((uint64_t)25) // pow(10, 10)

#define CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW            60
#define CRYPTONOTE_DISPLAY_DECIMAL_POINT                2
