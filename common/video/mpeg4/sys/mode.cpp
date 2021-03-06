/*************************************************************************

This software module was originally developed by 

	Ming-Chieh Lee (mingcl@microsoft.com), Microsoft Corporation
	Wei-ge Chen (wchen@microsoft.com), Microsoft Corporation
	Bruce Lin (blin@microsoft.com), Microsoft Corporation
	Chuang Gu (chuanggu@microsoft.com), Microsoft Corporation
	Simon Winder (swinder@microsoft.com), Microsoft Corporation
	(date: March, 1996)

in the course of development of the MPEG-4 Video (ISO/IEC 14496-2). 
This software module is an implementation of a part of one or more MPEG-4 Video tools 
as specified by the MPEG-4 Video. 
ISO/IEC gives users of the MPEG-4 Video free license to this software module or modifications 
thereof for use in hardware or software products claiming conformance to the MPEG-4 Video. 
Those intending to use this software module in hardware or software products are advised that its use may infringe existing patents. 
The original developer of this software module and his/her company, 
the subsequent editors and their companies, 
and ISO/IEC have no liability for use of this software module or modifications thereof in an implementation. 
Copyright is not released for non MPEG-4 Video conforming products. 
Microsoft retains full right to use the code for his/her own purpose, 
assign or donate the code to a third party and to inhibit third parties from using the code for non <MPEG standard> conforming products. 
This copyright notice must be included in all copies or derivative works. 

Copyright (c) 1996, 1997.


Module Name:

	mode.h

Abstract:

	basic coding modes for VOP and MB

Revision History:
	Dec. 12, 1997:	Interlaced tools added by NextLevel Systems
        May. 9   1998:  add boundary by Hyundai Electronics
                                  Cheol-Soo Park (cspark@super5.hyundai.co.kr)
        May. 9   1998:  add field based MC padding by Hyundai Electronics
                                  Cheol-Soo Park (cspark@super5.hyundai.co.kr)
	May 9, 1999:	tm5 rate control by DemoGraFX, duhoff@mediaone.net
*************************************************************************/


#include <string.h>
#include <iostream.h>
#include <math.h>
#include "typeapi.h"
#include "mode.hpp"
#include "warp.hpp"

#ifdef __MFC_
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW				   
#endif // __MFC_

// only works for 4:2:0
#define MAX_NUM_MV 4
UInt uiNumBlks = 10;
//#define uiNumBlks 10

CMBMode::~CMBMode ()
{ 
	delete [] m_rgbCodedBlockPattern; 
	delete [] m_rgfltMinErrors; 
}

CMBMode::CMBMode ()
{
	UInt i;
	for (i = 0; i < uiNumBlks + 1; i++) {
		m_rgTranspStatus [i] = NONE;
		m_rgNumNonTranspPixels [i] = 0;
	}
	/*BBM// Added for Boundary by Hyundai(1998-5-9)
        for (i = 0; i < uiNumBlks + 1; i++)
                m_rgTranspStatusBBM[i] = NONE;
        memset (m_bMerged, FALSE, 7 * sizeof(Bool));
	// End of Hyundai(1998-5-9)*/

	// Added for field based MC padding by Hyundai(1998-5-9)
        for (i = 0; i < 5; i++)
			m_rgFieldTranspStatus [i] = ALL;
		memset (m_rgbFieldPadded, 0, 5 * sizeof(Bool));
	// End of Hyundai(1998-5-9)

	m_rgbCodedBlockPattern = new Bool [uiNumBlks];
	memset (m_rgbCodedBlockPattern, FALSE, uiNumBlks * sizeof (Bool));
	m_rgfltMinErrors = new Float [uiNumBlks];
	memset (m_rgfltMinErrors, 0, uiNumBlks * sizeof (Float));
	m_bPadded = FALSE;
	m_bSkip = FALSE;
	m_dctMd = INTRA;
	m_shpmd = UNKNOWN;
	m_mbType = FORWARD;
	m_intStepDelta = 0;
	m_bhas4MVForward = FALSE; 
	m_bhas4MVBackward = FALSE;
	m_bFieldMV = FALSE;
	m_bForwardTop = FALSE;	  
	m_bForwardBottom = FALSE;
	m_bBackwardTop = FALSE;	
	m_bBackwardBottom = FALSE;
	m_bFieldDCT = FALSE;
	m_bPerspectiveForward = FALSE;
	m_bPerspectiveBackward = FALSE;
	m_stepSize = 0;
	m_stepSizeDelayed = 0;
	m_stepSizeAlpha = 0;
	m_bACPrediction = FALSE;
	m_bInterShapeCoding = FALSE;
	m_bColocatedMBSkip = FALSE;
	m_iVideoPacketNumber = 0;	
	m_vctDirectDeltaMV = CVector (0, 0);
}

