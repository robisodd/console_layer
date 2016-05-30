#pragma once
#include <pebble.h>
#define logging true  // Enable/Disable logging for debugging
//Note: printf uses APP_LOG_LEVEL_DEBUG
#if logging
  #define LOG(...) (printf(__VA_ARGS__))
#else
  #define LOG(...)
#endif

// =========================================================================================================== //
//  Inline Multi-Pebble Support
// =========================================================================================================== //
#if defined(PBL_PLATFORM_APLITE)
  #define IF_APLITE(statement) (statement)
  #define IF_BASALT(statement)
  #define IF_CHALK(statement)
#elif defined(PBL_PLATFORM_BASALT)
  #define IF_APLITE(statement)
  #define IF_BASALT(statement) (statement)
  #define IF_CHALK(statement)
#elif defined(PBL_PLATFORM_CHALK)
  #define IF_APLITE(statement)
  #define IF_BASALT(statement)
  #define IF_CHALK(statement) (statement)
#else
  #define IF_APLITE(statement)
  #define IF_BASALT(statement)
  #define IF_CHALK(statement)
#endif


#if defined(PBL_COLOR)
  #define IF_COLOR(color) (color)
  #define IF_BW(bw)
  #define IF_COLOR_ELSE(color, other) (color)
  #define IF_BW_ELSE(bw, other) (other)
  #define IF_COLOR_BW(color, bw) (color)
  #define IF_BW_COLOR(bw, color) (color)
  #define IF_COLOR_BW_ELSE(color, bw, other) (color)
  #define IF_BW_COLOR_ELSE(bw, color, other) (color)
#elif defined(PBL_BW)
  #define IF_COLOR(color)
  #define IF_BW(bw) (bw)
  #define IF_COLOR_ELSE(color, other) (other)
  #define IF_BW_ELSE(bw, other) (bw)
  #define IF_COLOR_BW(color, bw) (bw)
  #define IF_BW_COLOR(bw, color) (bw)
  #define IF_COLOR_BW_ELSE(color, bw, other) (bw)
  #define IF_BW_COLOR_ELSE(bw, color, other) (bw)
#else
  #define IF_COLOR(color)
  #define IF_BW(bw)
  #define IF_COLOR_ELSE(color, other) (other)
  #define IF_BW_ELSE(bw, other) (other)
  #define IF_COLOR_BW(color, bw)
  #define IF_BW_COLOR(bw, color)
  #define IF_COLOR_BW_ELSE(color, bw, other) (other)
  #define IF_BW_COLOR_ELSE(bw, color, other) (other)
#endif

  
#if defined(PBL_SDK_2)
  #define IF_SDK2(SDK2) (SDK2)
  #define IF_SDK3(SDK3)
  #define IF_SDK2_ELSE(SDK2, other) (SDK2)
  #define IF_SDK3_ELSE(SDK3, other) (other)
  #define IF_SDK2_SDK3(SDK2, SDK3) (SDK2)
  #define IF_SDK2_SDK3_ELSE(SDK2, SDK3, other) (SDK2)
#elif defined(PBL_SDK_3)
  #define IF_SDK2(SDK2)
  #define IF_SDK3(SDK3) (SDK3)
  #define IF_SDK2_ELSE(SDK2, other) (other)
  #define IF_SDK3_ELSE(SDK3, other) (SDK3)
  #define IF_SDK2_SDK3(SDK2, SDK3) (SDK3)
  #define IF_SDK2_SDK3_ELSE(SDK2, SDK3, other) (SDK3)
#else
  #define IF_SDK2(SDK2)
  #define IF_SDK3(SDK3)
  #define IF_SDK2_ELSE(SDK2, other) (other)
  #define IF_SDK3_ELSE(SDK3, other) (other)
  #define IF_SDK2_SDK3(SDK2, SDK3)
  #define IF_SDK2_SDK3_ELSE(SDK2, SDK3, other) (other)
#endif

#if defined(PBL_RECT)
  #define IF_RECT(rect) (rect)
  #define IF_ROUND(round)
  #define IF_RECT_ELSE(rect, other) (rect)
  #define IF_ROUND_ELSE(round, other) (other)
  #define IF_RECT_ROUND(rect, round) (rect)
  #define IF_ROUND_RECT(round, rect) (rect)
  #define IF_RECT_ROUND_ELSE(rect, round, other) (rect)
  #define IF_ROUND_RECT_ELSE(round, rect, other) (rect)
#elif defined(PBL_ROUND)
  #define IF_RECT(rect)
  #define IF_ROUND(round) (round)
  #define IF_RECT_ELSE(rect, other) (other)
  #define IF_ROUND_ELSE(round, other) (round)
  #define IF_RECT_ROUND(rect, round) (round)
  #define IF_ROUND_RECT(round, rect) (round)
  #define IF_RECT_ROUND_ELSE(rect, round, other) (round)
  #define IF_ROUND_RECT_ELSE(round, rect, other) (round)
#else
  #define IF_RECT(rect)
  #define IF_ROUND(round)
  #define IF_RECT_ELSE(rect, other) (other)
  #define IF_ROUND_ELSE(round, other) (other)
  #define IF_RECT_ROUND(rect, round)
  #define IF_ROUND_RECT(round, rect)
  #define IF_RECT_ROUND_ELSE(rect, round, other) (other)
  #define IF_ROUND_RECT_ELSE(round, rect, other) (other)
#endif

// =========================================================================================================== //
