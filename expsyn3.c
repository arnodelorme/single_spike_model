/* Created by Language version: 5.4  of 2001/8/17 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 
#include "md1redef.h"
#include "section.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#define exp hoc_Exp
extern double hoc_Exp();
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define delta_t dt
#define tau _p[0]
#define e _p[1]
#define i _p[2]
#define g _p[3]
#define Dg _p[4]
#define _g _p[5]
#define _nd_area  *_ppvar[0].pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double dt;
 extern double t;
 /* declaration of user functions */
 static int _mechtype;
extern int nrn_get_mechtype();
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(_vptr) void* _vptr; { destroy_point_process(_vptr);}
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 static _hoc_setdata(_vptr) void* _vptr; { Prop* _prop;
 _prop = ((Point_process*)_vptr)->prop;
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 0,0
};
 static struct Member_func {
	char* _name; double (*_member)();} _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "tau", 1e-09, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tau", "ms",
 "e", "mV",
 "g", "uS",
 "i", "nA",
 0,0
};
 static double g0 = 0;
 static double t0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static nrn_alloc(), nrn_init(), nrn_state();
 static nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
extern int nrn_cvode_;
 
#define _cvode_ieq _ppvar[2]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "5.4",
"ExpSyn3",
 "tau",
 "e",
 0,
 "i",
 0,
 "g",
 0,
 0};
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = (double *)ecalloc(6, sizeof(double));
 	/*initialize range parameters*/
 	tau = 0.1;
 	e = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 6;
  if (!nrn_point_prop_) {
 	_ppvar = (Datum *)ecalloc(3, sizeof(Datum));
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static _net_receive();
 typedef (*_Pfrv)();
 extern _Pfrv* pnt_receive;
 extern short* pnt_receive_size;
 _expsyn3_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func,
	 _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ExpSyn3 /home/arno/public_html/neuronfiles/expsyn3.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(), _ode_matsol1();
 extern int state_discon_flag_;
 static int _slist1[1], _dlist1[1];
 static int state();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   Dg = - g / tau ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 Dg = Dg  / (1. - dt*( ( - 1.0 ) / tau )) ;
}
 /*END CVODE*/
 static int state () {_reset=0;
 {
    g = g + (1. - exp(dt*(( - 1.0 ) / tau)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau ) - g) ;
   }
  return 0;
}
 
static _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{_p = _pnt->prop->param; _ppvar = _pnt->prop->dparam;
 {
   state_discontinuity ( _cvode_ieq + 0, & g , g + _args[0] ) ;
   } }
 
static int _ode_count(_type) int _type;{ return 1;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = _nd->_v;
  _ode_spec1();
 }
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; {
	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = _nd->_v;
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = t0;
{
  g = g0;
 {
   g = 0.0 ;
   }
  _sav_indep = t; t = _save;

}
}

static nrn_init(_nd, _pp, _ppd) Node *_nd; double *_pp; Datum* _ppd; {
 double _v;
 _p = _pp; _ppvar = _ppd;
 _v = _nd->_v;
 v = _v;
 initmodel();
}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   i = g * e ;
   }
 _current += i;

} return _current;
}

static nrn_cur(_nd, _pp, _ppd) Node *_nd;double *_pp; Datum* _ppd;{
double _rhs, _v;
 _p = _pp; _ppvar = _ppd;
 _v = _nd->_v;
 _g = _nrn_current(_v + .001);
 	{ state_discon_flag_ = 1; _rhs = _nrn_current(_v); state_discon_flag_ = 0;
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
 NODERHS(_nd) -= _rhs;
 
}

static nrn_jacob(_nd, _pp, _ppd) Node *_nd;double *_pp; Datum* _ppd;{
 _p = _pp;
 NODED(_nd) += _g;
 
}

static nrn_state(_nd, _pp, _ppd) Node *_nd; double *_pp; Datum* _ppd; {
 double _break, _save;
 double _v;
 _p = _pp; _ppvar = _ppd;
 _v = _nd->_v;
 _break = t + .5*dt; _save = t; delta_t = dt;
 v=_v;
{
 { {
 for (; t < _break; t += delta_t) {
 error =  state();
 if(error){fprintf(stderr,"at line 32 in file expsyn3.mod:\n	SOLVE state METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }
}
}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(g) - _p;  _dlist1[0] = &(Dg) - _p;
_first = 0;
}
