/**
* @brief CFMBBDSC_R.h: interface for the CCFMBBDSC_R class.
* CCFMBBDSC_R is a derive class of CCFMDSC_R. Receive cfm data is R, not RGB, and a full cfm line have PKTSIZE bytes, not 
* PKTSIZE*3 bytes. The section parameter is invalid.
*
* @version: 1.0
* @author: hehao
* @date: 2010-5-14
*/

#ifndef CFMBBDSC_R_H
#define CFMBBDSC_R_H

#include "CFMDSC_R.h"

class CCFMBBDSC_R : public CCFMDSC_R  
{
public:
	static CCFMBBDSC_R *Create(const DSCCONTROLATTRIBUTES &attrs, const UPDATEFRAME pUpdateFrame);
	virtual void Destroy(void);
	virtual bool GetUSBDatas(const unsigned char *pDatas);
	virtual void SetLocalZoomState(unsigned int scanLStart, unsigned int scanLEnd, unsigned int sampStart, 
		unsigned int sampEnd, float zoomScale);	
	void UpdateBBFlag(void);
};

#endif //CFMBBDSC_R_H
