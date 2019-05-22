// Copyright (c) 2012-2013 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include "include_base_utils.h"
using namespace epee;

#include "cryptonote_basic_impl.h"
#include "string_tools.h"
#include "serialization/binary_utils.h"
#include "serialization/vector.h"
#include "cryptonote_format_utils.h"
#include "cryptonote_config.h"
#include "misc_language.h"
#include "common/base58.h"
#include "crypto/hash.h"
#include "common/int-util.h"
#define ELECTRONERO_HARDFORK ((uint64_t)(310787)) 
#define MAINNET_HARDFORK_V1_HEIGHT ((uint64_t)(1)) // MAINNET v1 
#define MAINNET_HARDFORK_V7_HEIGHT ((uint64_t)(307003)) // MAINNET v7 hard fork 
#define MAINNET_HARDFORK_V8_HEIGHT ((uint64_t)(307054)) // MAINNET v8 hard fork 
#define MAINNET_HARDFORK_V9_HEIGHT ((uint64_t)(308110)) // MAINNET v9 hard fork 
#define MAINNET_HARDFORK_V10_HEIGHT ((uint64_t)(310790)) // MAINNET v10 hard fork 
#define MAINNET_HARDFORK_V11_HEIGHT ((uint64_t)(310860)) // MAINNET v11 hard fork -- 70 blocks difference from 10
#define MAINNET_HARDFORK_V12_HEIGHT ((uint64_t)(333690)) // MAINNET 72289156 hard fork 
#define MAINNET_HARDFORK_V13_HEIGHT ((uint64_t)(337496)) // MAINNET v13 hard fork  
#define MAINNET_HARDFORK_V14_HEIGHT ((uint64_t)(337816)) // MAINNET v14 hard fork
#define MAINNET_HARDFORK_V15_HEIGHT ((uint64_t)(337838)) // MAINNET v15 hard fork 
#define MAINNET_HARDFORK_V16_HEIGHT ((uint64_t)(500060)) // MAINNET v16 hard fork
#define MAINNET_HARDFORK_V17_HEIGHT ((uint64_t)(570000)) // MAINNET v17 hard fork
#define MAINNET_HARDFORK_V18_HEIGHT ((uint64_t)(659000)) // MAINNET v18 hard fork
#define MAINNET_HARDFORK_V19_HEIGHT ((uint64_t)(739800)) // MAINNET v19 hard fork
namespace cryptonote {

