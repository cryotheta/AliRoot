#ifndef ALIEMCALDigitizer_H
#define ALIEMCALDigitizer_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//_________________________________________________________________________
//  Task Class for making Digits in EMCAL      
//                  
//*-- Author: Sahal Yacoob (LBL)
// based on : AliPHOSDigit
//_________________________________________________________________________ 


// --- ROOT system ---

#include "TObjString.h"
class TArrayI ;
// --- Standard library ---

// --- AliRoot header files ---
class AliEMCALSDigitizer ;
#include "AliRunDigitizer.h"
#include "AliDigitizer.h"


class AliEMCALDigitizer: public AliDigitizer {

public:
  AliEMCALDigitizer() ;          // ctor
  AliEMCALDigitizer(const char *headerFile,const char * sDigitsBranchTitle = "Default") ; 
  AliEMCALDigitizer(AliRunDigitizer * ard) ;
  AliEMCALDigitizer(const AliEMCALDigitizer & dtizer) 
                  {( (AliEMCALDigitizer &)dtizer ).Copy(*this) ;} 
  virtual ~AliEMCALDigitizer() ;       

  void    Digitize(const Int_t);            // Make Digits from SDigits stored in fSDigits
  void    Exec(Option_t *option);                // Supervising method

  const Float_t GetEMCThreshold() const { return fEMCDigitThreshold;}
  const Float_t GetPedestal()     const { return fPedestal; }
  const Float_t GetPinNoise()     const { return fPinNoise;}
  const Float_t GetSlope()        const { return fSlope; }
  const Float_t GetTimeResolution() const { return fTimeResolution ; }
  const Float_t GetTowerchannel() const { return fADCchannelTower ; }
  const Float_t GetTowerpedestal() const { return fADCpedestalTower ; }
  const Float_t GetPreShochannel() const { return fADCchannelPreSho ; }
  const Float_t GetPreShopedestal() const { return fADCpedestalPreSho ; }

  void    MixWith(char* HeaderFile) ; // Add another one file to mix
  virtual void    Print(Option_t* option)const ;
  void    Reset() ;   //restarts starts event processing from 0 event(s)
  const Int_t   GetDigitsInRun()  const { return fDigitsInRun; } ;
  void    SetEMCThreshold(Float_t EMCThreshold)  {fEMCDigitThreshold = EMCThreshold;}
  void    SetPinNoise(Float_t PinNoise )         {fPinNoise = PinNoise;}

  void    SetSDigitsBranch(const char* file) ;
 

 AliEMCALDigitizer & operator = (const AliEMCALDigitizer & rvalue)  {
    // assignement operator requested by coding convention but not needed
    abort() ;
    return *this ; 
  }


private:

  Bool_t  Init();                   
  Bool_t  ReadSDigits() ;            // Read sdigits for particular events
  void    WriteDigits(Int_t evt) ;            // Writes Digits for particular event
  void    PrintDigits(Option_t * option) ;
  Float_t TimeOfNoise(void) ;                 // Calculate time signal generated by noise
  Float_t FrontEdgeTime(TClonesArray * ticks) ;
  Int_t   DigitizeEnergy(Float_t energy, Int_t absId) ;

private:
  
  AliEMCALSDigitizer * fSDigitizer ; // ! SDigitizer to extract some sdigitizing parameters
  Int_t   fNinputs ;                // Number of input files
  Bool_t  fInitialized ;            // 
 
  Int_t fDigitsInRun ;              //! Total number of digits in one run
  Float_t fPedestal ;                // Calibration parameters 
  Float_t fSlope ;                   // read from SDigitizer

  Float_t fPinNoise ;               // Electronics noise in EMC
  Float_t fEMCDigitThreshold  ;     // Threshold for storing digits in EMC
  Float_t fPreShowerDigitThreshold ; // Threshold for Preshower digits

  Float_t fTimeResolution ;         // Time resolution of FEE electronics
  Float_t fTimeThreshold ;          // Threshold to start timing for given crystall
  Float_t fTimeSignalLength ;       // Length of the timing signal 

  Float_t fADCchannelTower ;           // width of one ADC channel in Tower (GeV)
  Float_t fADCpedestalTower ;         //
  Int_t fNADCTower ;                // number of channels in Tower ADC

  Float_t fADCchannelPreSho ;           // width of one ADC channel in Pre Shower (GeV)
  Float_t fADCpedestalPreSho ;                   // 
  Int_t fNADCPreSho ;                // number of channels in Pre Shower ADC

  ClassDef(AliEMCALDigitizer,1)  // description 

};


#endif // AliEMCALDigitizer_H
