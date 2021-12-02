import numpy as np
from scipy import interpolate


events = np.loadtxt('output/genericMoveTest_Coincidences.dat', usecols=(0, 1, 2, 3, 4, 5, 6))


detector_sim = events[:, (3, 4, 5, 6)]
source_sim = events[:, (3, 0, 1, 2)]

source_real = np.loadtxt('data/moveSource.placements', skiprows=8, usecols=(0, 5, 6, 7))
detector_real = np.loadtxt('data/moveDetector.placements', skiprows=8, usecols=(0, 5, 6, 7))

source_bools = np.zeros(len(source_sim[:, 0]))
detector_bools = np.zeros(len(detector_sim[:, 0]))

for i in range(len(source_sim[:, 0])):

    source_index = np.where(source_real[:, 0] <= source_sim[i, 0])
    
    if source_sim[i, 3]-source_real[source_index[0][-1], 3] > 1*10**-10:
    
        source_bools[i] = False
    
    else:

        source_bools[i] = True

    
    detector_index = np.where(detector_real[:, 0] <= detector_sim[i, 0])


    if np.abs(detector_sim[i, 1])-np.abs(detector_real[detector_index[0][-1], 1]+87) >= 16:

        detector_bools[i] = False
    
    else:

        detector_bools[i] = True
  

print('Source Movement Test Pass: '+str(np.all(source_bools==True)))
print('Detector Movement Test Pass: '+str(np.all(detector_bools==True)))

