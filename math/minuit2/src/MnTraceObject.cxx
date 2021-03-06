// @(#)root/minuit2:$Id$
// Author:  L. Moneta 2012

/**********************************************************************
 *                                                                    *
 * Copyright (c) 2012 LCG ROOT Math team,  CERN/PH-SFT                *
 *                                                                    *
 **********************************************************************/

#include "Minuit2/MnTraceObject.h"
#include "Minuit2/MnPrint.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MinimumState.h"
#include <iomanip>

namespace ROOT {

   namespace Minuit2 {

      void MnTraceObject::operator() (int iter, const MinimumState & state) {

         MnPrint::PrintState(std::cout, state, "iteration  #  ",iter);
         if (!fUserState) return;

         // print also parameters and derivatives
         std::cout << "\t" << std::setw(12) << "  " << "  "
                   << std::setw(12)  << " ext value " << "  "
                   << std::setw(12)  << " int value " << "  "
                   << std::setw(12)  << " gradient  " << std::endl;
         int firstPar = 0;
         int lastPar =  state.Vec().size();
         if (fParNumber >= 0 && fParNumber < lastPar) {
            firstPar = fParNumber;
            lastPar = fParNumber+1;
         }
         for (int ipar = firstPar; ipar <lastPar; ++ipar) {
               int epar = fUserState->Trafo().ExtOfInt(ipar);
               double eval = fUserState->Trafo().Int2ext(ipar, state.Vec()(ipar) );
               std::cout << "\t" << std::setw(12) << fUserState->Name(epar) << "  "
                         << std::setw(12) << eval << "  "
                         << std::setw(12) << state.Vec()(ipar)  << "  "
                         << std::setw(12) << state.Gradient().Vec()(ipar) << std::endl;
         }
      }

   }  // namespace Minuit2

}  // namespace ROOT

