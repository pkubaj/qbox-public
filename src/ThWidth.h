////////////////////////////////////////////////////////////////////////////////
//
// ThWidth.h
//
////////////////////////////////////////////////////////////////////////////////
// $Id: ThWidth.h,v 1.1 2004-03-11 21:58:10 fgygi Exp $

#ifndef THWIDTH_H
#define THWIDTH_H

#include<iostream>
#include<iomanip>
#include<sstream>
#include<stdlib.h>

#include "Sample.h"

class ThWidth : public Var
{
  Sample *s;

  public:

  char *name ( void ) const { return "th_width"; };

  int set ( int argc, char **argv )
  {
    if ( argc != 2 )
    {
      if ( ui->onpe0() )
      cout << " th_width takes only one value" << endl;
      return 1;
    }
    
    double v = atof(argv[1]);
    if ( v <= 0.0 )
    {
      if ( ui->onpe0() )
        cout << " th_width must be positive" << endl;
      return 1;
    }

    s->ctrl.th_width = v;
    return 0;
  }

  string print (void) const
  {
     ostringstream st;
     st.setf(ios::left,ios::adjustfield);
     st << setw(10) << name() << " = ";
     st.setf(ios::right,ios::adjustfield);
     st << setw(10) << s->ctrl.th_width;
     return st.str();
  }

  ThWidth(Sample *sample) : s(sample) { s->ctrl.th_width = 100.0; }
};
#endif