CMBMode::CMBMode (const CMBMode& md)
{
	memcpy (m_rgTranspStatus, md.m_rgTranspStatus, (uiNumBlks + 1)  * sizeof (TransparentStatus));
	memcpy (m_rgNumNonTranspPixels, md.m_rgNumNonTranspPixels, (uiNumBlks + 1)  * sizeof (UInt));
	memcpy (m_preddir,md.m_preddir,uiNumBlks * sizeof(IntraPredDirection));

	/*BBM// Added for Boundary by Hyundai(1998-5-9)
        memcpy (m_rgTranspStatusBBM, md.m_rgTranspStatusBBM, (uiNumBlks + 1)  * sizeof (TransparentStatus));
        memcpy (m_bMerged, md.m_bMerged, 7 * sizeof (Bool));
	// End of Hyundai(1998-5-9)*/

	// Added for field based MC padding by Hyundai(1998-5-9)
        memcpy (m_rgFieldTranspStatus, md.m_rgFieldTranspStatus, 5  * sizeof (TransparentStatus));
		memcpy (m_rgbFieldPadded, md.m_rgbFieldPadded, 5 * sizeof (Bool));
	// End of Hyundai(1998-5-9)

	m_bPadded = md.m_bPadded;
	m_bSkip = md.m_bSkip;
	m_CODAlpha = md.m_CODAlpha;
	m_mbType = md.m_mbType;
	m_dctMd = md.m_dctMd;
	m_shpmd = md.m_shpmd ;
	m_intStepDelta = md.m_intStepDelta;
	m_bhas4MVForward = md.m_bhas4MVForward; 
	m_bhas4MVBackward = md.m_bhas4MVBackward; 
	m_bPerspectiveForward = md.m_bPerspectiveForward;
	m_bPerspectiveBackward = md.m_bPerspectiveBackward;
	m_stepSize = md.m_stepSize;
	m_stepSizeDelayed = md.m_stepSizeDelayed;
	m_stepSizeAlpha = md.m_stepSizeAlpha;
	m_bACPrediction = md.m_bACPrediction;
	m_bACPredictionAlpha = md.m_bACPredictionAlpha;
	m_bInterShapeCoding = md.m_bInterShapeCoding;
	m_bCodeDcAsAc = md.m_bCodeDcAsAc;
	m_bCodeDcAsAcAlpha = md.m_bCodeDcAsAcAlpha;
	m_bColocatedMBSkip = md.m_bColocatedMBSkip;
	m_iVideoPacketNumber = md.m_iVideoPacketNumber;

	m_rgbCodedBlockPattern = new Bool [uiNumBlks];
	memcpy (m_rgbCodedBlockPattern, md.m_rgbCodedBlockPattern, uiNumBlks * sizeof (Bool));
	m_rgfltMinErrors = new Float [uiNumBlks];
	memcpy (m_rgfltMinErrors, md.m_rgfltMinErrors, uiNumBlks * sizeof (Float));
}

