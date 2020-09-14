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

#include "positiondatagram.h"

/*! \class PositionDatagram

  Point position data (type 03)
  Information about each point is sent as follows.
  This data type is intended to emulate a Virtual (optical) Marker Set.

  4 bytes point identifier, this is 256 x the segment ID + the point ID
  4 bytes x–coordinate of point position
  4 bytes y–coordinate of point position
  4 bytes z–coordinate of point position

  Total: 16 bytes per point

  The coordinates use a Y-Up, right-handed coordinate system.
*/

/*! Constructor */
PositionDatagram::PositionDatagram()
	: Datagram()
{
	setType(SPPosePositions);
}

/*! Destructor */
PositionDatagram::~PositionDatagram()
{
}

/*! Deserialize the data from \a arr
	\sa serializeData
*/
void PositionDatagram::deserializeData(Streamer &inputStreamer)
{
	Streamer* streamer = &inputStreamer;

	for (int i = 0; i < dataCount(); i++)
	{
		VirtualMarkerSet marker;

		// Store the segement Id -> 4 byte
		streamer->read(marker.segmentId);

		// Store the Point Position in a Vector -> 12 byte	(3 x 4 byte)
		// The coordinates use a Y-Up, right-handed coordinate system.
		for (int k = 0; k < 3; k++)
			streamer->read(marker.pointPos[k]);

		for (int k = 0; k < 3; k++)
			marker.pointPos[k] /= EULERPOSITIONSCALE;

		convertFromYupToZup(marker.pointPos);

		m_data.push_back(marker);
	}
}


lsl::stream_info PositionDatagram::info[2] = {
	lsl::stream_info("PositionDatagram1", "MoCap", 23 * (3), lsl::IRREGULAR_RATE, lsl::cf_float32, "pd1"),
	lsl::stream_info("PositionDatagram2", "MoCap", 23 * (3), lsl::IRREGULAR_RATE, lsl::cf_float32, "pd2")
};

// Create the streams with that stream info
lsl::stream_outlet PositionDatagram::outlet[2] = {
	{ PositionDatagram::info[0] },
    { PositionDatagram::info[1] },
};

std::vector<float> PositionDatagram::alignData() const {
	std::vector<float> ret;

	for (auto s : m_data) {
		for (auto p : s.pointPos) ret.push_back(p);
	}
	return ret;
}

void PositionDatagram::streamData() const {

}

/*! Print Data datagram in a formated why
*/
void PositionDatagram::printData() const
{
	streamData();
}
