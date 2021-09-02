The instructions below are highly outdated. However, the model
might still run in recent versions of Neuron.

How to run the simulations
--------------------------
1) compile the Neuron software (www.neuron.yale.edu)
2) convert MOD files to C using "nrn/i686/bin/nocmodl", 
	nocmodl expsyn3.mod	
3) compile the MOD files "using nrn/i686/bin/nrnivmodl"
	nrnivmodl
    this will create the file "i686/special"
4) type "runneuron" to start neuron and load the basic_model.hoc
   Neuron simulation file. To use a different model, edit
   the cp line in "runneuron". If you are using windows or Mac
   you must perform the copy manually.
5) under neuron type mainRun()
   the program will
	- scan different level of inhibition
    - for each level of inhibition, optimize excitatory synaptic
      weights so the neuron discharge over 60 degree range of
      orientation at 100% contrast
    - once the optimization above is finished, test response at 
      different levels of contrast
   Neuron's plot while the program is running
    - top: different currents
    - middle: total inhibitory conductance (red), excitatory (green)
    - bottom: cortical neuron's potential
6) outputs text files
    "foutime1" without inhibition. The text file contains latency of
               discharge for different contrast (columns) at different
               orientations (rows). 
    "foutime2" first level of inhibition, same format as "foutime1"
    "foutime3" second level of inhibition, same format as "foutime1"
    ...

Files in archive
----------------
* runneuron: run Neuron and import simulation file (edit file to change of simulation file)
* expSyn3.mod: additive synapse model
* init.hoc: Neuron initialization file
* start3.hoc: Neuron graphical initialization file
* vectX folders: neuronal discharge of LGN cells. vect1N contains  discharges of LGN cells at 100% contrast (each file representing a different orienation), vect2N at 50%, vect4N at 25% ...)
* basic_model.hoc: original model
* additive_synapses__model.hoc: same as original with additive synapses
* multiple_spikes_model.hoc: same as original with multiple spikes
* decreased_inhib_model.hoc: same as original with some inhibitory connections randomly suppressed

Publication
-----------
Arnaud Delorme (2003) [Early Cortical Orientation Selectivity: How Fast Inhibition Decodes the Order of Spike Latencies](https://www.researchgate.net/publication/9008719_Early_Cortical_Orientation_Selectivity_How_Fast_Inhibition_Decodes_the_Order_of_Spike_Latencies
). Journal of Computational Neuroscience 15(3):357-65

Notes
-----
if you X-window server crashes when starting the model
update your version of Neuron (Michael Hines, the developper
of Neuron, specifically corrected this problem using my files).
note that the model "decreased_inhib_model.hoc" runs fine even 
under old versions of Neurons. 

Arnaud Delorme, arnodelorme at gmail.com, September 25, 2003