Void CMBMode::operator = (const CMBMode& md)
{
	memcpy (m_rgTranspStatus, md.m_rgTranspStatus, (uiNumBlks + 1) * sizeof (TransparentStatus));
	memcpy (m_rgNumNonTranspPixels, md.m_rgNumNonTranspPixels, (uiNumBlks + 1) * sizeof (UInt));
	memcpy (m_preddir,md.m_preddir,uiNumBlks * sizeof(IntraPredDirection));

	/*BBM// Added for Boundary by Hyundai(1998-5-9)
	memcpy (m_rgTranspStatusBBM, md.m_rgTranspStatusBBM, (uiNumBlks + 1)  * sizeof (TransparentStatus));
        memcpy (m_bMerged, md.m_bMerged, 7 * sizeof (Bool));
	// End of Hyundai(1998-5-9)*/

	// Added for field based MC padding by Hyundai(1998-5-9)
        memcpy (m_rgFieldTranspStatus, md.m_rgFieldTranspStatus, 5  * sizeof (TransparentStatus));
        memcpy (m_rgbFieldPadded, md.m_rgbFieldPadded, 5 * sizeof (Bool));
	// End of Hyundai(1998-5-9)

	m_bPadded = md.m_bPadded;
	m_bSkip = md.m_bSkip;
	m_CODAlpha = md.m_CODAlpha;
	m_mbType = md.m_mbType;
	m_dctMd = md.m_dctMd;
	m_shpmd = md.m_shpmd ;
	m_intStepDelta = md.m_intStepDelta;
	m_bhas4MVForward = md.m_bhas4MVForward; 
	m_bhas4MVBackward = md.m_bhas4MVBackward; 
	m_bPerspectiveForward = md.m_bPerspectiveForward;
	m_bPerspectiveBackward = md.m_bPerspectiveBackward;
	m_stepSize = md.m_stepSize;
	m_stepSizeDelayed = md.m_stepSizeDelayed;
	m_stepSizeAlpha = md.m_stepSizeAlpha;
	m_bACPrediction = md.m_bACPrediction;
	m_bACPredictionAlpha = md.m_bACPredictionAlpha;
	m_bInterShapeCoding = md.m_bInterShapeCoding;
	m_bCodeDcAsAc = md.m_bCodeDcAsAc;
	m_bCodeDcAsAcAlpha = md.m_bCodeDcAsAcAlpha;
	m_bColocatedMBSkip = md.m_bColocatedMBSkip;
	m_iVideoPacketNumber = md.m_iVideoPacketNumber;

	memcpy (m_rgbCodedBlockPattern, md.m_rgbCodedBlockPattern, uiNumBlks * sizeof (Bool));
	memcpy (m_rgfltMinErrors, md.m_rgfltMinErrors, uiNumBlks * sizeof (Float));
}

Void CMBMode::setCodedBlockPattern (const Bool* rgbblockNum)
{ 
	for (UInt i = 0; i < uiNumBlks; i++)
		m_rgbCodedBlockPattern[i] = rgbblockNum [i];
}

Void CMBMode::setMinError (const Float* pfltminError)
{
	for (UInt i = 0; i < uiNumBlks; i++)
		m_rgfltMinErrors[i] = pfltminError [i];

}

CDirectModeData::~CDirectModeData ()
{
	destroyMem ();
}

CDirectModeData::CDirectModeData ()
{
	m_ppmbmd = NULL;
	m_prgmv = NULL;
}

Bool CDirectModeData::inBound (UInt iMbIdx) const
{
	if (iMbIdx >= m_uiNumMB)
		return FALSE;
	else
		return TRUE;
}

Bool CDirectModeData::inBound (UInt idX, UInt idY) const
{
	if (idX >= m_uiNumMBX || idY >= m_uiNumMBY || idX * idY >= m_uiNumMB)
		return FALSE;
	else
		return TRUE;
}

Void CDirectModeData::reassign (UInt numMBX, UInt numMBY)
{
	destroyMem ();
	m_uiNumMBX = numMBX;
	m_uiNumMBY = numMBY;
	m_uiNumMB = m_uiNumMBX * m_uiNumMBY;
	m_ppmbmd = new CMBMode* [m_uiNumMB];
	m_prgmv = new CMotionVector* [m_uiNumMB];
	for (UInt i = 0; i < m_uiNumMB; i++) {
		m_ppmbmd [i] = new CMBMode;
		m_prgmv [i] = new CMotionVector [5];
	}
}

Void CDirectModeData::assign (UInt imb, const CMBMode& mbmd, const CMotionVector* rgmv)
{
	assert (inBound (imb));
	*(m_ppmbmd [imb]) = mbmd;
	memcpy (m_prgmv [imb], rgmv, 5 * sizeof (CMotionVector));
}

Void CDirectModeData::destroyMem ()
{
	if (m_ppmbmd != NULL) {
		for (UInt i = 0; i < m_uiNumMB; i++)
			delete m_ppmbmd [i];
		delete [] m_ppmbmd;
	}
	if (m_prgmv != NULL) {
		for (UInt i = 0; i < m_uiNumMB; i++)
			delete [] m_prgmv [i];
		delete [] m_prgmv;
	}
}

