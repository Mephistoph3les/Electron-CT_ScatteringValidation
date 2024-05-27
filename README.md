# Electron-CT_ScatteringValidation

Description
We are developing an imaging technique that utilizes an electron beam and it's multiple scattering in materials to reconstruct material budget and convert it to a 2D or 3D image similar to how it is done in an X-ray Computer Tomography (CT) image.
For this imaging to be as precise as possible we have to calibrate the multiple scattering beam broadening with different materials to get a translation of beam width broadening to material budget.
We also make heavy use of simulations with allpix-squared and want to compare different geant4 multiple scattering models within the allpix-squared framework to data taken from a testbeam environment.

Potential use
In medical treatments electron beams are already used for cancer treatment, but the localisation of tumors is still done with regular CT's or MRI's. The problem is that one has to make a coordinate transformation of the CT/MRI coordinates to the electron beam coordinate system, which is complex and have potential for errors.
Also the contraptions for that are really big and expensive.
With a method of electron beam imaging it could be possible to first scan a patient and then treat the tumor with the same machinery which save a tremendous amount of cost.
That technique could also be used in the industrial field for cheap imaging of the inside of materials.

Support
For questions or suggestions don't hesitate to contact me via kdojan@desy.de

Roadmap
A detailled overview of advantages and disadvantages of different geant4 multiple scattering models will at some point be available here for public use

Authors and acknowledgment
Paul Schuetze, Simon Spannagel, Hakan Wennloef, Malinda De Silva

Project status
Analysis of Testbeam data at ARES is rn the top priority. In the future there will be more on simulations of multiple scattering with different geant4 models to compare with testbeam results.
