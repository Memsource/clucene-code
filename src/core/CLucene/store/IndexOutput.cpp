/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#include "CLucene/_ApiHeader.h"
#include "IndexOutput.h"
#include "IndexInput.h"
#include "CLucene/util/Misc.h"

CL_NS_USE(util)
CL_NS_DEF(store)


  IndexOutput::IndexOutput()
  {
	  copyBuffer = NULL;
  }

  IndexOutput::~IndexOutput(){
	  _CLDELETE_LARRAY(copyBuffer);
  }

  void IndexOutput::writeInt(const int32_t i) {
    writeByte((uint8_t)(i >> 24));
    writeByte((uint8_t)(i >> 16));
    writeByte((uint8_t)(i >>  8));
    writeByte((uint8_t) i);
  }

  void IndexOutput::writeVInt(const int32_t vi) {
	  uint32_t i = vi;
    while ((i & ~0x7F) != 0) {
      writeByte((uint8_t)((i & 0x7f) | 0x80));
      i >>= 7; //doing unsigned shift
    }
    writeByte( (uint8_t)i );
  }

  void IndexOutput::writeLong(const int64_t i) {
    writeInt((int32_t) (i >> 32));
    writeInt((int32_t) i);
  }

  void IndexOutput::writeVLong(const int64_t vi) {
	uint64_t i = vi;
    while ((i & ~0x7F) != 0) {
      writeByte((uint8_t)((i & 0x7f) | 0x80));
      i >>= 7; //doing unsigned shift
    }
    writeByte((uint8_t)i);
  }

  void IndexOutput::writeString(const string& s ) {
    writeString(s.c_str(),s.length());
  }

#ifdef _UCS2
  void IndexOutput::writeString(const char* s, const int32_t length ) {
  	TCHAR* buf = _CL_NEWARRAY(TCHAR,length+1);
  	STRCPY_AtoT(buf,s,length);
  	try{
  		writeString(buf,length);
  	}_CLFINALLY ( _CLDELETE_CARRAY(buf); )
  }
#endif

  void IndexOutput::writeString(const TCHAR* s, const int32_t length ) {
    writeVInt(length);
    writeChars(s, length);
  }

  void IndexOutput::writeChars(const TCHAR* s, const int32_t length){
    if ( length < 0 )
      _CLTHROWA(CL_ERR_IllegalArgument, "IO Argument Error. Value must be a positive value.");

    const int32_t end = length;
    for (int32_t i = 0; i < end; ++i) {
        const int32_t code = (int32_t)s[i];
        if (code >= 0x01 && code <= 0x7F)
					writeByte((uint8_t)code);
        else if (((code >= 0x80) && (code <= 0x7FF)) || code == 0) {
					writeByte((uint8_t)(0xC0 | (code >> 6)));
					writeByte((uint8_t)(0x80 | (code & 0x3F)));
        } else {
					writeByte((uint8_t)(0xE0 | (((uint32_t)code) >> 12))); //unsigned shift
					writeByte((uint8_t)(0x80 | ((code >> 6) & 0x3F)));
					writeByte((uint8_t)(0x80 | (code & 0x3F)));
        }
    }
  }


  void IndexOutput::copyBytes(CL_NS(store)::IndexInput* input, int64_t numBytes)
  {
	  int64_t left = numBytes;
	  if (copyBuffer == NULL)
		  copyBuffer = _CL_NEWARRAY(uint8_t, COPY_BUFFER_SIZE);
	  while(left > 0) {
		  int32_t toCopy;
		  if (left > COPY_BUFFER_SIZE)
			  toCopy = COPY_BUFFER_SIZE;
		  else
			  toCopy = (int32_t) left;
		  input->readBytes(copyBuffer, toCopy);
		  writeBytes(copyBuffer, toCopy);
		  left -= toCopy;
	  }
  }

CL_NS_END
