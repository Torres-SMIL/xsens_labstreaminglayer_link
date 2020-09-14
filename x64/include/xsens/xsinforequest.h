#ifndef XSINFOREQUEST_H
#define XSINFOREQUEST_H

/*!	\addtogroup enums Global enumerations
	@{
*/
/*! \brief Information request identifiers
	\details These values are used by the XsDevice::requestInfo function and
	XsCallback::onInfoResponse functions.
*/
enum XsInfoRequest {
	XIR_BatteryLevel = 0,	//!< Request battery level
	XIR_GnssSvInfo,		//!< Request Gnss satellite vehicle information
	XIR_GpsSvInfo = XIR_GnssSvInfo			//!< Request Gps satellite vehicle information \deprecated Replaced with XIR_GnssSvInfo
};
/*! @} */
typedef enum XsInfoRequest XsInfoRequest;

#endif
