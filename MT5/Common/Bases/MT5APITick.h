//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2015, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Feeder constants                                                 |
//+------------------------------------------------------------------+
enum EnMTFeederConstants
  {
   MT_FEEDER_DEALER =-1,                              // feeder index for dealer ticks 
   MT_FEEDER_OFFSET =64                               // index offset for datafeed ticks
  };
//+------------------------------------------------------------------+
//| Tick full description structure                                  |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTTick
  {
   wchar_t           symbol[32];                      // symbol
   wchar_t           bank[32];                        // tick source ticker
   INT64             datetime;                        // datetime
   //--- basic price data
   double            bid;                             // bid price
   double            ask;                             // ask price
   double            last;                            // last price
   UINT64            volume;                          // last trade volume
   UINT              reserved[32];                    // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Tick short description structure                                 |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTTickShort
  {
   INT64             datetime;                        // last update datetime
   double            bid;                             // bid price
   double            ask;                             // ask price
   double            last;                            // last price
   UINT64            volume;                          // last trade volume
   UINT              reserved[32];                    // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Tick statistic description structure                             |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTTickStat
  {
   wchar_t           symbol[32];                   // symbol
   INT64             datetime;                     // last update datetime
   //--- bid
   double            bid_high;                     // bid high
   double            bid_low;                      // bid low
   //--- ask
   double            ask_high;                     // ask high
   double            ask_low;                      // ask low
   //--- last
   double            last_high;                    // last high
   double            last_low;                     // last low
   //--- trade volume
   UINT64            vol_high;                     // last high
   UINT64            vol_low;                      // last low
   //--- trade session  statistics
   UINT64            trade_deals;                  // total deals in current session
   UINT64            trade_volume;                 // total deals volume in current session
   UINT64            trade_turnover;               // total turnover in current session
   UINT64            trade_interest;               // open interest in current session
   UINT64            trade_buy_orders;             // total buy orders
   UINT64            trade_buy_volume;             // total buy orders volume
   UINT64            trade_sell_orders;            // total sell orders
   UINT64            trade_sell_volume;            // total sell orders volume
   int               trade_reserved[32];           // reserved
   //--- price session  statistics
   double            price_open;                   // session open price
   double            price_close;                  // session close price
   double            price_aw;                     // average weighted price
   double            price_change;                 // price change percentage
   double            price_volatility;             // price volatility
   double            price_theoretical;            // theoretical price
   int               price_reserved[28];           // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Tick events notification interface                               |
//+------------------------------------------------------------------+
class IMTTickSink
  {
public:
   //--- tick events
   virtual void      OnTick(LPCWSTR /*symbol*/,const MTTickShort& /*tick*/)       { }
   virtual void      OnTickStat(const MTTickStat& /*tick*/)                       { }
   //--- tick hooks
   virtual MTAPIRES  HookTick(const int /*feeder*/,MTTick& /*tick*/)              { return(MT_RET_OK); }
   virtual MTAPIRES  HookTickStat(const int /*feeder*/,MTTickStat& /*tstat*/)     { return(MT_RET_OK); }
   //--- extended tick events
   virtual void      OnTick(const int /*feeder*/,const MTTick& /*tick*/)          { }
   virtual void      OnTickStat(const int /*feeder*/,const MTTickStat& /*tstat*/) { }
  };
//+------------------------------------------------------------------+

