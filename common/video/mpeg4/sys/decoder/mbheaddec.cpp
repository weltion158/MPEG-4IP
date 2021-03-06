/*************************************************************************

This software module was originally developed by 

	Wei-ge Chen (wchen@microsoft.com), Microsoft Corporation
	Ming-Chieh Lee (mingcl@microsoft.com), Microsoft Corporation
	Simon Winder (swinder@microsoft.com), Microsoft Corporation
	(date: July, 1997)

and edited by
	Yoshihiro Kikuchi (TOSHIBA CORPORATION)
	Takeshi Nagai (TOSHIBA CORPORATION)
	Toshiaki Watanabe (TOSHIBA CORPORATION)
	Noboru Yamaguchi (TOSHIBA CORPORATION)

and also edited by
	Dick van Smirren (D.vanSmirren@research.kpn.com), KPN Research
	Cor Quist (C.P.Quist@research.kpn.com), KPN Research
	(date: July, 1998)

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

	MBHeadDec.cpp

Abstract:

	MacroBlock overhead decoder

Revision History:

	This software module was edited by

		Hiroyuki Katata (katata@imgsl.mkhar.sharp.co.jp), Sharp Corporation
		Norio Ito (norio@imgsl.mkhar.sharp.co.jp), Sharp Corporation
		Shuichi Watanabe (watanabe@imgsl.mkhar.sharp.co.jp), Sharp Corporation
		(date: October, 1997)

	for object based temporal scalability.
    
	Dec 20, 1997:	Interlaced tools added by NextLevel Systems (GI)
                    X. Chen (xchen@nlvl.com), B. Eifrig (beifrig@nlvl.com)

*************************************************************************/

#include "typeapi.h"
#include "codehead.h"
#include "mode.hpp"
#include "global.hpp"
#include "entropy/bitstrm.hpp"
#include "entropy/entropy.hpp"
#include "entropy/huffman.hpp"
#include "vopses.hpp"
#include "vopsedec.hpp"

#ifdef __MFC_
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW				   
#endif // __MFC_


Void CVideoObjectDecoder::decodeMBTextureHeadOfIVOP (CMBMode* pmbmd, Int& iCurrentQP,
													 Bool &bUseNewQPForVlcThr)
{
	assert (pmbmd->m_rgTranspStatus [0] != ALL);
	Int iBlk = 0, cNonTrnspBlk = 0;
	for (iBlk = (Int) Y_BLOCK1; iBlk <= (Int) Y_BLOCK4; iBlk++) {
		if (pmbmd->m_rgTranspStatus [iBlk] != ALL)	
			cNonTrnspBlk++;
	}
	Int iCBPC = 0;
	Int iCBPY = 0;
	//fprintf(stderr,"[%x]",m_pbitstrmIn->peekBits(32));
	Int iMCBPC = m_pentrdecSet->m_pentrdecMCBPCintra->decodeSymbol ();
	//fprintf(stderr,"MCBPC = %d\n",iMCBPC);
	assert (iMCBPC >= 0 && iMCBPC <= 7);			
	pmbmd->m_dctMd = INTRA;
	pmbmd->m_bSkip = FALSE; //reset for direct mode 
	if (iMCBPC > 3)
		pmbmd->m_dctMd = INTRAQ;
	iCBPC = iMCBPC % 4;

//	pmbmd->m_bACPrediction = m_pbitstrmIn->getBits (1);
    if (!short_video_header) {
		pmbmd->m_bACPrediction = m_pbitstrmIn->getBits(1);
	}

	switch (cNonTrnspBlk) {
	case 1:
		iCBPY = m_pentrdecSet->m_pentrdecCBPY1->decodeSymbol ();
		break;
	case 2:
		iCBPY = m_pentrdecSet->m_pentrdecCBPY2->decodeSymbol ();
		break;
	case 3:
		iCBPY = m_pentrdecSet->m_pentrdecCBPY3->decodeSymbol ();
		break;
	case 4:
		iCBPY = m_pentrdecSet->m_pentrdecCBPY->decodeSymbol ();
		break;
	default:
		assert (FALSE);
	}
	//fprintf(stderr,"CBPY=%d\n",iCBPY);
	setCBPYandC (pmbmd, iCBPC, iCBPY, cNonTrnspBlk);
	pmbmd->m_stepSize = iCurrentQP;
	pmbmd->m_stepSizeDelayed = iCurrentQP;
	if (pmbmd->m_dctMd == INTRAQ)	{
		Int iDQUANT = m_pbitstrmIn->getBits (2);
		switch (iDQUANT) {
		case 0:
			pmbmd->m_intStepDelta = -1;
			break;
		case 1:
			pmbmd->m_intStepDelta = -2;
			break;
		case 2:
			pmbmd->m_intStepDelta = 1;
			break;
		case 3:
			pmbmd->m_intStepDelta = 2;
			break;
		default:
			assert (FALSE);
		}
		pmbmd->m_stepSize += pmbmd->m_intStepDelta;
		if(bUseNewQPForVlcThr)
			pmbmd->m_stepSizeDelayed = pmbmd->m_stepSize;
		Int iQuantMax = (1<<m_volmd.uiQuantPrecision) - 1;
		checkrange (pmbmd->m_stepSize, 1, iQuantMax);
		iCurrentQP = pmbmd->m_stepSize;
	}

	// gets set to true at start of vop / packet header
	bUseNewQPForVlcThr = FALSE; // set to false once we decoded a macroblock

	pmbmd->m_bSkip = FALSE;
	pmbmd->m_bFieldMV = 0;
	if (m_vopmd.bInterlace)
		pmbmd->m_bFieldDCT = m_pbitstrmIn->getBits (1); // get dct_type
}

