////////////////////////////////////////////////////////////////////////////////
//
// Species.h:
//
////////////////////////////////////////////////////////////////////////////////
// $Id: Species.h,v 1.4 2003-05-16 16:14:00 fgygi Exp $

#ifndef SPECIES_H
#define SPECIES_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
#include "Context.h"

class Species
{
  private:
  
  const Context& ctxt_;
  int nlm_;             // number of non-local projectors: 
  int ndft_;
  
  vector<vector<double> > vps_spl_, phi_spl_;
  vector<double>          gspl_, vlocg_, vlocg_spl;
  vector<vector<double> > vnlg_, vnlg_spl;
  vector<double> wsg_;  // wsg_[l] Kleinman-Bylander weight 1/<phi|delta_V|phi>
  
  vector<double> rps_;  // radial linear mesh (same for all l)
  
  string name_;         // name used to refer to species in current application
  string uri_;          // uri of the resource defining the pseudopotential

  string symbol_;
  int atomic_number_;
  double mass_;        // mass in a.m.u (Carbon = 12.0)
  
  string description_; // description of the pseudopotential
  int zval_;           // valence charge
  int lmax_;           // largest angular momentum
  int llocal_;         // angular momentum taken as local
  int nquad_;          // number of semi-local quadrature points
  double rquad_;       // end of semi-local quadrature interval
  double deltar_;      // mesh spacing for potentials and wavefunctions
  vector<vector<double> > vps_;  // potentials for each l
  vector<vector<double> > phi_;  // atomic wavefunctions for each l
  double rcps_;        // cutoff radius of gaussian pseudocharge
  
  public:

  Species(const Context& ctxt, string name);
  
  const Context& context(void) const { return ctxt_; }
  const string& name(void) const { return name_; }
  const string& symbol(void) const { return symbol_; }
  const string& description(void) const { return description_; }
  const string& uri(void) const { return uri_; }
  int atomic_number(void) const { return atomic_number_; }
  int zval(void) const { return zval_; }
  double mass(void) const { return mass_; }
  int lmax(void) const { return lmax_; }
  int llocal(void) const { return llocal_; }
  int nquad(void) const { return nquad_; }
  double rquad(void) const { return rquad_; }
  double deltar(void) const { return deltar_; }
  double rcps(void) const { return rcps_; }

  // number of non-local projectors sum_(l!=llocal) (2*l+1)
  int nlm(void) { return nlm_; }
  
  bool non_local(void) { return lmax_ > 0; };
  double eself(void)
  { return zval_ * zval_ / ( sqrt ( 2.0 * M_PI ) * rcps_ ); };

  void vpsr(int l, double r, double &v);               // Vps(l,r) in r space
  void dvpsr(int l, double r, double &v, double &dv);  // Vps and dVps/dr 
  void vlocg(double q, double &v);                     // Vloc(g)
  void dvlocg(double q, double &v, double &dv);        // Vloc(g) and dVloc/dg
  void vnlg(int l, double q, double &v);               // Vnl(l,g)
  void dvnlg(int l, double q, double &v, double &dv);  // Vnl(l,g) and dVnl/dg
  double rhopsg(double q);        // pseudocharge in g space
  double wsg(int l) { return wsg_[l]; };
  double rcut_loc(double epsilon); // radius beyond which potential is local
  
  const vector<vector<double> >& vps(void) const { return vps_; }
  const vector<vector<double> >& phi(void) const { return phi_; }
  
  bool initialize(double rcps);
  void info(ostream& os);
  
  friend class SpeciesReader;
  friend class SpeciesHandler;
  
};
ostream& operator << ( ostream &os, Species &a );
class SpeciesInitException
{
  public:
  string msg;
  SpeciesInitException(string s) : msg(s) {}
};
#endif
