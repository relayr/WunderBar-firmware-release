/********************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
 *
 * @file flash_FTFE.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file includes flash routines
 *
 *****************************************************************************/

/*********************************** Includes ***********************************/
#include "flash_FTFE.h" /* include flash driver header file */
#include "MK24F12.h"
#include "string.h"
/*********************************** Macros ************************************/

/*********************************** Defines ***********************************/
#define PROG_WORD_SIZE 30       /* adequate space for the small program */

/********************************** Constant ***********************************/

/*********************************** Variables *********************************/

/*********************************** Prototype *********************************/

/*********************************** Function **********************************/
static void SpSub(void);
static void SpSubEnd(void);


/*******************************************************************************
 * Function:        Flash_Init
 *
 * Description:     Set the flash clock
 *
 * Returns:         never return
 *
 * Notes:
 *
 *******************************************************************************/
void Flash_Init(int a)
{
    /* checking access error */
    if (FTFE_FSTAT & FTFE_FSTAT_ACCERR_MASK)
    {
        /* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_ACCERR_MASK;
    }
    /* checking protection error */
    else if (FTFE_FSTAT & FTFE_FSTAT_FPVIOL_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_FPVIOL_MASK;
    }
    else if (FTFE_FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
     {
        	/* clear error flag */
        	FTFE_FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;
     }
    /* Disable Data Cache in Flash memory Controller Module  */
#if (defined (__MK_xxx_H__))
    FMC_PFB0CR &= ~FMC_PFB0CR_B0DCE_MASK;
    FMC_PFB1CR &= ~FMC_PFB1CR_B1DCE_MASK;
#endif
}


/*******************************************************************************
 * Function:        Flash_SectorErase
 *
 * Description:     erase a sector of the flash
 *
 * Returns:         Error Code
 *
 * Notes:
 *
 *******************************************************************************/
 unsigned char Flash_SectorErase(uint_32 FlashPtr)
{
    unsigned char Return = Flash_OK;
  
    /* copy code to stack */
    static void (*fnRAM_code)(void) = 0;
    int i = 0;
    unsigned char *ptrThumb2 = (unsigned char *)SpSub;
    static unsigned short usProgSpace[PROG_WORD_SIZE];               /*  make space for the routine on stack (this will have an even boundary) */

    ptrThumb2 =  (unsigned char *)(((unsigned long)ptrThumb2) & ~0x1);  /* thumb 2 address */
    while (i < PROG_WORD_SIZE) {                                     /* copy program to SRAM */
        usProgSpace[i++] = *(unsigned short *)ptrThumb2;
        ptrThumb2 += sizeof (usProgSpace[0]);
    }
    ptrThumb2 = (unsigned char *)usProgSpace;
    ptrThumb2++;                                                     /* create a thumb 2 call */
    fnRAM_code = (void(*)(void))(ptrThumb2);

    /* Allocate space on stack to run flash command out of SRAM */
    /* wait till CCIF is set*/
    while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)){};
    /* Write command to FCCOB registers */
    FTFE_FCCOB0 = FlashCmd_SectorErase;
    FTFE_FCCOB1 = (uint_8)(FlashPtr >> 16);
    FTFE_FCCOB2 = (uint_8)((FlashPtr >> 8) & 0xFF);
    FTFE_FCCOB3 = (uint_8)(FlashPtr & 0xFF);

    // fnRAM_code();
    /* Launch command */
    FTFE_FSTAT |= FTFE_FSTAT_CCIF_MASK;
    /* wait for command completion */
    while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)) {};

    /* checking access error */
    if (FTFE_FSTAT & FTFE_FSTAT_ACCERR_MASK)
    {
        /* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_ACCERR_MASK;

        /* update return value*/
        Return |= Flash_FACCERR;
    }
    /* checking protection error */
    else if (FTFE_FSTAT & FTFE_FSTAT_FPVIOL_MASK)
    {
    	/* clear error flag */
    	FTFE_FSTAT |= FTFE_FSTAT_FPVIOL_MASK;

        /* update return value*/
        Return |= Flash_FPVIOL;
    }
    else if (FTFE_FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
    {
       	/* clear error flag */
       	FTFE_FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;

           /* update return value*/
           Return |= Flash_RDCOLERR;
    }
    /* checking MGSTAT0 non-correctable error */
    else if (FTFE_FSTAT & FTFE_FSTAT_MGSTAT0_MASK)
    {
    	Return |= Flash_MGSTAT0;
    }
    /* function return */
    return  Return;
}


/*******************************************************************************
 * Function:        Flash_ByteProgram
 *
 * Description:     byte program the flash
 *
 * Returns:         Error Code
 *
 * Notes:
 *
 *******************************************************************************/