Void CVideoObjectDecoder::decodeMBAlphaHeadOfIVOP (CMBMode* pmbmd, Int iCurrQP, Int iCurrQPA, Int iVopQP, Int iVopQPA)
{
	// update alpha quantiser
	if(!m_volmd.bNoGrayQuantUpdate)
	{
		iCurrQPA = (iCurrQP * iVopQPA) / iVopQP;
		if(iCurrQPA<1)
			iCurrQPA = 1;
	}
	pmbmd->m_stepSizeAlpha = iCurrQPA;

	assert (pmbmd->m_rgTranspStatus [0] != ALL);

	// coded
	Int iCODA = m_pbitstrmIn->getBits (1);
	pmbmd->m_CODAlpha = iCODA ? ALPHA_ALL255 : ALPHA_CODED;
	if(iCODA)
		return;

	// intra prediction for ac
	pmbmd->m_bACPredictionAlpha = m_pbitstrmIn->getBits (1);

	// decode CBPA
	Int iBlk = 0, cNonTrnspBlk = 0;
	for (iBlk = (Int) Y_BLOCK1; iBlk <= (Int) Y_BLOCK4; iBlk++) {
		if (pmbmd->m_rgTranspStatus [iBlk] != ALL)	
			cNonTrnspBlk++;
	}

	Int iCBPA = 0;
	switch (cNonTrnspBlk) {
	case 1:
		iCBPA = 1 - m_pentrdecSet->m_pentrdecCBPY1->decodeSymbol ();
		break;
	case 2:
		iCBPA = 3 - m_pentrdecSet->m_pentrdecCBPY2->decodeSymbol ();
		break;
	case 3:
		iCBPA = 7 - m_pentrdecSet->m_pentrdecCBPY3->decodeSymbol ();
		break;
	case 4:
		iCBPA = 15 - m_pentrdecSet->m_pentrdecCBPY->decodeSymbol ();
		break;
	default:
		assert (FALSE);
	}

	Int iBitPos = 1;
	for (iBlk = A_BLOCK1; iBlk <= A_BLOCK4; iBlk++)	{
		if (pmbmd->m_rgTranspStatus [iBlk - 6] != ALL)	{
			pmbmd->setCodedBlockPattern (
				(BlockNum) iBlk, 
				(iCBPA >> (cNonTrnspBlk - iBitPos)) & 1
			);
			iBitPos++;
		}
		else
			pmbmd->setCodedBlockPattern ((BlockNum) iBlk, 0);
	}
}

