////////////////////////////////////////////////////////////////////////////////
//
// ConstraintSet.h
//
////////////////////////////////////////////////////////////////////////////////
// $Id: ConstraintSet.h,v 1.2 2005-09-16 23:08:11 fgygi Exp $

#ifndef CONSTRAINTSET_H
#define CONSTRAINTSET_H

#include <vector>
#include <string>
using namespace std;

class Atom;
class AtomSet;
class Constraint;
class Context;

class ConstraintSet
{
  private:
  
  const Context& ctxt_;
  vector<Constraint *> constraint_list;
  
  public:

  ConstraintSet(const Context& ctxt) : ctxt_(ctxt) {}
  bool define_constraint(AtomSet &atoms, int argc, char **argv);
  bool set_constraint(int argc, char **argv);
  bool delete_constraint(int argc, char **argv);
  void list_constraints(ostream &os);
  int size(void) const { return constraint_list.size(); }
  void enforce(AtomSet& atoms);
  void enforce_r(const vector<vector<double> > &r0,
                 vector<vector<double> > &rp);
  void enforce_v(const vector<vector<double> > &r0,
                 vector<vector<double> > &v0);
  void compute_forces(const vector<vector<double> > &r0,
                     const vector<vector<double> > &f);
  void update_constraints(double dt);
  void setup(AtomSet& atoms);
};
#endif