CStatistics::CStatistics ()
{
	reset ();
}
								
Void CStatistics::print (Bool bVOPPrint)
{
	(Void) total ();

	if (bVOPPrint)
		cout << "\t" << "VOP overhead:" << "\t\t" << nBitsHead << "\n";
	cout << "\t" << "Y:" << "\t\t\t" << nBitsY << "\n";
	cout << "\t" << "Cr:" << "\t\t\t" << nBitsCr << "\n";
	cout << "\t" << "Cb:" << "\t\t\t" << nBitsCb << "\n";
	cout << "\t" << "A:" << "\t\t\t" << nBitsA << "\n";
//	cout << "\t" << "1st Shape Code:" << "\t\t" << nBits1stShpCode << "\n";
	cout << "\t" << "CBPY:" << "\t\t\t" << nBitsCBPY << "\n";
	cout << "\t" << "MCBPC:" << "\t\t\t" << nBitsMCBPC << "\n";
	cout << "\t" << "DQUANT:" << "\t\t\t" << nBitsDQUANT << "\n";
	cout << "\t" << "nBitsMODB:" << "\t\t" << nBitsMODB << "\n";
	cout << "\t" << "nBitsCBPB:" << "\t\t" << nBitsCBPB << "\n";
	cout << "\t" << "nBitsMBTYPE:" << "\t\t" << nBitsMBTYPE << "\n";
	cout << "\t" << "nBitsIntraPred:" << "\t\t" << nBitsIntraPred << "\n";
	cout << "\t" << "nBitsNoDCT:" << "\t\t" << nBitsNoDCT << "\n";	
	cout << "\t" << "nBitsCODA:" << "\t\t" << nBitsCODA << "\n";
	cout << "\t" << "nBitsCBPA:" << "\t\t" << nBitsCBPA << "\n";
	cout << "\t" << "nBitsMODBA:" << "\t\t" << nBitsMODBA << "\n";
	cout << "\t" << "nBitsCBPBA:" << "\t\t" << nBitsCBPBA << "\n";
	cout << "\t" << "nBitsInterlace:" << "\t\t" << nBitsInterlace << "\n";
	cout << "\t" << "nBitsSTUFFING:" << "\t\t" << nBitsStuffing << "\n";
	cout << "\t" << "# of Skipped MB:" << "\t" << nSkipMB << "\n";
	cout << "\t" << "# of Inter MB:" << "\t\t" << nInterMB << "\n";
	cout << "\t" << "# of Inter4V MB:" << "\t" << nInter4VMB << "\n";
	cout << "\t" << "# of Intra MB:" << "\t\t" << nIntraMB << "\n";
	cout << "\t" << "# of Direct MB:" << "\t\t" << nDirectMB << "\n";
	cout << "\t" << "# of Forward MB:" << "\t" << nForwardMB << "\n";
	cout << "\t" << "# of Backward MB:" << "\t" << nBackwardMB << "\n";
	cout << "\t" << "# of Interpolate MB:" << "\t" << nInterpolateMB << "\n";
	cout << "\t" << "# of Field Fwd MB:" << "\t" << nFieldForwardMB << "\n";
	cout << "\t" << "# of Field Back MB:" << "\t" << nFieldBackwardMB << "\n";
	cout << "\t" << "# of Field Ave MB:" << "\t" << nFieldInterpolateMB << "\n";
	cout << "\t" << "# of Field Direct MB:" << "\t" << nFieldDirectMB << "\n";
	cout << "\t" << "# of Field DCT MBs:" << "\t" << nFieldDCTMB << "\n";
	cout << "\t" << "Motion:" << "\t\t\t" << nBitsMV << "\n";
	cout << "\t" << "Texture:" << "\t\t" << nBitsTexture << "\n";
//	if (bVOPPrint)
		cout << "\t" << "Shape:" << "\t\t\t" << nBitsShape << "\n";
	cout << "\t" << "Total:" << "\t\t\t" << nBitsTotal << "\n";
	cout << "\t" << "SNR Y:" << "\t\t\t" << dSNRY / nVOPs << " dB\n";
	cout << "\t" << "SNR U:" << "\t\t\t" << dSNRU / nVOPs << " dB\n";
	cout << "\t" << "SNR V:" << "\t\t\t" << dSNRV / nVOPs << " dB\n";
	cout << "\t" << "SNR A:" << "\t\t\t" << dSNRA / nVOPs << " dB\n\n";
	cout << "\t" << "average Qp:" << "\t\t" << (Double)nQp / nQMB << "\n\n";
	cout.flush ();
}

