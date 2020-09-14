/*! \file
	\section FileCopyright Copyright Notice
	This is free and unencumbered software released into the public domain.

	Anyone is free to copy, modify, publish, use, compile, sell, or
	distribute this software, either in source code form or as a compiled
	binary, for any purpose, commercial or non-commercial, and by any
	means.

	In jurisdictions that recognize copyright laws, the author or authors
	of this software dedicate any and all copyright interest in the
	software to the public domain. We make this dedication for the benefit
	of the public at large and to the detriment of our heirs and
	successors. We intend this dedication to be an overt act of
	relinquishment in perpetuity of all present and future rights to this
	software under copyright law.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#include "angularsegmentkinematicsdatagram.h"
#include <xsens/xsmath.h>

/*! \class AngularSegmentKinematicsDatagram
	\brief a Angular Kinematics datagram (type 0x22)

	Information about each segment is sent as follows.

	4 bytes segment ID, in the range 1-30
	4 bytes q1 segment orientation quaternion component 1 (re)
	4 bytes q2 segment orientation quaternion component 1 (i)
	4 bytes q3 segment orientation quaternion component 1 (j)
	4 bytes q4 segment orientation quaternion component 1 (k)
	4 bytes angular velocity around segment x axis
	4 bytes angular velocity around segment y axis
	4 bytes angular velocity around segment z axis
	4 bytes angular acceleration around segment x axis
	4 bytes angular acceleration around segment y axis
	4 bytes angular acceleration around segment z axis

	Total: 44 bytes per segment

	The coordinates use a Z-Up, right-handed coordinate system.
*/

/*! Constructor */
AngularSegmentKinematicsDatagram::AngularSegmentKinematicsDatagram()
	: Datagram()
{
	setType(SPAngularSegmentKinematics);
}

/*! Destructor */
AngularSegmentKinematicsDatagram::~AngularSegmentKinematicsDatagram()
{
}

/*! Deserialize the data from \a arr
	\sa serializeData
*/
void AngularSegmentKinematicsDatagram::deserializeData(Streamer &inputStreamer)
{
	Streamer* streamer = &inputStreamer;

	for (int i = 0; i < dataCount(); i++)
	{
		Kinematics kin;

		// Store the segement Id -> 4 byte 
		streamer->read(kin.segmentId);

		// Store the Segment orientation in a Vector -> 16 byte	(4 x 4 byte)
		for (int k = 0; k < 4; k++)
			streamer->read(kin.segmentOrien[k]);
		// trasform in degrees
		for (int k = 0; k < 4; k++)
			kin.segmentOrien[k] = XsMath_rad2deg(kin.segmentOrien[k]);

		// Store the Angular Velocity in a Vector -> 12 byte	(3 x 4 byte)
		for (int k = 0; k < 3; k++)
			streamer->read(kin.angularVeloc[k]);
		// trasform in degrees
		for (int k = 0; k < 3; k++)
			kin.angularVeloc[k] = XsMath_rad2deg(kin.angularVeloc[k]);

		// Store the Angular Acceleration in a Vector -> 12 byte	(3 x 4 byte)
		for (int k = 0; k < 3; k++)
			streamer->read(kin.angularAccel[k]);
		// trasform in degrees
		for (int k = 0; k < 3; k++)
			kin.angularAccel[k] = XsMath_rad2deg(kin.angularAccel[k]);

		m_data.push_back(kin);
	}
}

// Define the stream info for LabStreamingLayer
lsl::stream_info AngularSegmentKinematicsDatagram::info[2] = {
	lsl::stream_info("AngularKinematics1", "MoCap", 23 * (4 + 3 + 3), lsl::IRREGULAR_RATE, lsl::cf_float32, "ang1"),
	lsl::stream_info("AngularKinematics2", "MoCap", 23 * (4 + 3 + 3), lsl::IRREGULAR_RATE, lsl::cf_float32, "ang2")
};

// Create the streams with that stream info
lsl::stream_outlet AngularSegmentKinematicsDatagram::outlet[2] = {
	{AngularSegmentKinematicsDatagram::info[0]},
	{AngularSegmentKinematicsDatagram::info[1]},
};


std::vector<float> AngularSegmentKinematicsDatagram::alignData() const {
	std::vector<float> ret;
	for (auto seg : m_data) {
		for (auto or : seg.segmentOrien) {
			ret.push_back(or );
		}
		for (auto vel : seg.angularVeloc) {
			ret.push_back(vel);
		}
		for (auto acc : seg.angularAccel) {	
			ret.push_back(acc);
		}
	}
	return ret;
}

void AngularSegmentKinematicsDatagram::streamData() const {
	auto data = alignData();
	outlet[avatarId()].push_sample(data);
}


/*! Print Data datagram in a formated why
*/
void AngularSegmentKinematicsDatagram::printData() const
{
	streamData();
}
