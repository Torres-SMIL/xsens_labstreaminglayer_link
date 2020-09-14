#ifndef XSRAWGPSTIMEUTC_H
#define XSRAWGPSTIMEUTC_H

#include "pstdint.h"
#include <string.h>

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

#ifndef __cplusplus
#define XSRAWGPSTIMEUTC_INITIALIZER { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#endif

/*! \brief A container for NAV-TIMEUTC data
	\deprecated
*/
struct XsRawGpsTimeUtc
{
	uint32_t m_itow;	//!< Gps time of week (ms)
	uint32_t m_tacc;	//!< Time Accuracy Estimate (ns)
	int32_t  m_nano;	//!< Nanoseconds of second, range -500000000 .. 500000000 (UTC)
	uint16_t m_year;	//!< Year, range 1999..2099 (UTC)
	uint8_t  m_month;	//!< Month, range 1..12 (UTC)
	uint8_t  m_day;		//!< Day of Month, range 1..31 (UTC)
	uint8_t  m_hour;	//!< Hour of Day, range 0..23 (UTC)
	uint8_t  m_min;		//!< Minute of Hour, range 0..59 (UTC)
	uint8_t  m_sec;		//!< Minute of Hour, range 0..59 (UTC)
	uint8_t  m_valid;	/*!< Valid	0x01 = Valid Time of Week
									0x02 = Valid Week Number
									0x04 = Valid UTC (Leap Seconds already known?)
						*/
};
typedef struct XsRawGpsTimeUtc XsRawGpsTimeUtc;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#ifdef __cplusplus
inline bool operator == (XsRawGpsTimeUtc const& a, XsRawGpsTimeUtc const& b)
{
	return memcmp(&a, &b, sizeof(XsRawGpsTimeUtc)) == 0;
}
#endif

#endif