Void CStatistics::operator += (const CStatistics& statSrc)
{
	nBitsHead += statSrc.nBitsHead;
	nBitsY += statSrc.nBitsY;
	nBitsCr += statSrc.nBitsCr;
	nBitsCb += statSrc.nBitsCb;
	nBitsA += statSrc.nBitsA;
//	nBits1stShpCode += statSrc.nBits1stShpCode;
	nBitsCOD += statSrc.nBitsCOD;
	nBitsCBPY += statSrc.nBitsCBPY;
	nBitsMCBPC += statSrc.nBitsMCBPC;
	nBitsDQUANT += statSrc.nBitsDQUANT;
	nBitsMODB += statSrc.nBitsMODB;
	nBitsCBPB += statSrc.nBitsCBPB;
	nBitsMBTYPE += statSrc.nBitsMBTYPE;
	nBitsIntraPred += statSrc.nBitsIntraPred;
	nBitsNoDCT += statSrc.nBitsNoDCT;	
	nBitsCODA += statSrc.nBitsCODA;
	nBitsCBPA += statSrc.nBitsCBPA;
	nBitsMODBA += statSrc.nBitsMODBA;
	nBitsCBPBA += statSrc.nBitsCBPBA;
	nBitsStuffing += statSrc.nBitsStuffing;
	nSkipMB += statSrc.nSkipMB;
	nInterMB += statSrc.nInterMB;
	nInter4VMB += statSrc.nInter4VMB;
	nIntraMB += statSrc.nIntraMB;
	nDirectMB += statSrc.nDirectMB;
	nForwardMB += statSrc.nForwardMB;
	nBackwardMB += statSrc.nBackwardMB;
	nInterpolateMB += statSrc.nInterpolateMB;
	nBitsInterlace += statSrc.nBitsInterlace;
	nFieldForwardMB += statSrc.nFieldForwardMB;
	nFieldBackwardMB += statSrc.nFieldBackwardMB;
	nFieldInterpolateMB += statSrc.nFieldInterpolateMB;
	nFieldDirectMB += statSrc.nFieldDirectMB;
	nFieldDCTMB += statSrc.nFieldDCTMB;
	nVOPs += statSrc.nVOPs;
	nBitsMV += statSrc.nBitsMV;
	nBitsTexture += statSrc.nBitsTexture;
	nBitsShape += statSrc.nBitsShape;
	nBitsTotal += statSrc.nBitsTotal;
	dSNRY += statSrc.dSNRY;
	dSNRU += statSrc.dSNRU;
	dSNRV += statSrc.dSNRV;
	dSNRA += statSrc.dSNRA;
	nQMB += statSrc.nQMB;
	nQp += statSrc.nQp;
}

Void CStatistics::reset ()
{
	nBitsHead = 0;
	nBitsY = 0;
	nBitsCr = 0;
	nBitsCb = 0;
	nBitsA = 0;
//	nBits1stShpCode = 0;
	nBitsCOD = 0;
	nBitsCBPY = 0;
	nBitsMCBPC = 0;
	nBitsDQUANT = 0;
	nBitsMODB = 0;
	nBitsCBPB = 0;
	nBitsMBTYPE = 0;
	nBitsIntraPred = 0;
	nBitsNoDCT = 0;
	nBitsCODA = 0;
	nBitsCBPA = 0;
	nBitsMODBA = 0;
	nBitsCBPBA = 0;
	nBitsStuffing = 0;
	nSkipMB = 0;
	nInterMB = 0;
	nInter4VMB = 0;
	nIntraMB = 0;
	nDirectMB = 0;
	nForwardMB = 0;
	nBackwardMB = 0;
	nInterpolateMB = 0;
	nBitsInterlace = 0;
	nFieldForwardMB = 0;
	nFieldBackwardMB = 0;
	nFieldInterpolateMB = 0;
	nFieldDirectMB = 0;
	nFieldDCTMB = 0;
	nVOPs = 0;
	nBitsMV = 0;
	nBitsTexture = 0;
	nBitsShape = 0;
	nBitsTotal = 0;
	dSNRY = 0;
	dSNRU = 0;
	dSNRV = 0;
	dSNRA = 0;
	nQMB = 0;
	nQp = 0;
}

