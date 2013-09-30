/* --------------------------------------------
Copyright (c) 2013, University of Granada
Copyright (c) 2013, Real-Time Innovations, Inc.
Copyright (c) 2013, Javier Povedano-Molina
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notices, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notices,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the copyright holders or contributors.

This work was partially completed at the University of Granada under funding by 
Real-Time Innovations, Inc. (RTI).  The above license is granted with
 the permission of RTI.

-------------------------------------------- */

#ifndef VIDEOBUFFER_H_
#define VIDEOBUFFER_H_

#include <stdio.h>
#include <stdlib.h>

#include "simclist.h"


#define EMDS_BUFFER_FLAGS_METADATA  (0x1 << 0)
#define EMDS_BUFFER_FLAGS_KEYFRAME  (0x1 << 1)
#define EMDS_BUFFER_FLAGS_EOS       (0x1 << 2)
#define EMDS_BUFFER_FLAGS_ENCRYPTED (0x1 << 3)

typedef uint32_t EMDSBufferFlags;
typedef double EMDSTimestamp;

// ------------------------------------------------------------------------- //
//
// EMDSBuffer:
// Class that encapuslates a sized video buffer, which may include flags or
// metadata about that video buffer.
//
// ------------------------------------------------------------------------- //
class EMDSBuffer
{
public:

	// --- Constructors --- 
	EMDSBuffer();
	EMDSBuffer(int allocateSize);
	EMDSBuffer(EMDSBuffer& copyFrom);

	// --- Destructor --- 
	~EMDSBuffer();

	// --- Initialization --- 
	void Initialize();

	// --- Getters and Setters --- 
	unsigned char *GetData(); 
	void SetData(unsigned char *copyFrom, unsigned int sizeIn);

	int GetSize();

	void SetSeqn(unsigned int seqNumIn);
	unsigned int GetSeqn();

	EMDSBufferFlags GetFlags();
	void SetFlags(EMDSBufferFlags flagsIn);

	void SetTimestamp(EMDSTimestamp timestampIn);
	EMDSTimestamp GetTimestamp();
private:

	// --- Private members --- 
	unsigned char *data;
	unsigned int seqn;
	size_t size;
	EMDSTimestamp timestamp;
	EMDSBufferFlags flags;
};


class EMDSBufferQueue
{
public:

	// --- Constructor --- 
	EMDSBufferQueue();

	// --- Initialization --- 
	void Initialize();

	bool IsEmpty();

	void Queue(EMDSBuffer *data);
	EMDSBuffer *Dequeue();

private:
	// --- Private members --- 
	list_t _fifo;

};


#endif /* VIDEOBUFFER_H_ */