  /************************************************************************/
  /* Cryptonote helper functions                                          */
  /************************************************************************/
  //-----------------------------------------------------------------------------------------------
  size_t get_max_block_size()
  {
    return CRYPTONOTE_MAX_BLOCK_SIZE;
  }
  //-----------------------------------------------------------------------------------------------
  size_t get_max_tx_size()
  {
    return CRYPTONOTE_MAX_TX_SIZE;
  }
  //-----------------------------------------------------------------------------------------------
  bool get_block_reward(size_t median_size, size_t current_block_size, uint64_t already_generated_coins, uint64_t &reward, uint8_t version, uint64_t height) {
    static_assert(DIFFICULTY_TARGET_V2%60==0&&DIFFICULTY_TARGET_V1%60==0,"difficulty targets must be a multiple of 60");
    uint64_t versionHeight = height; // alias used for emissions
    auto version = BLOCK_MAJOR_VERSION_2;
    uint64_t TOKEN_SUPPLY = version < 7 ? MONEY_SUPPLY_ETN : version < 10 ? MONEY_SUPPLY : version < 16 ? TOKENS : ELECTRONERO_TOKENS;
    const int target = (uint64_t)versionHeight < MAINNET_HARDFORK_V7_HEIGHT ? DIFFICULTY_TARGET_V1 : (uint64_t)versionHeight >= MAINNET_HARDFORK_V14_HEIGHT ? DIFFICULTY_TARGET_V1 : DIFFICULTY_TARGET_V2;
    const int target_minutes = target / 60;
    const int emission_speed_factor = EMISSION_SPEED_FACTOR_PER_MINUTE - (target_minutes-1); 
    const int emission_speed_factor_v2 = EMISSION_SPEED_FACTOR_PER_MINUTE + (target_minutes-1);
    const int emission_speed_factor_v3 = EMISSION_SPEED_FACTOR_PER_MINUTE + (target_minutes-2); // v10 
    const int emission_speed_factor_v4 = EMISSION_SPEED_FACTOR_PER_MINUTE - (target_minutes-1); // v16 - 20 emf 
    const int emission_speed_factor_v5 = EMISSION_SPEED_FACTOR_PER_MINUTE + (target_minutes); //  21 emf 
    const int emission_speed_factor_v6 = EMISSION_SPEED_FACTOR_PER_MINUTE + (target_minutes+1); // v17 - 22 emf 
    const int emission_speed_factor_v7 = EMISSION_SPEED_FACTOR_PER_MINUTE + (target_minutes+9); // v18 - 30 emf 
    const int emission_speed_factor_v8 = EMISSION_SPEED_FACTOR_PER_MINUTE + (target_minutes+6); // v19 - 27 emf 
    uint64_t emission_speed = (uint64_t)versionHeight < MAINNET_HARDFORK_V7_HEIGHT ? emission_speed_factor : (uint64_t)versionHeight < MAINNET_HARDFORK_V10_HEIGHT ? emission_speed_factor_v2 : (uint64_t)versionHeight < MAINNET_HARDFORK_V16_HEIGHT ? emission_speed_factor_v3 : (uint64_t)versionHeight < MAINNET_HARDFORK_V17_HEIGHT ? emission_speed_factor_v4 : (uint64_t)versionHeight < MAINNET_HARDFORK_V18_HEIGHT ? emission_speed_factor_v6 : (uint64_t)versionHeight < MAINNET_HARDFORK_V19_HEIGHT ? emission_speed_factor_v7 : emission_speed_factor_v8;
    uint64_t base_reward = (TOKEN_SUPPLY - already_generated_coins) >> emission_speed_factor;
    
    
    uint64_t round_factor = 10; // 1 * pow(10, 1)
    if (version >= 7)
    {
      if (height < (PEAK_COIN_EMISSION_HEIGHT + COIN_EMISSION_HEIGHT_INTERVAL)) {
        uint64_t interval_num = height / COIN_EMISSION_HEIGHT_INTERVAL;
        double money_supply_pct = 0.1888 + interval_num*(0.023 + interval_num*0.0032);
        base_reward = ((uint64_t)(TOKEN_SUPPLY * money_supply_pct)) >> emission_speed;
      }
      else{
        base_reward = ((uint64_t)(TOKEN_SUPPLY - already_generated_coins)) >> emission_speed;
      }
    }
    else
    {
      // do something
      base_reward = (TOKEN_SUPPLY - already_generated_coins) >> emission_speed;
    }
    
   // maybe work on better final subsidy later
   const uint64_t FINAL_SUBSIDY_ACTIVATOR = 66600U;
    if (base_reward < FINAL_SUBSIDY_ACTIVATOR){
     if (already_generated_coins >= TOKEN_SUPPLY){
       base_reward = FINAL_SUBSIDY_PER_MINUTE;
     }
    }
    
    // rounding (floor) base reward
    if (version > 7)
    {
    base_reward = base_reward / round_factor * round_factor;
    }
    if (version < 2) 
    {
     base_reward = (MONEY_SUPPLY_ETN - already_generated_coins) >> emission_speed_factor;
    }
    uint64_t full_reward_zone = get_min_block_size(version);

    //make it soft
    if (median_size < full_reward_zone) {
      median_size = full_reward_zone;
    }

    if (current_block_size <= median_size) {
      reward = base_reward;
      return true;
    }

    if(current_block_size > 2 * median_size) {
      MERROR("Block cumulative size is too big: " << current_block_size << ", expected less than " << 2 * median_size);
      return false;
    }

    assert(median_size < std::numeric_limits<uint32_t>::max());
    assert(current_block_size < std::numeric_limits<uint32_t>::max());

    uint64_t product_hi;
    // BUGFIX: 32-bit saturation bug (e.g. ARM7), the result was being
    // treated as 32-bit by default.
    uint64_t multiplicand = 2 * median_size - current_block_size;
    multiplicand *= current_block_size;
    uint64_t product_lo = mul128(base_reward, multiplicand, &product_hi);

    uint64_t reward_hi;
    uint64_t reward_lo;
    div128_32(product_hi, product_lo, static_cast<uint32_t>(median_size), &reward_hi, &reward_lo);
    div128_32(reward_hi, reward_lo, static_cast<uint32_t>(median_size), &reward_hi, &reward_lo);
    assert(0 == reward_hi);
    assert(reward_lo < base_reward);

    reward = reward_lo;
    return true;
  }
  //------------------------------------------------------------------------------------
  uint8_t get_account_address_checksum(const public_address_outer_blob& bl)
  {
    const unsigned char* pbuf = reinterpret_cast<const unsigned char*>(&bl);
    uint8_t summ = 0;
    for(size_t i = 0; i!= sizeof(public_address_outer_blob)-1; i++)
      summ += pbuf[i];

    return summ;
  }
  //-----------------------------------------------------------------------
  std::string get_account_address_as_str(const account_public_address& adr)
  {
    return tools::base58::encode_addr(CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX, t_serializable_object_to_blob(adr));
  }
  //-----------------------------------------------------------------------
  bool is_coinbase(const transaction& tx)
  {
    if(tx.vin.size() != 1)
      return false;

    if(tx.vin[0].type() != typeid(txin_gen))
      return false;

    return true;
  }
  //-----------------------------------------------------------------------
  bool get_account_address_from_str(account_public_address& adr, const std::string& str)
  {
    if (2 * sizeof(public_address_outer_blob) != str.size())
    {
      blobdata data;
      uint64_t prefix;
      if (!tools::base58::decode_addr(str, prefix, data))
      {
        LOG_PRINT_L1("Invalid address format");
        return false;
      }

      if (CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX != prefix)
      {
        LOG_PRINT_L1("Wrong address prefix: " << prefix << ", expected " << CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX);
        return false;
      }

      if (!::serialization::parse_binary(data, adr))
      {
        LOG_PRINT_L1("Account public address keys can't be parsed");
        return false;
      }

      if (!crypto::check_key(adr.m_spend_public_key) || !crypto::check_key(adr.m_view_public_key))
      {
        LOG_PRINT_L1("Failed to validate address keys");
        return false;
      }
    }
    else
    {
      // Old address format
      std::string buff;
      if(!string_tools::parse_hexstr_to_binbuff(str, buff))
        return false;

      if(buff.size()!=sizeof(public_address_outer_blob))
      {
        LOG_PRINT_L1("Wrong public address size: " << buff.size() << ", expected size: " << sizeof(public_address_outer_blob));
        return false;
      }

      public_address_outer_blob blob = *reinterpret_cast<const public_address_outer_blob*>(buff.data());


      if(blob.m_ver > CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER)
      {
        LOG_PRINT_L1("Unknown version of public address: " << blob.m_ver << ", expected " << CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER);
        return false;
      }

      if(blob.check_sum != get_account_address_checksum(blob))
      {
        LOG_PRINT_L1("Wrong public address checksum");
        return false;
      }

      //we success
      adr = blob.m_address;
    }

    return true;
  }

  bool operator ==(const cryptonote::transaction& a, const cryptonote::transaction& b) {
    return cryptonote::get_transaction_hash(a) == cryptonote::get_transaction_hash(b);
  }

  bool operator ==(const cryptonote::block& a, const cryptonote::block& b) {
    return cryptonote::get_block_hash(a) == cryptonote::get_block_hash(b);
  }
}

//--------------------------------------------------------------------------------
bool parse_hash256(const std::string str_hash, crypto::hash& hash)
{
  std::string buf;
  bool res = epee::string_tools::parse_hexstr_to_binbuff(str_hash, buf);
  if (!res || buf.size() != sizeof(crypto::hash))
  {
    std::cout << "invalid hash format: <" << str_hash << '>' << std::endl;
    return false;
  }
  else
  {
    buf.copy(reinterpret_cast<char *>(&hash), sizeof(crypto::hash));
    return true;
  }
}
