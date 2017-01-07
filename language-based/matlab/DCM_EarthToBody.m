close all; clear; clc;

syms phi theta psi;

rz = [
  cos(psi) sin(psi) 0;
  -sin(psi) cos(psi) 0;
  0 0 1; ];
ry = [
  cos(theta) 0 -sin(theta);
  0 1 0;
  sin(theta) 0 cos(theta); ];
rx = [
  1 0 0;
  0 cos(phi) sin(phi) ;
  0 -sin(phi) cos(phi); ];
  

rz*ry*rx
rx*ry*rz