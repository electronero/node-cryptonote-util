#pragma once

#define CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER          0
#define CURRENT_TRANSACTION_VERSION                     2
#define CURRENT_BLOCK_MAJOR_VERSION                     1
#define CURRENT_BLOCK_MINOR_VERSION                     0

#define BLOCK_MAJOR_VERSION_1                           1
#define BLOCK_MAJOR_VERSION_2                           8

#define COIN                                            ((uint64_t)100) // pow(10, 12)
#define DEFAULT_FEE                                     ((uint64_t)25) // pow(10, 10)


#define DIFFICULTY_TARGET_V1                            60  // seconds - before first fork
#define DIFFICULTY_WINDOW                               720 // blocks
#define DIFFICULTY_LAG                                  15  // !!!
#define DIFFICULTY_CUT                                  60  // timestamps to cut after sorting
#define DIFFICULTY_BLOCKS_COUNT                         DIFFICULTY_WINDOW + DIFFICULTY_LAG

#define DIFFICULTY_TARGET_V2                            120  // seconds
#define DIFFICULTY_WINDOW_V2                            60
#define DIFFICULTY_BLOCKS_COUNT_V2                      DIFFICULTY_WINDOW_V2
#define CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V2           300*2 // https://github.com/zawy12/difficulty-algorithms/issues/3

#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS       1
#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS_V1   DIFFICULTY_TARGET_V1 * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS
#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS_V2   DIFFICULTY_TARGET_V2 * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS


#define CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW            18
#define CRYPTONOTE_DISPLAY_DECIMAL_POINT                2
