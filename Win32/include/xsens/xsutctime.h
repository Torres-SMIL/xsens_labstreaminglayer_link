#ifndef XSUTCTIME_H
#define XSUTCTIME_H

#include "xstypesconfig.h"
#include "pstdint.h"

#ifdef __cplusplus
extern "C"
{
#else
#define XSUTCTIME_INITIALIZER	{ 0, 0 ,0, 0, 0, 0, 0, 0}
#endif
struct XsUtcTime;

XSTYPES_DLL_API void XsUtcTime_currentTime(struct XsUtcTime * now);

#ifdef __cplusplus
} // extern "C"
#endif

/*! \brief A structure for storing UTC Time values. */
struct XsUtcTime {
	uint32_t	m_nano;		//!< \brief Nanosecond part of the time
	uint16_t	m_year;		//!< \brief The year (if date is valid)
	uint8_t		m_month;	//!< \brief The month (if date is valid)
	uint8_t		m_day;  	//!< \brief The day of the month (if date is valid)
	uint8_t		m_hour;		//!< \brief The hour (if time is valid)
	uint8_t		m_minute;	//!< \brief The minute (if time is valid)
	uint8_t		m_second;	//!< \brief The second (if time is valid)
	uint8_t		m_valid;	//!< \brief Validity indicator \details When received: bit (0) - UTC Date is valid; bit (1) - UTC Time of Day is valid; bit (2) - UTC Time of Day has been fully resolved (i.e. no seconds uncertainty).

#ifdef __cplusplus
	/*! \copydoc XsUtcTime_currentTime
	   \return The current UTC Time
	*/
	inline static XsUtcTime currentTime()
	{
		XsUtcTime tmp;
		XsUtcTime_currentTime(&tmp);
		return tmp;
	}

	/*! \brief Returns true if all fields of this and \a other are exactly identical */
	inline bool operator == (const XsUtcTime& other) const
	{
		return m_nano	== other.m_nano &&
			   m_year	== other.m_year &&
			   m_month	== other.m_month &&
			   m_day  	== other.m_day &&
			   m_hour	== other.m_hour &&
			   m_minute	== other.m_minute &&
			   m_second	== other.m_second &&
			   m_valid	== other.m_valid;
	}
#endif
};
typedef struct XsUtcTime XsUtcTime;

#endif
