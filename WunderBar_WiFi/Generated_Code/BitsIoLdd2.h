/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : BitsIoLdd2.h
**     Project     : WunderBar_WiFi
**     Processor   : MK24FN1M0VLQ12
**     Component   : BitsIO_LDD
**     Version     : Component 01.029, Driver 01.05, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-05-17, 14:28, # CodeGen: 27
**     Abstract    :
**         The HAL BitsIO component provides a low level API for unified
**         access to general purpose digital input/output 32 pins across
**         various device designs.
**
**         RTOS drivers using HAL BitsIO API are simpler and more
**         portable to various microprocessors.
**     Settings    :
**          Component name                                 : BitsIoLdd2
**          Port                                           : PTA
**          Pins                                           : 1
**            Pin0                                         : 
**              Pin                                        : PTA14/SPI0_PCS0/UART0_TX/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1
**              Pin signal                                 : 
**          Direction                                      : Output
**          Initialization                                 : 
**            Init. direction                              : Output
**            Init. value                                  : 1
**            Auto initialization                          : yes
**          Safe mode                                      : yes
**     Contents    :
**         Init   - LDD_TDeviceData* BitsIoLdd2_Init(LDD_TUserData *UserDataPtr);
**         GetDir - bool BitsIoLdd2_GetDir(LDD_TDeviceData *DeviceDataPtr);
**         GetVal - uint32_t BitsIoLdd2_GetVal(LDD_TDeviceData *DeviceDataPtr);
**         PutVal - void BitsIoLdd2_PutVal(LDD_TDeviceData *DeviceDataPtr, uint32_t Val);
**         GetBit - LDD_TError BitsIoLdd2_GetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit,...
**         PutBit - LDD_TError BitsIoLdd2_PutBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit,...
**         SetBit - LDD_TError BitsIoLdd2_SetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);
**         ClrBit - LDD_TError BitsIoLdd2_ClrBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);
**         NegBit - LDD_TError BitsIoLdd2_NegBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);
**
**     (c) 2012 by Freescale
** ###################################################################*/
/*!
** @file BitsIoLdd2.h
** @version 01.05
** @brief
**         The HAL BitsIO component provides a low level API for unified
**         access to general purpose digital input/output 32 pins across
**         various device designs.
**
**         RTOS drivers using HAL BitsIO API are simpler and more
**         portable to various microprocessors.
*/         
/*!
**  @addtogroup BitsIoLdd2_module BitsIoLdd2 module documentation
**  @{
*/         

#ifndef __BitsIoLdd2_H
#define __BitsIoLdd2_H

/* MODULE BitsIoLdd2. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "IO_Map.h"
#include "GPIO_PDD.h"

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif 



/*! Peripheral base address of a device allocated by the component. This constant can be used directly in PDD macros. */
#define BitsIoLdd2_PRPH_BASE_ADDRESS  0x400FF000U
  
/*! Device data structure pointer used when auto initialization property is enabled. This constant can be passed as a first parameter to all component's methods. */
#define BitsIoLdd2_DeviceData  ((LDD_TDeviceData *)PE_LDD_GetDeviceStructure(PE_LDD_COMPONENT_BitsIoLdd2_ID))

/* Methods configuration constants - generated for all enabled component's methods */
#define BitsIoLdd2_Init_METHOD_ENABLED /*!< Init method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_GetDir_METHOD_ENABLED /*!< GetDir method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_GetVal_METHOD_ENABLED /*!< GetVal method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_PutVal_METHOD_ENABLED /*!< PutVal method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_GetBit_METHOD_ENABLED /*!< GetBit method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_PutBit_METHOD_ENABLED /*!< PutBit method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_SetBit_METHOD_ENABLED /*!< SetBit method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_ClrBit_METHOD_ENABLED /*!< ClrBit method of the component BitsIoLdd2 is enabled (generated) */
#define BitsIoLdd2_NegBit_METHOD_ENABLED /*!< NegBit method of the component BitsIoLdd2 is enabled (generated) */

/* Definition of implementation constants */
#define BitsIoLdd2_MODULE_BASE_ADDRESS PTA_BASE_PTR /*!< Name of macro used as the base address */
#define BitsIoLdd2_PORTCONTROL_BASE_ADDRESS PORTA_BASE_PTR /*!< Name of macro used as the base address */
#define BitsIoLdd2_PORT_MASK 0x4000U   /*!< Mask of the allocated pin from the port */
#define BitsIoLdd2_PORT_VALID_VALUE_MASK 0x01 /*!< Mask of the allocated pins from the port as the first pin would be zero i.e. valid bits to be set in method PutVal */
#define BitsIoLdd2_PIN_ALLOC_0_MASK 0x4000 /*!< Mask of the first allocated pin from the port */
#define BitsIoLdd2_PIN_ALLOC_0_INDEX 14U /*!< The index of the first allocated pin from the port */