// Inter
Void CVideoObjectDecoder::decodeMBTextureHeadOfPVOP (CMBMode* pmbmd, Int& iCurrentQP,
													 Bool &bUseNewQPForVlcThr)
{
	assert (pmbmd->m_rgTranspStatus [0] != ALL);

	Int iBlk = 0, cNonTrnspBlk = 0;
	for (iBlk = (Int) Y_BLOCK1; iBlk <= (Int) Y_BLOCK4; iBlk++) {
		if (pmbmd->m_rgTranspStatus [iBlk] != ALL)	
			cNonTrnspBlk++;
	}
	Int iCBPC = 0;
	Int iCBPY = 0;
	pmbmd->m_bSkip = m_pbitstrmIn->getBits (1);
	if (!pmbmd->m_bSkip) {
		Int iMCBPC = m_pentrdecSet->m_pentrdecMCBPCinter->decodeSymbol ();
		assert (iMCBPC >= 0 && iMCBPC <= 20);			
		Int iMBtype = iMCBPC / 4; //per H.263's MBtype
		pmbmd -> m_bFieldMV = FALSE;
		switch (iMBtype) {			
		case 0:
			pmbmd->m_dctMd = INTER;
			pmbmd -> m_bhas4MVForward = FALSE;
			break;
		case 1:
			pmbmd->m_dctMd = INTERQ;
			pmbmd -> m_bhas4MVForward = FALSE;
			break;
		case 2:
			pmbmd -> m_dctMd = INTER;
			pmbmd -> m_bhas4MVForward = TRUE;
			break;
		case 3:
			pmbmd->m_dctMd = INTRA;
			break;
		case 4:
			pmbmd->m_dctMd = INTRAQ;
			break;
		default:
			assert (FALSE);
		}
		iCBPC = iMCBPC % 4;
		if (pmbmd->m_dctMd == INTRA || pmbmd->m_dctMd == INTRAQ)	{
			//			pmbmd->m_bACPrediction = m_pbitstrmIn->getBits (1); 
			if (!short_video_header) {  
				pmbmd->m_bACPrediction = m_pbitstrmIn->getBits (1); 
			
			} 
			
			switch (cNonTrnspBlk) {
			case 1:
				iCBPY = m_pentrdecSet->m_pentrdecCBPY1->decodeSymbol ();
				break;
			case 2:
				iCBPY = m_pentrdecSet->m_pentrdecCBPY2->decodeSymbol ();
				break;
			case 3:
				iCBPY = m_pentrdecSet->m_pentrdecCBPY3->decodeSymbol ();
				break;
			case 4:
				iCBPY = m_pentrdecSet->m_pentrdecCBPY->decodeSymbol ();
				break;
			default:
				assert (FALSE);
			}
		}
		else {
			switch (cNonTrnspBlk) {
			case 1:
				iCBPY = 1 - m_pentrdecSet->m_pentrdecCBPY1->decodeSymbol ();
				break;
			case 2:
				iCBPY = 3 - m_pentrdecSet->m_pentrdecCBPY2->decodeSymbol ();
				break;
			case 3:
				iCBPY = 7 - m_pentrdecSet->m_pentrdecCBPY3->decodeSymbol ();
				break;
			case 4:
				iCBPY = 15 - m_pentrdecSet->m_pentrdecCBPY->decodeSymbol ();
				break;
			default:
				assert (FALSE);
			}
		}
		assert (iCBPY >= 0 && iCBPY <= 15);			
	}
	else	{									//skipped
		pmbmd->m_dctMd = INTER;
		pmbmd -> m_bhas4MVForward = FALSE;
		pmbmd -> m_bFieldMV = FALSE;
	}
	setCBPYandC (pmbmd, iCBPC, iCBPY, cNonTrnspBlk);
	pmbmd->m_stepSize = iCurrentQP;
	pmbmd->m_stepSizeDelayed = iCurrentQP;
	if (pmbmd->m_dctMd == INTERQ || pmbmd->m_dctMd == INTRAQ) {
		assert (!pmbmd->m_bSkip);
		Int iDQUANT = m_pbitstrmIn->getBits (2);
		switch (iDQUANT) {
		case 0:
			pmbmd->m_intStepDelta = -1;
			break;
		case 1:
			pmbmd->m_intStepDelta = -2;
			break;
		case 2:
			pmbmd->m_intStepDelta = 1;
			break;
		case 3:
			pmbmd->m_intStepDelta = 2;
			break;
		default:
			assert (FALSE);
		}
		pmbmd->m_stepSize += pmbmd->m_intStepDelta;
		if(bUseNewQPForVlcThr) // need to prevent delay of quantiser
			pmbmd->m_stepSizeDelayed = pmbmd->m_stepSize;

		Int iQuantMax = (1<<m_volmd.uiQuantPrecision) - 1;
		checkrange (pmbmd->m_stepSize, 1, iQuantMax);
		iCurrentQP = pmbmd->m_stepSize;
	}

	if(!pmbmd->m_bSkip)
	{
		// gets set to true at start of vop / packet header
		bUseNewQPForVlcThr = FALSE; // set to false once we decoded a non-skipped macroblock
	}

// INTERLACE
	if (m_vopmd.bInterlace && !pmbmd->m_bSkip) {
		if ((pmbmd->m_dctMd == INTRA) || (pmbmd->m_dctMd == INTRAQ) || (iCBPY || iCBPC)) 
			pmbmd->m_bFieldDCT = m_pbitstrmIn->getBits (1); // get dct_type
		else
			pmbmd->m_bFieldDCT = FALSE;
		if (((pmbmd->m_dctMd == INTERQ) || (pmbmd->m_dctMd == INTER)) && (pmbmd -> m_bhas4MVForward == FALSE)) {
			pmbmd->m_bFieldMV = m_pbitstrmIn->getBits (1); // get field_prediction
			if (pmbmd->m_bFieldMV == TRUE) {
				pmbmd->m_bForwardTop = m_pbitstrmIn->getBits (1); // get top field reference
				pmbmd->m_bForwardBottom = m_pbitstrmIn->getBits (1); // get bottom field reference
			}
		}
	}
// ~INTERLACE
}

