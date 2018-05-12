#pragma once

#define CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER          0
#define CURRENT_TRANSACTION_VERSION                     2
#define CURRENT_BLOCK_MAJOR_VERSION                     1
#define CURRENT_BLOCK_MINOR_VERSION                     0

#define BLOCK_MAJOR_VERSION_1                           1
#define BLOCK_MAJOR_VERSION_2                           8
#define PEAK_EMISSIONS                                  0

// MONEY_SUPPLY - total number coins to be generated
#define MONEY_SUPPLY_ETN                               ((uint64_t)(2100000000000)) // ETN MONEY_SUPPLY
#define MONEY_SUPPLY                                   ((uint64_t)(21000000000000)) // after the ETNX fork

#define EMISSION_SPEED_FACTOR_PER_MINUTE                (20)
#define FINAL_SUBSIDY_PER_MINUTE                        ((uint64_t)0) // 0 * pow(10, 0)

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

// coin emission change interval/speed configs
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE       240 * 1024    // 240kB, used for emissions
#define BLOCK_SIZE_GROWTH_FAVORED_ZONE                  ((uint64_t) (CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE * 4))
#define DIFFICULTY_TARGET                               DIFFICULTY_TARGET_V2  // just alias, used for emissions
#define COIN_EMISSION_MONTH_INTERVAL                    6  // months to change emission speed
#define COIN_EMISSION_HEIGHT_INTERVAL                   ((uint64_t) (COIN_EMISSION_MONTH_INTERVAL * (30.4375 * 24 * 3600) / DIFFICULTY_TARGET)) // calculated to # of heights to change emission speed
#define PEAK_COIN_EMISSION_YEAR                         4
#define PEAK_COIN_EMISSION_HEIGHT                       ((uint64_t) (((12 * 30.4375 * 24 * 3600)/DIFFICULTY_TARGET) * PEAK_COIN_EMISSION_YEAR)) // = (# of heights emmitted per year) * PEAK_COIN_EMISSION_YEAR

#define CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW            60
#define CRYPTONOTE_DISPLAY_DECIMAL_POINT                2
