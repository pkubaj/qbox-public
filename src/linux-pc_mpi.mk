#-------------------------------------------------------------------------------
#
#  linux-pc_mpi.mk
#
#-------------------------------------------------------------------------------
# $Id: linux-pc_mpi.mk,v 1.5 2003-06-04 17:45:39 fgygi Exp $
#
 PLT=LINUX
#-------------------------------------------------------------------------------
 GCCDIR=/usr/apps/gcc/3.1
 MPIDIR=/usr/apps/mpich/1.2.4
 XERCESCDIR=/home/fgygi/software/xml/xerces-c-${PLT}

 CXX=$(GCCDIR)/bin/g++
 LD=$(CXX)

 FFTWDIR=$(HOME)/fftw/fftw-2.1.3/fftw
 BLASDIR=/usr/lib
 
 INCLUDE = -I$(MPIDIR)/include -I$(FFTWDIR) -I$(XERCESCDIR)/include
 
 CXXFLAGS= -O3 -DUSE_MPI -DSCALAPACK -DADD_ -D$(PLT) $(INCLUDE) $(DFLAGS) \
           -DAPP_NO_THREADS -DXML_USE_NO_THREADS

 LIBPATH = -L$(GCCDIR)/lib -L$(FFTWDIR) -L/usr/X11R6/lib \
           -L$(MPIDIR)/lib -L $(BLASDIR) -L$(XERCESCDIR)/lib
  
 LIBS =  $(PLIBS) -lfftw -llapack -lblas -lm -lg2c -lmpich -lpmpich -lmpich \
         -lxerces-c
 
 LDFLAGS = $(LIBPATH) $(LIBS) 

 # Blacs libraries
 BLACSDBGLVL   = 0
 BLACSdir      = /home/casc/repository/fpmd/software/BLACS/LIB
 BLACSFINIT    = $(BLACSdir)/blacsF77init_MPI-$(PLT)-$(BLACSDBGLVL).a
 BLACSCINIT    = $(BLACSdir)/blacsCinit_MPI-$(PLT)-$(BLACSDBGLVL).a
 BLACSLIB      = $(BLACSdir)/blacs_MPI-$(PLT)-$(BLACSDBGLVL).a

 CBLACSLIB     = $(BLACSCINIT) $(BLACSLIB) $(BLACSCINIT)
 FBLACSLIB     = $(BLACSFINIT) $(BLACSLIB) $(BLACSFINIT)

 # Scalapack libraries
 SCALAPACK_DIR = /home/casc/repository/fpmd/lib
 PBLASLIB      = $(SCALAPACK_DIR)/pblas_$(PLT).a
 SCALAPACKLIB  = $(SCALAPACK_DIR)/scalapack_$(PLT).a
 TOOLSLIB      = $(SCALAPACK_DIR)/tools_$(PLT).a
 REDISTLIB     = $(SCALAPACK_DIR)/redist_$(PLT).a

 LAPACKLIB = -llapack
 BLASLIB = -lblas

 # Parallel libraries
 PLIBS = $(SCALAPACKLIB) $(PBLASLIB) $(TOOLSLIB) $(REDISTLIB) $(CBLACSLIB)

#-------------------------------------------------------------------------------