// B-VOP
Void CVideoObjectDecoder::decodeMBTextureHeadOfBVOP (CMBMode* pmbmd, Int& iCurrQP)
{
	assert (pmbmd -> m_rgTranspStatus [0] != ALL);
	pmbmd -> m_bhas4MVForward = pmbmd -> m_bhas4MVBackward = FALSE;
	Int iBlk = 0, cNonTrnspBlk = 0;
	for (iBlk = (Int) Y_BLOCK1; iBlk <= (Int) Y_BLOCK4; iBlk++) {
		if (pmbmd->m_rgTranspStatus [iBlk] != ALL)	
			cNonTrnspBlk++;
	}
	Int iMODB = 0;
	//Int iMCBPC = 0;
	Int iCBPC = 0;
	Int iCBPY = 0;
	Int iMbType = -1, uiCBPB = 0;
	if (m_pbitstrmIn->getBits (1) == 1)	 {					//MODB=1 colocated non-skip but curr skip
		pmbmd->m_bSkip = TRUE;  
		iMODB = 0;
		pmbmd->m_mbType = (!(m_volmd.volType == ENHN_LAYER && m_vopmd.iRefSelectCode == 0))? DIRECT : FORWARD;
		pmbmd->m_dctMd = INTER;
		if(m_volmd.volType == ENHN_LAYER && m_vopmd.iRefSelectCode == 0)
			return;
	}
	else if (m_pbitstrmIn->getBits (1) == 1)	{	//MODB="01"
		pmbmd->m_bSkip = FALSE;
		if (m_volmd.volType == BASE_LAYER || (m_volmd.volType == ENHN_LAYER && m_vopmd.iRefSelectCode != 0))
			iMbType = m_pentrdecSet->m_pentrdecMbTypeBVOP->decodeSymbol ();
		else	{
			if (m_pbitstrmIn->getBits (1) == 1)	
				iMbType = FORWARD;
			else if (m_pbitstrmIn->getBits (1) == 1)	
				iMbType = INTERPOLATE;
			else if (m_pbitstrmIn->getBits (1) == 1)
				iMbType = BACKWARD;
			else {
				fprintf(stderr,"MB Type 0000 does not exsit.\n");
				exit(2);
			}
		}
		assert (iMbType >= 0 && iMbType <= 3);
		pmbmd->m_mbType = (MBType) iMbType;
		iMODB = 1;
	}												//MODB="00"
	else {
		pmbmd->m_bSkip = FALSE;
		if (m_volmd.volType == BASE_LAYER || (m_volmd.volType == ENHN_LAYER && m_vopmd.iRefSelectCode != 0))
			iMbType = m_pentrdecSet->m_pentrdecMbTypeBVOP->decodeSymbol ();
		else	{
			if (m_pbitstrmIn->getBits (1) == 1)	
				iMbType = FORWARD;
			else if (m_pbitstrmIn->getBits (1) == 1)	
				iMbType = INTERPOLATE;
			else if (m_pbitstrmIn->getBits (1) == 1)
				iMbType = BACKWARD;
			else{
				fprintf(stderr,"MB Type 0000 is not exsit.\n");
				exit(2);
			}
		}
		assert (iMbType >= 0 && iMbType <= 3);
		pmbmd->m_mbType = (MBType) iMbType;		
		iMODB = 2;
		uiCBPB = m_pbitstrmIn->getBits (cNonTrnspBlk + 2);
		pmbmd->m_bhas4MVForward = pmbmd->m_bhas4MVBackward = FALSE;	//this is okay; will be reset later
									//Only one mv for B-VOP except direct mode (will be reset in mvdec.cpp)
		iCBPC = uiCBPB & 0x0003;
		iCBPY = (uiCBPB >> 2) & 0x000F;
		pmbmd->m_stepSize = iCurrQP;
		if (pmbmd->m_mbType != DIRECT)	{
			Int DQUANT;
			if (m_pbitstrmIn->getBits (1) == 0)
				DQUANT = 0;
			else if (m_pbitstrmIn->getBits (1) == 0)
				DQUANT = -2;
			else
				DQUANT = 2;
			pmbmd->m_intStepDelta = DQUANT;
			pmbmd->m_stepSize += pmbmd->m_intStepDelta;
			Int iQuantMax = (1<<m_volmd.uiQuantPrecision) - 1;
            pmbmd->m_stepSize = checkrange (pmbmd->m_stepSize, 1, iQuantMax); 
			iCurrQP = pmbmd->m_stepSize;
		}
	}
	setCBPYandC (pmbmd, iCBPC, iCBPY, cNonTrnspBlk);

	if (pmbmd->m_mbType == DIRECT)
		pmbmd->m_dctMd = INTER;		//direct mode doesn't have dquant
	else	
		pmbmd->m_dctMd = INTERQ;		//meaningless in B_VOP 'cause DQUANT is always sent
// INTERLACE
	pmbmd->m_bFieldDCT = FALSE;
	pmbmd->m_bFieldMV = FALSE;
	if (m_vopmd.bInterlace) {
		if (uiCBPB != 0)
			pmbmd->m_bFieldDCT = m_pbitstrmIn->getBits (1); // get dct_type
		if (pmbmd->m_mbType != DIRECT) {
			pmbmd->m_bFieldMV = m_pbitstrmIn->getBits (1);
			if (pmbmd->m_bFieldMV) {
				if (pmbmd->m_mbType != BACKWARD) {
					pmbmd->m_bForwardTop = m_pbitstrmIn->getBits (1);
					pmbmd->m_bForwardBottom = m_pbitstrmIn->getBits (1);
				}
				if (pmbmd->m_mbType != FORWARD) {
					pmbmd->m_bBackwardTop = m_pbitstrmIn->getBits (1);
					pmbmd->m_bBackwardBottom = m_pbitstrmIn->getBits (1);
				}
			}
		}
	}
// ~INTERLACE
}

