////////////////////////////////////////////////////////////////////////////////
//
// SDCellStepper.C
//
////////////////////////////////////////////////////////////////////////////////
// $Id: SDCellStepper.C,v 1.1 2004-03-11 21:58:10 fgygi Exp $

#include "SDCellStepper.h"

////////////////////////////////////////////////////////////////////////////////
void SDCellStepper::compute_new_cell(const valarray<double>& sigma)
{
  cout << " SDCellStepper::compute_new_cell" << endl;
  // multiply stress by A^T to get dE/da_ij
  valarray<double> deda(9);
  
  const UnitCell& cell = s_.wf.cell();
  const double cell_mass = s_.ctrl.cell_mass;
  
  if ( cell_mass <= 0.0 )
  {
    if ( s_.ctxt_.onpe0() )
    {
      cout << "<!-- SDCellStepper::compute_new_cell: cell mass is zero\n"
           << "     cannot update cell -->" << endl;
      return;
    }
  }
  
  // deda = - omega * sigma * A^-T
  cell.compute_deda(sigma,deda);
  
  for ( int i = 0; i < 9; i++ )
    cout << " deda[" << i << "] = " << deda[i] << endl;
  
  string cell_lock = s_.ctrl.cell_lock;
  if ( cell_lock != "OFF" )
  {
    // constraints on the cell derivatives
    if ( cell_lock.find("A") != string::npos )
    {
      // vector A is locked
      deda[0] = deda[1] = deda[2] = 0.0;
    }
    if ( cell_lock.find("B") != string::npos )
    {
      // vector B is locked
      deda[3] = deda[4] = deda[5] = 0.0;
    }
    if ( cell_lock.find("C") != string::npos )
    {
      // vector C is locked
      deda[6] = deda[7] = deda[8] = 0.0;
    }
    cout << " cell derivatives after constraints" << endl;
    for ( int i = 0; i < 9; i++ )
      cout << " deda[" << i << "] = " << deda[i] << endl;
  }
  
  const double dt = s_.ctrl.dt;
  const double dt2bym = dt*dt/cell_mass;
  
  // cellp = cell - deda * dt^2 / cell_mass
  D3vector a0p = cell.a(0) - dt2bym * D3vector(deda[0],deda[1],deda[2]);
  D3vector a1p = cell.a(1) - dt2bym * D3vector(deda[3],deda[4],deda[5]);
  D3vector a2p = cell.a(2) - dt2bym * D3vector(deda[6],deda[7],deda[8]);
  
  cellp = UnitCell(a0p,a1p,a2p);
  
  cout << " SDCellStepper::compute_new_cell: cellp: " << endl;
  cout << cellp;
  
}

////////////////////////////////////////////////////////////////////////////////
void SDCellStepper::update_cell(void)
{
  const UnitCell& cell = s_.wf.cell();
  
  // rescale atomic positions in AtomSet
  
  // r_new = A_new A_old^-1 r_old
  vector<vector<double> > r;
  s_.atoms.get_positions(r);
  const double* const ainv = cell.amat_inv();
  const double* const ap = cellp.amat();
  
  double tau[3];
  for ( int is = 0; is < r.size(); is++ )
  {
    // transform r to tau: multiply by A^-1
    const int nais = r[is].size()/3;
    for ( int ia = 0; ia < nais; ia++ )
    {
      // multiply r[is][ia] by A_old^-1, result in tau
      cell.vecmult3x3(cell.amat_inv(),&r[is][3*ia],&tau[0]);
      // multiply tau by A_new, result in r[is][3*ia]
      cellp.vecmult3x3(cellp.amat(),&tau[0],&r[is][3*ia]);
    }
  }
  s_.atoms.set_positions(r);
  
  // resize wavefunction and basis sets
  
  cout << " SDCellStepper::update_cell" << endl;
  s_.wf.resize(cellp,s_.wf.refcell(),s_.wf.ecut());
  if ( s_.wfv != 0 )
  {
    s_.wfv->resize(cellp,s_.wf.refcell(),s_.wf.ecut());
    // s_.wfv->clear();
  }
}