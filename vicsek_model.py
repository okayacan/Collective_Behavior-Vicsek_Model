#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 11 09:54:53 2022

@author: okayacan
"""

import matplotlib.pyplot as plt
import numpy as np

"""
Simulation code --- Viscek model for particles.

Reference:
Tamás Vicsek, András Czirók, Eshel Ben-Jacob, Inon Cohen, and Ofer Shochet,
"Novel Type of Phase Transition in a System of Self-Driven Particles",
Phys. Rev. Lett. 75, 1226.
"""

def main():
    
	
	# Parameters used in Vicsek model:
	v0           = 1.0      # velocity
	eta          = 0.5      # random fluctuation in angle (in radians)
	L            = 10       # size of box
	R            = 1        # interaction radius
	tstep        = 0.2      # time step
	tmax         = 200      # number of time steps
	N            = 500      # number of birds
	plotRealTime = True
	
    
	# Initial configuration
	np.random.seed(10)      # set seed for generating random number

	# Particle positions are specified at random.
	x = np.random.rand(N,1)*L
	y = np.random.rand(N,1)*L
	
	# Particle velocities are specified at random.
	theta = 2 * np.pi * np.random.rand(N,1)
	vx = v0 * np.cos(theta)
	vy = v0 * np.sin(theta)
	
	# Preparation of figures...
	fig = plt.figure(figsize=(4,4), dpi=80)
	ax = plt.gca()
	
    
	# Monte Carlo Steps begin here:
	for i in range(tmax):

		# move
		x += vx*tstep
		y += vy*tstep
		
		# Periodic Boundary Conditions applies.
		x = x % L
		y = y % L
		
		# Evaluation of mean angle of neighbors within Rd
		mean_theta = theta
		for b in range(N):
			neighbors = (x-x[b])**2+(y-y[b])**2 < R**2 # neighbors considered only within R
			sx = np.sum(np.cos(theta[neighbors])) # summation of cosines...
			sy = np.sum(np.sin(theta[neighbors])) # summation of sinuses...
			mean_theta[b] = np.arctan2(sy, sx) # mean angle...
			
		# Random Perturbation are added to angles.
		theta = mean_theta + eta*(np.random.rand(N,1)-0.5)
		
		# Updating velocities.
		vx = v0 * np.cos(theta)
		vy = v0 * np.sin(theta)
		
		# Plotting positions and velocities in real time.
		if plotRealTime or (i == tmax-1):
			plt.cla()
			plt.quiver(x,y,vx,vy)
			ax.set(xlim=(0, L), ylim=(0, L))
			ax.set_aspect('equal')	
			ax.get_xaxis().set_visible(False)
			ax.get_yaxis().set_visible(False)
			plt.pause(0.001)
				
    
	# Saving figures as png files...
	plt.savefig('birds.png',dpi=240)
	plt.show()
	    
	return 0



if __name__== "__main__":
  main()