Void CVideoObjectDecoder::decodeMBAlphaHeadOfPVOP (CMBMode* pmbmd, Int iCurrQP, Int iCurrQPA)
{
	if(pmbmd->m_dctMd == INTRA || pmbmd->m_dctMd == INTRAQ)
	{
		decodeMBAlphaHeadOfIVOP(pmbmd, iCurrQP, iCurrQPA, m_vopmd.intStep, m_vopmd.intStepPAlpha);
	}
	else
	{
		// update alpha quantiser
		if(!m_volmd.bNoGrayQuantUpdate)
		{
			iCurrQPA = (iCurrQP * m_vopmd.intStepPAlpha) / m_vopmd.intStep;
			if(iCurrQPA<1)
				iCurrQPA = 1;
		}
		pmbmd->m_stepSizeAlpha = iCurrQPA;

		assert (pmbmd->m_rgTranspStatus [0] != ALL);

		if(m_pbitstrmIn->getBits (1) == 0)	 {
			if(m_pbitstrmIn->getBits (1) == 0)
				pmbmd->m_CODAlpha = ALPHA_CODED;
			else
				pmbmd->m_CODAlpha = ALPHA_ALL255;
		}
		else
			pmbmd->m_CODAlpha = ALPHA_SKIPPED;

		if(pmbmd->m_CODAlpha!=ALPHA_CODED)
			return;

		Int iBlk = 0, cNonTrnspBlk = 0;
		for (iBlk = (Int) Y_BLOCK1; iBlk <= (Int) Y_BLOCK4; iBlk++) {
			if (pmbmd->m_rgTranspStatus [iBlk] != ALL)	
				cNonTrnspBlk++;
		}

		Int iCBPA = 0;
		switch (cNonTrnspBlk) {
		case 1:
			iCBPA = 1 - m_pentrdecSet->m_pentrdecCBPY1->decodeSymbol ();
			break;
		case 2:
			iCBPA = 3 - m_pentrdecSet->m_pentrdecCBPY2->decodeSymbol ();
			break;
		case 3:
			iCBPA = 7 - m_pentrdecSet->m_pentrdecCBPY3->decodeSymbol ();
			break;
		case 4:
			iCBPA = 15 - m_pentrdecSet->m_pentrdecCBPY->decodeSymbol ();
			break;
		default:
			assert (FALSE);
		}

		Int iBitPos = 1;
		for (iBlk = A_BLOCK1; iBlk <= A_BLOCK4; iBlk++)	{
			if (pmbmd->m_rgTranspStatus [iBlk - 6] != ALL)	{
				pmbmd->setCodedBlockPattern (
					(BlockNum) iBlk, 
					(iCBPA >> (cNonTrnspBlk - iBitPos)) & 1
				);
				iBitPos++;
			}
			else
				pmbmd->setCodedBlockPattern ((BlockNum) iBlk, 0);
		}
	}
}

