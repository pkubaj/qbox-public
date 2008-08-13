////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008 The Regents of the University of California
//
// This file is part of Qbox
//
// Qbox is distributed under the terms of the GNU General Public License 
// as published by the Free Software Foundation, either version 2 of 
// the License, or (at your option) any later version.
// See the file COPYING in the root directory of this distribution
// or <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////
//
// AtomsDyn.h
//
////////////////////////////////////////////////////////////////////////////////
// $Id: AtomsDyn.h,v 1.5 2008-08-13 06:39:42 fgygi Exp $

#ifndef ATOMSDYN_H
#define ATOMSDYN_H

#include<iostream>
#include<iomanip>
#include<sstream>
#include<stdlib.h>

#include "Sample.h"

class AtomsDyn : public Var
{
  Sample *s;

  public:

  char *name ( void ) const { return "atoms_dyn"; };

  int set ( int argc, char **argv )
  {
    if ( argc != 2 )
    {
      if ( ui->onpe0() )
      cout << " atoms_dyn takes only one value" << endl;
      return 1;
    }

    string v = argv[1];
    if ( !( v == "LOCKED" || v == "SD" || v == "SDA" || v == "CG" || v == "MD" ) )
    {
      if ( ui->onpe0() )
        cout << " atoms_dyn must be LOCKED or SD or SDA or CG or MD" << endl;
      return 1;
    }

    s->ctrl.atoms_dyn = v;

    return 0;
  }

  string print (void) const
  {
     ostringstream st;
     st.setf(ios::left,ios::adjustfield);
     st << setw(10) << name() << " = ";
     st.setf(ios::right,ios::adjustfield);
     st << setw(10) << s->ctrl.atoms_dyn;
     return st.str();
  }

  AtomsDyn(Sample *sample) : s(sample) { s->ctrl.atoms_dyn = "LOCKED"; };
};
#endif
