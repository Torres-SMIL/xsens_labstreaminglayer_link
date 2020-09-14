#ifndef XSDATAIDENTIFIERVALUE_H
#define XSDATAIDENTIFIERVALUE_H

#define XDI_MAX_FREQUENCY		((uint16_t) 0xFFFF)

//////////////////////////////////////////////////////////////////////////////////////////
/*!	\addtogroup enums Global enumerations
	@{
*/

/*!	\enum XsDataIdentifierValue
	\brief Defines some convenience values for use with the data identifiers

	Refer to the Low Level Communication Protocol for more details.
*/
enum XsDataIdentifierValue
{
	XDIV_MaxFrequency			= XDI_MAX_FREQUENCY,	//!< Maximum / no frequency
};
/*! @} */

typedef enum XsDataIdentifierValue XsDataIdentifierValue;

#endif