CStatistics& CStatistics::operator = (const CStatistics& statSrc)
{
	nBitsHead = statSrc.nBitsHead;
	nBitsY = statSrc.nBitsY;
	nBitsCr = statSrc.nBitsCr;
	nBitsCb = statSrc.nBitsCb;
	nBitsA = statSrc.nBitsA;
//	nBits1stShpCode = statSrc.nBits1stShpCode;
	nBitsCOD = statSrc.nBitsCOD;
	nBitsCBPY = statSrc.nBitsCBPY;
	nBitsMCBPC = statSrc.nBitsMCBPC;
	nBitsDQUANT = statSrc.nBitsDQUANT;
	nBitsMODB = statSrc.nBitsMODB;
	nBitsCBPB = statSrc.nBitsCBPB;
	nBitsMBTYPE = statSrc.nBitsMBTYPE;
	nBitsIntraPred = statSrc.nBitsIntraPred;
	nBitsNoDCT = statSrc.nBitsNoDCT;	
	nBitsCODA = statSrc.nBitsCODA;
	nBitsCBPA = statSrc.nBitsCBPA;
	nBitsMODBA = statSrc.nBitsMODBA;
	nBitsCBPBA = statSrc.nBitsCBPBA;
	nBitsStuffing = statSrc.nBitsStuffing;
	nSkipMB = statSrc.nSkipMB;
	nInterMB = statSrc.nInterMB;
	nInter4VMB = statSrc.nInter4VMB;
	nIntraMB = statSrc.nIntraMB;
	nDirectMB = statSrc.nDirectMB;
	nForwardMB = statSrc.nForwardMB;
	nBackwardMB = statSrc.nBackwardMB;
	nInterpolateMB = statSrc.nInterpolateMB;
	nBitsInterlace = statSrc.nBitsInterlace;
	nFieldForwardMB = statSrc.nFieldForwardMB;
	nFieldBackwardMB = statSrc.nFieldBackwardMB;
	nFieldInterpolateMB = statSrc.nFieldInterpolateMB;
	nFieldDirectMB = statSrc.nFieldDirectMB;
	nFieldDCTMB = statSrc.nFieldDCTMB;
	nVOPs = statSrc.nVOPs;
	nBitsMV = statSrc.nBitsMV;
	nBitsTexture = statSrc.nBitsTexture;
	nBitsShape = statSrc.nBitsShape;
	nBitsTotal = statSrc.nBitsTotal;
	dSNRY = statSrc.dSNRY;
	dSNRU = statSrc.dSNRU;
	dSNRV = statSrc.dSNRV;
	dSNRA = statSrc.dSNRA;
	nQMB = statSrc.nQMB;
	nQp = statSrc.nQp;
	return *this;
}


UInt CStatistics::total ()
{
	nBitsTexture = nBitsY + nBitsCr + nBitsCb + nBitsA + nBitsCOD
					+ nBitsCBPY + nBitsMCBPC + nBitsDQUANT
					+ nBitsMODB + nBitsCBPB	+ nBitsMBTYPE 
					+ nBitsIntraPred + nBitsNoDCT
					+ nBitsInterlace
					+ nBitsCODA + nBitsCBPA + nBitsMODBA + nBitsCBPBA;
	nBitsTotal = nBitsHead + nBitsTexture + nBitsMV + nBitsShape + nBitsStuffing;
	return nBitsTotal;
}

UInt CStatistics::head ()
{
	/*
	UInt bitsHead = nBitsCr + nBitsCb + nBitsA + nBitsCOD
					+ nBitsCBPY + nBitsMCBPC + nBitsDQUANT
					+ nBitsMODB + nBitsCBPB	+ nBitsMBTYPE 
					+ nBitsIntraPred + nBitsNoDCT
					+ nBitsInterlace
					+ nBitsCODA + nBitsCBPA + nBitsMODBA + nBitsCBPBA;
	bitsHead +=  nBitsHead + nBitsMV + nBitsShape + nBitsStuffing;
	*/
	UInt bitsHead = nBitsTotal - nBitsTexture;
	return bitsHead;
}