unsigned char Flash_ByteProgram(uint_32 FlashStartAdd,uint_32 *DataSrcPtr,uint_32 NumberOfBytes)
{
    unsigned char Return = Flash_OK;
    uint_32 size_buffer;
 
    static void (*fnRAM_code)(void) = 0;
    int i = 0;
    unsigned char *ptrThumb2 = (unsigned char *)SpSub;
    static unsigned short usProgSpace[PROG_WORD_SIZE];               /*  make space for the routine on stack (this will have an even boundary) */

    ptrThumb2 =  (unsigned char *)(((unsigned long)ptrThumb2) & ~0x1);  /* thumb 2 address */
    while (i < PROG_WORD_SIZE) {                                     /* copy program to SRAM */
        usProgSpace[i++] = *(unsigned short *)ptrThumb2;
        ptrThumb2 += sizeof (usProgSpace[0]);
    }
    ptrThumb2 = (unsigned char *)usProgSpace;
    ptrThumb2++;                                                     /* create a thumb 2 call */
    fnRAM_code = (void(*)(void))(ptrThumb2);

    if (NumberOfBytes == 0)
    {
    	return Flash_CONTENTERR;
    }
    else
    {
    	size_buffer = (NumberOfBytes - 1)/8 + 1;	
    }
    /* wait till CCIF is set*/
    while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)){};
        
	while ((size_buffer) && (Return == Flash_OK))
	{
		/* Write command to FCCOB registers */
		FTFE_FCCOB0 = FlashCmd_ProgramPhrase;
		FTFE_FCCOB1 = (uint_8)(FlashStartAdd >> 16);
		FTFE_FCCOB2 = (uint_8)((FlashStartAdd >> 8) & 0xFF);
		FTFE_FCCOB3 = (uint_8)(FlashStartAdd & 0xFF);
		FTFE_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+3));
		FTFE_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		FTFE_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		FTFE_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+0));
		FTFE_FCCOB8 = (uint_8)(*((uint_8*)DataSrcPtr+7));
		FTFE_FCCOB9 = (uint_8)(*((uint_8*)DataSrcPtr+6));
		FTFE_FCCOBA = (uint_8)(*((uint_8*)DataSrcPtr+5));
		FTFE_FCCOBB = (uint_8)(*((uint_8*)DataSrcPtr+4));

		// #ifdef __MK_xxx_H__ /*little endian*/
		// 		FTFE_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+3));
		// FTFE_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		// FTFE_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		// FTFE_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+0));
		// #else /* Big endian */
		// 		
		// FTFE_FCCOB4 = (uint_8)(*((uint_8*)DataSrcPtr+0));
		// FTFE_FCCOB5 = (uint_8)(*((uint_8*)DataSrcPtr+1));
		// FTFE_FCCOB6 = (uint_8)(*((uint_8*)DataSrcPtr+2));
		// FTFE_FCCOB7 = (uint_8)(*((uint_8*)DataSrcPtr+3));
		// #endif		
		/* Launch command */
        fnRAM_code();

        /* checking access error */
	    if (FTFE_FSTAT & FTFE_FSTAT_ACCERR_MASK)
	    {
	        /* clear error flag */
	    	FTFE_FSTAT |= FTFE_FSTAT_ACCERR_MASK;

	        /* update return value*/
	        Return |= Flash_FACCERR;
	        }
	    /* checking protection error */
	    else if (FTFE_FSTAT & FTFE_FSTAT_FPVIOL_MASK)
	    {
	    	/* clear error flag */
	    	FTFE_FSTAT |= FTFE_FSTAT_FPVIOL_MASK;

	        /* update return value*/
	        Return |= Flash_FPVIOL;
	    }
	    else if (FTFE_FSTAT & FTFE_FSTAT_RDCOLERR_MASK)
	     {
	        	/* clear error flag */
	        	FTFE_FSTAT |= FTFE_FSTAT_RDCOLERR_MASK;

	            /* update return value*/
	            Return |= Flash_RDCOLERR;
	     }
	    /* checking MGSTAT0 non-correctable error */
	    else if (FTFE_FSTAT & FTFE_FSTAT_MGSTAT0_MASK)
	    {
	    	Return |= Flash_MGSTAT0;
	    }
		/* decrement byte count */
		 size_buffer--;
		 DataSrcPtr += 2;
		 FlashStartAdd +=8;
		 
	}
    /* function return */
    return  Return;
}

/*******************************************************************************
 * Function:        SpSub
 *
 * Description:     Execute the Flash write while running out of SRAM
 *
 * Returns:
 *
 * Notes:
 *
 *******************************************************************************/
static void SpSub(void)
    {
        /* Launch command */
        FTFE_FSTAT |= FTFE_FSTAT_CCIF_MASK;    
        /* wait for command completion */
        while (!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK)) {};
    }

/* Leave this immediately after SpSub */
static void SpSubEnd(void) {}