Void CVideoObjectDecoder::decodeMBAlphaHeadOfBVOP (CMBMode* pmbmd, Int iCurrQP, Int iCurrQPA)
{
	// update alpha quantiser
	if(!m_volmd.bNoGrayQuantUpdate)
	{
		iCurrQPA = (iCurrQP * m_vopmd.intStepBAlpha) / m_vopmd.intStepB;
		if(iCurrQPA<1)
			iCurrQPA = 1;
	}
	pmbmd->m_stepSizeAlpha = iCurrQPA;

	assert (pmbmd->m_rgTranspStatus [0] != ALL);

	if(m_pbitstrmIn->getBits (1) == 0)	 {
		if(m_pbitstrmIn->getBits (1) == 0)
			pmbmd->m_CODAlpha = ALPHA_CODED;
		else
			pmbmd->m_CODAlpha = ALPHA_ALL255;
	}
	else
		pmbmd->m_CODAlpha = ALPHA_SKIPPED;

	if(pmbmd->m_CODAlpha!=ALPHA_CODED)
		return;

	Int iBlk = 0, cNonTrnspBlk = 0;
	for (iBlk = (Int) Y_BLOCK1; iBlk <= (Int) Y_BLOCK4; iBlk++) {
		if (pmbmd->m_rgTranspStatus [iBlk] != ALL)	
			cNonTrnspBlk++;
	}

	Int iCBPA = 0;
	switch (cNonTrnspBlk) {
	case 1:
		iCBPA = 1 - m_pentrdecSet->m_pentrdecCBPY1->decodeSymbol ();
		break;
	case 2:
		iCBPA = 3 - m_pentrdecSet->m_pentrdecCBPY2->decodeSymbol ();
		break;
	case 3:
		iCBPA = 7 - m_pentrdecSet->m_pentrdecCBPY3->decodeSymbol ();
		break;
	case 4:
		iCBPA = 15 - m_pentrdecSet->m_pentrdecCBPY->decodeSymbol ();
		break;
	default:
		assert (FALSE);
	}

	Int iBitPos = 1;
	for (iBlk = A_BLOCK1; iBlk <= A_BLOCK4; iBlk++)	{
		if (pmbmd->m_rgTranspStatus [iBlk - 6] != ALL)	{
			pmbmd->setCodedBlockPattern (
				(BlockNum) iBlk, 
				(iCBPA >> (cNonTrnspBlk - iBitPos)) & 1
			);
			iBitPos++;
		}
		else
			pmbmd->setCodedBlockPattern ((BlockNum) iBlk, 0);
	}
}