Void CRCMode::reset (UInt uiFirstFrame, UInt uiLastFrame, UInt uiTemporalRate, 
					   UInt uiBufferSize, Double mad, UInt uiBitsFirstFrame, Double dFrameHz)
{
	m_Ts = (uiLastFrame - uiFirstFrame + 1) / 30.0;
	m_Rs = (UInt) (uiBufferSize / m_Ts);
	m_Ns = uiTemporalRate;
	m_X1 = m_Rs * m_Ns / 2.0;				// 1st order coefficient transient
	m_X2 = 0.0;								// 2nd order coeeficient transient
	m_Nr = (uiLastFrame - uiFirstFrame + 1) / m_Ns - 1;
	m_Nc = 0;
	m_Rf = uiBitsFirstFrame;
	m_Rc = uiBitsFirstFrame;
	m_S = uiBitsFirstFrame;
	m_Qc = 15;
	m_Qp = 15;							// a simple solution (assumption)
	m_Rr = (UInt) (m_Ts * m_Rs) - m_Rf;	// total number of bits available for this segment
	m_Rp = m_Rr / m_Nr;					// average bits to be removed from the buffer
	m_Bs = m_Rs / 2;					// assumed buffer size
	m_B = m_Rs / 4;						// current buffer level	containing the bits for first frame
	for (UInt i = 0; i < RC_MAX_SLIDING_WINDOW; i++) {// if 0, don't use that frame (rejected outliers)
		m_rgQp[i] = 0;
		m_rgRp[i] = 0.0;
	}
	m_Ec = mad; 
	m_skipNextFrame = FALSE;
}

UInt CRCMode::updateQuanStepsize ()
{
	// Target bit calculation 
	m_T = (UInt) max (m_Rs / 30.0, m_Rr / m_Nr * (1.0 - RC_PAST_PERCENT) + m_S * RC_PAST_PERCENT); // a minimum of Rs/30 is assigned to each frame
	m_T = (UInt) (m_T * (m_B + 2.0 * (m_Bs - m_B)) / (2.0 * m_B + (m_Bs - m_B))); // increase if less than half, decrease if more than half, don't change if half
	if ((m_B + m_T) >	(1.0 - RC_SAFETY_MARGIN) * m_Bs)
		m_T = (UInt) max (m_Rs / 30.0, (1.0 - RC_SAFETY_MARGIN) * m_Bs - m_B); // to avoid buffer overflow
	else if ((m_B - m_Rp + m_T) < RC_SAFETY_MARGIN * m_Bs)
		m_T = m_Rp - m_B + (UInt) (RC_SAFETY_MARGIN * m_Bs);			  // to avoid buffer underflow
	m_T = min (m_T, (UInt)m_Rr);	

	// Quantization level calculation
	m_T = max (m_Rp / 3 + m_Hp, m_T);
	Double dtmp = m_Ec * m_X1 * m_Ec * m_X1 + 4 * m_X2 * m_Ec * (m_T - m_Hp);
	if ((m_X2 == 0.0) || (dtmp < 0) || ((sqrt (dtmp) - m_X1 * m_Ec) <= 0.0))	// fall back 1st order mode
		m_Qc = (UInt) (m_X1 * m_Ec / (Double) (m_T - m_Hp));
	else				// 2nd order mode
		m_Qc = (UInt) ((2 * m_X2 * m_Ec) / (sqrt (dtmp) - m_X1 * m_Ec));
	m_Qc = (UInt) min (ceil(m_Qp * (1.0 + RC_MAX_Q_INCREASE)), (Double) m_Qc);	// control variation
	m_Qc = min (m_Qc, RC_MAX_QUANT);						// clipping
	m_Qc = (UInt) max (ceil(m_Qp * (1.0 - RC_MAX_Q_INCREASE)), (Double) m_Qc);	// control variation
	m_Qc = max (m_Qc, RC_MIN_QUANT);						// clipping	
	return m_Qc;
}