/*
** ===================================================================
**     Method      :  BitsIoLdd2_Init (component BitsIO_LDD)
*/
/*!
**     @brief
**         This method initializes the associated peripheral(s) and the
**         component internal variables. The method is called
**         automatically as a part of the application initialization
**         code.
**     @param
**         UserDataPtr     - Pointer to the RTOS device
**                           structure. This pointer will be passed to
**                           all events as parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* BitsIoLdd2_Init(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_GetDir (component BitsIO_LDD)
*/
/*!
**     @brief
**         Returns the selected direction.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Possible values:
**                           [false] - Input
**                           [true] - Output
*/
/* ===================================================================*/
bool BitsIoLdd2_GetDir(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_GetVal (component BitsIO_LDD)
*/
/*!
**     @brief
**         Returns the value of the Input/Output component. If the
**         direction is [input] then reads the input value of the pins
**         and returns it. If the direction is [output] then returns
**         the last written value (see [Safe mode] property for
**         limitations).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Input value
*/
/* ===================================================================*/
uint32_t BitsIoLdd2_GetVal(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_PutVal (component BitsIO_LDD)
*/
/*!
**     @brief
**         Specified value is passed to the Input/Output component. If
**         the direction is [input] saves the value to a memory or a
**         register, this value will be written to the pins after
**         switching to the output mode - using [SetDir(TRUE)] (see
**         [Safe mode] property for limitations). If the direction is
**         [output] it writes the value to the pins. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Val             - Output value
*/
/* ===================================================================*/
void BitsIoLdd2_PutVal(LDD_TDeviceData *DeviceDataPtr, uint32_t Val);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_GetBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Returns the value of the specified bit/pin of the
**         Input/Output component. If the direction is [input] then it
**         reads the input value of the pin and returns it. If the
**         direction is [output] then it returns the last written value
**         (see [Safe mode] property for limitations).
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         Bit             - Bit/pin number to read
**     @param
**         BitVal          - The returned value: 
**                           [false] - logical "0" (Low level)
**                           [true] - logical "1" (High level)
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
**                           ERR_PARAM_VALUE - Invalid output parameter
*/
/* ===================================================================*/
LDD_TError BitsIoLdd2_GetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit, bool *BitVal);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_PutBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Specified value is passed to the specified bit/pin of the
**         Input/Output component. If the direction is [input] it saves
**         the value to a memory or register, this value will be
**         written to the pin after switching to the output mode -
**         using [SetDir(TRUE)] (see [Safe mode] property for
**         limitations). If the direction is [output] it writes the
**         value to the pin. (Method is available only if the Direction
**         = _[output]_ or _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number
**     @param
**         Val             - A new bit value. Possible values:
**                           [false] - logical "0" (Low level)
**                           [true] - logical "1" (High level)
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd2_PutBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit, bool Val);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_SetBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Sets (to one) the specified bit of the Input/Output
**         component. It is the same as [PutBit(Bit, TRUE)]. (Method is
**         available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number to set
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd2_SetBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_ClrBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Clears (sets to zero) the specified bit of the Input/Output
**         component. It is the same as [PutBit(Bit, FALSE)]. (Method
**         is available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number to clear
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd2_ClrBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);

/*
** ===================================================================
**     Method      :  BitsIoLdd2_NegBit (component BitsIO_LDD)
*/
/*!
**     @brief
**         Negates (inverts) the specified bit of the Input/Output
**         component. It is the same as [PutBit(Bit,!GetBit(Bit))].
**         (Method is available only if the Direction = _[output]_ or
**         _[input/output]_).
**     @param
**         DeviceDataPtr   - Pointer to device data
**                           structure pointer.
**     @param
**         Bit             - Bit/pin number to invert
**     @return
**                         - Error code, possible values:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - Invalid pin index
*/
/* ===================================================================*/
LDD_TError BitsIoLdd2_NegBit(LDD_TDeviceData *DeviceDataPtr, uint8_t Bit);

/* END BitsIoLdd2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif
/* ifndef __BitsIoLdd2_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/