Void CRCMode::updateRCModel (UInt uiBitsTotalCurr, UInt uiBitsHeadCurr)
{
	UInt n_windowSize;

	m_Rc = uiBitsTotalCurr;		// total bits used for the current frame 
	m_B += m_Rc - m_Rp;			// update buffer fillness
	m_Rr -= m_Rc;				// update the remaining bits
	if (m_Nr != 1) 
		assert (m_Rr > 0.0);	// check if there is any bits left, except the last frame
	m_S = m_Rc;					// update the previous bits
	m_Hc = uiBitsHeadCurr;		// update the current header and motion bits
	m_Hp = m_Hc;				// update the previous header and motion bits
	m_Qp = m_Qc;				// update the previous qunatization level
	m_Nr--;						// update the frame counter
	m_Nc++;

	Int i;
	for (i = RC_MAX_SLIDING_WINDOW - 1; i > 0; i--) {// update the history
		m_rgQp[i] = m_rgQp[i - 1];
		m_rgRp[i] = m_rgRp[i - 1];
	}
	m_rgQp[0] = m_Qc;
	m_rgRp[0] = (m_Rc - m_Hc) / m_Ec;

	n_windowSize = (m_Ep > m_Ec) ? (UInt) (m_Ec / m_Ep * 20) : (UInt) (m_Ep / m_Ec * 20);
	n_windowSize = max (n_windowSize, 1);
	n_windowSize = min (n_windowSize, m_Nc);
	for (i = 0; i < RC_MAX_SLIDING_WINDOW; i++) {
		m_rgRejected[i] = FALSE;
	}

	// initial RD model estimator
	RCModelEstimator (n_windowSize);

	// remove outlier	
	Double error[20], std = 0.0, threshold;
	for (i = 0; i < (Int) n_windowSize; i++) {
		error[i] = m_X1 / m_rgQp[i] + m_X2 / (m_rgQp[i] * m_rgQp[i]) - m_rgRp[i];
		std += error[i] * error[i];	
	}
	threshold = (n_windowSize == 2) ? 0 : sqrt (std / n_windowSize);
	for (i = 0; i < (Int) n_windowSize; i++) {
		if (fabs(error[i]) > threshold)
			m_rgRejected[i] = TRUE;
	}
    // always include the last data point
	m_rgRejected[0] = FALSE;

	// second RD model estimator
	RCModelEstimator (n_windowSize);
}

Bool CRCMode::skipThisFrame ()
{
	if (m_B > (Int) ((RC_SKIP_MARGIN / 100.0) * m_Bs)) {	// buffer full!
		m_skipNextFrame = TRUE;						// set the status
		m_Nr--;										// skip one frame
		m_B -= m_Rp;								// decrease current buffer level
	} else
		m_skipNextFrame = FALSE;
	return m_skipNextFrame;
}

Void CRCMode::RCModelEstimator (UInt n_windowSize)
{
	UInt n_realSize = n_windowSize;
	UInt i;
	for (i = 0; i < n_windowSize; i++) {// find the number of samples which are not rejected
		if (m_rgRejected[i])
			n_realSize--;
	}

	// default RD model estimation results
	Bool estimateX2 = FALSE;
	m_X1 = m_X2 = 0.0;
	Double oneSampleQ = 0.0;
	for (i = 0; i < n_windowSize; i++)	{
		if (!m_rgRejected[i])
			oneSampleQ = m_rgQp[i];
	}
	for (i = 0; i < n_windowSize; i++)	{// if all non-rejected Q are the same, take 1st order model
		if ((m_rgQp[i] != oneSampleQ) && !m_rgRejected[i])
			estimateX2 = TRUE;
		if (!m_rgRejected[i])
			m_X1 += (m_rgQp[i] * m_rgRp[i]) / n_realSize;
	}

	// take 2nd order model to estimate X1 and X2
	if ((n_realSize >= RC_START_RATE_CONTROL) && estimateX2) {
		Double a00 = 0.0, a01 = 0.0, a10 = 0.0, a11 = 0.0, b0 = 0.0, b1 = 0.0;
		for (UInt i = 0; i < n_windowSize; i++) {
			if (!m_rgRejected[i]) {
				a00 = a00 + 1.0;
				a01 += 1.0 / m_rgQp[i];
				a10 = a01;
				a11 += 1.0 / (m_rgQp[i] * m_rgQp[i]);
				b0 += m_rgQp[i] * m_rgRp[i];
				b1 += m_rgRp[i];
			}
		}
		// solve the equation of AX = B
		CMatrix2x2D A = CMatrix2x2D (a00, a01, a10, a11);
		CMatrix2x2D AInv = A.inverse ();
		CVector2D B = CVector2D (b0, b1);
		CVector2D solution = AInv.apply (B);
		if (solution.x != 0.0) {
			m_X1 = solution.x;
			m_X2 = solution.y;
		}	
	}
}

